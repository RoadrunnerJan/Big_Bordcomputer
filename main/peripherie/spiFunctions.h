#pragma once

/*
 * ============================================================================
 * SPI DISPLAY DRIVER - Multi Display Control via SPI Interface
 * ============================================================================
 * Manages SPI communication with multiple LCD displays using ESP-IDF LCD driver
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - Multi-display SPI initialization (up to 4 displays)
 *      - LVGL integration for graphics rendering
 *      - Display task scheduling and timing
 *
 */

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF LCD Drivers ===== */
#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_commands.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_io_spi.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "driver/ledc.h"
#include "esp_timer.h"

/* ===== LVGL Graphics Library ===== */
#include "lvgl.h"
#include "esp_heap_caps.h"
#include "../lvgl/src/ui/ui.h"
#include "../lvgl/src/ui/screens.h"
#include "../lvgl/src/ui/vars.h"
#include "../managed_components/lvgl__lvgl/src/extra/widgets/meter/lv_meter.h"

/* ===== RTOS & System ===== */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


/* ===== SPI Configuration Structure ===== */
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

/* ===== Display Configuration Structure ===== */
struct display_settings
{
    // Hardware & Connection
    spi_host_device_t spi_host;
    int screen_selection;
    
    // Pin Configuration
    int lcd_pin_dc;
    int lcd_pin_cs;
    int lcd_pin_rst;
    
    // Display Settings
    int lcd_res_h;
    int lcd_res_v;
    lcd_rgb_element_order_t lcd_rgb_order;
    bool lcd_invert_color;
    bool lcd_mirror_x;
    bool lcd_mirror_y;
    
    // Memory & Buffering
    int malloc_cap;
    int buffer_factor;
    
    // Task Configuration
    int task_step_depth;
    int task_priority;
    int task_delay_time_ms;
    int tast_core;
    
    // ESP-IDF Panel Handles
    esp_lcd_panel_io_handle_t io_handle;
    esp_lcd_panel_handle_t panel_handle;
    
    // LVGL Configuration
    lv_disp_t *lv_displays;
    lv_color_t *buf;
    lv_disp_drv_t disp_drv;
    lv_disp_draw_buf_t draw_buf;
    
    // Configuration Structures
    esp_lcd_panel_io_spi_config_t io_config;
    esp_lcd_panel_dev_config_t panel_config;
};


/* ===== Global Variables ===== */
extern struct spi_settings SPI_SETUP[NUMBER_OF_SPI];
extern struct display_settings DISPLAYS[NUMBER_OF_DISPLAYS];
extern esp_timer_handle_t periodic_timer;


/* ===== Function Declarations ===== */

void setUp_Variables(void);
void spi_init(void);
void display_init(void);
void buffer_and_driver_init(void);
void timer_start(void);
void set_Displays(void);




