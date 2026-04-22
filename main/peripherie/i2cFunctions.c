/**
 * @file i2cFunctions.c
 * @brief I2C interface RTC and ADC device communication implementation.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - DS3231 real-time clock interface
 *      - NTC temperature table interpolation
 *      - Button control for time adjustment
 *      - Dual ADC support for enhanced sensor coverage
 */

#include "i2cFunctions.h"

i2c_master_bus_config_t bus_cfg = {0};
i2c_master_bus_handle_t bus_handle = NULL;

/* RTC (DS3231) Configuration */
i2c_device_config_t ds3231_cfg = {0};
i2c_master_dev_handle_t ds3231_handle = NULL;

/* Time adjustment buttons: [0] = Hour, [1] = Minute */
button_config_t cfg_time[2] = {0};
button_gpio_config_t gpio_cfg_time[2] = {0};
button_handle_t btn_time[2] = {0};

bool testmode_activated = false;
TickType_t testmode_activation_time = 0;
int testmode_activation_count = 0;
int testmode_activation_state = 0;

/**
 * @brief Initialize I2C bus and attach RTC and ADC devices.
 *
 * Sets up the I2C master bus and attaches the DS3231 device for multi-device support.
 */
void init_i2c() {
    // Configure I2C bus
    bus_cfg.clk_source = I2C_CLK_SRC;
    bus_cfg.i2c_port = I2C_PORT;
    bus_cfg.scl_io_num = I2C_SCL_PIN;
    bus_cfg.sda_io_num = I2C_SDA_PIN;
    bus_cfg.glitch_ignore_cnt = I2C_GLITCH_IGNORE;
    bus_cfg.flags.enable_internal_pullup = I2C_INT_PULLUP_ENB;

    // Configure RTC (DS3231)
    ds3231_cfg.dev_addr_length = RTC_ADDR_LENGTH;
    ds3231_cfg.device_address = RTC_DS3231_ADDR;
    ds3231_cfg.scl_speed_hz = RTC_SCL_SPEED_HZ;
    
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ds3231_cfg, &ds3231_handle));
}

inline uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
inline uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) | (val % 10); }

void sync_rtc_to_system() {
    uint8_t data[7];
    uint8_t reg = 0x00;  // RTC start register (Seconds)

    // Read 7 bytes of time data
    i2c_master_transmit_receive(ds3231_handle, &reg, 1, data, 7, 1000);

    struct tm tm = {
        .tm_sec  = bcd2dec(data[0] & 0x7F),
        .tm_min  = bcd2dec(data[1]),
        .tm_hour = bcd2dec(data[2] & 0x3F), // 24-hour format
        .tm_mday = bcd2dec(data[4]),
        .tm_mon  = bcd2dec(data[5] & 0x1F) - 1, // tm_mon is 0-11
        .tm_year = bcd2dec(data[6]) + 100,      // tm_year is years since 1900
    };

    // Convert to Unix timestamp
    time_t t = mktime(&tm);
    
    // Set ESP32 system time
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);
}

/**
 * Write the given time struct into the DS3231 RTC.
 *
 * @param time Pointer to struct tm containing the desired time to set.
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t ds3231_set_time(struct tm *time) {
    uint8_t data[8];
    data[0] = 0x00;  // RTC register address (Seconds)
    
    data[1] = dec2bcd(time->tm_sec);
    data[2] = dec2bcd(time->tm_min);
    data[3] = dec2bcd(time->tm_hour); // Bit 6 must be 0 for 24-hour format
    data[4] = dec2bcd(time->tm_wday + 1); // Day of week (1-7)
    data[5] = dec2bcd(time->tm_mday);
    data[6] = dec2bcd(time->tm_mon + 1); // DS3231 uses 1-12
    data[7] = dec2bcd(time->tm_year % 100); // Only last two digits (e.g., 26 for 2026)

    // Send 8 bytes (register address + 7 bytes of time data)
    return i2c_master_transmit(ds3231_handle, data, 8, -1);
}

/**
 * Button callback for single-click forward adjustments.
 *
 * Implements the activation sequence for test mode:
 * 1) minute minus twice
 * 2) hour minus once
 * 3) minute plus twice
 * 4) hour plus once -> toggle test mode
 * All within TESTMODE_ACTIVATE_TIMEOUT_MS (7 seconds).
 */
static void button_event_cb(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour + 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour incremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 4) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_4_COUNT) {
                    testmode_activation_state = -1;
                    testmode_activation_count = 0;
                    testmode_activated = !testmode_activated; // Toggle test mode
                    printWarningLog(testmode_activated == true ? "Test mode ACTIVATED!" : "Test mode DEACTIVATED!");
                }
            }
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min + 1 + 60) % 60;
        if (timeinfo.tm_min == 0) { 
            timeinfo.tm_hour = (timeinfo.tm_hour + 1) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour incremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute incremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == 3) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_3_COUNT) {
                    testmode_activation_state = 4;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }

    ds3231_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

/**
 * Button callback for single-click backward adjustments.
 *
 * Handles the reverse time-decrement path as part of the testmode activation sequence.
 */
static void button_event_cb_back(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour decremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 2) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_2_COUNT) {
                    testmode_activation_state = 3;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min - 1 + 60) % 60;
        if (timeinfo.tm_min == 59) { 
            timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour decremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute decremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == -1) {
            testmode_activation_state = 0;
            testmode_activation_time = xTaskGetTickCount();
            testmode_activation_count = 1;
        }
        else if (testmode_activation_state == 0) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_1_COUNT) {
                    testmode_activation_state = 2;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }

    // Write to RTC
    ds3231_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

void init_time_buttons() {

    cfg_time[0].short_press_time = BUTTON_CLOCK_MINUTE_SHORT_MS;
    cfg_time[0].long_press_time = BUTTON_CLOCK_MINUTE_LONG_MS;
    gpio_cfg_time[0].gpio_num = BUTTON_CLOCK_HOUR_PIN;
    gpio_cfg_time[0].active_level = BUTTON_CLOCK_MINUTE_ACTIVE_LEVEL;    
    cfg_time[1].short_press_time = BUTTON_CLOCK_HOUR_SHORT_MS;
    cfg_time[1].long_press_time = BUTTON_CLOCK_HOUR_LONG_MS;
    gpio_cfg_time[1].gpio_num = BUTTON_CLOCK_MINUTE_PIN;
    gpio_cfg_time[1].active_level = BUTTON_CLOCK_HOUR_ACTIVE_LEVEL;

    iot_button_new_gpio_device(&cfg_time[0], &gpio_cfg_time[0], &btn_time[0]);
    iot_button_register_cb(btn_time[0], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_register_cb(btn_time[0], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_new_gpio_device(&cfg_time[1], &gpio_cfg_time[1], &btn_time[1]);
    iot_button_register_cb(btn_time[1], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
    iot_button_register_cb(btn_time[1], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_MINUTE_PIN);
}
