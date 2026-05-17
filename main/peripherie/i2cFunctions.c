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
int testmode_activation_state = -1;

int64_t StartUpTime_sec = 0;
int64_t last_executed_time[NUMBER_OF_DISPLAYS + 1] = {0}; // Display 1-4 last executed time for value updates
int64_t last_executed_time_brightness = 0;
int64_t last_brightness_check_time = 0;
int64_t now_ms = 0;

bool time_Update_Possible = true;

/**
 * @brief Initialize I2C bus and attach RTC and ADC devices.
 *
 * Sets up the I2C master bus with configured GPIO pins and clock source,
 * then attaches the DS3231 real-time clock device for time operations.
 * Call this once during system initialization before using I2C functions.
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

/**
 * @brief Convert Binary-Coded Decimal (BCD) to decimal value.
 *
 * BCD format uses 4 bits per digit (high nibble = tens, low nibble = ones).
 *
 * @param val BCD-encoded byte value
 * @return Decoded decimal value (0-99)
 */
inline uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }

/**
 * @brief Convert decimal value to Binary-Coded Decimal (BCD) format.
 *
 * BCD format uses 4 bits per digit (high nibble = tens, low nibble = ones).
 *
 * @param val Decimal value to encode (0-99)
 * @return BCD-encoded byte value
 */
inline uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) | (val % 10); }

/**
 * @brief Read time from DS3231 RTC and synchronize ESP32 system time.
 *
 * Reads the current time from the DS3231 real-time clock via I2C,
 * converts from BCD format to standard time structure, and updates
 * the ESP32 system clock. This ensures accurate time after boot.
 */
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
 * @brief Write time to DS3231 RTC device.
 *
 * Converts the provided time structure to BCD format and writes it to the
 * DS3231 real-time clock. This updates the RTC's internal time keeping.
 *
 * @param time Pointer to struct tm containing the desired time to write
 * @return ESP_OK on success, error code otherwise
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
 * @brief Button callback for forward time adjustments and test mode activation.
 *
 * Implements the forward path of test mode activation sequence:
 * - Increments hour or minute based on button pressed
 * - Checks if button sequence matches testmode activation pattern (states 3-4)
 * - Toggles test mode when final activation condition is met
 * - Synchronizes updated time to both RTC and system clock
 *
 * Activation sequence (within TESTMODE_ACTIVATE_TIMEOUT_MS):
 * 1. Press minute button twice (decrease, state 0-1)
 * 2. Press hour button once (decrease, state 1-2)
 * 3. Press minute button twice (increase, state 2-3)
 * 4. Press hour button once (increase, state 3-4) -> toggles test mode
 *
 * @param btn_handle Button handle (unused)
 * @param usr_data Button ID as void pointer (BUTTON_CLOCK_HOUR_PIN or BUTTON_CLOCK_MINUTE_PIN)
 */
static void button_event_cb(void *btn_handle, void *usr_data) {
    time_Update_Possible = false;
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

    // Update last execution time for hours
    now_ms = tv.tv_sec * 1000;
    for (int i = 0; i < NUMBER_OF_DISPLAYS + 1; i++) {
        last_executed_time[i] = now_ms;
    }
    last_executed_time_brightness = now_ms;
    time_Update_Possible = true;
}

/**
 * @brief Button callback for backward time adjustments and test mode activation.
 *
 * Implements the backward path of test mode activation sequence:
 * - Decrements hour or minute based on button pressed
 * - Checks if button sequence matches testmode activation pattern (states 0-2)
 * - Transitions through activation states when conditions are met
 * - Synchronizes updated time to both RTC and system clock
 *
 * Activation sequence (within TESTMODE_ACTIVATE_TIMEOUT_MS):
 * 1. First button press initializes activation counter (state -1 to 0)
 * 2. Subsequent presses increment counter until TESTMODE_ACTIVATE_BUTTON_1_COUNT is reached
 * 3. Progresses through states 0 -> 2 -> 3 before final state 4 completion
 *
 * @param btn_handle Button handle (unused)
 * @param usr_data Button ID as void pointer (BUTTON_CLOCK_HOUR_PIN or BUTTON_CLOCK_MINUTE_PIN)
 */
static void button_event_cb_back(void *btn_handle, void *usr_data) {
    time_Update_Possible = false;
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

    // Update last execution time for hours
    now_ms = tv.tv_sec * 1000;
    for (int i = 0; i < NUMBER_OF_DISPLAYS + 1; i++) {
        last_executed_time[i] = now_ms;
    }
    last_executed_time_brightness = now_ms;
    time_Update_Possible = true;
}

/**
 * @brief Initialize time adjustment buttons with callbacks.
 *
 * Configures GPIO-based buttons for hour and minute time adjustments.
 * Registers single-click handlers for time increment and long-press handlers
 * for time decrement. Each button is independently configured with its own
 * debounce timing and active level settings.
 *
 * Called during system initialization to enable runtime time adjustments
 * and test mode activation via button sequences.
 */
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

/**
 * @brief Capture the system startup time from current system clock.
 *
 * Records the current time as the application startup time.
 * Used for calculating elapsed time and scheduling delayed initialization tasks.
 * Should be called once during system initialization after time synchronization.
 */
void set_startup_time_sec() { 
    struct timeval time;
    gettimeofday(&time, NULL);
    StartUpTime_sec = time.tv_sec;
}

/**
 * @brief Update current system time in milliseconds.
 *
 * Reads the current system time and converts to millisecond precision.
 * Only updates if time checks are permitted (not blocked by button operations).
 * Called periodically by the main loop to keep the timing reference current.
 */
void set_now_time_ms() { 
    if (!isCheckPossible()) return;
    struct timeval time;
    gettimeofday(&time, NULL);
    now_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
}

/**
 * @brief Set the last execution timestamp for a specific display.
 *
 * Updates the timestamp tracking when sensor values were last read/calculated
 * for the specified display. Used for controlling update frequency per display.
 * Only updates if time checks are permitted.
 *
 * @param displayID Index of the display (0 to NUMBER_OF_DISPLAYS-1)
 * @param time Timestamp in milliseconds to record
 */
void set_last_executed_time_per_screen(int displayID, int64_t time) { 
    if (!isCheckPossible()) return;
    last_executed_time[displayID] = time;
}

/**
 * @brief Update the last execution timestamp to current time for a display.
 *
 * Records the current system time as the last update time for the specified display.
 * Called after sensor values are successfully read and processed.
 * Only updates if time checks are permitted.
 *
 * @param displayID Index of the display (0 to NUMBER_OF_DISPLAYS-1)
 */
void update_last_executed_time_per_screen(int displayID) { 
    if (!isCheckPossible()) return;
    last_executed_time[displayID] = get_now_time_ms(); 
}

/**
 * @brief Update the last brightness adjustment timestamp to current time.
 *
 * Records when brightness control calculations were last performed.
 * Used to control the frequency of brightness updates independent of display updates.
 * Only updates if time checks are permitted.
 */
void set_last_executed_brightness() { 
    if (!isCheckPossible()) return;
    last_executed_time_brightness = now_ms;
}
