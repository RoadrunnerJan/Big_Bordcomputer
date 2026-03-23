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

void init_i2c_ds3231() {
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

void set_time(){

    struct tm time = {
        .tm_sec = 0,
        .tm_min = 15,
        .tm_hour = 12,
        .tm_wday = 5,      // Wochentag (1-7)
        .tm_mday = 20,     // Tag
        .tm_mon = 3,    // Monat (0-11)
        .tm_year = 26     // Jahr (2000 + 25 = 2025)
    };
    

    ds3231_set_time( &time);
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
        timeinfo.tm_hour = (timeinfo.tm_hour + 1) % 24;
        printf("Stunde erhöht: %d\n", timeinfo.tm_hour);
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min + 1) % 60;
        timeinfo.tm_sec = 0; // Sekunden nullen beim Stellen
        printf("Minute erhöht: %d\n", timeinfo.tm_min);
    }

    // 1. Zur RTC schreiben
    ds3231_set_time(&timeinfo);
    
    // 2. Systemzeit synchronisieren (damit der ESP es sofort weiß)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

void init_time_buttons() {
    // 1. GPIO Konfiguration
    button_config_t cfg_hour = {
        .long_press_time = 2000, // Beispielwert
        .short_press_time = 50
    };

    // ACHTUNG: Die API verlangt laut deiner Fehlermeldung 3 Argumente!
    // esp_err_t iot_button_create(config, driver, ret_button);
    
    button_handle_t btn_hour;
    iot_button_create(&cfg_hour, NULL, &btn_hour); // NULL für Standard-Treiber
    
    // Die Callback-Registrierung hat ebenfalls eine andere Signatur
    iot_button_register_cb(btn_hour, BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);

    button_config_t cfg_minute = {
        .long_press_time = 2000, // Beispielwert
        .short_press_time = 50
    };
    button_handle_t btn_min;
    iot_button_create(&cfg_minute, NULL, &btn_min);
    iot_button_register_cb(btn_min, BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
}

