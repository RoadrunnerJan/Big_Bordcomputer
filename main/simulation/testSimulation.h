#pragma once
#include "esp_system.h"

extern int pressure_test_switch;
extern int temperature_test_switch;
extern int volt_test_switch;
extern int Clocktemp_test_switch;
extern int brightness_test_switch;

extern double test_steps[5][4];
extern double test_thresholds[5][4];

void reset_test_switches();
void lv_pressure_test(double* oil_pressure_value);
void lv_volt_test(double* volt_value);
void lv_temperature_test(double* oil_temperature_value);
void lv_Clocktemp_test(double* Clocktemp_value);
void brightness_test(int* brightness_value, bool* night_mode_active);