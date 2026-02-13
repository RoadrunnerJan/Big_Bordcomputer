
#include "includes.h"
#include "individual_config.h"




static double pressure_value = 0.0;
static int pressure_test_switch = 0;
static double temperature_value = 0.0;
static int temperature_test_switch = 0;
static double volt_value = 8.0;
static int volt_test_switch = 0;
static double tempClock_value = 0.0;
static int tempClock_test_switch = 0;

/*
static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}*/



static void lv_tick_task(void *pv)
{
    (void)pv;
    while (1) {

        if (lv_disp_get_scr_act(lv_displays[0]) != NULL) {
            lv_disp_set_default(lv_displays[0]);
            tick_screen_gauge_oil_pressure();
            lv_timer_handler();
        }
        #if NUMBER_OF_DISPLAYS > 1
            if (lv_disp_get_scr_act(lv_displays[1]) != NULL) {
                lv_disp_set_default(lv_displays[1]);
                tick_screen_gauge_oil_temperature();
                lv_timer_handler();
            }
        #endif
        #if NUMBER_OF_DISPLAYS > 2                
            if (lv_disp_get_scr_act(lv_displays[2]) != NULL) {
                lv_disp_set_default(lv_displays[2]);
                tick_screen_gauge_voltage();
                lv_timer_handler();
            }
        #endif
        #if NUMBER_OF_DISPLAYS > 3
            if (lv_disp_get_scr_act(lv_displays[3]) != NULL) {
                lv_disp_set_default(lv_displays[3]);
                tick_screen_gauge_temperature_clock();
                lv_timer_handler(); 
            }
        #endif
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}



static void lv_pressure_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

    while (1) {
        switch (pressure_test_switch) {
            case 0:
                pressure_value += 0.01;
                if (pressure_value >= 4.5) {
                    pressure_test_switch = 1;
                }
                break;
            case 1:
                pressure_value -= 0.005;
                if (pressure_value <= 2.5) {
                    pressure_test_switch = 2;
                }
                break;
            case 2:
                pressure_value += 0.01;
                if (pressure_value >= 5.5) {
                    pressure_test_switch = 3;
                }
                break;
            case 3:
                pressure_value -= 0.01;
                if (pressure_value <= 0.04) {
                    pressure_test_switch = 0;
                }
                break;
        }

        snprintf(ziel_string, sizeof(ziel_string), "%.1f", pressure_value);

        set_var_lvgl_value_oil_pressure(pressure_value * EEZ_VALUE_FACTOR);
        set_var_lvgl_value_oil_pressure_string(ziel_string);


        vTaskDelay(pdMS_TO_TICKS(20));

        /* WICHTIG!!!!
        
        Die goldene Regel: Main-Loop vs. Timer
        Du darfst die GUI nicht aus einer Sensor-Task heraus aktualisieren, wenn diese gleichzeitig mit der lv_timer_handler Task läuft (Gefahr von Abstürzen). Nutze entweder einen Mutex oder aktualisiere die Werte direkt in deiner lv_tick_task:
        c
        static void lv_tick_task(void *pv) {
            while (1) {
                // Hier könntest du die Variable aktualisieren, bevor der Handler zeichnet
                char buf[16];
                snprintf(buf, sizeof(buf), "%.1f", mein_globaler_sensor_wert);
                set_var_lvgl_value_temperature_string(buf);

                lv_timer_handler(); // Verarbeitet die Änderung und zeichnet neu
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }
        
        */
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

        snprintf(ziel_string, sizeof(ziel_string), "%.1f", volt_value);

        set_var_lvgl_value_voltage(volt_value * EEZ_VALUE_FACTOR);
        set_var_lvgl_value_voltage_string(ziel_string);


        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

static void lv_temperature_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

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

        snprintf(ziel_string, sizeof(ziel_string), "%d", (int)temperature_value);

        set_var_lvgl_value_oil_temperature(temperature_value * EEZ_VALUE_FACTOR);
        set_var_lvgl_value_oil_temperature_string(ziel_string);


        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void lv_tempClock_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

    while (1) {
        switch (tempClock_test_switch) {
            case 0:
                tempClock_value += 0.03;
                if (tempClock_value >= 33) {
                    tempClock_test_switch = 1;
                }
                break;
            case 1:
                tempClock_value -= 0.03;
                if (tempClock_value <= -15) {
                    tempClock_test_switch = 2;
                }
                break;
            case 2:
                tempClock_value += 0.03;
                if (tempClock_value >= 20) {
                    tempClock_test_switch = 3;
                }
                break;
            case 3:
                tempClock_value -= 0.03;
                if (tempClock_value <= 0.06) {
                    tempClock_test_switch = 0;
                }
                break;
        }

        //snprintf(ziel_string, sizeof(ziel_string), "%d", (int)tempClock_value);

        set_var_lvgl_value_temperature(tempClock_value * EEZ_VALUE_FACTOR);
       // set_var_lvgl_value_oil_temperature_string(ziel_string);


        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void set_NightMode(void *pv) {
    //if (objects.pressure_gauge_scale_labels == NULL) return;
    //if (objects.pressure_gauge_scale_labels == NULL) return;
    (void)pv;
    
    bool enabled = true;

    while(1)
    {
        lv_color_t col = !enabled ? lv_color_hex(0xff5a00) : lv_color_white();
        int opac = !enabled ? 60 : 0;

        lv_obj_set_style_text_color(objects.pressure_gauge_unit, col, LV_PART_MAIN);
        lv_obj_set_style_text_color(objects.pressure_gauge_scale_labels, col, LV_PART_TICKS);
        lv_obj_set_style_img_opa(objects.pressure_needle_knop_light_shadow, opac, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(objects.pressure_black_background_opa, opac/2, LV_PART_MAIN);

        lv_meter_t * m = (lv_meter_t *)objects.pressure_gauge_scale;
        // Wir holen die erste Skala aus der internen Liste des Meters
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

        enabled = !enabled;
        vTaskDelay(pdMS_TO_TICKS(5000));

    }
}

void app_main(void)
{


    setUp_Variables();

    spi_init();
    init_lcd_backlight_pwm();
    set_lcd_brightness(0); 

    display_init(); // Ihre Funktion
    lv_init();

    buffer_init(); // Initialisiert die LVGL-Puffer für alle Displays

    driver_init(); // Initialisiert die LVGL-Treiber für alle Displays

    timer_start(); // Startet die Timer für alle Displays
    


    // UI starten
    //ui_init();  
    
    set_Displays();

    // für bildänderungen
    //lv_scr_load_anim(objects.gauge_oil_pressure_night, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false);

    //lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);



    // Timer Handler Task starten
    //xTaskCreate(lv_pressure_test, "lv_pressure_test", 4096, NULL, 1, NULL);
    //xTaskCreate(lv_temperature_test, "lv_temperature_test", 4096, NULL, 1, NULL);
    //xTaskCreate(lv_volt_test, "lv_volt_test", 4096, NULL, 1, NULL);

    //xTaskCreate(set_NightMode, "set_NightMode", 4096, NULL, 9, NULL);

    xTaskCreatePinnedToCore(lv_pressure_test, "lv_pressure_test", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(lv_temperature_test, "lv_temperature_test", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(lv_volt_test, "lv_volt_test", 4096, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(lv_tempClock_test, "lv_tempClock_test", 4096, NULL, 3, NULL, 0);


    xTaskCreatePinnedToCore(lv_tick_task, "lv_tick_task", 16384, NULL, 10, NULL, 1);
    //xTaskCreate(lv_tick_task, "lv_tick_task", 8192, NULL, 10, NULL);

    vTaskDelay(pdMS_TO_TICKS(1000));
    set_lcd_brightness(100); 
    

}
