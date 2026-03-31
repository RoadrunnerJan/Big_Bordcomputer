#include "pwmSensor.h"

volatile sensor_data_t latest_sensor_values = {0};
uint32_t last_pos_edge = 0;
int pulse_idx = 0;
uint32_t period_us = 0;
uint32_t width = 0;

int first_init_done = 0;

inline int get_diag(int value_us) {
    return value_us < 280 ? 0 : // OPS Funktionszustand
           value_us < 440 ? 1 : // Druckausfall
           value_us < 600 ? 2 : // Temperaturausfall
           3;                   // Hardwareausfall
}

inline double calc_temperature(int value_us){ return ((double) value_us + PWM_SENSOR_TEMP_CALC_VALUE_1) / PWM_SENSOR_TEMP_CALC_VALUE_2; }
inline double calc_pressure(int value_us){ return ((double) value_us + PWM_SENSOR_PRES_CALC_VALUE_1) / PWM_SENSOR_PRES_CALC_VALUE_2; }

double get_value(int id)
{
    return id == PWM_SENSOR_TEMP_PULSE_ID ? calc_temperature(latest_sensor_values.temp_us.value_us) : 
           id == PWM_SENSOR_PRES_PULSE_ID ? calc_pressure(latest_sensor_values.press_us.value_us) :
           (double) get_diag(latest_sensor_values.diag_us.value_us);
}

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

void pwm_sensor_init(void){
    mcpwm_cap_timer_handle_t cap_timer = NULL;
    mcpwm_capture_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_CAPTURE_CLK_SRC_DEFAULT,
        .resolution_hz = PWM_SENSOR_RESOLUTION_MHZ*1000000, // 10 MHz
    };
    mcpwm_new_capture_timer(&timer_config, &cap_timer);

    // 2. Capture Channel erstellen
    mcpwm_cap_channel_handle_t cap_chan = NULL;
    mcpwm_capture_channel_config_t chan_config = {
        .gpio_num = PWM_SENSOR_PIN,
        .prescale = PWM_SENSOR_PRESCALE,
        .flags.neg_edge = PWM_SENSOR_NEG_EDGE, // Wir brauchen beide Flanken
        .flags.pos_edge = PWM_SENSOR_POS_EDGE,
        .flags.pull_up = PWM_SENSOR_PULL_UP,  // Je nach Signalquelle
        //.glitch_filter_config = {
        //    .max_glitch_width = 800, // Filtert Spikes kürzer als 10us (bei 80MHz)
        //},
    };
    mcpwm_new_capture_channel(cap_timer, &chan_config, &cap_chan);

    // 3. Callback registrieren (wird bei jeder Flanke aufgerufen)
    mcpwm_capture_event_callbacks_t cbs = {
        .on_cap = pwm_capture_callback,
    };
    mcpwm_capture_channel_register_event_callbacks(cap_chan, &cbs, NULL);

    mcpwm_capture_timer_enable(cap_timer);
    mcpwm_capture_timer_start(cap_timer);
    mcpwm_capture_channel_enable(cap_chan);

}

#if TESTMODE == true
    static void pwm_sensor_print(void *pv)
    {
        (void)pv;   
        uint32_t last_seen_count = 0;
        float f_temp = 0, f_press = 0;
        bool value_init_set = false;
        
        while (true) {
            // Prüfen, ob seit dem letzten Print neue Daten reinkamen
            if (latest_sensor_values.update_count != last_seen_count) {
                last_seen_count = latest_sensor_values.update_count;
                if (!value_init_set)
                {
                    f_temp = latest_sensor_values.temp_us.value_us;
                    f_press = latest_sensor_values.press_us.value_us;
                    value_init_set = true;
                }
                else {
                    f_temp = calc_filter(latest_sensor_values.temp_us.value_us, f_temp);
                    f_press = calc_filter(latest_sensor_values.press_us.value_us, f_press);
                }
                
                
                printf("AKTUELL -> Temp: %.0f°C | Temp f: %.0f°C | Temp: %luµs | Period: %luµs (Paket #%lu)\n", 
                        calc_temperature(latest_sensor_values.temp_us.value_us),
                        calc_temperature(f_temp),
                        latest_sensor_values.temp_us.value_us, 
                        latest_sensor_values.temp_us.period_us, 
                        last_seen_count);
                printf("AKTUELL -> Druck %.1fbar | Druck f %.1fbar | Druck: %luµs | Period: %luµs (Paket #%lu)\n", 
                        calc_pressure(latest_sensor_values.press_us.value_us),
                        calc_pressure(f_press),
                        latest_sensor_values.press_us.value_us, 
                        latest_sensor_values.press_us.period_us, 
                        last_seen_count);
                printf("AKTUELL -> Diag: %luµs | Period: %luµs (Paket #%lu)\n", 
                        latest_sensor_values.diag_us.value_us, 
                        latest_sensor_values.diag_us.period_us, 
                        last_seen_count);
            }
            else {
                printf("Warten auf Sensor-Signal...\n");
            }
            
            vTaskDelay(pdMS_TO_TICKS(200)); 
        }
    }

    void create_timer_pwm(void)
    {
        xTaskCreatePinnedToCore(pwm_sensor_print, "pwm_sensor_print", 8192, NULL, 15, NULL, 0);
    }

#else
    void create_timer_pwm(void) {} // Dummy-Funktion, damit der Aufruf in main.c nicht zu Kompilierungsfehlern führt
#endif