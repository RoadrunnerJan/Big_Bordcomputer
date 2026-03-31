
// . $HOME/tools/esp/esp-idf/export.sh
// allgemein . $HOME/esp/esp-idf/export.sh

#include "individual_config.h"

#include "peripherie/spiFunctions.h"
#include "lvgl/variableFunctions.h"
#include "peripherie/ledBacklight.h"
#include "peripherie/i2cFunctions.h"
#include "logging/logging.h"

#if USE_BUZZER == true
    #include "peripherie/buzzer.h"
#endif

#if TESTMODE == true
    #include "simulation/testSimulation.h"
#else
    static bool pres_value_set = false;
    static bool temp_value_set = false;
#endif

#if USE_PWM_SENSOR == true
    #include "peripherie/pwmSensor.h"
#endif


static double value_oil_pressure = 0.0;
static double value_oil_temperature = 0.0;
static double value_volt = 8.0;
static double value_outside_temperature = 0.0;
static int value_brightness = 100;
static bool night_mode_active = false;

static time_t now;
static struct tm timeinfo;

time_t StartUpTime = 0;
time_t checkTime = 0;
bool time_checked[2] = {false, false}; // [0] = Gauge, [1] = Beeper

#if USE_BUZZER == true
    static int buzzed = 0;
    static void temperature_beep() {
        buzzer_beep(BEEPER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));
        buzzer_beep(BEEPER_QUIET_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_OFF_TIME));
        buzzer_beep(BEEPER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));
        buzzer_beep(BEEPER_QUIET_VALUE);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
        printf("buzzed!\n");
        vTaskDelete(NULL);     // Remove new created beeper task     
    }
#endif

static void tick_switch(int id)
{
    char ziel_string[20];

    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            #if TESTMODE == true
                lv_pressure_test(&value_oil_pressure);
            #else
                #if USE_PWM_SENSOR == true
                    if (!pres_value_set) {
                        value_oil_pressure = get_value(PWM_SENSOR_PRES_PULSE_ID);
                        pres_value_set = true;
                    }
                    else {
                        value_oil_pressure = calc_filter(get_value(PWM_SENSOR_PRES_PULSE_ID), value_oil_pressure);
                    }
                #else
                    value_oil_pressure = get_i2c_adc_oil_press();
                #endif
                if (value_oil_pressure < 0) {
                    value_oil_pressure = 0;
                }

            #endif
            snprintf(ziel_string, sizeof(ziel_string), "%.1f", value_oil_pressure);
            set_var_lvgl_value_oil_pressure(value_oil_pressure * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_pressure_string(ziel_string);

            if(!night_mode_active)
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
                lv_temperature_test(&value_oil_temperature);
            #else
                #if USE_PWM_SENSOR == true
                    if (!temp_value_set) {
                        value_oil_temperature = get_value(PWM_SENSOR_TEMP_PULSE_ID);
                        temp_value_set = true;
                    }
                    else {
                        value_oil_temperature = calc_filter(get_value(PWM_SENSOR_TEMP_PULSE_ID), value_oil_temperature);
                    }
                #else
                    value_oil_temperature = get_i2c_adc_oil_temp();
                #endif
                if (value_oil_temperature < 0) {
                    value_oil_temperature = 0;
                }
            #endif

            snprintf(ziel_string, sizeof(ziel_string), "%d", (int)value_oil_temperature);
            set_var_lvgl_value_oil_temperature(value_oil_temperature < 0 ? 0 : value_oil_temperature * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_temperature_string(ziel_string); 

            if(!night_mode_active)
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
                lv_volt_test(&value_volt);
            #else
                value_volt = get_i2c_adc_volt();
                if (value_volt < 8) {
                    value_volt = 0;
                }
            #endif
            snprintf(ziel_string, sizeof(ziel_string), "%.1f", value_volt);
            set_var_lvgl_value_voltage(value_volt * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_voltage_string(ziel_string);

            if(!night_mode_active)
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
                lv_Clocktemp_test(&value_outside_temperature);
            #else
                value_outside_temperature = get_i2c_adc_outside_temp();
                if (value_outside_temperature < -30) {
                    value_outside_temperature = -30;
                }
                if (value_outside_temperature > 70) {
                    value_outside_temperature = 70;
                }
            #endif
 
            time(&now);
            localtime_r(&now, &timeinfo);
            snprintf(ziel_string, sizeof(ziel_string), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
            set_var_lvgl_value_temperature(value_outside_temperature * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_clock(ziel_string); 

            if(!night_mode_active)
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
                lv_Clocktemp_test(&value_outside_temperature);
            #else
                value_outside_temperature = get_i2c_adc_outside_temp();
                if (value_outside_temperature < -30) {
                    value_outside_temperature = -30;
                }
                if (value_outside_temperature > 70) {
                    value_outside_temperature = 70;
                }
            #endif

            time(&now);
            localtime_r(&now, &timeinfo);
            int hour = timeinfo.tm_hour >= 12 ? timeinfo.tm_hour - 12 : timeinfo.tm_hour;
            set_var_lvgl_value_clock_hour(hour * 50 + ((timeinfo.tm_min*10)/12));
            set_var_lvgl_value_clock_minute(timeinfo.tm_min);

            // temperature Value
            if (value_outside_temperature > -10 && value_outside_temperature < 10)
            {
                if ((value_outside_temperature*10 - ((int)value_outside_temperature )*10) >= 5 )
                    snprintf(ziel_string, sizeof(ziel_string), "%d.5", (int) value_outside_temperature);
                else
                    snprintf(ziel_string, sizeof(ziel_string), "%d.0", (int) value_outside_temperature);
            }
            else
            {
                snprintf(ziel_string, sizeof(ziel_string), "%d", (int)value_outside_temperature);
            }
            
            set_var_lvgl_value_temperature_string(ziel_string);
            if(!night_mode_active)
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
            brightness_test(&value_brightness, &night_mode_active);
        #else 
            float adc_brightness = get_i2c_adc_volt_bel(); // 1-10.74V entsprechen 0-80% Helligkeit, 0 entspricht 100%
            //adc_brightness = 10.74;
            if (adc_brightness < 1) 
            {
                value_brightness = BRIGHTNESS_DAY;
                night_mode_active = false;
            }
            else {
                night_mode_active = true;
                value_brightness = (adc_brightness - BRIGHTNESS_NIGHT_MIN_V) / (BRIGHTNESS_NIGHT_MAX_V - BRIGHTNESS_NIGHT_MIN_V) * BRIGHTNESS_NIGHT_MAX;
                if (value_brightness > BRIGHTNESS_NIGHT_MAX) value_brightness = BRIGHTNESS_NIGHT_MAX;
                if (value_brightness < BRIGHTNESS_NIGHT_MIN) value_brightness = BRIGHTNESS_NIGHT_MIN;
            }
        #endif

        if ((long)(checkTime - StartUpTime) > GAUGE_ON_DELAY_SEC)
        { 
            if (!time_checked[0]) {
                time_checked[0] = !time_checked[0];
            }
            set_lcd_brightness(value_brightness); 
        }

        for (int i = 0; i < NUMBER_OF_DISPLAYS; i++){
            if (lv_disp_get_scr_act(DISPLAYS[i].lv_displays) != NULL) {
                lv_disp_set_default(DISPLAYS[i].lv_displays);
                tick_switch(DISPLAYS[i].screen_selection);
            }
        }

        #if USE_BUZZER == true
            if (!time_checked[1]) {
                time(&checkTime);
            }// ToDo: beeper nach einer bestimmten Zeit wieder aktivieren?
            if ((long)(checkTime - StartUpTime) >= BEEPER_ON_DELAY_SEC)
            {
                if (!time_checked[1]) {
                    time_checked[1] = !time_checked[1];
                }
                if (buzzed == false && value_outside_temperature < BEEPER_TEMP_MIN)
                {
                    xTaskCreatePinnedToCore(temperature_beep, "temperature_beep", BEEPER_TASK_STEPDEPTH, NULL, BEEPER_TASK_PRIORITY, NULL, BEEPER_TASK_CORE);
                    buzzed = true;
                }
            }
        #endif

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void init_system()
{
    // init display backlight
    init_lcd_backlight_pwm();
    //set_lcd_brightness(0);

    // init rtc
    init_i2c();
    sync_rtc_to_system();
    
    // Startzeitpunkt des Systems merken
    time(&StartUpTime);
    printf("System started at: %ld\n", (long)StartUpTime);

    // init buttons
    init_time_buttons();

    // init displays
    spi_init();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialisiert die LVGL-Puffer und LVGL-Treiberfür alle Displays
    timer_start(); // Startet die Timer für alle Displays 
    set_Displays();

    // init pwm sensor
    #if USE_PWM_SENSOR == true
        pwm_sensor_init();
        #if TESTMODE == true
            create_timer_pwm();
        #endif
    #endif

    // init buzzer
    #if USE_BUZZER == true
        buzzed = false;
        buzzer_init();
    #endif

}

void app_main(void)
{
    printLog("Starting Board Computer Application...");
    init_system();
    printLog("Initialization complete. Entering main loop.");

    printLog("Setting up LVGL tick task...");
    xTaskCreatePinnedToCore(lv_tick_task_screen, "lv_tick_task_screen", DISPLAYS[0].task_step_depth, NULL, DISPLAYS[0].task_priority, NULL, DISPLAYS[0].tast_core);
    printLog("LVGL tick task created successfully.");

    vTaskDelay(pdMS_TO_TICKS(MAIN_TASK_FINISHED_DELAY));
    printLog("Main task finished setup. Entering main loop idle state. Running tasks will handle the rest of the application logic.");
}
