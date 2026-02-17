
#include "includes.h"
#include "individual_config.h"


static double pressure_value = 0.0;
static int pressure_test_switch = 0;
static double temperature_value = 0.0;
static int temperature_test_switch = 0;
static double volt_value = 8.0;
static int volt_test_switch = 0;
static double tempClock_value = 0.0;
static double Clocktemp_value = 0.0;
static int Clocktemp_test_switch = 0;

static time_t now;
static struct tm timeinfo;

static bool night_mode = false;

static void switch_screen_to_night(int id){
    lv_obj_t *target_screen;

    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
        break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
        break;
        case SCREEN_ID_GAUGE_VOLTAGE: 
        break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        break;
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
        break;
        
    }
    vTaskDelay(pdMS_TO_TICKS(10));
}

static void tick_switch(int id)
{
    char ziel_string[20];

    switch (id)
    {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            snprintf(ziel_string, sizeof(ziel_string), "%.1f", pressure_value);
            set_var_lvgl_value_oil_pressure(pressure_value * EEZ_VALUE_FACTOR);
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
            snprintf(ziel_string, sizeof(ziel_string), "%d", (int)temperature_value);
            set_var_lvgl_value_oil_temperature(temperature_value * EEZ_VALUE_FACTOR);
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
            time(&now);
            localtime_r(&now, &timeinfo);
            set_var_lvgl_value_clock_hour(timeinfo.tm_hour * 50 + ((timeinfo.tm_min*10)/12));
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
            if(night_mode)
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
            switch_screen_to_night(DISPLAYS[0].screen_selection);
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
            switch_screen_to_night(DISPLAYS[1].screen_selection);
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
                switch_screen_to_night(DISPLAYS[2].screen_selection);
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
                switch_screen_to_night(DISPLAYS[3].screen_selection);
                tick_switch(DISPLAYS[3].screen_selection);
            }
            vTaskDelay(pdMS_TO_TICKS(DISPLAYS[3].task_delay_time_ms));
        }
    #endif
}


static void lv_pressure_test(void *pv)
{
    (void)pv;


    while (1) {
        switch (pressure_test_switch) {
            case 0:
                pressure_value += 0.003;
                if (pressure_value >= 4.5) {
                    pressure_test_switch = 1;
                }
                break;
            case 1:
                pressure_value -= 0.001;
                if (pressure_value <= 2.5) {
                    pressure_test_switch = 2;
                }
                break;
            case 2:
                pressure_value += 0.003;
                if (pressure_value >= 5.5) {
                    pressure_test_switch = 3;
                }
                break;
            case 3:
                pressure_value -= 0.003;
                if (pressure_value <= 0.04) {
                    pressure_test_switch = 0;
                }
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


static void lv_volt_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

    while (1) {
        switch (volt_test_switch) {
            case 0:
                volt_value += 0.005;
                if (volt_value >= 15.5) {
                    volt_test_switch = 1;
                }
                break;
            case 1:
                volt_value -= 0.005;
                if (volt_value <= 11) {
                    volt_test_switch = 2;
                }
                break;
            case 2:
                volt_value += 0.005;
                if (volt_value >= 14) {
                    volt_test_switch = 3;
                }
                break;
            case 3:
                volt_value -= 0.005;
                if (volt_value <= 8.04) {
                    volt_test_switch = 0;
                }
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

static void lv_temperature_test(void *pv)
{
    (void)pv;
    while (1) {
        switch (temperature_test_switch) {
            case 0:
                temperature_value += 0.03;
                if (temperature_value >= 100) {
                    temperature_test_switch = 1;
                }
                break;
            case 1:
                temperature_value -= 0.03;
                if (temperature_value <= 110) {
                    temperature_test_switch = 2;
                }
                break;
            case 2:
                temperature_value += 0.03;
                if (temperature_value >= 140) {
                    temperature_test_switch = 3;
                }
                break;
            case 3:
                temperature_value -= 0.03;
                if (temperature_value <= 0.06) {
                    temperature_test_switch = 0;
                }
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void lv_Clocktemp_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

    while (1) {
        switch (Clocktemp_test_switch) {
            case 0:
                Clocktemp_value += 0.03;
                if (Clocktemp_value >= 33) {
                    Clocktemp_test_switch = 1;
                }
                break;
            case 1:
                Clocktemp_value -= 0.03;
                if (Clocktemp_value <= -15) {
                    Clocktemp_test_switch = 2;
                }
                break;
            case 2:
                Clocktemp_value += 0.03;
                if (Clocktemp_value >= 20) {
                    Clocktemp_test_switch = 3;
                }
                break;
            case 3:
                Clocktemp_value -= 0.03;
                if (Clocktemp_value <= 0.06) {
                    Clocktemp_test_switch = 0;
                }
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


static void NightMode_Setter(bool enabled)
{
    /*lv_color_t col = !enabled ? lv_color_hex(COLOR_NIGHT_MODE_HEX) : lv_color_hex(COLOR_DAY_MODE_HEX) ;
    int opac = !enabled ? OPACITY_NIGHT_MODE : OPACITY_DAY_MODE;

    lv_obj_set_style_text_color(objects.pressure_gauge_unit, col, LV_PART_MAIN);
    lv_obj_set_style_text_color(objects.pressure_gauge_scale_labels, col, LV_PART_TICKS);
    lv_obj_set_style_img_opa(objects.pressure_needle_knop_light_shadow, opac, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(objects.pressure_black_background_opa, opac/2, LV_PART_MAIN);

    lv_meter_t * m = (lv_meter_t *)objects.pressure_gauge_scale;
    lv_meter_scale_t * scale = _lv_ll_get_head(&m->scale_ll); 
    lv_meter_indicator_t * indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
    
    if(scale) {
        scale->tick_color = col;       // Kleine Striche
        scale->tick_major_color = col; // Große Striche
        indic->type_data.needle_line.color = col; // Nadelfarbe
    }
    m = (lv_meter_t *)objects.pressure_gauge_scale_labels;
    scale = _lv_ll_get_head(&m->scale_ll); 
    indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
    
    if(scale) {
        scale->tick_color = col;       // Kleine Striche
        scale->tick_major_color = col; // Große Striche
    }

    #if NUMBER_OF_DISPLAYS > 1
        col = !enabled ? lv_color_hex(COLOR_NIGHT_MODE_HEX) : lv_color_hex(COLOR_DAY_MODE_HEX) ;
        lv_obj_set_style_text_color(objects.temperature_gauge_unit, col, LV_PART_MAIN);
        lv_obj_set_style_text_color(objects.temperature_gauge_scale_labels, col, LV_PART_TICKS);
        m = (lv_meter_t *)objects.temperature_gauge_scale;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
            indic->type_data.needle_line.color = col; // Nadelfarbe
        }
        m = (lv_meter_t *)objects.temperature_gauge_scale_labels;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
    }
    #endif

    #if NUMBER_OF_DISPLAYS > 2
        col = !enabled ? lv_color_hex(COLOR_NIGHT_MODE_HEX) : lv_color_hex(COLOR_DAY_MODE_HEX) ;
        lv_obj_set_style_text_color(objects.volt_gauge_unit, col, LV_PART_MAIN);
        lv_obj_set_style_text_color(objects.volt_gauge_scale_labels, col, LV_PART_TICKS);
        m = (lv_meter_t *)objects.volt_gauge_scale;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
            indic->type_data.needle_line.color = col; // Nadelfarbe
        }
        m = (lv_meter_t *)objects.volt_gauge_scale_labels;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
    }
    #endif

    #if NUMBER_OF_DISPLAYS > 3
        col = !enabled ? lv_color_hex(COLOR_NIGHT_MODE_HEX) : lv_color_hex(COLOR_DAY_MODE_HEX) ;
        lv_obj_set_style_text_color(objects.temp_clock_gauge_unit, col, LV_PART_MAIN);
        lv_obj_set_style_text_color(objects.temp_clock_gauge_scale_labels, col, LV_PART_TICKS);
        m = (lv_meter_t *)objects.temp_clock_gauge_scale;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
            indic->type_data.needle_line.color = col; // Nadelfarbe
        }
        m = (lv_meter_t *)objects.temp_clock_gauge_scale_labels;
        scale = _lv_ll_get_head(&m->scale_ll); 
        indic = _lv_ll_get_head(&m->indicator_ll); // Erster Indikator (Nadel)
        if(scale) {
            scale->tick_color = col;       // Kleine Striche
            scale->tick_major_color = col; // Große Striche
    }
    #endif*/
    
    
    //DISPLAYS[2].night_Mode_Switched


/* Alternative: Einfach den ganzen Screen wechseln (so wie es in der UI-Definition vorgesehen ist) - Problem: Die Nadel bewegt sich im Nachtmodus nicht
        lv_obj_t *target_screen = enabled ? objects.gauge_oil_pressure_night : objects.gauge_oil_pressure_day;

        // Prüfen, ob wir nicht schon auf dem Screen sind (verhindert Flackern)
        if (lv_scr_act() == target_screen) return;

        // Screen laden mit Animation
        lv_scr_load_anim(target_screen, 
                            LV_SCR_LOAD_ANIM_FADE_ON, // Animations-Typ (siehe unten)
                            250,                      // Dauer in ms
                            0,                        // Verzögerung (Delay) vor Start
                            false);  
 */
}

static void set_NightMode(void *pv) {
    (void)pv;
    
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        night_mode = !night_mode;
    }
}

void app_main(void)
{
    spi_init();
    init_lcd_backlight_pwm();
    display_init(); 
    lv_init();
    buffer_and_driver_init(); // Initialisiert die LVGL-Puffer und LVGL-Treiberfür alle Displays
    timer_start(); // Startet die Timer für alle Displays 
    set_Displays();


    xTaskCreatePinnedToCore(lv_pressure_test, "lv_pressure_test", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(lv_temperature_test, "lv_temperature_test", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(lv_volt_test, "lv_volt_test", 4096, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(lv_Clocktemp_test, "lv_Clocktemp_test", 4096, NULL, 4, NULL, 0);


    xTaskCreate(set_NightMode, "set_NightMode", 4096, NULL, 5, NULL);


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


    
    vTaskDelay(pdMS_TO_TICKS(1000));
    set_lcd_brightness(100);  // ToDo: überprüfen, ob das so funktioniert
    

}
