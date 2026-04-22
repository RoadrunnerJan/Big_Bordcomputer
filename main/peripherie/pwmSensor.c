/**
 * @file pwmSensor.c
 * @brief PWM sensor reader Hella 6PP 010 378-201 oil sensor implementation.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - MCPWM capture for PWM signal decoding
 *      - Multi-pulse sensor support (temperature, pressure, diagnostic)
 *      - Hella 6PP 010 378-201 sensor integration
 *      - Test mode with serial output
 */

#include "pwmSensor.h"


mcpwm_cap_timer_handle_t cap_timer = NULL;
mcpwm_capture_timer_config_t timer_config = {0};
mcpwm_cap_channel_handle_t cap_chan = NULL;
mcpwm_capture_channel_config_t chan_config = {0};
mcpwm_capture_event_callbacks_t cbs = {0};

volatile sensor_data_t latest_sensor_values = {0};
uint32_t last_pos_edge = 0;
int pulse_idx = 0;
uint32_t period_us = 0;
uint32_t width = 0;

uint32_t last_seen_count = 0;

int first_init_done = 0;

inline int get_diag(int value_us) {
    return value_us < 280 ? 0 : // OPS functional state
           value_us < 440 ? 1 : // Pressure failure
           value_us < 600 ? 2 : // Temperature failure
           3;                   // Hardware failure
}

inline double calc_temperature(int value_us){ return ((double) value_us + PWM_SENSOR_TEMP_CALC_VALUE_1) / PWM_SENSOR_TEMP_CALC_VALUE_2; }
inline double calc_pressure(int value_us){ return ((double) value_us + PWM_SENSOR_PRES_CALC_VALUE_1) / PWM_SENSOR_PRES_CALC_VALUE_2; }

/**
 * @brief Get the last decoded PWM value for a sensor by ID.
 *
 * Retrieves the calculated sensor value (temperature, pressure, or diagnostic code)
 * for the specified sensor ID. Returns -99 if value hasn't been updated.
 *
 * @param id PWM sensor ID (PWM_SENSOR_TEMP_PULSE_ID, PWM_SENSOR_PRES_PULSE_ID, or PWM_SENSOR_DIAG_PULSE_ID)
 * @return Calculated sensor value, or -99 if value not updated
 */
double get_pwm_value(int id)
{
    if (latest_sensor_values.update_count == last_seen_count) return -99;
    else {
        last_seen_count = latest_sensor_values.update_count;
        return id == PWM_SENSOR_TEMP_PULSE_ID ? calc_temperature(latest_sensor_values.temp_us.value_us) : 
            id == PWM_SENSOR_PRES_PULSE_ID ? calc_pressure(latest_sensor_values.press_us.value_us) :
            (double) get_diag(latest_sensor_values.diag_us.value_us);
    }
}

/**
 * @brief MCPWM capture callback reacting on rising/falling edges.
 *
 * Parses pulse width and period into sensor data buckets and tracks sequence state.
 * Called by MCPWM driver on each edge detection event.
 */
static bool IRAM_ATTR pwm_capture_callback(mcpwm_cap_channel_handle_t cap_chan, const mcpwm_capture_event_data_t *edata, void *user_data)
{
    if (edata->cap_edge == MCPWM_CAP_EDGE_POS) {
        period_us = (edata->cap_value - last_pos_edge) / PWM_SENSOR_RESOLUTION_MHZ; // 10 wenn 10 MHz

        if (period_us > PWM_SENSOR_DIAG_PERIOD_MIN && period_us < PWM_SENSOR_DIAG_PERIOD_MAX)
        {
            pulse_idx = PWM_SENSOR_DIAG_PULSE_ID;
            first_init_done = 1;
        }
        if (first_init_done)
        {
            if (   pulse_idx == PWM_SENSOR_DIAG_PULSE_ID
                && period_us > PWM_SENSOR_DIAG_PERIOD_MIN
                && period_us < PWM_SENSOR_DIAG_PERIOD_MAX
                && width > PWM_SENSOR_DIAG_VALUE_MIN
                && width < PWM_SENSOR_DIAG_VALUE_MAX
            ) {
                latest_sensor_values.diag_us.value_us = width;
                latest_sensor_values.diag_us.period_us = period_us;
            }
            else if (   pulse_idx == PWM_SENSOR_TEMP_PULSE_ID
                     && period_us > PWM_SENSOR_TEMP_PERIOD_MIN 
                     && period_us < PWM_SENSOR_TEMP_PERIOD_MAX
                     && width > PWM_SENSOR_TEMP_VALUE_MIN
                     && width < PWM_SENSOR_TEMP_VALUE_MAX
            ) {
                latest_sensor_values.temp_us.value_us = width;
                latest_sensor_values.temp_us.period_us = period_us;
            }
            else if (   pulse_idx == PWM_SENSOR_PRES_PULSE_ID
                     && period_us > PWM_SENSOR_PRES_PERIOD_MIN
                     && period_us < PWM_SENSOR_PRES_PERIOD_MAX
                     && width > PWM_SENSOR_PRES_VALUE_MIN
                     && width < PWM_SENSOR_PRES_VALUE_MAX
                ) {
                latest_sensor_values.press_us.value_us = width;
                latest_sensor_values.press_us.period_us = period_us;
                latest_sensor_values.update_count++;
                if(latest_sensor_values.update_count > PWM_SENSOR_MAX_SENSOR_COUNT)
                    latest_sensor_values.update_count = 0;
            }
            pulse_idx = (pulse_idx + 1) % 3;
        }
        
        last_pos_edge = edata->cap_value;
    } else {
        width = (edata->cap_value - last_pos_edge) / PWM_SENSOR_RESOLUTION_MHZ; // 10 wenn 10 MHz
    }
    return false;
}

/**
 * Initialize PWM sensor capture on configured GPIO pin.
 *
 * Sets up MCPWM capture timer/channel with edge callbacks and starts capture.
 */
void pwm_sensor_init(void){
    timer_config.group_id = 0;
    timer_config.clk_src = MCPWM_CAPTURE_CLK_SRC_DEFAULT;
    timer_config.resolution_hz = PWM_SENSOR_RESOLUTION_MHZ*1000000; // 10 MHz
    chan_config.gpio_num = PWM_SENSOR_PIN;
    chan_config.prescale = PWM_SENSOR_PRESCALE;
    chan_config.flags.neg_edge = PWM_SENSOR_NEG_EDGE;
    chan_config.flags.pos_edge = PWM_SENSOR_POS_EDGE;
    chan_config.flags.pull_up = PWM_SENSOR_PULL_UP;
    //chan_config.glitch_filter_config.max_glitch_width = 800; // Filtert Spikes kürzer als 10us (bei 80MHz)
    cbs.on_cap = pwm_capture_callback;

    mcpwm_new_capture_timer(&timer_config, &cap_timer);
    mcpwm_new_capture_channel(cap_timer, &chan_config, &cap_chan);
    mcpwm_capture_channel_register_event_callbacks(cap_chan, &cbs, NULL);

    mcpwm_capture_timer_enable(cap_timer);
    mcpwm_capture_timer_start(cap_timer);
    mcpwm_capture_channel_enable(cap_chan);
}

/**
 * Print last read PWM sensor values for debugging.
 */
void pwm_sensor_print(void)
{
    // Check if new data has arrived since last print
    if (latest_sensor_values.update_count != last_seen_count) {
        last_seen_count = latest_sensor_values.update_count;
        char log_msg[100];
        
        snprintf(log_msg, sizeof(log_msg), "AKTUELL -> Temp: %.0f°C | Temp: %luµs | Period: %luµs (Paket #%lu)", 
                calc_temperature(latest_sensor_values.temp_us.value_us),
                latest_sensor_values.temp_us.value_us, 
                latest_sensor_values.temp_us.period_us, 
                last_seen_count);
        printLog(log_msg);
        snprintf(log_msg, sizeof(log_msg), "AKTUELL -> Druck %.1fbar | Druck: %luµs | Period: %luµs (Paket #%lu)", 
                calc_pressure(latest_sensor_values.press_us.value_us),
                latest_sensor_values.press_us.value_us, 
                latest_sensor_values.press_us.period_us, 
                last_seen_count);
        printLog(log_msg);
        snprintf(log_msg, sizeof(log_msg), "AKTUELL -> Diag: %luµs | Period: %luµs (Paket #%lu)", 
                latest_sensor_values.diag_us.value_us, 
                latest_sensor_values.diag_us.period_us, 
                last_seen_count);
        printLog(log_msg);
    }
    else {
        printLog("Waiting for sensor signal...");
    }
}