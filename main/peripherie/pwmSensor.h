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

extern mcpwm_cap_timer_handle_t cap_timer;
extern mcpwm_capture_timer_config_t timer_config;
extern mcpwm_cap_channel_handle_t cap_chan;
extern mcpwm_capture_channel_config_t chan_config;
extern mcpwm_capture_event_callbacks_t cbs;

extern volatile sensor_data_t latest_sensor_values;

extern uint32_t last_pos_edge;
extern int pulse_idx;
extern uint32_t period_us;
extern uint32_t width;

extern uint32_t last_seen_count;

extern int first_init_done;

void pwm_sensor_init();
void create_timer_pwm();

double get_pwm_value(int id);