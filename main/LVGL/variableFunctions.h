#pragma once

// lvgl variables and functions

#include <inttypes.h>
#include <string.h>

extern double lvgl_value_temperature;
extern char lvgl_value_clock[100];
extern double lvgl_value_oil_pressure;
extern int32_t lvgl_value_oil_temperature;
extern double lvgl_value_voltage;
extern int32_t lvgl_value_clock_hour;
extern int32_t lvgl_value_clock_minute;
extern char lvgl_value_temperature_string[100];
extern char lvgl_value_voltage_string[100];
extern char lvgl_value_oil_temperature_string[100];
extern char lvgl_value_oil_pressure_string[100];

extern const char *get_var_lvgl_value_oil_pressure_string() ;

extern void set_var_lvgl_value_oil_pressure_string(const char *value);

extern const char *get_var_lvgl_value_oil_temperature_string();

extern void set_var_lvgl_value_oil_temperature_string(const char *value) ;

extern const char *get_var_lvgl_value_voltage_string() ;

extern void set_var_lvgl_value_voltage_string(const char *value) ;

extern const char *get_var_lvgl_value_temperature_string() ;

extern void set_var_lvgl_value_temperature_string(const char *value);

extern double get_var_lvgl_value_voltage();

extern void set_var_lvgl_value_voltage(double value) ;

extern int32_t get_var_lvgl_value_oil_temperature() ;

extern void set_var_lvgl_value_oil_temperature(int32_t value);

extern double get_var_lvgl_value_oil_pressure() ;

extern void set_var_lvgl_value_oil_pressure(double value);

extern double get_var_lvgl_value_temperature() ;

extern void set_var_lvgl_value_temperature(double value) ;

extern const char *get_var_lvgl_value_clock() ;

extern void set_var_lvgl_value_clock(const char *value) ;

extern int32_t get_var_lvgl_value_clock_hour();

extern void set_var_lvgl_value_clock_hour(int32_t value) ;

extern int32_t get_var_lvgl_value_clock_minute();

extern void set_var_lvgl_value_clock_minute(int32_t value) ;