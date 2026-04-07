#pragma once

/**
 * @file i2cFunctions.h
 * @brief I2C interface for DS3231 RTC and ADS1115 ADC.
 *
 * Handles I2C communication with DS3231 RTC and ADS1115 ADC sensors.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - DS3231 real-time clock interface
 *      - ADS1115 ADC for analog sensor readings
 *      - NTC temperature table interpolation
 *      - Button control for time adjustment
 *      - Dual ADC support for enhanced sensor coverage
 */

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


/* ===== NTC Temperature Lookup Table Structure ===== */
typedef struct {
    float temp;  // Temperature in °C
    float res;   // Resistance in Ohms
} lookup_values_t;


/* ===== I2C Bus Configuration ===== */
extern i2c_master_bus_config_t bus_cfg;
extern i2c_master_bus_handle_t bus_handle;

/* ===== RTC (DS3231) Configuration ===== */
extern i2c_device_config_t ds3231_cfg;
extern i2c_master_dev_handle_t ds3231_handle;

/* ===== ADC (ADS1115) Configuration ===== */
extern i2c_device_config_t ads_cfg[NUMBER_OF_ADS1115_DEVICES];
extern i2c_master_dev_handle_t ads_handle[NUMBER_OF_ADS1115_DEVICES];

/**
 * ADC reference voltage for resistance calculations (dynamically adjustable).
 */
extern float reference_voltage;

/* ===== Time Adjustment Buttons ===== */
extern button_config_t cfg_time[2];           // [0] = Hour, [1] = Minute
extern button_gpio_config_t gpio_cfg_time[2];
extern button_handle_t btn_time[2];

/* ===== Temperature Lookup Tables ===== */
extern const lookup_values_t oil_temp_table[];
extern const lookup_values_t outside_temperature_table[];
#define OIL_TABLE_SIZE (sizeof(oil_temp_table) / sizeof(lookup_values_t))
#define OUTSIDE_TABLE_SIZE (sizeof(outside_temperature_table) / sizeof(lookup_values_t))
#define PRESSURE_TABLE_SIZE (sizeof(pressure_table) / sizeof(pressure_table[0]))

/* ===== Testmode Activation Values ===== */
extern bool testmode_activated;
extern TickType_t testmode_activation_time;
extern int testmode_activation_count;
extern int testmode_activation_state;

/* ===== Reference Voltage ===== */
extern float reference_voltage;

/* ===== Function Declarations ===== */

/**
 * Initialize I2C bus and attach connected sensors (RTC and ADC).
 */
void init_i2c(void);

/**
 * Sync system time with RTC DS3231 time.
 */
void sync_rtc_to_system(void);

/**
 * Initialize the time adjustment buttons and callbacks.
 */
void init_time_buttons(void);

/**
 * Read battery voltage from ADS1115 ADC
 */
float get_i2c_adc_volt(void);

/**
 * Read brightness/light sensor voltage from ADS1115 ADC
 */
float get_i2c_adc_volt_bel(void);

/**
 * Read oil temperature from ADS1115 ADC with NTC lookup table
 */
float get_i2c_adc_oil_temp(void);

/**
 * Read oil pressure from ADS1115 ADC with resistance-to-pressure conversion
 */
float get_i2c_adc_oil_press(void);

/**
 * Read outdoor temperature from ADS1115 ADC with NTC lookup table
 */
float get_i2c_adc_outside_temp(void);

/**
 * Measure and update the ADC reference voltage dynamically.
 *
 * Reads from the second ADS1115 ADC device and updates the global reference_voltage.
 */
void get_i2c_adc_reference_voltage(void);

/**
 * Read reference voltage from ADS1115 ADC (Version 4.2 feature)
 */
void get_i2c_adc_reference_voltage(void);

/**
 * Return the state of the testmode_activation
 */
inline bool is_testmode_activated(void) {
    return testmode_activated;
}