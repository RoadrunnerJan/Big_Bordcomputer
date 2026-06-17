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

int64_t StartUpTime_sec = 0;
int64_t last_executed_time[NUMBER_OF_DISPLAYS + 1] = {0}; // Display 1-4 last executed time for value updates
int64_t last_executed_time_brightness = 0;
int64_t last_brightness_check_time = 0;
int64_t now_ms = 0;

bool time_Update_Possible = true;
bool time_is_updated = true;


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

void rtc_set_time(struct tm* timeinfo){
    ds3231_set_time(timeinfo);
}

void rtc_set_last_executionTime(struct timeval* tv ){
    now_ms = tv->tv_sec * 1000;
    for (int i = 0; i < NUMBER_OF_DISPLAYS + 1; i++) {
        last_executed_time[i] = now_ms;
    }
    last_executed_time_brightness = now_ms;
}

void setIsCheckPossible(bool isPossible) { time_Update_Possible = isPossible; }

void setTimeIsUpdated(bool isUpdated) { time_is_updated = isUpdated; }

bool getTimeIsUpdated() { return time_is_updated; }