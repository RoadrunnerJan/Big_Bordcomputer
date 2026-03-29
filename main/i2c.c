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

#define VOLTAGE_MIN_THRESHOLD 3.0f 

#define BEL_MAX_PLAUSIBLE 16.0f  // Alles darüber ist "Offener Pin / Rauschen"
#define BEL_MIN_PLAUSIBLE 0.8f   // Mindestspannung für "Licht an" (Schutz gegen Kriechströme)
#define BOARD_MIN_PLAUSIBLE 6.0f 


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
    // Config Register zusammenbauen:
    // OS=1 (Start), MUX=Channel, PGA=pga_setting, MODE=Single-Shot, DR=128SPS, COMP_QUE=Disable
    uint16_t config = 0x8003 | ((0x04 | channel) << 12) | (pga_setting << 9);
    uint8_t tx_buf[3] = { 0x01, (uint8_t)(config >> 8), (uint8_t)(config & 0xFF) };

    // 1. Konfiguration senden
    i2c_master_transmit(dev, tx_buf, 3, -1);
    
    // 2. Wandlungszeit abwarten (ca. 8-10ms bei 128 SPS)
    vTaskDelay(pdMS_TO_TICKS(10));

    // 3. Pointer auf Conversion Register (0x00) setzen und 2 Bytes lesen
    uint8_t reg_addr = 0x00;
    uint8_t rx_buf[2];
    i2c_master_transmit_receive(dev, &reg_addr, 1, rx_buf, 2, -1);

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
    // 1. Hardware-Limit Check (Offener Pin am ADS1115 liefert oft 0x7FFF)
    if (raw >= 0x7F00) { 
        filtered_v_board = 0;
        return 0.0f;
    }

    float v_adc = (raw * LSB_2048) / 1000.0f;
    float real_v = v_adc * ((10.0f + 1.5f) / 1.5f);
    
    // 2. Rausch-Check
    if (real_v < BOARD_MIN_PLAUSIBLE) {
        filtered_v_board = 0;
        return 0.0f;
    }

    // 3. Filter
    if (filtered_v_board == 0) filtered_v_board = real_v;
    filtered_v_board = (real_v * FILTER_ALPHA) + (filtered_v_board * (1.0f - FILTER_ALPHA));
    return filtered_v_board;
}
float get_v_bel_safe(int16_t raw) {
    // WICHTIG: PGA muss im ads1115_read_raw Aufruf 0x01 sein!
    float v_adc = (raw * LSB_4096) / 1000.0f; 
    float real_v = v_adc * ((10.0f + 2.2f) / 2.2f); // Teiler 10k/2.2k
    
    // 1. Rausch-Unterdrückung (Hysterese)
    // Wenn der Pin offen ist, springt er auf ~18V -> wir setzen auf 0
    if (real_v > BEL_MAX_PLAUSIBLE || real_v < BEL_MIN_PLAUSIBLE) {
        filtered_v_bel = 0; 
        return 0.0f;
    }
    
    // 2. Filter-Start-Logik
    // Verhindert, dass der Filter von 0 langsam hochkriecht, wenn du einschaltest
    if (filtered_v_bel == 0) {
        filtered_v_bel = real_v; 
    } else {
        // Glättung im Betrieb
        filtered_v_bel = (real_v * FILTER_ALPHA) + (filtered_v_bel * (1.0f - FILTER_ALPHA));
    }
    
    return filtered_v_bel;
}
// --- Sensor Messungen mit Plausibilitäts-Check ---

float get_oil_temp_filtered(int16_t raw) {
    float r = raw_to_res_safe(raw, 680.0f);
    if (r < 0) return -99.0f; // Fehler (Offen)
    
    float temp = interpolate_temp(r);
    filtered_oil_temp = (temp * FILTER_ALPHA) + (filtered_oil_temp * (1.0f - FILTER_ALPHA));
    return filtered_oil_temp;
}

float get_oil_press_filtered(int16_t raw) {
    float r = raw_to_res_safe(raw, 680.0f);
    if (r < 0 || r > 250.0f) return -1.0f; // Fehler oder unplausibel hoch
    
    float press = (r - 10.0f) * (10.0f / (184.0f - 10.0f));
    if (press < 0) press = 0;
    
    filtered_oil_press = (press * FILTER_ALPHA) + (filtered_oil_press * (1.0f - FILTER_ALPHA));
    return filtered_oil_press;
}

float get_outside_temp_safe(int16_t raw) {
    // 1. Widerstand berechnen (PGA 0x01 = 4.096V)
    float r = raw_to_res_safe(raw, 4700.0f); 

    // 2. Plausibilitäts-Check (Sensor abgesteckt oder Kurzschluss)
    if (r < 0 || r > 150000.0f) {
        filtered_outside_temp = 20.0f; // Reset auf Standardwert für den nächsten Start
        return -99.0f; // Fehlercode für LVGL
    }

    // 3. Temperatur aus Tabelle ermitteln
    float temp_c = interpolate_bmw_temp(r);

    // 4. Filter anwenden
    if (filtered_outside_temp == 20.0f && temp_c != -99.0f) {
        filtered_outside_temp = temp_c; // Schneller Startwert
    } else {
        filtered_outside_temp = (temp_c * FILTER_ALPHA) + (filtered_outside_temp * (1.0f - FILTER_ALPHA));
    }

    return filtered_outside_temp;
}


void adc_task(void *pvParameters) {
    while(1) { // --- ADS1 (0x48) auslesen ---
    
    int16_t raw_0 = read_ads1115(ads1_handle, 0, 0x02); // Board
    int16_t raw_1 = read_ads1115(ads1_handle, 1, 0x01); // Bel
    int16_t raw_2 = read_ads1115(ads1_handle, 2, 0x01); // Temp
    int16_t raw_3 = read_ads1115(ads1_handle, 3, 0x01); // Druck
    int16_t raw_4 = read_ads1115(ads2_handle, 0, 0x01);

    // 2. Berechnen mit Schutz und Filter
    float v_board = get_v_board_safe(raw_0);
    float v_bel   = get_v_bel_safe(raw_1);
    float oil_t   = get_oil_temp_filtered(raw_2);
    float oil_p   = get_oil_press_filtered(raw_3);
    float outside_t = get_outside_temp_safe(raw_4);


    // 3. Ausgabe/Logik
    printf("--- SENSOR UPDATE ---\n");
    
    if (v_board > 0) printf("Board: %.2f V\n", v_board);
    else printf("Board: NICHT ANGESCHLOSSEN\n");

    if (v_bel > 0) printf("Bel.:  %.2f V\n", v_bel);
    else printf("Bel.:  NICHT ANGESCHLOSSEN\n");

    if (oil_t > -50.0f) printf("Temp:  %.1f °C\n", oil_t);
    else printf("Temp:  FEHLER/OFFEN\n");

    if (oil_p >= 0) printf("Druck: %.2f bar\n", oil_p);
    else printf("Druck: FEHLER/OFFEN\n");   
    
    if (outside_t > -50.0f) printf("Außen: %.1f °C\n", outside_t);
    else printf("Außen: SENSOR FEHLER / OFFEN\n");

        // --- Ausgabe / LVGL Update ---
        // Hier kannst du die float-Werte direkt an deine LVGL Labels senden
        printf("BOARD: %.2fV | BEL: %.2fV | OIL: %.1fC / %.1fbar | OUT: %.1fC\n", 
            v_board, v_bel, oil_t, oil_p, outside_t);
    printf("---------------------\n");
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void start_adc_task() {
    xTaskCreate(adc_task, "adc_task", 4096, NULL, 5, NULL);
}