#include "testSimulation.h"

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
    /* brightness        */ { 15,  50,   2,  100} 
};

void reset_test_switches() {
    pressure_test_switch    = 0;
    temperature_test_switch = 0;
    volt_test_switch        = 0;
    Clocktemp_test_switch   = 0;
    brightness_test_switch  = 0;
}

void lv_pressure_test(double* oil_pressure_value)
{
    switch (pressure_test_switch) {
        case 0:
            *oil_pressure_value += test_steps[0][0];
            if (*oil_pressure_value >= test_thresholds[0][0]) {
                pressure_test_switch = 1;
            }
        break;
        case 1:
            *oil_pressure_value += test_steps[0][1];
            if (*oil_pressure_value <= test_thresholds[0][1]) {
                pressure_test_switch = 2;
            }
        break;
        case 2:
            *oil_pressure_value += test_steps[0][2];
            if (*oil_pressure_value >= test_thresholds[0][2]) {
                pressure_test_switch = 3;
            }
        break;
        case 3:
            *oil_pressure_value += test_steps[0][3];
            if (*oil_pressure_value <= test_thresholds[0][3]) {
                pressure_test_switch = 0;
            }
        break;
    }
}

void lv_volt_test(double* volt_value)
{
    switch (volt_test_switch) {
        case 0:
            *volt_value += test_steps[1][0];
            if (*volt_value >= test_thresholds[1][0]) {
                volt_test_switch = 1;
            }
        break;
        case 1:
            *volt_value += test_steps[1][1];
            if (*volt_value <= test_thresholds[1][1]) {
                volt_test_switch = 2;
            }
        break;
        case 2:
            *volt_value += test_steps[1][2];
            if (*volt_value >= test_thresholds[1][2]) {
                volt_test_switch = 3;
            }
        break;
        case 3:
            *volt_value += test_steps[1][3];
            if (*volt_value <= test_thresholds[1][3]) {
                volt_test_switch = 0;
            }
        break;
    }
}

void lv_temperature_test(double* oil_temperature_value)
{
    switch (temperature_test_switch) {
        case 0:
            *oil_temperature_value += test_steps[2][0];
            if (*oil_temperature_value >= test_thresholds[2][0]) {
                temperature_test_switch = 1;
            }
        break;
        case 1:
            *oil_temperature_value += test_steps[2][1];
            if (*oil_temperature_value <= test_thresholds[2][1]) {
                temperature_test_switch = 2;
            }
        break;
        case 2:
            *oil_temperature_value += test_steps[2][2];
            if (*oil_temperature_value >= test_thresholds[2][2]) {
                temperature_test_switch = 3;
            }
        break;
        case 3:
            *oil_temperature_value += test_steps[2][3];
            if (*oil_temperature_value <= test_thresholds[2][3]) {
                temperature_test_switch = 0;
            }
        break;
    }
}

void lv_Clocktemp_test(double* Clocktemp_value)
{
    switch (Clocktemp_test_switch) {
        case 0:
            *Clocktemp_value += test_steps[3][0];
            if (*Clocktemp_value >= test_thresholds[3][0]) {
                Clocktemp_test_switch = 1;
            }
        break;
        case 1:
            *Clocktemp_value += test_steps[3][1];
            if (*Clocktemp_value <= test_thresholds[3][1]) {
                Clocktemp_test_switch = 2;
            }
        break;
        case 2:
            *Clocktemp_value += test_steps[3][2];
            if (*Clocktemp_value >= test_thresholds[3][2]) {
                Clocktemp_test_switch = 3;
            }
        break;
        case 3:
            *Clocktemp_value += test_steps[3][3];
            if (*Clocktemp_value <= test_thresholds[3][3]) {
                Clocktemp_test_switch = 0;
            }
        break;
    }
}

void brightness_test(int* brightness_value, bool* night_mode_active) {
    
    switch (brightness_test_switch) {
        case 0:
            *brightness_value += test_steps[4][0];
            if (*brightness_value <= test_thresholds[4][0]) {
                brightness_test_switch = 1;
            }
        break;
        case 1:
            *brightness_value += test_steps[4][1];
            if (*brightness_value >= test_thresholds[4][1]) {
                brightness_test_switch = 2;
            }
        break;
        case 2:
            *brightness_value += test_steps[4][2];
            if (*brightness_value <= test_thresholds[4][2]) {
                brightness_test_switch = 3;
            }
        break;
        case 3:
            *brightness_value += test_steps[4][3];
            if (*brightness_value >= test_thresholds[4][3]) {
                brightness_test_switch = 0;
                *night_mode_active = !(*night_mode_active);
            }
        break;
    }
}