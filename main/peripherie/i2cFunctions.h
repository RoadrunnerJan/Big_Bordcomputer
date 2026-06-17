/**
 * @file i2cFunctions.h
 * @brief I2C interface for DS3231 RTC and time adjustment buttons.
 *
 * Manages I2C communication with the DS3231 real-time clock and provides
 * button handlers for manual time adjustment functionality.
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

#pragma once

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF I2C Driver ===== */
#include "driver/i2c_master.h"

/* ===== RTOS & System ===== */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/time.h>

/* ===== RTOS & System ===== */
#include "../logging/logging.h"


/* ===== I2C Bus Configuration ===== */
/**
 * @brief I2C master bus configuration parameters.
 */
extern i2c_master_bus_config_t bus_cfg;

/**
 * @brief I2C master bus handle for device operations.
 */
extern i2c_master_bus_handle_t bus_handle;

/* ===== RTC (DS3231) Configuration ===== */
/**
 * @brief DS3231 RTC device configuration parameters.
 */
extern i2c_device_config_t ds3231_cfg;

/**
 * @brief DS3231 RTC device handle for read/write operations.
 */
extern i2c_master_dev_handle_t ds3231_handle;

/**
 * @brief System startup time in seconds since Unix epoch.
 */
extern int64_t StartUpTime_sec;

/**
 * @brief Last execution timestamps for each display and brightness update.
 *
 * Array indices: [0..NUMBER_OF_DISPLAYS-1] = display updates,
 * [NUMBER_OF_DISPLAYS] = brightness update timestamp
 */
extern int64_t last_executed_time[NUMBER_OF_DISPLAYS + 1];

/**
 * @brief Last brightness control update timestamp in milliseconds.
 */
extern int64_t last_executed_time_brightness;

/**
 * @brief Current system time in milliseconds since boot.
 */
extern int64_t now_ms;

/**
 * @brief Flag indicating whether time updates are allowed.
 *
 * Set to false during button operations to prevent time updates.
 * Set to true when button processing is complete.
 */
extern bool time_Update_Possible;

/* ===== Function Declarations ===== */

/**
 * @brief Initialize I2C bus and attach connected sensors.
 *
 * Sets up the I2C master bus and attaches the DS3231 RTC device.
 */
void init_i2c(void);

/**
 * @brief Synchronize system time with RTC DS3231 time.
 *
 * Reads current time from the DS3231 and updates ESP32 system time.
 */
void sync_rtc_to_system(void);

/**
 * @brief Get the system startup time in seconds.
 *
 * @return Pointer to startup time value in seconds since Unix epoch
 */
inline long long int* get_startup_time_sec() { return (long long int*)&StartUpTime_sec; }

/**
 * @brief Get the current system time in milliseconds.
 *
 * @return Current time in milliseconds
 */
inline int64_t get_now_time_ms() { return now_ms; };

/**
 * @brief Get the last execution timestamp for a specific display.
 *
 * @param displayID Index of the display (0 to NUMBER_OF_DISPLAYS-1)
 * @return Last execution timestamp in milliseconds for the display
 */
inline int64_t get_last_executed_time_per_screen(int displayID) { return last_executed_time[displayID]; }

/**
 * @brief Get the last brightness adjustment timestamp.
 *
 * @return Last brightness update timestamp in milliseconds
 */
inline int64_t get_last_executed_brightness() { return last_executed_time_brightness; }

/**
 * @brief Record and set the system startup time.
 *
 * Captures the current system time as the startup reference.
 * Should be called once after RTC synchronization during initialization.
 */
void set_startup_time_sec();

/**
 * @brief Update the current system time in millisecond precision.
 *
 * Reads the system clock and updates the global millisecond counter.
 * Called periodically by the main loop for accurate time tracking.
 */
void set_now_time_ms();

/**
 * @brief Set a specific execution timestamp for a display update.
 *
 * Manually sets the last execution time for a particular display.
 * Used during time synchronization and button operations.
 *
 * @param displayID Index of the display (0 to NUMBER_OF_DISPLAYS-1)
 * @param time Timestamp in milliseconds to record
 */
void set_last_executed_time_per_screen(int displayID, int64_t time);

/**
 * @brief Update the last execution timestamp for a display to current time.
 *
 * Automatically records when sensor values were last successfully updated
 * for the specified display. Called after value readings are processed.
 *
 * @param displayID Index of the display (0 to NUMBER_OF_DISPLAYS-1)
 */
void update_last_executed_time_per_screen(int displayID);

/**
 * @brief Update the last brightness adjustment timestamp to current time.
 *
 * Records when brightness calculations were last performed.
 * Separates brightness update frequency from display update frequency.
 */

void set_last_executed_brightness();

void rtc_set_time(struct tm* timeinfo);

void rtc_set_last_executionTime(struct timeval* tv );

/**
 * @brief Check if time value updates are currently permitted.
 *
 * Returns whether external code can safely update timing values.
 * Blocks during button operations to prevent time synchronization conflicts.
 *
 * @return true if time updates are allowed, false if blocked
 */
inline bool isCheckPossible() { return time_Update_Possible; }

void setIsCheckPossible(bool isPossible);

void setTimeIsUpdated(bool isUpdated);

bool getTimeIsUpdated();