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

/* ===== Test Value Controllers ===== */

/**
 * @brief Phase counter for oil pressure test cycle.
 *
 * Current phase in the pressure test sequence (0-3), incremented by lv_pressure_test().
 */
extern int pressure_test_switch;

/**
 * @brief Phase counter for oil temperature test cycle.
 *
 * Current phase in the temperature test sequence (0-3), incremented by lv_temperature_test().
 */
extern int temperature_test_switch;

/**
 * @brief Phase counter for voltage test cycle.
 *
 * Current phase in the voltage test sequence (0-3), incremented by lv_volt_test().
 */
extern int volt_test_switch;

/**
 * @brief Phase counter for outdoor temperature test cycle.
 *
 * Current phase in the outdoor temperature test sequence (0-3), incremented by lv_Clocktemp_test().
 */
extern int Clocktemp_test_switch;

/**
 * @brief Phase counter for brightness test cycle.
 *
 * Current phase in the brightness test sequence (0-3), incremented by brightness_test().
 */
extern int brightness_test_switch;

/* ===== Test Value Arrays ===== */

/**
 * @brief Test value increment per phase for each sensor type.
 *
 * Array structure: [sensor_type][phase_index]
 * - sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=outdoor_temperature, 4=brightness
 * - phase_index: 0-3 representing the four test cycle phases
 * Values can be positive (increase) or negative (decrease).
 */
extern double test_steps[5][4];

/**
 * @brief Test value threshold limits for phase transitions.
 *
 * Array structure: [sensor_type][threshold_index]
 * - sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=outdoor_temperature, 4=brightness
 * - threshold_index: 0-3 representing the four test cycle phase boundaries
 * Each threshold defines when to transition to the next phase.
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