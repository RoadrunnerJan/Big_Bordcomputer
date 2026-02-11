/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "esp_log.h"


#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_commands.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_io_spi.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "driver/ledc.h"
#include "esp_timer.h"      // Für esp_timer_create_args_t


#include "lvgl.h"
#include "esp_heap_caps.h"

/* Include your generated UI header here - adjust the path to your UI */
#include "lvgl/Gauge_All/src/ui/ui.h"
#include "lvgl/Gauge_All/src/ui/vars.h"
#include "../managed_components/lvgl__lvgl/src/extra/widgets/meter/lv_meter.h"

#include <string.h>

#include "Logo.c"
#include "jro.c"

#define LCD_HOST SPI2_HOST

/*MOSI (DIN): 32
MISO: 33
SCK (CLK): 36
CS/SS: 26*/

// keine Strapping-Pins (GPIO 34-38) für SPI-Signale

#define PIN_SPI_SCLK 30
#define PIN_SPI_MOSI 29
#define PIN_SPI_MISO -1
#define PIN_LCD_BL      54

#define PIN_LCD_1_CS 28
#define PIN_LCD_2_CS 0
#define PIN_LCD_3_CS 0
#define PIN_LCD_4_CS 0

#define PIN_LCD_1_DC 49
#define PIN_LCD_2_DC 0
#define PIN_LCD_3_DC 0
#define PIN_LCD_4_DC 0


#define PIN_LCD_1_RST 50
#define PIN_LCD_2_RST 0
#define PIN_LCD_3_RST 0
#define PIN_LCD_4_RST 0

#define LCD_1_H_RES 240
#define LCD_1_V_RES 240
#define LCD_2_H_RES 240
#define LCD_2_V_RES 240
#define LCD_3_H_RES 240
#define LCD_3_V_RES 240
#define LCD_4_H_RES 240
#define LCD_4_V_RES 240

#define LCD_PIXEL_CLOCK_HZ 40*1000*1000  // 40MHz
#define LCD_CMD_BITS 8
#define LCD_PARAM_BITS 8

esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_handle_t panel_handle = NULL;
esp_timer_handle_t periodic_timer = NULL;
static lv_disp_drv_t disp_drv;
/*
static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}*/

static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_map) {
    // WICHTIG: Hier KEIN lv_disp_flush_ready aufrufen!
    esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
}

// Dieser wird automatisch gerufen, wenn die Hardware FERTIG ist
static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver); // Jetzt darf LVGL den nächsten Teil schicken
    return false;
}


static void lv_tick_inc_cb(void *arg) {
    lv_tick_inc(1);
}

// Backlight per PWM dimmen

void init_lcd_backlight_pwm() {
    // 1. Timer Konfiguration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT, // 0 bis 8191
        .freq_hz          = 5000,              // 5 kHz (flimmerfrei)
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 2. Kanal Konfiguration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = PIN_LCD_BL,
        .duty           = 4095, // Start-Helligkeit 50% (8191 / 2)
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

void set_lcd_brightness(uint8_t percentage) {
    if (percentage > 100) percentage = 100;
    
    // Berechnung der Duty-Cycle basierend auf 13-bit Resolution
    uint32_t duty = (8191 * percentage) / 100;
    
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
static void display_init(void)
{
    
    //gpio_set_direction(PIN_LCD_1_BL, GPIO_MODE_OUTPUT);
    //gpio_set_level(PIN_LCD_1_BL, 1); // Turn on the backlight

    spi_bus_config_t buscfg = {
    .sclk_io_num = PIN_SPI_SCLK,
    .mosi_io_num = PIN_SPI_MOSI,
    .miso_io_num = PIN_SPI_MISO,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 240 * 120 * sizeof(uint16_t), // Nur 240 Zeilen statt des ganzen Bildes

    //.max_transfer_sz = 240 * 240 * sizeof(uint16_t), // Voller Frame-Buffer Support (assume pixel is RGB565) at most in one SPI transaction
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO)); // Enable the DMA feature

    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_LCD_1_DC,
        .cs_gpio_num = PIN_LCD_1_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = LCD_CMD_BITS, // muss angepasst werden
        .lcd_param_bits = LCD_PARAM_BITS, // muss angepasst werden
        .spi_mode = 3, //0
        .trans_queue_depth = 10,
        .on_color_trans_done = notify_lvgl_flush_ready, // Callback für LVGL
        .user_ctx = &disp_drv,      // LVGL Display-Treiber Kontext
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_LCD_1_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR, // muss angepasst werden
        .bits_per_pixel = 16,
    };
    // Create LCD panel handle for ST7789, with the SPI IO device handle
    ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle, &panel_config, &panel_handle));

    // Initialize the LCD panel
    int x_gap = 0; // Setze den horizontalen Gap auf 0
    int y_gap = 0; // Setze den vertikalen Gap auf 0
    esp_lcd_panel_set_gap(panel_handle, x_gap, y_gap);
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    esp_lcd_panel_disp_on_off(panel_handle, false); 


    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true)); // Optional: Invertiere die Farben für besseren Kontrast auf manchen Displays

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    init_lcd_backlight_pwm();
    set_lcd_brightness(0); 

    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false)); // Optional: Spiegeln des Displays horizontal


    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_inc_cb,
        .name = "periodic_gui"
    };
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));


    
    // Logos
    
   // esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 240, 240, Logo_map);
    //vTaskDelay(pdMS_TO_TICKS(500));
    //esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 240, 240, jro_map);
    //vTaskDelay(pdMS_TO_TICKS(2000));
    

}




/* Top-level LVGL support objects and functions */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf1 = NULL;
static lv_color_t *buf2 = NULL;


/*
static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_map)
{    
    uint16_t x_start = area->x1;
    uint16_t y_start = area->y1;
    uint16_t x_end   = area->x2 + 1;
    uint16_t y_end   = area->y2 + 1;

    // Sicherstellen, dass die Werte innerhalb der 240x240 Grenzen liegen
    if (x_end > 240) x_end = 240;
    if (y_end > 240) y_end = 240;

    esp_lcd_panel_draw_bitmap(panel_handle, x_start, y_start, x_end, y_end, color_map);

    //esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, w, h, (uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv);

}*/

static void lv_tick_task(void *pv)
{
    (void)pv;
    while (1) {
        lv_obj_invalidate(lv_scr_act());

        ui_tick();
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}




double lvgl_value_temperature;
char lvgl_value_clock[100] = { 0 };
double lvgl_value_oil_pressure;
int32_t lvgl_value_oil_temperature;
double lvgl_value_voltage;
char lvgl_value_temperature_string[100] = { 0 };
char lvgl_value_voltage_string[100] = { 0 };
char lvgl_value_oil_temperature_string[100] = { 0 };
char lvgl_value_oil_pressure_string[100] = { 0 };

const char *get_var_lvgl_value_oil_pressure_string() {
    return lvgl_value_oil_pressure_string;
}

void set_var_lvgl_value_oil_pressure_string(const char *value) {
    strncpy(lvgl_value_oil_pressure_string, value, sizeof(lvgl_value_oil_pressure_string) / sizeof(char));
    lvgl_value_oil_pressure_string[sizeof(lvgl_value_oil_pressure_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_oil_temperature_string() {
    return lvgl_value_oil_temperature_string;
}

void set_var_lvgl_value_oil_temperature_string(const char *value) {
    strncpy(lvgl_value_oil_temperature_string, value, sizeof(lvgl_value_oil_temperature_string) / sizeof(char));
    lvgl_value_oil_temperature_string[sizeof(lvgl_value_oil_temperature_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_voltage_string() {
    return lvgl_value_voltage_string;
}

void set_var_lvgl_value_voltage_string(const char *value) {
    strncpy(lvgl_value_voltage_string, value, sizeof(lvgl_value_voltage_string) / sizeof(char));
    lvgl_value_voltage_string[sizeof(lvgl_value_voltage_string) / sizeof(char) - 1] = 0;
}

const char *get_var_lvgl_value_temperature_string() {
    return lvgl_value_temperature_string;
}

void set_var_lvgl_value_temperature_string(const char *value) {
    strncpy(lvgl_value_temperature_string, value, sizeof(lvgl_value_temperature_string) / sizeof(char));
    lvgl_value_temperature_string[sizeof(lvgl_value_temperature_string) / sizeof(char) - 1] = 0;
}


double get_var_lvgl_value_voltage() {
    return lvgl_value_voltage;
}

void set_var_lvgl_value_voltage(double value) {
    lvgl_value_voltage = value;
}

int32_t get_var_lvgl_value_oil_temperature() {
    return lvgl_value_oil_temperature;
}

void set_var_lvgl_value_oil_temperature(int32_t value) {
    lvgl_value_oil_temperature = value;
}

double get_var_lvgl_value_oil_pressure() {
    return lvgl_value_oil_pressure;
}

void set_var_lvgl_value_oil_pressure(double value) {
    lvgl_value_oil_pressure = value;
}


double get_var_lvgl_value_temperature() {
    return lvgl_value_temperature;
}

void set_var_lvgl_value_temperature(double value) {
    lvgl_value_temperature = value;
}


const char *get_var_lvgl_value_clock() {
    return lvgl_value_clock;
}

void set_var_lvgl_value_clock(const char *value) {
    strncpy(lvgl_value_clock, value, sizeof(lvgl_value_clock) / sizeof(char));
    lvgl_value_clock[sizeof(lvgl_value_clock) / sizeof(char) - 1] = 0;
}

static double pressure_value = 0.0;
static int pressure_test_switch = 0;
static const char *TAG = "MEIN_PROJEKT";
static void lv_pressure_test(void *pv)
{
    (void)pv;

    char ziel_string[20];

    while (1) {
        switch (pressure_test_switch) {
            case 0:
                pressure_value += 0.1;
                if (pressure_value >= 3.5) {
                    pressure_test_switch = 1;
                }
                break;
            case 1:
                pressure_value -= 0.1;
                if (pressure_value <= 2.5) {
                    pressure_test_switch = 2;
                }
                break;
            case 2:
                pressure_value += 0.1;
                if (pressure_value >= 5.5) {
                    pressure_test_switch = 3;
                }
                break;
            case 3:
                pressure_value -= 0.1;
                if (pressure_value <= 0.04) {
                    pressure_test_switch = 0;
                }
                break;
        }

        snprintf(ziel_string, sizeof(ziel_string), "%.1f", pressure_value);

        set_var_lvgl_value_oil_pressure(pressure_value*1000);
        set_var_lvgl_value_oil_pressure_string(ziel_string);


        vTaskDelay(pdMS_TO_TICKS(10));

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

static void set_NightMode(void *pv) {
    //if (objects.pressure_gauge_scale_labels == NULL) return;
    //if (objects.pressure_gauge_scale_labels == NULL) return;
    (void)pv;
    
    bool enabled = false;

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

    display_init(); // Ihre Funktion
    lv_init();

    // Puffer allokieren (Wichtig: im internen RAM für Geschwindigkeit)
    buf1 = heap_caps_malloc(LCD_1_H_RES * LCD_1_V_RES * sizeof(lv_color_t), MALLOC_CAP_DMA);
    memset(buf1, 0, 240 * 240 * sizeof(lv_color_t));

    //buf2 = heap_caps_malloc(LCD_1_H_RES * 60 * sizeof(lv_color_t), MALLOC_CAP_DMA);

    //lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_1_H_RES * LCD_1_V_RES);
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LCD_1_H_RES * LCD_1_V_RES);

    // Treiber registrieren
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_1_H_RES;
    disp_drv.ver_res = LCD_1_V_RES;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = panel_handle;
    disp_drv.full_refresh = 1; 
    lv_disp_drv_register(&disp_drv);
    

    // Tick-Timer starten (siehe Punkt 1)
    // ...

    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000)); // 1ms Tick

    // UI starten
    ui_init(); 

    // für bildänderungen
    //lv_scr_load_anim(objects.gauge_oil_pressure_night, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false);

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);



    // Timer Handler Task starten
    xTaskCreate(lv_pressure_test, "lv_pressure_test", 4096, NULL, 1, NULL);
    xTaskCreate(set_NightMode, "set_NightMode", 4096, NULL, 9, NULL);
    xTaskCreate(lv_tick_task, "lv_tick_task", 8192, NULL, 10, NULL);

    vTaskDelay(pdMS_TO_TICKS(250));
    set_lcd_brightness(100); 
    

}
