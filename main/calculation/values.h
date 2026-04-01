#pragma once
#include "../individual_config.h"
#include "../lvgl/src/ui/screens.h"
#include "esp_system.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

extern bool pres_value_set;
extern bool temp_value_set;
extern bool volt_value_set;
extern bool outside_temperature_set;

extern double value_oil_pressure;
extern double value_oil_temperature;
extern double value_volt;
extern double value_outside_temperature;
extern int value_brightness;
extern bool night_mode_active;

extern char output_string[20];

inline double calc_filter(double new_value_us, double pre_value_us) {
    return (new_value_us * PWM_SENSOR_FILTER_ALPHA) + (pre_value_us * (1.0f - PWM_SENSOR_FILTER_ALPHA));
};

void reset_values(int screenSelection);
void reset_brightness();
void calculate_value(int screenSelection, double new_value);
double get_value_by_screen_id(int screenSelection);
void calcBrightness(float value);
char* get_output_string();
int getBrightness();
bool getNightModeActive();

