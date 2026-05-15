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
    /* oil pressure      */ {+0.10, -0.02, +0.35, -0.25},
    /* volt              */ {+0.20, -0.10, +0.10, -0.15},
    /* oil temperature   */ {+0.20, -0.20, +0.20, -0.20},
    /* clock temperature */ {+0.20, -0.20, +0.20, -0.20},
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
 * Cycles through four predefined pressure phases:
 * 1. Increase from current value to MAX (4.5 bar)
 * 2. Decrease to MIN (2.5 bar)
 * 3. Increase to MAX+ (5.5 bar)
 * 4. Decrease to near MIN (0.04 bar)
 * Then repeats from phase 1.
 *
 * @return Current simulated oil pressure in bar
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
 * @brief Simulate voltage test cycle.
 *
 * Cycles through four predefined voltage phases:
 * 1. Increase from current value to MAX (15.5 V)
 * 2. Decrease to MIN (11 V)
 * 3. Increase to MID (14 V)
 * 4. Decrease to near MIN (8.04 V)
 * Then repeats from phase 1.
 *
 * @return Current simulated voltage in volts
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
 * @brief Simulate oil temperature test cycle.
 *
 * Cycles through four predefined temperature phases:
 * 1. Increase from current value to MAX (100°C)
 * 2. Decrease to MIN (110°C, note reverse range)
 * 3. Increase to MAX+ (140°C)
 * 4. Decrease to near MIN (0.06°C)
 * Then repeats from phase 1.
 *
 * @return Current simulated oil temperature in °C
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
 * @brief Simulate outdoor temperature test cycle.
 *
 * Cycles through four predefined temperature phases:
 * 1. Increase from current value to MAX (33°C)
 * 2. Decrease to MIN (-15°C)
 * 3. Increase to MID (20°C)
 * 4. Decrease to near MIN (0.06°C)
 * Then repeats from phase 1.
 *
 * @return Current simulated outdoor temperature in °C
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
 * @brief Run brightness test sequence with night mode transitions.
 *
 * Cycles brightness through four phases:
 * 1. Decrease from current value to night minimum
 * 2. Increase to day maximum
 * 3. Decrease to night minimum again
 * 4. Increase to day maximum
 * Then repeats from phase 1.
 *
 * Automatically toggles night mode based on brightness level:
 * - Night mode enabled when brightness <= BRIGHTNESS_NIGHT_MAX
 * - Night mode disabled when brightness > BRIGHTNESS_NIGHT_MAX
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