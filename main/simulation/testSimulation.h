#pragma once
#include "esp_system.h"

extern double test_value_oil_pressure;
extern double test_value_oil_temperature;
extern double test_value_volt;
extern double test_value_outside_temperature;
extern int test_value_brightness;
extern bool test_night_mode_active;

extern int pressure_test_switch;
extern int temperature_test_switch;
extern int volt_test_switch;
extern int Clocktemp_test_switch;
extern int brightness_test_switch;

extern double test_steps[5][4];
extern double test_thresholds[5][4];

void reset_test_switches();
double lv_pressure_test();
double lv_volt_test();
double lv_temperature_test();
double lv_Clocktemp_test();
void brightness_test();

int getBrightnessTestValue();
bool getNightModeActiveTestValue();