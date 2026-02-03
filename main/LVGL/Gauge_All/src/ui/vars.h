#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_OIL_TEMPERATURE = 0,
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_VOLTAGE = 1,
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_CLOCK = 2,
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_TEMPERATURE = 3
};

// Native global variables

extern double get_var_lvgl_value_oil_pressure();
extern void set_var_lvgl_value_oil_pressure(double value);
extern int32_t get_var_lvgl_value_oil_temperature();
extern void set_var_lvgl_value_oil_temperature(int32_t value);
extern double get_var_lvgl_value_voltage();
extern void set_var_lvgl_value_voltage(double value);
extern const char *get_var_lvgl_value_clock();
extern void set_var_lvgl_value_clock(const char *value);
extern double get_var_lvgl_value_temperature();
extern void set_var_lvgl_value_temperature(double value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/