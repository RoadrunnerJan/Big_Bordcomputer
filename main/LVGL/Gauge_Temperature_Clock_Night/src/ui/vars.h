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
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_TEMPERATURE = 0,
    FLOW_GLOBAL_VARIABLE_LVGL_VALUE_CLOCK = 1
};

// Native global variables

extern double get_var_lvgl_value_temperature();
extern void set_var_lvgl_value_temperature(double value);
extern const char *get_var_lvgl_value_clock();
extern void set_var_lvgl_value_clock(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/