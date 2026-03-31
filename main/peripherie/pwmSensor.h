#pragma once
#include "../individual_config.h"
#include "driver/mcpwm_cap.h"
#include "esp_system.h"
#include <inttypes.h>
#if TESTMODE == true
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
#endif

typedef struct {
    uint32_t period_us;
    uint32_t value_us;
} value_pair_t;

typedef struct {
    value_pair_t temp_us;
    value_pair_t press_us;
    value_pair_t diag_us;
    uint32_t update_count; 
} sensor_data_t;

extern volatile sensor_data_t latest_sensor_values;
extern uint32_t last_pos_edge;
extern int pulse_idx;
extern uint32_t period_us;
extern uint32_t width;

extern int first_init_done;



void pwm_sensor_init();
void create_timer_pwm();

inline double calc_filter(double new_value_us, double pre_value_us) { return (new_value_us * PWM_SENSOR_FILTER_ALPHA) + (pre_value_us * (1.0f - PWM_SENSOR_FILTER_ALPHA)); };
double get_value(int id);