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
#include "lvgl/Gauge_All/src/ui/vars.h"
#include "../managed_components/lvgl__lvgl/src/extra/widgets/meter/lv_meter.h"

#include <string.h>

#include "individual_config.h"


extern esp_lcd_panel_io_handle_t io_handle[NUMBER_OF_DISPLAYS];
extern esp_lcd_panel_handle_t panel_handle[NUMBER_OF_DISPLAYS];
extern esp_timer_handle_t periodic_timer;
extern lv_disp_t *lv_displays[NUMBER_OF_DISPLAYS];
extern lv_obj_t *nadeln[NUMBER_OF_DISPLAYS];

// defined in /lvgl/display_functions.c
void setUp_Variables();
void spi_init();
void init_lcd_backlight_pwm();
void set_lcd_brightness(uint8_t percentage); 
void display_init();
void buffer_init(); // Initialisiert die LVGL-Puffer für alle Displays
void driver_init(); // Initialisiert die LVGL-Treiber für alle Displays
void timer_start(); // Startet die Timer für alle Displays
void set_Displays();
