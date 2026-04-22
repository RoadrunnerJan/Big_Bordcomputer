
/**
 * @file main.c
 * @brief Main application entry point for E36 Board Computer.
 *
 * FreeRTOS-based multi-display gauge system with real-time sensor processing,
 * LVGL graphical interface, and peripheral management for classic vehicle dashboard.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - Multi-display support with FreeRTOS tasks
 *      - PWM sensor and I2C ADC interface
 *      - LVGL gauge system with day/night mode switching
 *      - Buzzer alert system for temperature warnings
 */



/* ===== Project Configuration ===== */
#include "individual_config.h"

/* ===== Display & UI ===== */
#include "peripherie/spiFunctions.h"
#include "peripherie/ledBacklight.h"
#include "lvgl/variableFunctions.h"

/* ===== Communication Interfaces ===== */
#include "peripherie/i2cFunctions.h"
#include "peripherie/pwmSensor.h"
#include "peripherie/pwmSwitch.h"
#include "peripherie/adc.h"

/* ===== Utilities ===== */
#include "logging/logging.h"
#include "calculation/values.h"
#include "simulation/testSimulation.h"

/* ===== Buzzer (Optional) ===== */
#if USE_BUZZER == true
    #include "peripherie/buzzer.h"
#endif


/* ===== Global Variables ===== */
static time_t now;
static struct tm timeinfo;

struct timeval StartUpTime;
struct timeval checkTime;
int testmodeActivated = false;

bool night_mode = false;
bool time_checked[2] = {false, false};  // [0] = Gauge, [1] = Beeper


/* ===== Buzzer Task (only if enabled) ===== */
#if USE_BUZZER == true
    static int buzzed = 0;

    /**
     * @brief Generate temperature alert beep pattern.
     *
     * Generates a double beep pattern when outdoor temperature falls below 3°C.
     * Task runs to completion then deletes itself.
     *
     * @param pvParameters Task parameter (unused)
     */
    static void temperature_buzzering(void *pvParameters)
    {
        buzzer_beep(BUZZER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BUZZER_BEEP_ON_TIME));
        
        buzzer_beep(BUZZER_QUIET_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BUZZER_BEEP_OFF_TIME));
        
        buzzer_beep(BUZZER_BEEPING_VALUE);
        vTaskDelay(pdMS_TO_TICKS(BUZZER_BEEP_ON_TIME));
        
        buzzer_beep(BUZZER_QUIET_VALUE);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
        
        vTaskDelete(NULL);     // Remove buzzer task after completion
    }
#endif


/* ===== Display Update Tasks ===== */

/**
 * @brief Update sensor values and LVGL variables for a display.
 *
 * Reads sensor data (PWM or I2C ADC) based on current screen selection,
 * calculates processed values, and updates LVGL display variables for rendering.
 *
 * Handles:
 * - Sensor reading in test mode or from actual hardware
 * - Value calculation with calibration
 * - LVGL variable updates for display rendering
 * - Automatic day/night mode adjustments
 *
 * @param displayID Index of the display to update values for (0 to NUMBER_OF_DISPLAYS-1)
 */
static void update_values(int displayID)
{
    double value = 0.0;
    switch (DISPLAYS[displayID].screen_selection)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            if(is_testmode_activated()) {
                value = lv_pressure_test();
            }
            else 
            {
                if (isPWM()) value = get_pwm_value(PWM_SENSOR_PRES_PULSE_ID);
                else value = get_adc_oil_press();
            }
            calculate_value(SCREEN_ID_GAUGE_OIL_PRESSURE, value);
            set_var_lvgl_value_oil_pressure(get_value_by_screen_id(SCREEN_ID_GAUGE_OIL_PRESSURE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_pressure_string(get_output_string_by_screen_id(SCREEN_ID_GAUGE_OIL_PRESSURE));
            
        break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if(is_testmode_activated()) {
                value = lv_temperature_test();
            }
            else {
                if (isPWM()) value = get_pwm_value(PWM_SENSOR_TEMP_PULSE_ID);
                else value = get_adc_oil_temp();
            }
            calculate_value(SCREEN_ID_GAUGE_OIL_TEMPERATURE, value);
            set_var_lvgl_value_oil_temperature(get_value_by_screen_id(SCREEN_ID_GAUGE_OIL_TEMPERATURE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_oil_temperature_string(get_output_string_by_screen_id(SCREEN_ID_GAUGE_OIL_TEMPERATURE));
            
        break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if(is_testmode_activated()) {
                value = lv_volt_test();
            }
            else {
                value = get_adc_volt();
            }
            calculate_value(SCREEN_ID_GAUGE_VOLTAGE, value);
            set_var_lvgl_value_voltage(get_value_by_screen_id(SCREEN_ID_GAUGE_VOLTAGE) * EEZ_VALUE_FACTOR);
            set_var_lvgl_value_voltage_string(get_output_string_by_screen_id(SCREEN_ID_GAUGE_VOLTAGE));
            
        break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
            if(is_testmode_activated()) {
                value = lv_Clocktemp_test();
            }
            else {
                value = get_adc_outside_temp();
            }

            time(&now);
            localtime_r(&now, &timeinfo);
            char output_string[20];
            snprintf(output_string, sizeof(output_string), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
            set_var_lvgl_value_clock(output_string); 
            calculate_value(SCREEN_ID_GAUGE_TEMPERATURE_CLOCK, value);

            set_var_lvgl_value_temperature(get_value_by_screen_id(SCREEN_ID_GAUGE_TEMPERATURE_CLOCK) * EEZ_VALUE_FACTOR);
        break;
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if(is_testmode_activated()) {
                value = lv_Clocktemp_test();
            }
            else {
                value = get_adc_outside_temp();
            }
            calculate_value(SCREEN_ID_GAUGE_CLOCK_TEMPERATURE, value);
            set_var_lvgl_value_temperature_string(get_output_string_by_screen_id(SCREEN_ID_GAUGE_CLOCK_TEMPERATURE));

            time(&now);
            localtime_r(&now, &timeinfo);
            int hour = timeinfo.tm_hour >= 12 ? timeinfo.tm_hour - 12 : timeinfo.tm_hour;
            set_var_lvgl_value_clock_hour(hour * 50 + ((timeinfo.tm_min*10)/12));
            set_var_lvgl_value_clock_minute(timeinfo.tm_min);
        break;
    }
}

/**
 * @brief Handle display screen updates and rendering for a given display.
 *
 * Manages screen switching between day and night modes based on brightness settings.
 * Performs screen load with animation and calls the appropriate screen-specific
 * tick function to render updated values. Screen is only reloaded if it differs
 * from the currently active screen to optimize performance.
 *
 * @param displayID Index of the display to update (0 to NUMBER_OF_DISPLAYS-1)
 * @param force_night_mode_update Flag to force screen update when night mode changes
 */
static void tick_switch(int displayID, bool force_night_mode_update)
{
    lv_disp_set_default(DISPLAYS[displayID].lv_displays);
    switch (DISPLAYS[displayID].screen_selection)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
        
            if (force_night_mode_update || is_testmode_activated() || updateLVGLScreen(DISPLAYS[displayID].screen_selection) )
            {
                if(!night_mode)
                {
                    if (lv_scr_act() != objects.gauge_oil_pressure) 
                    {
                        lv_scr_load_anim(objects.gauge_oil_pressure, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_oil_pressure();
                }
                else
                {
                    if (lv_scr_act() != objects.gauge_oil_pressure_night) 
                    {
                        lv_scr_load_anim(objects.gauge_oil_pressure_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_oil_pressure_night();
                }
            }
        break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if (force_night_mode_update || is_testmode_activated() || updateLVGLScreen(DISPLAYS[displayID].screen_selection) )
            {
                if(!night_mode)
                {
                    if (lv_scr_act() != objects.gauge_oil_temperature) 
                    {
                        lv_scr_load_anim(objects.gauge_oil_temperature, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_oil_temperature();
                }
                else
                {
                    if (lv_scr_act() != objects.gauge_oil_temperature_night) 
                    {
                        lv_scr_load_anim(objects.gauge_oil_temperature_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_oil_temperature_night();
                }
            }
        break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if (force_night_mode_update || is_testmode_activated() || updateLVGLScreen(DISPLAYS[displayID].screen_selection) )
            {
                if(!night_mode)
                {
                    if (lv_scr_act() != objects.gauge_voltage) 
                    {
                        lv_scr_load_anim(objects.gauge_voltage, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_voltage();
                }
                else
                {
                    if (lv_scr_act() != objects.gauge_voltage_night) 
                    {
                        lv_scr_load_anim(objects.gauge_voltage_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_voltage_night();
                }
            }
        break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
            if (force_night_mode_update || is_testmode_activated() || updateLVGLScreen(DISPLAYS[displayID].screen_selection) )
            {
                if(!night_mode)
                {
                    if (lv_scr_act() != objects.gauge_temperature_clock) 
                    {
                        lv_scr_load_anim(objects.gauge_temperature_clock, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_temperature_clock();
                }
                else
                {
                    if (lv_scr_act() != objects.gauge_temperature_clock_night) 
                    {
                        lv_scr_load_anim(objects.gauge_temperature_clock_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_temperature_clock_night();
                }
            }
        break;
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if (force_night_mode_update || is_testmode_activated() || updateLVGLScreen(DISPLAYS[displayID].screen_selection) )
            {
                if(!night_mode)
                {
                    if (lv_scr_act() != objects.gauge_clock_temperature) 
                    {
                        lv_scr_load_anim(objects.gauge_clock_temperature, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_clock_temperature();
                }
                else
                {
                    if (lv_scr_act() != objects.gauge_clock_temperature_night) 
                    {
                        lv_scr_load_anim(objects.gauge_clock_temperature_night, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);  
                    }
                    tick_screen_gauge_clock_temperature_night();
                }
            }
        break;
    }
    lv_timer_handler();
}

/**
 * @brief Main LVGL tick task for periodic display updates.
 *
 * Core FreeRTOS task that runs the display update loop at 50ms intervals.
 * Handles brightness calculation, night mode switching, sensor reading,
 * value updates, screen rendering, and optional buzzer alerts.
 *
 * @param pv Task parameter (unused)
 */
static void lv_tick_task_screen(void *pv)
{
    (void)pv;

    while (1) {
        gettimeofday(&checkTime, NULL);
        if(is_testmode_activated()) {
            vTaskDelay(pdMS_TO_TICKS(50));
            brightness_test();
            night_mode = getNightModeActiveTestValue();
        }
        else {
            calcBrightness(get_adc_volt_bel());
            if(BRIGHTNESS_AUTO_ENABLE) {
                night_mode = getNightModeActive();
            }
            else {
                night_mode = false; // Force day mode if auto brightness is disabled
            }
        }

        if (((long long)checkTime.tv_sec * 1000 + checkTime.tv_usec / 1000 - (long long)StartUpTime.tv_sec * 1000 + StartUpTime.tv_usec / 1000) > GAUGE_ON_DELAY_MS)
        { 
            if (!time_checked[0]) {
                time_checked[0] = !time_checked[0];
            }
            if(is_testmode_activated()) {
                set_lcd_brightness(getBrightnessTestValue());
            }
            else {
                if(BRIGHTNESS_AUTO_ENABLE) {
                    set_lcd_brightness(getBrightness());
                }
                else {
                    set_lcd_brightness(BRIGHTNESS_DAY); // Force day mode brightness if auto brightness is disabled
                }
            }
        }

        // Read reference voltage for ADC calculations (Version 4.2 feature)
        if(!is_testmode_activated()) {
            get_adc_reference_voltage();
        }

        // Phase 1: Update all sensor values and LVGL variables for all displays
        for (int i = 0; i < NUMBER_OF_DISPLAYS; i++){
            update_values(i);
        }
        // Phase 2: Update and render screen displays with current values
        bool force_night_mode_update = getNightModechanged() ? true : false; // Force screen update if night mode state changed
        for (int i = 0; i < NUMBER_OF_DISPLAYS; i++){
            tick_switch(i, force_night_mode_update);
        }

        #if USE_BUZZER == true
            if (!time_checked[1]) {
                gettimeofday(&checkTime, NULL);
            }
            if ((long)((long long)checkTime.tv_sec * 1000 + checkTime.tv_usec / 1000 - (long long)StartUpTime.tv_sec * 1000 + StartUpTime.tv_usec / 1000) >= BUZZER_ON_DELAY_MS)
            {
                if (!time_checked[1]) {
                    time_checked[1] = !time_checked[1];
                }
                if (buzzed == false && value_outside_temperature < BUZZER_TEMP_MIN && value_outside_temperature > VALUE_MIN_OUT_TEMP && getOutputTemperatureSet())
                {
                    xTaskCreatePinnedToCore(temperature_buzzering, "temperature_buzzering", BUZZER_TASK_STEPDEPTH, NULL, BUZZER_TASK_PRIORITY, NULL, BUZZER_TASK_CORE);
                    buzzed = true;
                }
            }
        #endif

        if (read_pwmSW())
        {
            reset_values(SCREEN_ID_GAUGE_OIL_PRESSURE);
            reset_values(SCREEN_ID_GAUGE_OIL_TEMPERATURE);
        }

        if(is_testmode_activated() && !testmodeActivated)
        {
            testmodeActivated = true;
            reset_test_values();
            reset_test_switches();
            reset_values(-1);

        }
        else if (!is_testmode_activated() && testmodeActivated)
        {
            testmodeActivated = false;
            reset_values(-1);
        }
        
        if (isPWM() && is_testmode_activated()){
            pwm_sensor_print();
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

/**
 * @brief Initialize all hardware and system components.
 *
 * Sets up all peripherals and services required for the board computer:
 * - Display backlight PWM and brightness control
 * - ADC for sensor input
 * - I2C bus with RTC (DS3231) and synchronizes system time
 * - Time adjustment buttons with callbacks
 * - SPI display layers and LVGL graphics engine
 * - PWM/ADC sensor mode selector
 * - Optional buzzer component for temperature alerts
 *
 * Must be called once during application startup before creating tasks.
 */
void init_system()
{
    printLog("Initializing system...");

    // init display backlight
    init_lcd_backlight_pwm();
    printLog("Display backlight initialized.");

    adc_init();
    printLog("ADC initialized.");

    // init rtc
    init_i2c();
    sync_rtc_to_system();
    printLog("RTC initialized and synchronized to system time.");
    gettimeofday(&StartUpTime, NULL);
    char log_msg[50];
    snprintf(log_msg, sizeof(log_msg), "System started at: %s", ctime(&StartUpTime.tv_sec));
    printLog(log_msg);

    // init buttons
    init_time_buttons();
    printLog("Time Setting Buttons initialized.");

    // init displays
    spi_init();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialize LVGL buffers and drivers for all displays
    timer_start(); // Start timers for all displays
    set_Displays();
    printLog("Displays initialized and screens set.");

    // init pwm sensor
    init_pwmSW();
    pwm_sensor_init();
    printLog("PWM Sensor initialized.");

    // init buzzer
    #if USE_BUZZER == true
        buzzed = false;
        buzzer_init();
        printLog("Buzzer initialized.");
    #endif
    printLog("Initialization complete. Entering main loop.");
}


/**
 * @brief ESP-IDF application main entry point.
 *
 * Initializes all system resources and creates the main LVGL tick task
 * for periodic display updates. After task creation, enters idle mode
 * while background tasks handle application logic.
 *
 * This function is automatically called by ESP-IDF runtime.
 */
void app_main(void)
{
    printLog("Starting Board Computer Application...");
    init_system();

    xTaskCreatePinnedToCore(lv_tick_task_screen, "lv_tick_task_screen", DISPLAYS[0].task_step_depth, NULL, DISPLAYS[0].task_priority, NULL, DISPLAYS[0].tast_core);
    printLog("LVGL tick task created successfully.");

    vTaskDelay(pdMS_TO_TICKS(MAIN_TASK_FINISHED_DELAY));
    printLog("Main task finished setup. Entering main loop idle state. Running tasks will handle the rest of the application logic.");
}
