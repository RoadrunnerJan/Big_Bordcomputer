
#include "includes.h"
#include "individual_config.h"

#if TESTMODE == true
    static int pressure_test_switch = 0;
    static int temperature_test_switch = 0;
    static int volt_test_switch = 0;
    static int Clocktemp_test_switch = 0;
    static int brightness_test_switch = 0;
#else
    static bool pres_value_set = false;
    static bool temp_value_set = false;
#endif

static double oil_pressure_value = 0.0;
static double oil_temperature_value = 0.0;
static double volt_value = 8.0;
static double Clocktemp_value = 0.0;


static int brightness_value = 100;
static bool night_mode = false;

static time_t now;
static struct tm timeinfo;

#if USE_BEEP == true
    static bool beeped = false;
    static void temperature_beep()
    {
        while (!beeped)
        {
            if (Clocktemp_value < BEEPER_TEMP_MIN)
            {
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 30); // max 256
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
                //gpio_set_level(BEEPER_PIN, BEEPER_BEEPING_VALUE);
                vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
                //gpio_set_level(BEEPER_PIN, BEEPER_QUIET_VALUE);
                vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_OFF_TIME));
                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 30);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);

                //gpio_set_level(BEEPER_PIN, BEEPER_BEEPING_VALUE);
                vTaskDelay(pdMS_TO_TICKS(BEEPER_BEEP_ON_TIME));

                ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, 0);
                ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
                //gpio_set_level(BEEPER_PIN, BEEPER_QUIET_VALUE);
                beeped = true;
            }
            vTaskDelay(pdMS_TO_TICKS(BEEPER_TASK_DELAYTIME));
        }
        vTaskDelete(NULL); 
    }
#endif

#if TESTMODE == true
    static void lv_pressure_test()
    {
        switch (pressure_test_switch) {
            case 0:
                oil_pressure_value += 0.06;
                if (oil_pressure_value >= 4.5) {
                    pressure_test_switch = 1;
                }
            break;
            case 1:
                oil_pressure_value -= 0.02;
                if (oil_pressure_value <= 2.5) {
                    pressure_test_switch = 2;
                }
            break;
            case 2:
                oil_pressure_value += 0.06;
                if (oil_pressure_value >= 5.5) {
                    pressure_test_switch = 3;
                }
            break;
            case 3:
                oil_pressure_value -= 0.06;
                if (oil_pressure_value <= 0.04) {
                    pressure_test_switch = 0;
                }
            break;
        }
    }

    static void lv_volt_test()
    {
        switch (volt_test_switch) {
            case 0:
                volt_value += 0.05;
                if (volt_value >= 15.5) {
                    volt_test_switch = 1;
                }
            break;
            case 1:
                volt_value -= 0.05;
                if (volt_value <= 11) {
                    volt_test_switch = 2;
                }
            break;
            case 2:
                volt_value += 0.05;
                if (volt_value >= 14) {
                    volt_test_switch = 3;
                }
            break;
            case 3:
                volt_value -= 0.05;
                if (volt_value <= 8.04) {
                    volt_test_switch = 0;
                }
            break;
        }
    }

    static void lv_temperature_test()
    {
        switch (temperature_test_switch) {
            case 0:
                oil_temperature_value += 0.3;
                if (oil_temperature_value >= 100) {
                    temperature_test_switch = 1;
                }
            break;
            case 1:
                oil_temperature_value -= 0.3;
                if (oil_temperature_value <= 110) {
                    temperature_test_switch = 2;
                }
            break;
            case 2:
                oil_temperature_value += 0.3;
                if (oil_temperature_value >= 140) {
                    temperature_test_switch = 3;
                }
            break;
            case 3:
                oil_temperature_value -= 0.3;
                if (oil_temperature_value <= 0.06) {
                    temperature_test_switch = 0;
                }
            break;
        }
    }

    static void lv_Clocktemp_test()
    {
        switch (Clocktemp_test_switch) {
            case 0:
                Clocktemp_value += 0.3;
                if (Clocktemp_value >= 33) {
                    Clocktemp_test_switch = 1;
                }
            break;
            case 1:
                Clocktemp_value -= 0.3;
                if (Clocktemp_value <= -15) {
                    Clocktemp_test_switch = 2;
                }
            break;
            case 2:
                Clocktemp_value += 0.3;
                if (Clocktemp_value >= 20) {
                    Clocktemp_test_switch = 3;
                }
            break;
            case 3:
                Clocktemp_value -= 0.3;
                if (Clocktemp_value <= 0.06) {
                    Clocktemp_test_switch = 0;
                }
            break;
        }
    }

    #if TESTBRIGHTNESS == true
        static void test_brightness() {
            
            switch (brightness_test_switch) {
                case 0:
                    brightness_value -= 1;
                    if (brightness_value <= 15) {
                        brightness_test_switch = 1;
                    }
                break;
                case 1:
                    brightness_value += 1;
                    if (brightness_value >= 50) {
                        brightness_test_switch = 2;
                    }
                break;
                case 2:
                    brightness_value -= 1;
                    if (brightness_value <= 2) {
                        brightness_test_switch = 3;
                    }
                break;
                case 3:
                    brightness_value += 1;
                    if (brightness_value >= 100) {
                        brightness_test_switch = 0;
                    }
                break;
            }
        }
    #endif

    static void set_NightMode(void *pv) {
        (void)pv;
        
        while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(5000));
            night_mode = !night_mode;
        }
    }
#endif

static void tick_switch(int id)
{
    char ziel_string[20];

    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            #if TESTMODE == true
                lv_pressure_test();
            #else
                if (!pres_value_set) {
                    oil_pressure_value = get_value(PWM_SENSOR_PRES_PULSE_ID);
                    pres_value_set = true;
                }
                else {
                    oil_pressure_value = calc_filter(get_value(PWM_SENSOR_PRES_PULSE_ID), oil_pressure_value);
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
                lv_temperature_test(); 
            #else
                if (!temp_value_set) {
                    oil_temperature_value = get_value(PWM_SENSOR_TEMP_PULSE_ID);
                    temp_value_set = true;
                }
                else {
                    oil_temperature_value = calc_filter(get_value(PWM_SENSOR_TEMP_PULSE_ID), oil_temperature_value);
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
                lv_volt_test();
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
                lv_Clocktemp_test();
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
                lv_Clocktemp_test();
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

static void lv_tick_task_screen_1(void *pv)
{
    (void)pv;
    while (1) {
        if (lv_disp_get_scr_act(DISPLAYS[0].lv_displays) != NULL) {
            lv_disp_set_default(DISPLAYS[0].lv_displays);
            tick_switch(DISPLAYS[0].screen_selection);
        }
        vTaskDelay(pdMS_TO_TICKS(DISPLAYS[0].task_delay_time_ms));
    }
}

static void lv_tick_task_screen_2(void *pv)
{
    (void)pv;
    #if NUMBER_OF_DISPLAYS > 1 
    while (1) {
        if (lv_disp_get_scr_act(DISPLAYS[1].lv_displays) != NULL) {
            lv_disp_set_default(DISPLAYS[1].lv_displays);
            tick_switch(DISPLAYS[1].screen_selection);
        }       
        vTaskDelay(pdMS_TO_TICKS(DISPLAYS[1].task_delay_time_ms));
    }
    #endif
}

static void lv_tick_task_screen_3(void *pv)
{
    (void)pv;

    #if NUMBER_OF_DISPLAYS > 2
        while (1) {
            if (lv_disp_get_scr_act(DISPLAYS[2].lv_displays) != NULL) {
                lv_disp_set_default(DISPLAYS[2].lv_displays);
                tick_switch(DISPLAYS[2].screen_selection);
            }
            vTaskDelay(pdMS_TO_TICKS(DISPLAYS[2].task_delay_time_ms));
        }
    #endif
}

static void lv_tick_task_screen_4(void *pv)
{
    (void)pv;

    #if NUMBER_OF_DISPLAYS > 3
        while (1) {
            if (lv_disp_get_scr_act(DISPLAYS[3].lv_displays) != NULL) {
                lv_disp_set_default(DISPLAYS[3].lv_displays);
                tick_switch(DISPLAYS[3].screen_selection);
            }
            vTaskDelay(pdMS_TO_TICKS(DISPLAYS[3].task_delay_time_ms));
        }
    #endif
}
    

static void brightness(void *pv) {
    while(1)
    {
        #if TESTMODE == true && TESTBRIGHTNESS == true
            test_brightness();
        #endif
        set_lcd_brightness(brightness_value); 
        vTaskDelay(pdMS_TO_TICKS(BRIGHTNESS_DELAY));
    }
}

void app_main(void)
{
    // init rtc
    init_i2c_ds3231();
    //set_time();
    //vTaskDelay(pdMS_TO_TICKS(500));
    sync_rtc_to_system();

    //init_time_buttons();

    spi_init();
    init_lcd_backlight_pwm();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialisiert die LVGL-Puffer und LVGL-Treiberfür alle Displays
    timer_start(); // Startet die Timer für alle Displays 
    set_Displays();

    vTaskDelay(pdMS_TO_TICKS(DISPLAY_SETUP_DELAY));
    pwm_sensor_init();
    #if TESTMODE == true && USE_PWM_SENSOR == true
        create_timer_pwm();
    #endif

    #if USE_BEEP == true
        beeped = false;
        beeper_init();
    #endif

    #if TESTMODE == true
        xTaskCreate(set_NightMode, "set_NightMode", 4096, NULL, 12, NULL);
    #endif


    xTaskCreatePinnedToCore(lv_tick_task_screen_1, "lv_tick_task_screen_1", DISPLAYS[0].task_step_depth, NULL, DISPLAYS[0].task_priority, NULL, DISPLAYS[0].tast_core);
    #if NUMBER_OF_DISPLAYS > 1
        xTaskCreatePinnedToCore(lv_tick_task_screen_2, "lv_tick_task_screen_2", DISPLAYS[1].task_step_depth, NULL, DISPLAYS[1].task_priority, NULL, DISPLAYS[1].tast_core);
    #endif
    #if NUMBER_OF_DISPLAYS > 2
        xTaskCreatePinnedToCore(lv_tick_task_screen_3, "lv_tick_task_screen_3", DISPLAYS[2].task_step_depth, NULL, DISPLAYS[2].task_priority, NULL, DISPLAYS[2].tast_core);
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        xTaskCreatePinnedToCore(lv_tick_task_screen_4, "lv_tick_task_screen_4", DISPLAYS[3].task_step_depth, NULL, DISPLAYS[3].task_priority, NULL, DISPLAYS[3].tast_core);
    #endif

    vTaskDelay(pdMS_TO_TICKS(GAUGE_ON_DELAY));
    xTaskCreatePinnedToCore(brightness, "brightness", 8192, NULL, 20, NULL, 0);

    vTaskDelay(pdMS_TO_TICKS(BEEPER_ON_DELAY));
    #if USE_BEEP == true
        xTaskCreatePinnedToCore(temperature_beep, "temperature_beep", BEEPER_TASK_STEPDEPTH, NULL, BEEPER_TASK_PRIORITY, NULL, BEEPER_TASK_CORE);
    #endif


    vTaskDelay(pdMS_TO_TICKS(MAIN_TASK_FINISHED_DELAY));
    

    

}
