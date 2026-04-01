#include "testSimulation.h"

double test_value_oil_pressure = 0.0;
double test_value_oil_temperature = 0.0;
double test_value_volt = 8.0;
double test_value_outside_temperature = 0.0;
int test_value_brightness = 0;
bool test_night_mode_active = false;

int pressure_test_switch = 0;
int temperature_test_switch = 0;
int volt_test_switch = 0;
int Clocktemp_test_switch = 0;
int brightness_test_switch = 0;

double test_steps[5][4] = { // step changes for each test phase
    /* oil pressure      */ {+0.06, -0.02, +0.06, -0.06},
    /* volt              */ {+0.50, -0.05, +0.05, -0.50},
    /* oil temperature   */ {+0.30, -0.30, +0.30, -0.30},
    /* clock temperature */ {+0.30, -0.30, +0.30, -0.30},
    /* brightness        */ {-1.00, +1.00, -1.00, +1.00}
};

double test_thresholds[5][4] = { // thresholds for switching test steps
    //                        >=   <=   >=    <=
    /* oil pressure      */ {4.5, 2.5, 5.5, 0.04},

    //                        >=   <=   >=    <=
    /* volt              */ {15.5, 11,  14, 8.04},

    //                        >=   <=   >=    <=
    /* oil temperature   */ {100, 110, 140, 0.06},

    //                        >=   <=   >=    <=
    /* clock temperature */ { 33, -15,  20, 0.06},

    //                        <=   >=   <=    >=
    /* brightness        */ {  2,  40,   2,  80} 
};

void reset_test_values() {
    test_value_oil_pressure = 0.0;
    test_value_oil_temperature = 0.0;
    test_value_volt = 8.0;
    test_value_outside_temperature = 0.0;
    test_value_brightness = 0;
    test_night_mode_active = false;
}

void reset_test_switches() {
    pressure_test_switch    = 0;
    temperature_test_switch = 0;
    volt_test_switch        = 0;
    Clocktemp_test_switch   = 0;
    brightness_test_switch  = 0;
}

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
                test_night_mode_active = !(test_night_mode_active);
            }
        break;
    }
}

int getBrightnessTestValue() {return test_value_brightness;}
bool getNightModeActiveTestValue() {return test_night_mode_active;}