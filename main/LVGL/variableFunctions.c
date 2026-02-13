
#include <inttypes.h>
#include <string.h>


double lvgl_value_temperature= 0.0;
char lvgl_value_clock[100] = { 0 };
double lvgl_value_oil_pressure=0.0;
int32_t lvgl_value_oil_temperature=0;
double lvgl_value_voltage=8.0;
int32_t lvgl_value_clock_hour=0;
int32_t lvgl_value_clock_minute=0;
char lvgl_value_temperature_string[100] = { 0 };
char lvgl_value_voltage_string[100] = { 0 };
char lvgl_value_oil_temperature_string[100] = { 0 };
char lvgl_value_oil_pressure_string[100] = { 0 };

const char *get_var_lvgl_value_oil_pressure_string() {
    return lvgl_value_oil_pressure_string;
}

void set_var_lvgl_value_oil_pressure_string(const char *value) {
    strncpy(lvgl_value_oil_pressure_string, value, sizeof(lvgl_value_oil_pressure_string) / sizeof(char));
    lvgl_value_oil_pressure_string[sizeof(lvgl_value_oil_pressure_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_oil_temperature_string() {
    return lvgl_value_oil_temperature_string;
}

void set_var_lvgl_value_oil_temperature_string(const char *value) {
    strncpy(lvgl_value_oil_temperature_string, value, sizeof(lvgl_value_oil_temperature_string) / sizeof(char));
    lvgl_value_oil_temperature_string[sizeof(lvgl_value_oil_temperature_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_voltage_string() {
    return lvgl_value_voltage_string;
}

void set_var_lvgl_value_voltage_string(const char *value) {
    strncpy(lvgl_value_voltage_string, value, sizeof(lvgl_value_voltage_string) / sizeof(char));
    lvgl_value_voltage_string[sizeof(lvgl_value_voltage_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_temperature_string() {
    return lvgl_value_temperature_string;
}

void set_var_lvgl_value_temperature_string(const char *value) {
    strncpy(lvgl_value_temperature_string, value, sizeof(lvgl_value_temperature_string) / sizeof(char));
    lvgl_value_temperature_string[sizeof(lvgl_value_temperature_string) / sizeof(char) - 1] = 0;
}


double get_var_lvgl_value_voltage() {
    return lvgl_value_voltage;
}

void set_var_lvgl_value_voltage(double value) {
    lvgl_value_voltage = value;
}

int32_t get_var_lvgl_value_oil_temperature() {
    return lvgl_value_oil_temperature;
}

void set_var_lvgl_value_oil_temperature(int32_t value) {
    lvgl_value_oil_temperature = value;
}

double get_var_lvgl_value_oil_pressure() {
    return lvgl_value_oil_pressure;
}

void set_var_lvgl_value_oil_pressure(double value) {
    lvgl_value_oil_pressure = value;
}


double get_var_lvgl_value_temperature() {
    return lvgl_value_temperature;
}

void set_var_lvgl_value_temperature(double value) {
    lvgl_value_temperature = value;
}

const char *get_var_lvgl_value_clock() {
    return lvgl_value_clock;
}

void set_var_lvgl_value_clock(const char *value) {
    strncpy(lvgl_value_clock, value, sizeof(lvgl_value_clock) / sizeof(char));
    lvgl_value_clock[sizeof(lvgl_value_clock) / sizeof(char) - 1] = 0;
}

int32_t get_var_lvgl_value_clock_hour() {
    return lvgl_value_clock_hour;
}

void set_var_lvgl_value_clock_hour(int32_t value) {
    lvgl_value_clock_hour = value;
}

int32_t get_var_lvgl_value_clock_minute() {
    return lvgl_value_clock_minute;
}

void set_var_lvgl_value_clock_minute(int32_t value) {
    lvgl_value_clock_minute = value;
}