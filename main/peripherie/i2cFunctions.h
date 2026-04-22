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

/* ===== Button Library ===== */
#include "iot_button.h"
#include "button_gpio.h"

/* ===== RTOS & System ===== */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/time.h>

/* ===== RTOS & System ===== */
#include "../logging/logging.h"


/* ===== I2C Bus Configuration ===== */
extern i2c_master_bus_config_t bus_cfg;
extern i2c_master_bus_handle_t bus_handle;

/* ===== RTC (DS3231) Configuration ===== */
extern i2c_device_config_t ds3231_cfg;
extern i2c_master_dev_handle_t ds3231_handle;

/* ===== Time Adjustment Buttons ===== */
extern button_config_t cfg_time[2];           // [0] = Hour, [1] = Minute
extern button_gpio_config_t gpio_cfg_time[2];
extern button_handle_t btn_time[2];

/* ===== Testmode Activation Values ===== */
extern bool testmode_activated;
extern TickType_t testmode_activation_time;
extern int testmode_activation_count;
extern int testmode_activation_state;

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
 * @brief Initialize the time adjustment buttons and callbacks.
 *
 * Configures GPIO buttons for hour and minute adjustment with interrupt handlers.
 */
void init_time_buttons(void);

/**
 * @brief Get the state of testmode activation.
 *
 * @return true if test mode is currently active, false otherwise
 */
inline bool is_testmode_activated(void) {
    return testmode_activated;
}