/**
 * @file testSimulation.c
 * @brief Test simulation module debug mode value generation implementation.
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

/* ===== Includes ===== */
#include "testSimulation.h"

/* ===== Global Test Value Variables ===== */

/// Simulated oil pressure value (bar)
double test_value_oil_pressure         = 0.0;
/// Simulated oil temperature value (°C)
double test_value_oil_temperature      = 0.0;
/// Simulated battery voltage value (V)
double test_value_volt                 = 8.0;
/// Simulated outdoor temperature value (°C)
double test_value_outside_temperature  = 0.0;
/// Simulated brightness level (0-100)
int test_value_brightness              = 0;
/// Simulated night mode state
bool test_night_mode_active            = false;

/**
 * @brief Direction array for test value oscillation.
 * 
 * Controls direction of value changes: 1 for increasing, -1 for decreasing.
 * Array indices: [0]=oil pressure, [1]=voltage, [2]=oil temp, [3]=outdoor temp, [4]=brightness.
 */
int test_direction[5] = {1, 1, 1, 1, 1};

/**
 * @brief Step size array for test value oscillation.
 * 
 * Controls rate of value change for each sensor.
 * Array indices: [0]=oil pressure (0.015 bar/cycle), [1]=voltage (0.01 V/cycle), 
 * [2]=oil temp (0.1°C/cycle), [3]=outdoor temp (0.5°C/cycle), [4]=brightness (1%/cycle).
 */
double test_step[5] = {0.015, 0.01, 0.10, 0.05, 1};

/* ===== Function Implementations ===== */

/**
 * @brief Reset all test values to default state.
 */
void reset_test_values(void) {
    test_value_oil_pressure         = VALUE_DEFAULT_PRES;
    test_value_oil_temperature      = VALUE_DEFAULT_TEMP;
    test_value_volt                 = VALUE_DEFAULT_VOLT;
    test_value_outside_temperature  = 4.0;
    test_value_brightness           = BRIGHTNESS_DAY;
    test_night_mode_active          = false;
}

/**
 * @brief Simulate oil pressure test cycle.
 *
 * Simulates oil pressure by oscillating between minimum and maximum values.
 *
 * @return Current simulated oil pressure in bar
 */
double lv_pressure_test()
{
    test_value_oil_pressure += test_direction[0] * test_step[0];

    if(test_value_oil_pressure >= VALUE_MAX_PRES-test_step[0]) test_direction[0] = -1;
    if(test_value_oil_pressure <= VALUE_MIN_PRES-test_step[0]) test_direction[0] = +1;
    return test_value_oil_pressure;
}

/**
 * @brief Simulate voltage test cycle.
 *
 * Simulates battery voltage by oscillating between minimum and maximum values.
 *
 * @return Current simulated voltage in volts
 */
double lv_volt_test()
{
    test_value_volt += test_direction[1] * test_step[1];

    if(test_value_volt >= VALUE_MAX_VOLT-test_step[1]) test_direction[1] = -1;
    if(test_value_volt <= VALUE_MIN_VOLT-test_step[1]) test_direction[1] = +1;
    return test_value_volt;
}

/**
 * @brief Simulate oil temperature test cycle.
 * 
 * Simulates oil temperature by oscillating between minimum and maximum values.
 *
 * @return Current simulated oil temperature in °C
 */
double lv_temperature_test()
{
    test_value_oil_temperature += test_direction[2] * test_step[2];

    if(test_value_oil_temperature >= VALUE_MAX_TEMP-test_step[2]) test_direction[2] = -1;
    if(test_value_oil_temperature <= VALUE_MIN_TEMP-test_step[2]) test_direction[2] = +1;
    return test_value_oil_temperature;
}

/**
 * @brief Simulate outdoor temperature test cycle.
 *
 * Simulates outdoor temperature by oscillating between minimum and maximum values.
 *
 * @return Current simulated outdoor temperature in °C
 */
double lv_Clocktemp_test()
{
    test_value_outside_temperature += test_direction[3] * test_step[3];

    if(test_value_outside_temperature >= VALUE_MAX_OUT_TEMP-test_step[3]) test_direction[3] = -1;
    if(test_value_outside_temperature <= VALUE_MIN_OUT_TEMP-test_step[3]) test_direction[3] = +1;
    return test_value_outside_temperature;
}

/**
 * @brief Run brightness test sequence with night mode transitions.
 *
 * Cycles brightness through predefined phases and automatically manages night mode state.
 * Night mode is enabled when brightness <= BRIGHTNESS_NIGHT_MAX, disabled otherwise.
 * This function updates both test_value_brightness and test_night_mode_active.
 * 
 */
void brightness_test() {

    test_value_brightness += test_direction[4] * test_step[4];

    if(test_value_brightness >= BRIGHTNESS_DAY-test_step[4]) test_direction[4] = -1;
    if(test_value_brightness <= BRIGHTNESS_NIGHT_MIN-test_step[4]) test_direction[4] = +1;
    if (test_value_brightness <= BRIGHTNESS_NIGHT_MAX) 
        test_night_mode_active = true;
    else test_night_mode_active = false;
}

/**
 * @brief Get the current simulated brightness value.
 *
 * @return Current test brightness value (0-100 representing brightness percentage)
 */
int getBrightnessTestValue() {return test_value_brightness;}

/**
 * @brief Get the current simulated night mode state.
 *
 * Reflects whether night mode is active during test simulation.
 * Automatically updated by brightness_test() based on brightness levels.
 *
 * @return true if night mode is currently active, false for day mode
 */
bool getNightModeActiveTestValue() {return test_night_mode_active;}