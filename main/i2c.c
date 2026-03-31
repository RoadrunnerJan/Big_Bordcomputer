#include "includes.h"
/*
Für Buttons internen Pull Up Widerstand verwenden


rtc modul
7-Bit Adresse: 0x68 (Standard für fast alle DS3231-Varianten).
8-Bit Adresse (Write): 0xD0 (0x68 linksgeschoben um 1 Bit mit LSB=0).
8-Bit Adresse (Read): 0xD1 (0x68 linksgeschoben um 1 Bit mit LSB=1).
*/

i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t ds3231_handle;

i2c_master_dev_handle_t ads1_handle;
i2c_master_dev_handle_t ads2_handle;

typedef struct {
    int repeat_count;
} button_state_t;

static button_state_t hour_state = {0};
static button_state_t min_state  = {0};

// ADS1115 Spannungsstufen (LSB in mV)
#define LSB_2048 0.0625f
#define LSB_4096 0.125f
typedef struct {
    float temp;
    float res;
} ntc_table_t;

const ntc_table_t oil_temp_table[] = {
    {0, 2500.0}, {10, 1500.0}, {20, 1000.0}, {30, 650.0}, {40, 430.0},
    {50, 322.0}, {60, 225.0},  {70, 155.0},  {80, 112.0}, {90, 83.0},
    {100, 62.0}, {110, 47.0},  {120, 37.0},  {130, 29.0}, {140, 23.0}, {150, 19.0}
};
#define OIL_TABLE_SIZE (sizeof(oil_temp_table) / sizeof(ntc_table_t))

#define ADC_MAX_V_VALID 3.25f 

#define FILTER_ALPHA 0.1f 

#define BEL_MAX_PLAUSIBLE 16.0f  // Alles darüber ist "Offener Pin / Rauschen"
#define BEL_MIN_PLAUSIBLE 0.8f   // Mindestspannung für "Licht an" (Schutz gegen Kriechströme)
#define BOARD_MIN_PLAUSIBLE 6.0f 

bool value_set[6] = {false, false, false, false, false, false}; // Flags für die ersten 6 Sensoren


typedef struct {
    float temp;
    float res;
} bmw_ntc_table_t;

const bmw_ntc_table_t bmw_outside_table[] = {
    {-30, 88000.0}, {-20, 52000.0}, {-10, 31500.0}, {0, 19500.0},
    {10, 12500.0},  {20, 8200.0},   {25, 6700.0},   {30, 5500.0},
    {40, 3800.0},   {50, 2600.0},   {60, 1850.0},   {70, 1300.0}
};
#define BMW_TABLE_SIZE (sizeof(bmw_outside_table) / sizeof(bmw_ntc_table_t))


// Globale Variablen für die gefilterten Werte (Initialisierung auf 0)
static float filtered_v_board = 8.0f; // Startwert, z.B. 8V
static float filtered_v_bel = 0;
static float filtered_oil_temp = 0;
static float filtered_oil_press = 0;
static float filtered_outside_temp = 0; // Startwert ca. Zimmertemperatur


void init_i2c() {
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = RTC_I2C_SCL_PIN,
        .sda_io_num = RTC_I2C_SDA_PIN,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = false
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));
    #if CHECK_I2C_DEVICES == false
        i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = RTC_DS3231_ADDR,
            .scl_speed_hz = 100000,
        };
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &ds3231_handle));

        i2c_device_config_t ads_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .scl_speed_hz = 400000, // ADS1115 schafft bis zu 400kHz
        };

        ads_cfg.device_address = ADC_ADS1115_1_ADDR;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg, &ads1_handle));

        ads_cfg.device_address = ADC_ADS1115_2_ADDR;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg, &ads2_handle));
    #else
        for (int addr = 1; addr < 127; addr++) {
            i2c_device_config_t dev_cfg = {
                .dev_addr_length = I2C_ADDR_BIT_LEN_7,
                .device_address = addr,
                .scl_speed_hz = 100000,
            };

            i2c_master_dev_handle_t tmp;
            if (i2c_master_bus_add_device(bus_handle, &dev_cfg, &tmp) == ESP_OK) {
                if (i2c_master_probe(bus_handle, addr, 100) == ESP_OK) {
                    printf("Device at 0x%02X\n", addr);
                }
                i2c_master_bus_rm_device(tmp);
            }
        }
    #endif

}

inline uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
inline uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) | (val % 10); }

void sync_rtc_to_system() {
    uint8_t data[7];
    uint8_t reg = 0x00; // Startregister (Sekunden)

    // 7 Bytes Zeitdaten lesen
    i2c_master_transmit_receive(ds3231_handle, &reg, 1, data, 7, 1000); // 1000 = Timeout

    struct tm tm = {
        .tm_sec  = bcd2dec(data[0] & 0x7F),
        .tm_min  = bcd2dec(data[1]),
        .tm_hour = bcd2dec(data[2] & 0x3F), // 24h Modus
        .tm_mday = bcd2dec(data[4]),
        .tm_mon  = bcd2dec(data[5] & 0x1F) - 1, // tm_mon ist 0-11
        .tm_year = bcd2dec(data[6]) + 100,      // tm_year ist seit 1900
    };

    // In Unix-Timestamp umwandeln
    time_t t = mktime(&tm);
    
    // Systemzeit des ESP32 setzen
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);
}

esp_err_t ds3231_set_time(struct tm *time) {
    uint8_t data[8];
    data[0] = 0x00; // Startregister Adresse (Sekunden)
    
    data[1] = dec2bcd(time->tm_sec);
    data[2] = dec2bcd(time->tm_min);
    data[3] = dec2bcd(time->tm_hour); // Bit 6 muss 0 sein für 24h Modus
    data[4] = dec2bcd(time->tm_wday + 1); // Wochentag (1-7)
    data[5] = dec2bcd(time->tm_mday);
    data[6] = dec2bcd(time->tm_mon + 1); // DS3231 nutzt 1-12
    data[7] = dec2bcd(time->tm_year % 100); // Nur die letzten zwei Stellen (z.B. 26 für 2026)

    // Sende 8 Bytes (Register-Adresse + 7 Byte Zeitdaten)
    return i2c_master_transmit(ds3231_handle, data, 8, -1);
}

// Callback wenn ein Button gedrückt wurde
static void button_event_cb(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    
    // Aktuelle ESP-Systemzeit holen
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour + 1 + 24) % 24;
        printf("Stunde erhöht: %d\n", timeinfo.tm_hour);
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min + 1 + 60) % 60;
        if (timeinfo.tm_min == 0) { 
            timeinfo.tm_hour = (timeinfo.tm_hour + 1) % 24;
            printf("Stunde erhöht wegen Minute: %d\n", timeinfo.tm_hour);
        }
        timeinfo.tm_sec = 0; // Sekunden nullen beim Stellen
        printf("Minute erhöht: %d\n", timeinfo.tm_min);
    }

    ds3231_set_time(&timeinfo);
    
    // Systemzeit synchronisieren (damit der ESP es sofort weiß)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

static void button_event_cb_back(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    
    // Aktuelle ESP-Systemzeit holen
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
        printf("Stunde verringert: %d\n", timeinfo.tm_hour);
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min - 1 + 60) % 60;
        if (timeinfo.tm_min == 59) { 
            timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
            printf("Stunde verringert wegen Minute: %d\n", timeinfo.tm_hour);
        }
        timeinfo.tm_sec = 0; // Sekunden nullen beim Stellen
        printf("Minute verringert: %d\n", timeinfo.tm_min);
    }

    // Zur RTC schreiben
    ds3231_set_time(&timeinfo);
    
    // Systemzeit synchronisieren (damit der ESP es sofort weiß)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

void init_time_buttons() {
    button_config_t cfg_hour = {
        .short_press_time = 50,
        .long_press_time = 500,
    };

    button_gpio_config_t gpio_cfg_hour = 
    {
        .gpio_num = BUTTON_CLOCK_HOUR_PIN,
        .active_level = 0,
    };
    button_handle_t btn_hour = NULL;
    iot_button_new_gpio_device(&cfg_hour, &gpio_cfg_hour, &btn_hour);

    iot_button_register_cb(btn_hour, BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_register_cb(btn_hour, BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_HOUR_PIN);

    button_config_t cfg_minute = {
        .long_press_time = 500, 
        .short_press_time = 50
    };
    button_gpio_config_t gpio_cfg_minute = 
    {
        .gpio_num = BUTTON_CLOCK_MINUTE_PIN,
        .active_level = 0,
    };
    button_handle_t btn_min = NULL;
    iot_button_new_gpio_device(&cfg_minute, &gpio_cfg_minute, &btn_min);
    iot_button_register_cb(btn_min, BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
    iot_button_register_cb(btn_min, BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_MINUTE_PIN);
}

int16_t read_ads1115(i2c_master_dev_handle_t dev, uint8_t channel, uint16_t pga_setting) {
    // Sicherstellen, dass der Channel nur 0-3 ist
    uint16_t mux = (0x04 | (channel & 0x03)) << 12; // 0x4000, 0x5000, 0x6000 oder 0x7000
    uint16_t pga = (pga_setting & 0x07) << 9;
    
    // Bit 15: OS = 1 (Start)
    // Bit 8: Mode = 1 (Single Shot)
    // Bits 7-5: Data Rate = 100 (128 SPS)
    // Bits 4-0: Standard-Werte (0x03)
    uint16_t config = 0x8000 | mux | pga | 0x0100 | 0x0080 | 0x0003;
    
    uint8_t tx_buf[3] = { 0x01, (uint8_t)(config >> 8), (uint8_t)(config & 0xFF) };

    // 1. Senden
    ESP_ERROR_CHECK(i2c_master_transmit(dev, tx_buf, 3, -1));

    // 2. Warten (128 SPS brauchen ca. 8ms, 20ms ist absolut sicher)
    vTaskDelay(pdMS_TO_TICKS(15)); 

    // 3. Conversion Register auslesen
    uint8_t reg_addr = 0x00;
    uint8_t rx_buf[2];
    ESP_ERROR_CHECK(i2c_master_transmit_receive(dev, &reg_addr, 1, rx_buf, 2, -1));

    return (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
}


// Lineare Interpolation für die Tabelle
float interpolate_temp(float r_measured) {
    if (r_measured >= oil_temp_table[0].res) return oil_temp_table[0].temp;
    if (r_measured <= oil_temp_table[OIL_TABLE_SIZE-1].res) return oil_temp_table[OIL_TABLE_SIZE-1].temp;

    for (int i = 0; i < OIL_TABLE_SIZE - 1; i++) {
        if (r_measured <= oil_temp_table[i].res && r_measured > oil_temp_table[i+1].res) {
            float r_range = oil_temp_table[i+1].res - oil_temp_table[i].res;
            float t_range = oil_temp_table[i+1].temp - oil_temp_table[i].temp;
            return oil_temp_table[i].temp + (r_measured - oil_temp_table[i].res) * (t_range / r_range);
        }
    }
    return 0;
}

float interpolate_bmw_temp(float r_measured) {
    if (r_measured >= bmw_outside_table[0].res) return bmw_outside_table[0].temp;
    if (r_measured <= bmw_outside_table[BMW_TABLE_SIZE-1].res) return bmw_outside_table[BMW_TABLE_SIZE-1].temp;

    for (int i = 0; i < BMW_TABLE_SIZE - 1; i++) {
        if (r_measured <= bmw_outside_table[i].res && r_measured > bmw_outside_table[i+1].res) {
            float r_range = bmw_outside_table[i+1].res - bmw_outside_table[i].res;
            float t_range = bmw_outside_table[i+1].temp - bmw_outside_table[i].temp;
            return bmw_outside_table[i].temp + (r_measured - bmw_outside_table[i].res) * (t_range / r_range);
        }
    }
    return -99.0f;
}

float raw_to_res_safe(int16_t raw, float r_pullup) {
    float v_adc = (raw * LSB_4096) / 1000.0f;
    
    // Check: Wenn Spannung fast 3.3V -> Sensor offen oder Kabelbruch
    if (v_adc >= ADC_MAX_V_VALID || v_adc <= 0.01f) {
        return -1.0f; // Signal für "Fehler"
    }
    return (v_adc * r_pullup) / (3.3f - v_adc);
}

float get_v_board_safe(int16_t raw) {

    float v_adc = (raw * LSB_2048) / 1000.0f;
    float real_v = v_adc * ((10.0f + 1.5f) / 1.5f);

    if (value_set[0] == false) {
        filtered_v_board = real_v; 
        value_set[0] = true;
    }
    filtered_v_board = (real_v * FILTER_ALPHA) + (filtered_v_board * (1.0f - FILTER_ALPHA));
    return filtered_v_board;
}

float get_v_bel_safe(int16_t raw) {
    // dies muss anders gelöst werden!


    // WICHTIG: PGA muss im ads1115_read_raw Aufruf 0x01 sein!
    float v_adc = (raw * LSB_4096) / 1000.0f; 
    float real_v = v_adc * ((10.0f + 2.2f) / 2.2f); // Teiler 10k/2.2k
    
    /*if ((real_v > BEL_MAX_PLAUSIBLE || real_v < BEL_MIN_PLAUSIBLE) && value_set[1] == false) {
        filtered_v_bel = real_v; 
        value_set[1] = true;
    }*/
    filtered_v_bel = real_v; 
    //filtered_v_bel = (real_v * FILTER_ALPHA) + (filtered_v_bel * (1.0f - FILTER_ALPHA));
    return filtered_v_bel;
}
// --- Sensor Messungen mit Plausibilitäts-Check ---

float get_oil_temp_filtered(int16_t raw) {
    float r = raw_to_res_safe(raw, 680.0f);
    if (r < 0) return -99.0f; // Fehler (Offen)
    
    float temp = interpolate_temp(r);
    if (value_set[2] == false) {
        filtered_oil_temp = temp; 
        value_set[2] = true;
    }
    filtered_oil_temp = (temp * FILTER_ALPHA) + (filtered_oil_temp * (1.0f - FILTER_ALPHA));
    return filtered_oil_temp;
}

float get_oil_press_filtered(int16_t raw) {
    float r = raw_to_res_safe(raw, 680.0f);
    if (r < 0 || r > 250.0f) return -1.0f; // Fehler oder unplausibel hoch
    
    float press = (r - 10.0f) * (10.0f / (184.0f - 10.0f));
    if (press < 0) press = 0;
    
    if (value_set[3] == false) {
        filtered_oil_press = press; 
        value_set[3] = true;
    }
    filtered_oil_press = (press * FILTER_ALPHA) + (filtered_oil_press * (1.0f - FILTER_ALPHA));
    return filtered_oil_press;
}

float get_outside_temp_safe(int16_t raw) {
    float r = raw_to_res_safe(raw, 4700.0f); 
    if (r < 0 || r > 150000.0f) {
        value_set[4] = false; 
        return -99.0f; // Fehlercode für LVGL
    }

    // 3. Temperatur aus Tabelle ermitteln
    float temp_c = interpolate_bmw_temp(r);
    if (temp_c < -30.0f) {
        temp_c = -30.0f;
    }
    if (temp_c > 70.0f) {
        temp_c = 70.0f;
    }

    // 4. Filter anwenden
    if (value_set[4] == false) {
        filtered_outside_temp = temp_c; 
        value_set[4] = true;
    } 
    filtered_outside_temp = (temp_c * FILTER_ALPHA) + (filtered_outside_temp * (1.0f - FILTER_ALPHA));
    
    return filtered_outside_temp;
}

float get_i2c_adc_volt() {
    int16_t raw = read_ads1115(ads1_handle, 0, 0x02); // Board
    float v_board = get_v_board_safe(raw);
    printf("Board Voltage: %.2f V\n", v_board);
    return v_board;
}
float get_i2c_adc_volt_bel() {
    int16_t raw = read_ads1115(ads1_handle, 1, 0x01); // Bel
    float v_bel = get_v_bel_safe(raw);
    printf("Bel Voltage: %.2f V\n", v_bel);
    return v_bel;
}
float get_i2c_adc_oil_temp() {
    int16_t raw = read_ads1115(ads1_handle, 2, 0x01); // Temp
    float oil_t = get_oil_temp_filtered(raw);
    printf("Oil Temperature: %.1f °C\n", oil_t);
    return oil_t;
}
float get_i2c_adc_oil_press() {
    int16_t raw = read_ads1115(ads1_handle, 3, 0x01); // Druck
    float oil_p = get_oil_press_filtered(raw);
    printf("Oil Pressure: %.2f bar\n", oil_p);
    return oil_p;
}
float get_i2c_adc_outside_temp() {
    int16_t raw = read_ads1115(ads2_handle, 0, 0x01); // Außentemperatur
    float outside_t = get_outside_temp_safe(raw);
    printf("Outside Temperature: %.1f °C\n", outside_t);
    return outside_t;
}