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
double test_value_oil_pressure         = 0.0;
double test_value_oil_temperature      = 0.0;
double test_value_volt                 = 8.0;
double test_value_outside_temperature  = 0.0;
int test_value_brightness              = 0;
bool test_night_mode_active            = false;

/* ===== Test State Variables ===== */
int pressure_test_switch    = 0;
int temperature_test_switch = 0;
int volt_test_switch        = 0;
int Clocktemp_test_switch   = 0;
int brightness_test_switch  = 0;

/* ===== Test Configuration Arrays ===== */

/**
 * @brief Test step changes for each sensor type.
 *
 * Format: [sensor_type][step_index]
 * sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=clock_temperature, 4=brightness
 */
double test_steps[5][4] = {
    /* oil pressure      */ {+0.06, -0.02, +0.06, -0.06},
    /* volt              */ {+0.50, -0.05, +0.05, -0.50},
    /* oil temperature   */ {+0.30, -0.30, +0.30, -0.30},
    /* clock temperature */ {+0.30, -0.30, +0.30, -0.30},
    /* brightness        */ {-1.00, +1.00, -1.00, +1.00}
};

/**
 * @brief Test thresholds for switching between test phases.
 *
 * Format: [sensor_type][threshold_index]
 * sensor_type: 0=oil_pressure, 1=volt, 2=oil_temperature, 3=clock_temperature, 4=brightness
 */
double test_thresholds[5][4] = {
    //                        >=   <=   >=    <=
    /* oil pressure      */ {4.5, 2.5, 5.5, 0.04},

    //                        >=   <=   >=    <=
    /* volt              */ {15.5, 11,  14, 8.04},

    //                        >=   <=   >=    <=
    /* oil temperature   */ {100, 110, 140, 0.06},

    //                        >=   <=   >=    <=
    /* clock temperature */ { 33, -15,  20, 0.06},

    //                        <=   >=   <=    >=
    /* brightness        */ {  BRIGHTNESS_NIGHT_MIN,  BRIGHTNESS_DAY,   BRIGHTNESS_NIGHT_MIN,  BRIGHTNESS_DAY}
};

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
 * @brief Reset all test state switches to initial phase.
 */
void reset_test_switches() {
    pressure_test_switch    = 0;
    temperature_test_switch = 0;
    volt_test_switch        = 0;
    Clocktemp_test_switch   = 0;
    brightness_test_switch  = 0;
}

/**
 * @brief Simulate oil pressure test cycle.
 *
 * Cycles through predefined pressure values for testing gauge functionality.
 */
double lv_pressure_test()
{
    switch (pressure_test_switch) {
        case 0:
            test_value_oil_pressure += test_steps[0][0];
            if (test_value_oil_pressure >= test_thresholds[0][0]) {
                pressure_test_switch = 1;
            }
        break;
        case 1:
            test_value_oil_pressure += test_steps[0][1];
            if (test_value_oil_pressure <= test_thresholds[0][1]) {
                pressure_test_switch = 2;
            }
        break;
        case 2:
            test_value_oil_pressure += test_steps[0][2];
            if (test_value_oil_pressure >= test_thresholds[0][2]) {
                pressure_test_switch = 3;
            }
        break;
        case 3:
            test_value_oil_pressure += test_steps[0][3];
            if (test_value_oil_pressure <= test_thresholds[0][3]) {
                pressure_test_switch = 0;
            }
        break;
    }
    return test_value_oil_pressure;
}

/**
 * Simulate voltage test cycle
 * Cycles through 4 phases: increase to 15.5, decrease to 11, increase to 14, decrease to 8.04
 * @return Current simulated voltage value
 */
double lv_volt_test()
{
    switch (volt_test_switch) {
        case 0:
            test_value_volt += test_steps[1][0];
            if (test_value_volt >= test_thresholds[1][0]) {
                volt_test_switch = 1;
            }
        break;
        case 1:
            test_value_volt += test_steps[1][1];
            if (test_value_volt <= test_thresholds[1][1]) {
                volt_test_switch = 2;
            }
        break;
        case 2:
            test_value_volt += test_steps[1][2];
            if (test_value_volt >= test_thresholds[1][2]) {
                volt_test_switch = 3;
            }
        break;
        case 3:
            test_value_volt += test_steps[1][3];
            if (test_value_volt <= test_thresholds[1][3]) {
                volt_test_switch = 0;
            }
        break;
    }
    return test_value_volt;
}

/**
 * Simulate oil temperature test cycle
 * Cycles through 4 phases: increase to 100, decrease to 110, increase to 140, decrease to 0.06
 * @return Current simulated oil temperature value
 */
double lv_temperature_test()
{
    switch (temperature_test_switch) {
        case 0:
            test_value_oil_temperature += test_steps[2][0];
            if (test_value_oil_temperature >= test_thresholds[2][0]) {
                temperature_test_switch = 1;
            }
        break;
        case 1:
            test_value_oil_temperature += test_steps[2][1];
            if (test_value_oil_temperature <= test_thresholds[2][1]) {
                temperature_test_switch = 2;
            }
        break;
        case 2:
            test_value_oil_temperature += test_steps[2][2];
            if (test_value_oil_temperature >= test_thresholds[2][2]) {
                temperature_test_switch = 3;
            }
        break;
        case 3:
            test_value_oil_temperature += test_steps[2][3];
            if (test_value_oil_temperature <= test_thresholds[2][3]) {
                temperature_test_switch = 0;
            }
        break;
    }
    return test_value_oil_temperature;
}

/**
 * Simulate outside temperature test cycle
 * Cycles through 4 phases: increase to 33, decrease to -15, increase to 20, decrease to 0.06
 * @return Current simulated outside temperature value
 */
double lv_Clocktemp_test()
{
    switch (Clocktemp_test_switch) {
        case 0:
            test_value_outside_temperature += test_steps[3][0];
            if (test_value_outside_temperature >= test_thresholds[3][0]) {
                Clocktemp_test_switch = 1;
            }
        break;
        case 1:
            test_value_outside_temperature += test_steps[3][1];
            if (test_value_outside_temperature <= test_thresholds[3][1]) {
                Clocktemp_test_switch = 2;
            }
        break;
        case 2:
            test_value_outside_temperature += test_steps[3][2];
            if (test_value_outside_temperature >= test_thresholds[3][2]) {
                Clocktemp_test_switch = 3;
            }
        break;
        case 3:
            test_value_outside_temperature += test_steps[3][3];
            if (test_value_outside_temperature <= test_thresholds[3][3]) {
                Clocktemp_test_switch = 0;
            }
        break;
    }
    return test_value_outside_temperature;
}

/**
 * Simulate brightness test cycle
 * Cycles through 4 phases with night mode toggle at the end
 */
void brightness_test() {

    switch (brightness_test_switch) {
        case 0:
            test_value_brightness += test_steps[4][0];
            if (test_value_brightness <= test_thresholds[4][0]) {
                brightness_test_switch = 1;
            }
        break;
        case 1:
            test_value_brightness += test_steps[4][1];
            if (test_value_brightness >= test_thresholds[4][1]) {
                brightness_test_switch = 2;
            }
        break;
        case 2:
            test_value_brightness += test_steps[4][2];
            if (test_value_brightness <= test_thresholds[4][2]) {
                brightness_test_switch = 3;
            }
        break;
        case 3:
            test_value_brightness += test_steps[4][3];
            if (test_value_brightness >= test_thresholds[4][3]) {
                brightness_test_switch = 0;
            }
        break;
    }
    if (test_value_brightness <= BRIGHTNESS_NIGHT_MAX) 
        test_night_mode_active = true;
    else test_night_mode_active = false;
}

/**
 * Get current brightness test value
 * @return Current simulated brightness value
 */
int getBrightnessTestValue() {return test_value_brightness;}

/**
 * Get current night mode test state
 * @return True if night mode is active in test
 */
bool getNightModeActiveTestValue() {return test_night_mode_active;}