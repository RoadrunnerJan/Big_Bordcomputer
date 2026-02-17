#pragma once


#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "esp_log.h"
#include "esp_task_wdt.h"

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
#include "lvgl/Gauge_All/src/ui/screens.h"
#include "lvgl/Gauge_All/src/ui/vars.h"
#include "../managed_components/lvgl__lvgl/src/extra/widgets/meter/lv_meter.h"

#include <string.h>

#include "individual_config.h"
#include <time.h>

struct spi_settings
{
    int pin_sclk;
    int pin_mosi;
    int pin_miso;
    int quadwp_io_num;
    int quadhd_io_num;
    int max_transfer_sz;
    int intr_flags;
    spi_host_device_t spi_host;
    spi_common_dma_t spi_dma;

    spi_bus_config_t buscfg;
};

struct display_settings
{
    spi_host_device_t spi_host;
    int screen_selection; //ScreensEnum

    int lcd_pin_dc;
    int lcd_pin_cs;
    int lcd_pin_rst;
    int lcd_res_h;
    int lcd_res_v;
    lcd_rgb_element_order_t lcd_rgb_order;
    bool lcd_invert_color;
    bool lcd_mirror_x;
    bool lcd_mirror_y;
    int malloc_cap;
    int buffer_factor;
    int task_step_depth;
    int task_priority;
    int task_delay_time_ms;
    int tast_core;
    

    esp_lcd_panel_io_handle_t io_handle;
    esp_lcd_panel_handle_t panel_handle;
    lv_disp_t *lv_displays;
    lv_color_t *buf;
    lv_disp_drv_t disp_drv;
    lv_disp_draw_buf_t draw_buf;
    esp_lcd_panel_io_spi_config_t io_config;
    esp_lcd_panel_dev_config_t panel_config;

};

extern struct spi_settings SPI_SETUP[NUMBER_OF_SPI];
extern struct display_settings DISPLAYS[NUMBER_OF_DISPLAYS];

extern esp_timer_handle_t periodic_timer;
// Backlight
extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

// defined in /lvgl/display_functions.c
void setUp_Variables();
void spi_init();
void init_lcd_backlight_pwm();
void set_lcd_brightness(uint8_t percentage); 
void display_init();
void buffer_and_driver_init(); // Initialisiert die LVGL-Puffer für alle Displays
void timer_start(); // Startet die Timer für alle Displays
void set_Displays();
