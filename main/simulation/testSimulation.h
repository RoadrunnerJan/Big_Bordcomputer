#pragma once

/**
 * @file testSimulation.h
 * @brief Test simulation module for debug mode value generation.
 *
 * Generates deterministic test sensor values for development and testing without hardware.
 * Useful for UI/logic testing when hardware sensors are unavailable.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - Test value generation for all sensor types
 *      - Brightness and night mode simulation
 *      - Compile-time enable/disable support
 */

/* ===== System Includes ===== */
#include "esp_system.h"

#include "../individual_config.h"


/* ===== Test Value Storage ===== */

/**
 * @brief Simulated oil pressure sensor value in bar.
 *
 * Range: 0.0 - 6.0 bar, updated by lv_pressure_test() in test mode.
 */
extern double test_value_oil_pressure;

/**
 * @brief Simulated oil temperature sensor value in °C.
 *
 * Range: 0 - 150°C, updated by lv_temperature_test() in test mode.
 */
extern double test_value_oil_temperature;

/**
 * @brief Simulated battery voltage sensor value in volts.
 *
 * Range: 8.0 - 16.0 V, updated by lv_volt_test() in test mode.
 */
extern double test_value_volt;

/**
 * @brief Simulated outdoor/ambient temperature sensor value in °C.
 *
 * Range: -30 to 70°C, updated by lv_Clocktemp_test() in test mode.
 */
extern double test_value_outside_temperature;

/**
 * @brief Simulated display brightness level in percentage.
 *
 * Range: 0 (minimum) to 100 (maximum), updated by brightness_test() in test mode.
 */
extern int test_value_brightness;

/**
 * @brief Simulated night mode active state.
 *
 * true for night mode (reduced brightness), false for day mode (full brightness).
 * Automatically updated by brightness_test() based on brightness thresholds.
 */
extern bool test_night_mode_active;

/**
 * @brief Direction array for test value oscillation.
 * 
 * Controls direction of value changes: 1 for increasing, -1 for decreasing.
 * Array indices: [0]=oil pressure, [1]=voltage, [2]=oil temp, [3]=outdoor temp, [4]=brightness.
 */
extern int test_direction[5];

/**
 * @brief Step size array for test value oscillation.
 * 
 * Controls rate of value change for each sensor.
 * Array indices: [0]=oil pressure (0.015 bar/cycle), [1]=voltage (0.01 V/cycle), 
 * [2]=oil temp (0.5°C/cycle), [3]=outdoor temp (0.5°C/cycle), [4]=brightness (1%/cycle).
 */
extern double test_step[5];


/* ===== Function Declarations ===== */

/**
 * @brief Generate test oil pressure value.
 *
 * @return Simulated oil pressure in bar
 */
double lv_pressure_test(void);

/**
 * @brief Generate test battery voltage value.
 *
 * @return Simulated voltage in volts
 */
double lv_volt_test(void);

/**
 * @brief Generate test oil temperature value.
 *
 * @return Simulated oil temperature in °C
 */
double lv_temperature_test(void);

/**
 * @brief Generate test outdoor temperature value.
 *
 * @return Simulated outdoor temperature in °C
 */
double lv_Clocktemp_test(void);

/**
 * @brief Run brightness test sequence with night mode transitions.
 *
 * Cycles brightness through predefined phases and automatically manages night mode state.
 * Night mode is enabled when brightness <= BRIGHTNESS_NIGHT_MAX, disabled otherwise.
 *
 * @note This function updates both test_value_brightness and test_night_mode_active.
 */
void brightness_test(void);

/**
 * @brief Get current test brightness value.
 *
 * @return Brightness level (0-100)
 */
int getBrightnessTestValue(void);

/**
 * @brief Get current night mode test state.
 *
 * @return true if night mode is active in test, false if day mode
 */
bool getNightModeActiveTestValue(void);

/**
 * @brief Reset all test values to defaults.
 */
void reset_test_values(void);