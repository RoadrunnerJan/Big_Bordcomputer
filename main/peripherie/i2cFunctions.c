#include "i2cFunctions.h"

i2c_master_bus_config_t bus_cfg = {0};
i2c_master_bus_handle_t bus_handle = NULL;
// RTC
i2c_device_config_t ds3231_cfg = {0};
i2c_master_dev_handle_t ds3231_handle = NULL;
// ADS1115
i2c_device_config_t ads_cfg[NUMBER_OF_ADS1115_DEVICES] = {0};
i2c_master_dev_handle_t ads_handle[NUMBER_OF_ADS1115_DEVICES];

// Buttons 
button_config_t cfg_time[2] = {0}; // 0 = Stunde, 1 = Minute
button_gpio_config_t gpio_cfg_time[2] = {0};
button_handle_t btn_time[2] = {0};

const ntc_table_t oil_temp_table[] = {
    {0, 2500.0}, {10, 1500.0}, {20, 1000.0}, {30, 650.0}, {40, 430.0},
    {50, 322.0}, {60, 225.0},  {70, 155.0},  {80, 112.0}, {90, 83.0},
    {100, 62.0}, {110, 47.0},  {120, 37.0},  {130, 29.0}, {140, 23.0}, {150, 19.0}
};
bool value_set[6] = {false, false, false, false, false, false}; // Flags für die ersten 6 Sensoren

const outside_ntc_table_t outside_temperature_table[] = {
    {-30, 88000.0}, {-20, 52000.0}, {-10, 31500.0}, {0, 19500.0},
    {10, 12500.0},  {20, 8200.0},   {25, 6700.0},   {30, 5500.0},
    {40, 3800.0},   {50, 2600.0},   {60, 1850.0},   {70, 1300.0}
};


// Globale Variablen für die gefilterten Werte (Initialisierung auf 0)
float filtered_v_board = 8.0f; // Startwert, z.B. 8V
float filtered_v_bel = 0;
float filtered_oil_temp = 0;
float filtered_oil_press = 0;
float filtered_outside_temp = 0; // Startwert ca. Zimmertemperatur

void init_i2c() {
    // I2C
    bus_cfg.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_cfg.i2c_port = I2C_NUM_0;
    bus_cfg.scl_io_num = RTC_I2C_SCL_PIN;
    bus_cfg.sda_io_num = RTC_I2C_SDA_PIN;
    bus_cfg.glitch_ignore_cnt = 7;
    bus_cfg.flags.enable_internal_pullup = false;

    // RTC
    ds3231_cfg.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    ds3231_cfg.device_address = RTC_DS3231_ADDR;
    ds3231_cfg.scl_speed_hz = 100000;
    for (int i = 0; i < NUMBER_OF_ADS1115_DEVICES; i++) {
        ads_cfg[i].dev_addr_length = I2C_ADDR_BIT_LEN_7;
        ads_cfg[i].scl_speed_hz = 400000; // ADS1115 schafft bis zu 400kHz
    }
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ds3231_cfg, &ds3231_handle));

    // ADS1115
    ads_cfg[0].device_address = ADC_ADS1115_1_ADDR;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg[0], &ads_handle[0]));

    #if NUMBER_OF_ADS1115_DEVICES > 1
        ads_cfg[1].device_address = ADC_ADS1115_2_ADDR;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg[1], &ads_handle[1]));
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

    cfg_time[0].short_press_time = 50;
    cfg_time[0].long_press_time = 500;
    gpio_cfg_time[0].gpio_num = BUTTON_CLOCK_HOUR_PIN;
    gpio_cfg_time[0].active_level = 0;    
    cfg_time[1].short_press_time = 50;
    cfg_time[1].long_press_time = 500;
    gpio_cfg_time[1].gpio_num = BUTTON_CLOCK_MINUTE_PIN;
    gpio_cfg_time[1].active_level = 0;

    iot_button_new_gpio_device(&cfg_time[0], &gpio_cfg_time[0], &btn_time[0]);
    iot_button_register_cb(btn_time[0], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_register_cb(btn_time[0], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_new_gpio_device(&cfg_time[1], &gpio_cfg_time[1], &btn_time[1]);
    iot_button_register_cb(btn_time[1], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
    iot_button_register_cb(btn_time[1], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_MINUTE_PIN);
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

// Lineare Interpolation für die Oil Temperature Tabelle
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

// Lineare Interpolation für die BMW Outside Temperature Tabelle
float interpolate_outside_temp(float r_measured) {
    if (r_measured >= outside_temperature_table[0].res) return outside_temperature_table[0].temp;
    if (r_measured <= outside_temperature_table[OUTSIDE_TABLE_SIZE-1].res) return outside_temperature_table[OUTSIDE_TABLE_SIZE-1].temp;

    for (int i = 0; i < OUTSIDE_TABLE_SIZE - 1; i++) {
        if (r_measured <= outside_temperature_table[i].res && r_measured > outside_temperature_table[i+1].res) {
            float r_range = outside_temperature_table[i+1].res - outside_temperature_table[i].res;
            float t_range = outside_temperature_table[i+1].temp - outside_temperature_table[i].temp;
            return outside_temperature_table[i].temp + (r_measured - outside_temperature_table[i].res) * (t_range / r_range);
        }
    }
    return -99.0f;
}

float raw_to_res_safe(int16_t raw, float r_pullup) {
    float v_adc = (raw * LSB_4096) / 1000.0f;
    // Check: Wenn Spannung fast 3.3V -> Sensor offen oder Kabelbruch
    if (v_adc >= ADC_MAX_V_VALID || v_adc <= 0.01f) return -99.0f; // Signal für "Fehler"
    return (v_adc * r_pullup) / (3.3f - v_adc);
}

float get_i2c_adc_volt() {
    int16_t raw = read_ads1115(ads_handle[0], 0, 0x02); // Board
    float v_board = (raw * LSB_2048) / 1000.0f;
    v_board = v_board * ((10.0f + 1.5f) / 1.5f);
    printf("Board unfiltered Voltage: %.2f V\n", v_board);
    return v_board;
}

float get_i2c_adc_volt_bel() {
    int16_t raw = read_ads1115(ads_handle[0], 1, 0x01); // Bel
    float v_bel = (raw * LSB_4096) / 1000.0f; 
    v_bel = v_bel * ((10.0f + 2.2f) / 2.2f); // Teiler 10k/2.2k
    printf("Bel unfiltered Voltage: %.2f V\n", v_bel);
    return v_bel;
}

float get_i2c_adc_oil_temp() {
    int16_t raw = read_ads1115(ads_handle[0], 2, 0x01); // Temp
    float oil_t = raw_to_res_safe(raw, 680.0f);
    if (oil_t < -50) oil_t = -99.0f; // Fehler (Offen)
    else oil_t = interpolate_temp(oil_t);
    printf("Oil unfiltered Temperature: %.1f °C\n", oil_t);
    return oil_t;
}

float get_i2c_adc_oil_press() {
    int16_t raw = read_ads1115(ads_handle[0], 3, 0x01); // Druck
    float oil_p = raw_to_res_safe(raw, 680.0f);
    if (oil_p < 0 || oil_p > 250.0f) oil_p = -99.0f; // Fehler oder unplausibel hoch
    else oil_p = (oil_p - 10.0f) * (10.0f / (184.0f - 10.0f));
    printf("Oil unfiltered Pressure: %.2f bar\n", oil_p);
    return oil_p;
}

float get_i2c_adc_outside_temp() {
    int16_t raw = read_ads1115(ads_handle[1], 0, 0x01); // Außentemperatur
    float outside_t = raw_to_res_safe(raw, 4700.0f); 
    if (outside_t < 0 || outside_t > 150000.0f) outside_t = -99.0f; 
    else outside_t = interpolate_outside_temp(outside_t);
    printf("Outside unfiltered Temperature: %.1f °C\n", outside_t);
    return outside_t;
}