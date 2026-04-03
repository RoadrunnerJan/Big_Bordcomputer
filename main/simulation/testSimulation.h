#pragma once

/*
 * ============================================================================
 * TEST SIMULATION MODULE - Debug Mode Value Generation
 * ============================================================================
 * Generates test sensor values for development and testing without hardware.
 * Useful for UI/logic testing when hardware is unavailable.
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - Test value generation for all sensor types
 *      - Brightness and night mode simulation
 *      - Compile-time enable/disable support
 *
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

extern double test_value_volt;             // Simulated battery voltage (V)
extern double test_value_outside_temperature; // Simulated outdoor temperature (°C)
extern int test_value_brightness;          // Simulated brightness (0-100)
extern bool test_night_mode_active;        // Simulated night mode state

/* ===== Test Value Controllers ===== */
extern int pressure_test_switch;           // Pressure test mode control
extern int temperature_test_switch;        // Temperature test mode control
extern int volt_test_switch;               // Voltage test mode control
extern int Clocktemp_test_switch;          // Outdoor temperature test mode control
extern int brightness_test_switch;         // Brightness test mode control

/* ===== Test Value Arrays ===== */
extern double test_steps[5][4];            // Test value increment arrays
extern double test_thresholds[5][4];       // Test value thresholds


/* ===== Function Declarations ===== */

/**
 * Reset all test mode switches to initial state
 */
void reset_test_switches(void);

/**
 * Generate test pressure value
 */
double lv_pressure_test(void);

/**
 * Generate test voltage value
 */
double lv_volt_test(void);

/**
 * Generate test temperature value
 */
double lv_temperature_test(void);

/**
 * Generate test outdoor temperature value
 */
double lv_Clocktemp_test(void);

/**
 * Run brightness test sequence
 */
void brightness_test(void);

/**
 * Get current test brightness value
 */
int getBrightnessTestValue(void);

/**
 * Get current night mode test state
 */
bool getNightModeActiveTestValue(void);

void reset_test_values(void);