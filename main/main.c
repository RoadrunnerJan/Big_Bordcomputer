
// . $HOME/tools/esp/esp-idf/export.sh
// allgemein . $HOME/esp/esp-idf/export.sh

#include "includes.h"
#include "individual_config.h"

#if USE_BUZZER == true
    #include "peripherie/buzzer.h"
#endif

#if TESTMODE == true
    #include "simulation/testSimulation.h"
    
#else
    static bool pres_value_set = false;
    static bool temp_value_set = false;
#endif

static double oil_pressure_value = 0.0;
static double oil_temperature_value = 0.0;
static double volt_value = 8.0;
static double Clocktemp_value = 0.0;

static int brightness_value = 100;
static int night_mode = 0;

static time_t now;
static struct tm timeinfo;

time_t StartUpTime = 0;
time_t checkTime = 0;
bool time_checked[2] = {false, false}; // [0] = Gauge, [1] = Beeper

#if USE_BUZZER == true
    static int beeped = 0;

    static void temperature_beep() {
        buzzer_beep(BEEPER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));
        buzzer_beep(BEEPER_QUIET_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_OFF_TIME));
        buzzer_beep(BEEPER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));
        buzzer_beep(BEEPER_QUIET_VALUE);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);

        printf("Beeped!\n");

        vTaskDelete(NULL);         
    }
#endif

static void tick_switch(int id)
{
    char ziel_string[20];

    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            #if TESTMODE == true
                lv_pressure_test(&oil_pressure_value);
            #else
                #if USE_PWM_SENSOR == true
                    if (!pres_value_set) {
                        oil_pressure_value = get_value(PWM_SENSOR_PRES_PULSE_ID);
                        pres_value_set = true;
                    }
                    else {
                        oil_pressure_value = calc_filter(get_value(PWM_SENSOR_PRES_PULSE_ID), oil_pressure_value);
                    }
                #else
                    oil_pressure_value = get_i2c_adc_oil_press();
                #endif
                if (oil_pressure_value < 0) {
                    oil_pressure_value = 0;
                }

            #endif
            snprintf(ziel_string, sizeof(ziel_string), "%.1f", oil_pressure_value);
            set_var_lvgl_value_oil_pressure(oil_pressure_value * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_pressure_string(ziel_string);

            if(!night_mode)
            {
                if (lv_scr_act() != objects.gauge_oil_pressure) 
                {
                    lv_scr_load_anim(objects.gauge_oil_pressure, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_oil_pressure();
            }
            else
            {
                if (lv_scr_act() != objects.gauge_oil_pressure_night) 
                {
                    lv_scr_load_anim(objects.gauge_oil_pressure_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_oil_pressure_night();
            }
            lv_timer_handler();
        break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            #if TESTMODE == true
                lv_temperature_test(&oil_temperature_value);
            #else
                #if USE_PWM_SENSOR == true
                    if (!temp_value_set) {
                        oil_temperature_value = get_value(PWM_SENSOR_TEMP_PULSE_ID);
                        temp_value_set = true;
                    }
                    else {
                        oil_temperature_value = calc_filter(get_value(PWM_SENSOR_TEMP_PULSE_ID), oil_temperature_value);
                    }
                #else
                    oil_temperature_value = get_i2c_adc_oil_temp();
                #endif
                if (oil_temperature_value < 0) {
                    oil_temperature_value = 0;
                }
            #endif

            snprintf(ziel_string, sizeof(ziel_string), "%d", (int)oil_temperature_value);
            set_var_lvgl_value_oil_temperature(oil_temperature_value < 0 ? 0 : oil_temperature_value * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_temperature_string(ziel_string); 

            if(!night_mode)
            {
                if (lv_scr_act() != objects.gauge_oil_temperature) 
                {
                    lv_scr_load_anim(objects.gauge_oil_temperature, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_oil_temperature();
            }
            else
            {
                if (lv_scr_act() != objects.gauge_oil_temperature_night) 
                {
                    lv_scr_load_anim(objects.gauge_oil_temperature_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_oil_temperature_night();
            }
            lv_timer_handler();
        break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            #if TESTMODE == true
                lv_volt_test(&volt_value);
            #else
                volt_value = get_i2c_adc_volt();
                if (volt_value < 8) {
                    volt_value = 0;
                }
            #endif
            snprintf(ziel_string, sizeof(ziel_string), "%.1f", volt_value);
            set_var_lvgl_value_voltage(volt_value * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_voltage_string(ziel_string);

            if(!night_mode)
            {
                if (lv_scr_act() != objects.gauge_voltage) 
                {
                    lv_scr_load_anim(objects.gauge_voltage, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_voltage();
            }
            else
            {
                if (lv_scr_act() != objects.gauge_voltage_night) 
                {
                    lv_scr_load_anim(objects.gauge_voltage_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_voltage_night();
            }
            lv_timer_handler();
        break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
            #if TESTMODE == true
                lv_Clocktemp_test(&Clocktemp_value);
            #else
                Clocktemp_value = get_i2c_adc_outside_temp();
                if (Clocktemp_value < -30) {
                    Clocktemp_value = -30;
                }
                if (Clocktemp_value > 70) {
                    Clocktemp_value = 70;
                }
            #endif
 
            time(&now);
            localtime_r(&now, &timeinfo);
            snprintf(ziel_string, sizeof(ziel_string), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
            set_var_lvgl_value_temperature(Clocktemp_value * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_clock(ziel_string); 

            if(!night_mode)
            {
                if (lv_scr_act() != objects.gauge_temperature_clock) 
                {
                    lv_scr_load_anim(objects.gauge_temperature_clock, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_temperature_clock();
            }
            else
            {
                if (lv_scr_act() != objects.gauge_temperature_clock_night) 
                {
                    lv_scr_load_anim(objects.gauge_temperature_clock_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_temperature_clock_night();
            }
            lv_timer_handler();
        break;
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            #if TESTMODE == true
                lv_Clocktemp_test(&Clocktemp_value);
            #else
                Clocktemp_value = get_i2c_adc_outside_temp();
                if (Clocktemp_value < -30) {
                    Clocktemp_value = -30;
                }
                if (Clocktemp_value > 70) {
                    Clocktemp_value = 70;
                }
            #endif

            time(&now);
            localtime_r(&now, &timeinfo);
            int hour = timeinfo.tm_hour >= 12 ? timeinfo.tm_hour - 12 : timeinfo.tm_hour;
            set_var_lvgl_value_clock_hour(hour * 50 + ((timeinfo.tm_min*10)/12));
            set_var_lvgl_value_clock_minute(timeinfo.tm_min);

            // temperature Value
            if (Clocktemp_value > -10 && Clocktemp_value < 10)
            {
                if ((Clocktemp_value*10 - ((int)Clocktemp_value )*10) >= 5 )
                    snprintf(ziel_string, sizeof(ziel_string), "%d.5", (int) Clocktemp_value);
                else
                    snprintf(ziel_string, sizeof(ziel_string), "%d.0", (int) Clocktemp_value);
            }
            else
            {
                snprintf(ziel_string, sizeof(ziel_string), "%d", (int)Clocktemp_value);
            }
            
            set_var_lvgl_value_temperature_string(ziel_string);
            if(!night_mode)
            {
                if (lv_scr_act() != objects.gauge_clock_temperature) 
                {
                    lv_scr_load_anim(objects.gauge_clock_temperature, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_clock_temperature();
            }
            else
            {
                if (lv_scr_act() != objects.gauge_clock_temperature_night) 
                {
                    lv_scr_load_anim(objects.gauge_clock_temperature_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                tick_screen_gauge_clock_temperature_night();
            }
            lv_timer_handler(); 
        break;
    }
}

static void lv_tick_task_screen(void *pv)
{
    (void)pv;
    while (1) {
        if (!time_checked[0]) {
            time(&checkTime);
        }
        #if TESTMODE == true 
            brightness_test(&brightness_value, &night_mode);
        #else 
            float adc_brightness = get_i2c_adc_volt_bel(); // 1-10.74V entsprechen 0-80% Helligkeit, 0 entspricht 100%
            //adc_brightness = 10.74;
            if (adc_brightness < 1) 
            {
                brightness_value = BRIGHTNESS_DAY;
                night_mode = 0;
            }
            else {
                night_mode = 1;
                brightness_value = (adc_brightness - BRIGHTNESS_NIGHT_MIN_V) / (BRIGHTNESS_NIGHT_MAX_V - BRIGHTNESS_NIGHT_MIN_V) * BRIGHTNESS_NIGHT_MAX;
                if (brightness_value > BRIGHTNESS_NIGHT_MAX) brightness_value = BRIGHTNESS_NIGHT_MAX;
                if (brightness_value < BRIGHTNESS_NIGHT_MIN) brightness_value = BRIGHTNESS_NIGHT_MIN;
            }
        #endif

        if ((long)(checkTime - StartUpTime) > GAUGE_ON_DELAY_SEC)
        {
            if (!time_checked[0]) {
                time_checked[0] = !time_checked[0];
            }
            set_lcd_brightness(brightness_value); 
        }

        for (int i = 0; i < NUMBER_OF_DISPLAYS; i++){
            if (lv_disp_get_scr_act(DISPLAYS[i].lv_displays) != NULL) {
                lv_disp_set_default(DISPLAYS[i].lv_displays);
                tick_switch(DISPLAYS[i].screen_selection);
            }
        }

        #if USE_BUZZER == true
            if !(time_checked[1]) {
                time(&checkTime);
            }
            if ((long)(checkTime - StartUpTime) >= BEEPER_ON_DELAY_SEC)
            {
                if (!time_checked[1]) {
                    time_checked[1] = !time_checked[1];
                }
                if (beeped == false && Clocktemp_value < BEEPER_TEMP_MIN)
                {
                    xTaskCreatePinnedToCore(temperature_beep, "temperature_beep", BEEPER_TASK_STEPDEPTH, NULL, BEEPER_TASK_PRIORITY, NULL, BEEPER_TASK_CORE);
                    beeped = true;
                }
            }
        #endif

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void app_main(void)
{
    init_lcd_backlight_pwm();
    
    // init rtc
    init_i2c();
    sync_rtc_to_system();
    
    time(&StartUpTime);
    printf("System started at: %ld\n", (long)StartUpTime);

    init_time_buttons();

    spi_init();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialisiert die LVGL-Puffer und LVGL-Treiberfür alle Displays
    timer_start(); // Startet die Timer für alle Displays 
    set_Displays();

    //vTaskDelay(pdMS_TO_TICKS(DISPLAY_SETUP_DELAY));
    pwm_sensor_init();
    #if USE_PWM_SENSOR == true
        create_timer_pwm();
    #endif

    #if USE_BUZZER == true
        beeped = false;
        beeper_init();
    #endif

    // Anfangs Licht aus! in Funktion beachten
    xTaskCreatePinnedToCore(lv_tick_task_screen, "lv_tick_task_screen", DISPLAYS[0].task_step_depth, NULL, DISPLAYS[0].task_priority, NULL, DISPLAYS[0].tast_core);

    vTaskDelay(pdMS_TO_TICKS(MAIN_TASK_FINISHED_DELAY));

}
