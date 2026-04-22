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
 * @brief Simulated oil pressure in bar.
 */
extern double test_value_oil_pressure;

/**
 * @brief Simulated oil temperature in °C.
 */
extern double test_value_oil_temperature;

/**
 * @brief Simulated battery voltage in volts.
 */
extern double test_value_volt;

/**
 * @brief Simulated outdoor temperature in °C.
 */
extern double test_value_outside_temperature;

/**
 * @brief Simulated display brightness (0-100).
 */
extern int test_value_brightness;

/**
 * @brief Simulated night mode state.
 */
extern bool test_night_mode_active;

/* ===== Test Value Controllers ===== */

/**
 * @brief Pressure test mode control variable.
 */
extern int pressure_test_switch;

/**
 * @brief Temperature test mode control variable.
 */
extern int temperature_test_switch;

/**
 * @brief Voltage test mode control variable.
 */
extern int volt_test_switch;

/**
 * @brief Outdoor temperature test mode control variable.
 */
extern int Clocktemp_test_switch;

/**
 * @brief Brightness test mode control variable.
 */
extern int brightness_test_switch;

/* ===== Test Value Arrays ===== */

/**
 * @brief Test value increment arrays for cycling through test phases.
 *
 * Format: [sensor_type][step_index]
 * sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=clock_temperature, 4=brightness
 */
extern double test_steps[5][4];

/**
 * @brief Test value thresholds for switching between test phases.
 *
 * Format: [sensor_type][threshold_index]
 * sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=clock_temperature, 4=brightness
 */
extern double test_thresholds[5][4];


/* ===== Function Declarations ===== */

/**
 * @brief Reset all test mode switches to initial state.
 */
void reset_test_switches(void);

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
 * @brief Run brightness test sequence.
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