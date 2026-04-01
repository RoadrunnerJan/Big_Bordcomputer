
// . $HOME/tools/esp/esp-idf/export.sh
// allgemein . $HOME/esp/esp-idf/export.sh

#include "individual_config.h"

#include "peripherie/spiFunctions.h"
#include "lvgl/variableFunctions.h"
#include "peripherie/ledBacklight.h"
#include "peripherie/i2cFunctions.h"
#include "logging/logging.h"

#include "simulation/testSimulation.h"
#include "peripherie/pwmSensor.h"
#include "peripherie/pwmSwitch.h"

#include "calculation/values.h"

#if USE_BUZZER == true
    #include "peripherie/buzzer.h"
#endif

static time_t now;
static struct tm timeinfo;

time_t StartUpTime = 0;
time_t checkTime = 0;

bool night_mode = false;

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
    double value = 0.0;
    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            #if TESTMODE == true
                value = lv_pressure_test();
            #else
                if (isPWM()) value = get_pwm_value(PWM_SENSOR_PRES_PULSE_ID);
                else value = get_i2c_adc_oil_press();
            #endif
            calculate_value(SCREEN_ID_GAUGE_OIL_PRESSURE, value);
            
            set_var_lvgl_value_oil_pressure(get_value_by_screen_id(SCREEN_ID_GAUGE_OIL_PRESSURE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_pressure_string(get_output_string());

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
                value = lv_temperature_test();
            #else
                if (isPWM()) value = get_pwm_value(PWM_SENSOR_TEMP_PULSE_ID);
                else value = get_i2c_adc_oil_temp();
            #endif
            calculate_value(SCREEN_ID_GAUGE_OIL_TEMPERATURE, value);

            set_var_lvgl_value_oil_temperature(get_value_by_screen_id(SCREEN_ID_GAUGE_OIL_TEMPERATURE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_temperature_string(get_output_string());

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
                value = lv_volt_test();
            #else
                value = get_i2c_adc_volt();
            #endif
            calculate_value(SCREEN_ID_GAUGE_VOLTAGE, value);

            set_var_lvgl_value_voltage(get_value_by_screen_id(SCREEN_ID_GAUGE_VOLTAGE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_voltage_string(get_output_string());

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
                value = lv_Clocktemp_test();
            #else
                value = get_i2c_adc_outside_temp();
            #endif
            calculate_value(SCREEN_ID_GAUGE_TEMPERATURE_CLOCK, value);

            time(&now);
            localtime_r(&now, &timeinfo);
            char output_string[20];
            snprintf(output_string, sizeof(output_string), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
            set_var_lvgl_value_temperature(get_value_by_screen_id(SCREEN_ID_GAUGE_TEMPERATURE_CLOCK) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_clock(output_string); 

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
                value = lv_Clocktemp_test();
            #else
                value = get_i2c_adc_outside_temp();
            #endif
            calculate_value(SCREEN_ID_GAUGE_CLOCK_TEMPERATURE, value);

            time(&now);
            localtime_r(&now, &timeinfo);
            int hour = timeinfo.tm_hour >= 12 ? timeinfo.tm_hour - 12 : timeinfo.tm_hour;
            set_var_lvgl_value_clock_hour(hour * 50 + ((timeinfo.tm_min*10)/12));
            set_var_lvgl_value_clock_minute(timeinfo.tm_min);

            set_var_lvgl_value_temperature_string(get_output_string());
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
            brightness_test();
            night_mode = getNightModeActiveTestValue();
        #else 
            calcBrightness(get_i2c_adc_volt_bel());
            night_mode = getNightModeActive();
        #endif

        if ((long)(checkTime - StartUpTime) > GAUGE_ON_DELAY_SEC)
        { 
            if (!time_checked[0]) {
                time_checked[0] = !time_checked[0];
            }
            #if TESTMODE == true 
                set_lcd_brightness(getBrightnessTestValue());
            #else
                set_lcd_brightness(getBrightness());
            #endif
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

        if (read_pwmSW())
        {
            reset_values(SCREEN_ID_GAUGE_OIL_PRESSURE);
            reset_values(SCREEN_ID_GAUGE_OIL_TEMPERATURE);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void init_system()
{
    printLog("Initializing system...");
    #if TESTMODE == true
        printWarningLog("Running in TEST MODE: Simulated sensor values, night mode, and brightness test enabled.");
    #endif
    // init display backlight
    init_lcd_backlight_pwm();
    printLog("Display backlight initialized.");

    // init rtc
    init_i2c();
    sync_rtc_to_system();
    printLog("RTC initialized and synchronized to system time.");
    time(&StartUpTime);
    printf("System started at: %s", ctime(&StartUpTime));

    // init buttons
    init_time_buttons();
    printLog("Time Setting Buttons initialized.");

    // init displays
    spi_init();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialisiert die LVGL-Puffer und LVGL-Treiberfür alle Displays
    timer_start(); // Startet die Timer für alle Displays 
    set_Displays();
    printLog("Displays initialized and screens set.");

    // init pwm sensor
    init_pwmSW();
    pwm_sensor_init();
    #if TESTMODE == true
        create_timer_pwm();
    #endif
    printLog("PWM Sensor initialized.");

    // init buzzer
    #if USE_BUZZER == true
        buzzed = false;
        buzzer_init();
        printLog("Buzzer initialized.");
    #endif
    printLog("Initialization complete. Entering main loop.");
}

void app_main(void)
{
    printLog("Starting Board Computer Application...");
    init_system();

    xTaskCreatePinnedToCore(lv_tick_task_screen, "lv_tick_task_screen", DISPLAYS[0].task_step_depth, NULL, DISPLAYS[0].task_priority, NULL, DISPLAYS[0].tast_core);
    printLog("LVGL tick task created successfully.");

    vTaskDelay(pdMS_TO_TICKS(MAIN_TASK_FINISHED_DELAY));
    printLog("Main task finished setup. Entering main loop idle state. Running tasks will handle the rest of the application logic.");
}
