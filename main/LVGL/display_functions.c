#include "../includes.h"
#include "../individual_config.h"

//#include "Logos/Logo.c"

struct spi_settings SPI_SETUP[NUMBER_OF_SPI];
struct display_settings DISPLAYS[NUMBER_OF_DISPLAYS];
esp_timer_handle_t periodic_timer;
ledc_timer_config_t ledc_timer = {0};
ledc_channel_config_t ledc_channel = {0};
int reset_is_set = false;
#if USE_BEEP ==true 
    gpio_config_t beeper_conf;
#endif

void set_Displays() {

    lv_disp_set_default(DISPLAYS[0].lv_displays);
    ui_init(); 
    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        lv_disp_set_default(DISPLAYS[i].lv_displays);
        switch(DISPLAYS[i].screen_selection)
        {
            case SCREEN_ID_GAUGE_OIL_PRESSURE:
                create_screen_gauge_oil_pressure_night();
                create_screen_gauge_oil_pressure();
                lv_scr_load(objects.gauge_oil_pressure);
                break;
            case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
                create_screen_gauge_oil_temperature_night();
                create_screen_gauge_oil_temperature();
                lv_scr_load(objects.gauge_oil_temperature);
                break;
            case SCREEN_ID_GAUGE_VOLTAGE:
                create_screen_gauge_voltage_night();
                create_screen_gauge_voltage();
                lv_scr_load(objects.gauge_voltage);
                break;
            case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
                create_screen_gauge_temperature_clock_night();
                create_screen_gauge_temperature_clock();
                lv_scr_load(objects.gauge_temperature_clock);
                break;
            case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
                create_screen_gauge_clock_temperature_night();
                create_screen_gauge_clock_temperature();
                lv_scr_load(objects.gauge_clock_temperature);
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_map) {    
    esp_lcd_panel_handle_t panel = (esp_lcd_panel_handle_t)disp_drv->user_data;

    // Versuche zu senden. Falls die Queue voll ist, kurz warten statt crashen.
    esp_err_t ret;
    int retry = 5;
    do {
        ret = esp_lcd_panel_draw_bitmap(panel, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
        if (ret != ESP_OK) {
            vTaskDelay(pdMS_TO_TICKS(1)); // 1ms Pause für den Bus
            retry--;
        }
    } while (ret != ESP_OK && retry > 0);

    if (ret != ESP_OK) {
        ESP_LOGE("LCD", "SPI Bus Timeout auf Display %p", panel);
    }
}

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

static void lv_tick_inc_cb(void *arg) {
    lv_tick_inc(1);
}

// Backlight per PWM dimmen

void init_lcd_backlight_pwm() {
    // 1. Timer Konfiguration
    ledc_timer.speed_mode =       LED_SPEED;
    ledc_timer.timer_num =        LED_TIMER;
    ledc_timer.duty_resolution =  LED_DUTY_RESOLUTION;
    ledc_timer.freq_hz =          LED_FREQ;              
    ledc_timer.clk_cfg =          LED_CLK;
    ledc_channel.speed_mode =     LED_SPEED;
    ledc_channel.channel =        LED_CHANNEL;
    ledc_channel.timer_sel =      LED_TIMER;
    ledc_channel.intr_type =      LED_INTR;
    ledc_channel.gpio_num =       LED_GPIO;
    ledc_channel.duty =           LED_START_BRIGHT;
    ledc_channel.hpoint =         LED_H_POINT;
    
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
}

void set_lcd_brightness(uint8_t percentage) {
    if (percentage > 100) percentage = 100;
    uint32_t duty = (LED_DUTY_RES_VALUE * percentage) / 100;
    
    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}

void spi_init(void) {
    SPI_SETUP[0].pin_sclk =             PIN_SPI_1_SCLK;
    SPI_SETUP[0].pin_mosi =             PIN_SPI_1_MOSI;
    SPI_SETUP[0].pin_miso =             PIN_SPI_1_MISO;
    SPI_SETUP[0].quadwp_io_num =        SPI_1_QUADWP_IO_NUM;
    SPI_SETUP[0].quadhd_io_num =        SPI_1_QUADHD_IO_NUM;
    SPI_SETUP[0].max_transfer_sz =      SPI_1_MAX_TRANSFER_SZ;
    SPI_SETUP[0].intr_flags =           SPI_1_INTR_FLAGS;
    SPI_SETUP[0].spi_host =             LCD_HOST_1;
    SPI_SETUP[0].spi_dma =              SPI_1_DMA;

    #if NUMBER_OF_SPI > 1
        SPI_SETUP[1].pin_sclk =         PIN_SPI_2_SCLK;
        SPI_SETUP[1].pin_mosi =         PIN_SPI_2_MOSI;
        SPI_SETUP[1].pin_miso =         PIN_SPI_2_MISO;
        SPI_SETUP[1].quadwp_io_num =    SPI_2_QUADWP_IO_NUM;
        SPI_SETUP[1].quadhd_io_num =    SPI_2_QUADHD_IO_NUM;
        SPI_SETUP[1].max_transfer_sz =  SPI_2_MAX_TRANSFER_SZ;
        SPI_SETUP[1].intr_flags =       SPI_2_INTR_FLAGS;
        SPI_SETUP[1].spi_host =         LCD_HOST_2;
        SPI_SETUP[1].spi_dma =          SPI_2_DMA;
    #endif

    for (int i = 0; i < NUMBER_OF_SPI; i++)
    {
        SPI_SETUP[i].buscfg.sclk_io_num =     SPI_SETUP[i].pin_sclk;
        SPI_SETUP[i].buscfg.mosi_io_num =     SPI_SETUP[i].pin_mosi;
        SPI_SETUP[i].buscfg.miso_io_num =     SPI_SETUP[i].pin_miso;
        SPI_SETUP[i].buscfg.quadwp_io_num =   SPI_SETUP[i].quadwp_io_num;
        SPI_SETUP[i].buscfg.quadhd_io_num =   SPI_SETUP[i].quadhd_io_num;
        SPI_SETUP[i].buscfg.max_transfer_sz = SPI_SETUP[i].max_transfer_sz; 
        SPI_SETUP[i].buscfg.intr_flags =      SPI_SETUP[i].intr_flags;
        ESP_ERROR_CHECK(spi_bus_initialize(SPI_SETUP[i].spi_host, &(SPI_SETUP[i].buscfg), SPI_SETUP[i].spi_dma)); // Enable the DMA feature
    }
}

void display_init(void)
{
    set_lcd_brightness(0); 

    DISPLAYS[0].screen_selection =       LCD_1_SCREEN_ID;
    DISPLAYS[0].spi_host =               LCD_1_SPI_HOST;
    DISPLAYS[0].lcd_pin_dc =             PIN_LCD_1_DC;
    DISPLAYS[0].lcd_pin_cs =             PIN_LCD_1_CS;
    DISPLAYS[0].lcd_pin_rst =            PIN_LCD_1_RST;
    DISPLAYS[0].lcd_res_h =              LCD_1_H_RES;
    DISPLAYS[0].lcd_res_v =              LCD_1_V_RES;
    DISPLAYS[0].lcd_rgb_order =          LCD_1_RGB_ELEMENT_ORDER_BGR;
    DISPLAYS[0].lcd_invert_color =       LCD_1_INVERT_COLOR;
    DISPLAYS[0].lcd_mirror_x =           LCD_1_MIRROR_X;
    DISPLAYS[0].lcd_mirror_y =           LCD_1_MIRROR_Y;
    DISPLAYS[0].malloc_cap =             LCD_1_MALLOC_CAP;
    DISPLAYS[0].buffer_factor =          LCD_1_BUFFER_FACTOR;
    DISPLAYS[0].task_step_depth =        TASK_1_STEPDEPTH_SCREEN;
    DISPLAYS[0].task_priority =          TASK_1_PRIORITY_SCREEN;
    DISPLAYS[0].task_delay_time_ms =     TASK_1_DELAYTIME_SCREEN;
    DISPLAYS[0].tast_core =              TASK_1_CORE_SCREEN;
    
    #if NUMBER_OF_DISPLAYS > 1
        DISPLAYS[1].screen_selection =     LCD_2_SCREEN_ID;
        DISPLAYS[1].spi_host =             LCD_2_SPI_HOST;
        DISPLAYS[1].lcd_pin_dc =           PIN_LCD_2_DC;
        DISPLAYS[1].lcd_pin_cs =           PIN_LCD_2_CS;
        DISPLAYS[1].lcd_pin_rst =          PIN_LCD_2_RST;
        DISPLAYS[1].lcd_res_h =            LCD_2_H_RES;
        DISPLAYS[1].lcd_res_v =            LCD_2_V_RES;
        DISPLAYS[1].lcd_rgb_order =        LCD_2_RGB_ELEMENT_ORDER_BGR;
        DISPLAYS[1].lcd_invert_color =     LCD_2_INVERT_COLOR;
        DISPLAYS[1].lcd_mirror_x =         LCD_2_MIRROR_X;
        DISPLAYS[1].lcd_mirror_y =         LCD_2_MIRROR_Y;
        DISPLAYS[1].malloc_cap =           LCD_2_MALLOC_CAP;
        DISPLAYS[1].buffer_factor =        LCD_2_BUFFER_FACTOR;
        DISPLAYS[1].task_step_depth =      TASK_2_STEPDEPTH_SCREEN;
        DISPLAYS[1].task_priority =        TASK_2_PRIORITY_SCREEN;
        DISPLAYS[1].task_delay_time_ms =   TASK_2_DELAYTIME_SCREEN;
        DISPLAYS[1].tast_core =            TASK_2_CORE_SCREEN;
    #endif
    #if NUMBER_OF_DISPLAYS > 2 
        DISPLAYS[2].screen_selection =     LCD_3_SCREEN_ID;
        DISPLAYS[2].spi_host =             LCD_3_SPI_HOST;
        DISPLAYS[2].lcd_pin_dc =           PIN_LCD_3_DC;
        DISPLAYS[2].lcd_pin_cs =           PIN_LCD_3_CS;
        DISPLAYS[2].lcd_pin_rst =          PIN_LCD_3_RST;
        DISPLAYS[2].lcd_res_h =            LCD_3_H_RES;
        DISPLAYS[2].lcd_res_v =            LCD_3_V_RES;
        DISPLAYS[2].lcd_rgb_order =        LCD_3_RGB_ELEMENT_ORDER_BGR;
        DISPLAYS[2].lcd_invert_color =     LCD_3_INVERT_COLOR;
        DISPLAYS[2].lcd_mirror_x =         LCD_3_MIRROR_X;
        DISPLAYS[2].lcd_mirror_y =         LCD_3_MIRROR_Y;
        DISPLAYS[2].malloc_cap =           LCD_3_MALLOC_CAP;
        DISPLAYS[2].buffer_factor =        LCD_3_BUFFER_FACTOR;
        DISPLAYS[2].task_step_depth =      TASK_3_STEPDEPTH_SCREEN;
        DISPLAYS[2].task_priority =        TASK_3_PRIORITY_SCREEN;
        DISPLAYS[2].task_delay_time_ms =   TASK_3_DELAYTIME_SCREEN;
        DISPLAYS[2].tast_core =            TASK_3_CORE_SCREEN;
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        DISPLAYS[3].screen_selection =     LCD_4_SCREEN_ID;
        DISPLAYS[3].spi_host =             LCD_4_SPI_HOST;
        DISPLAYS[3].lcd_pin_dc =           PIN_LCD_4_DC;
        DISPLAYS[3].lcd_pin_cs =           PIN_LCD_4_CS;
        DISPLAYS[3].lcd_pin_rst =          PIN_LCD_4_RST;
        DISPLAYS[3].lcd_res_h =            LCD_4_H_RES;
        DISPLAYS[3].lcd_res_v =            LCD_4_V_RES;
        DISPLAYS[3].lcd_rgb_order =        LCD_4_RGB_ELEMENT_ORDER_BGR;
        DISPLAYS[3].lcd_invert_color =     LCD_4_INVERT_COLOR;
        DISPLAYS[3].lcd_mirror_x =         LCD_4_MIRROR_X;
        DISPLAYS[3].lcd_mirror_y =         LCD_4_MIRROR_Y;
        DISPLAYS[3].malloc_cap =           LCD_4_MALLOC_CAP;
        DISPLAYS[3].buffer_factor =        LCD_4_BUFFER_FACTOR;
        DISPLAYS[3].task_step_depth =      TASK_4_STEPDEPTH_SCREEN;
        DISPLAYS[3].task_priority =        TASK_4_PRIORITY_SCREEN;
        DISPLAYS[3].task_delay_time_ms =   TASK_4_DELAYTIME_SCREEN;
        DISPLAYS[3].tast_core =            TASK_4_CORE_SCREEN;
    #endif

    for(int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        
        DISPLAYS[i].io_config.dc_gpio_num =         DISPLAYS[i].lcd_pin_dc;
        DISPLAYS[i].io_config.cs_gpio_num =         DISPLAYS[i].lcd_pin_cs;
        DISPLAYS[i].io_config.pclk_hz =             LCD_PIXEL_CLOCK_HZ;
        DISPLAYS[i].io_config.lcd_cmd_bits =        LCD_CMD_BITS; // muss angepasst werden
        DISPLAYS[i].io_config.lcd_param_bits =      LCD_PARAM_BITS; // muss angepasst werden
        DISPLAYS[i].io_config.spi_mode =            SPI_MODE; //0
        DISPLAYS[i].io_config.trans_queue_depth =   TRANS_QUEUE_DEPTH; //10
        DISPLAYS[i].io_config.on_color_trans_done = notify_lvgl_flush_ready; // Callback für LVGL
        DISPLAYS[i].io_config.user_ctx =            &(DISPLAYS[i].disp_drv);      // LVGL Display-Treiber Kontext
        
        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)(DISPLAYS[i].spi_host), &(DISPLAYS[i].io_config), &(DISPLAYS[i].io_handle)));

        DISPLAYS[i].panel_config.reset_gpio_num =   DISPLAYS[i].lcd_pin_rst;
        DISPLAYS[i].panel_config.rgb_ele_order =    DISPLAYS[i].lcd_rgb_order; // muss angepasst werden
        DISPLAYS[i].panel_config.bits_per_pixel =   16;
        
        // Create LCD panel handle for ST7789, with the SPI IO device handle
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(DISPLAYS[i].io_handle, &(DISPLAYS[i].panel_config), &(DISPLAYS[i].panel_handle)));
        if (!reset_is_set)
        {
            // Bei gemeinsamen Ressets nur einaml Reset aufrufen
            ESP_ERROR_CHECK(esp_lcd_panel_reset(DISPLAYS[i].panel_handle));
            reset_is_set = true;
        }
    
        // Initialize the LCD panel
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(DISPLAYS[i].panel_handle, 0, 0));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(DISPLAYS[i].panel_handle, false));
        ESP_ERROR_CHECK(esp_lcd_panel_init(DISPLAYS[i].panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(DISPLAYS[i].panel_handle, DISPLAYS[i].lcd_invert_color)); // Optional: Invertiere die Farben für besseren Kontrast auf manchen Displays
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(DISPLAYS[i].panel_handle, true));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(DISPLAYS[i].panel_handle, DISPLAYS[i].lcd_mirror_x, DISPLAYS[i].lcd_mirror_y)); // Optional: Spiegeln des Displays horizontal
    
        DISPLAYS[i].lvgl_mux = xSemaphoreCreateMutex();
    }

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_inc_cb,
        .name = "periodic_gui"
    };
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));  

}

void buffer_and_driver_init()
{
    for(int i = 0; i < NUMBER_OF_DISPLAYS; i++)
    {
        // buffer init
        DISPLAYS[i].buf = heap_caps_malloc(DISPLAYS[i].lcd_res_h * (DISPLAYS[i].lcd_res_v / DISPLAYS[i].buffer_factor) * sizeof(lv_color_t), DISPLAYS[i].malloc_cap);
        memset(DISPLAYS[i].buf, 0, DISPLAYS[i].lcd_res_h * (DISPLAYS[i].lcd_res_v / DISPLAYS[i].buffer_factor) * sizeof(lv_color_t));
        lv_disp_draw_buf_init(&(DISPLAYS[i].draw_buf), DISPLAYS[i].buf, NULL, DISPLAYS[i].lcd_res_h * (DISPLAYS[i].lcd_res_v / DISPLAYS[i].buffer_factor));
        
        // driver_init
        lv_disp_drv_init(&(DISPLAYS[i].disp_drv));
        DISPLAYS[i].disp_drv.hor_res =      DISPLAYS[i].lcd_res_h;
        DISPLAYS[i].disp_drv.ver_res =      DISPLAYS[i].lcd_res_v;
        DISPLAYS[i].disp_drv.flush_cb =     lvgl_flush_cb;
        DISPLAYS[i].disp_drv.draw_buf =     &(DISPLAYS[i].draw_buf);
        DISPLAYS[i].disp_drv.user_data =    DISPLAYS[i].panel_handle;
        DISPLAYS[i].disp_drv.full_refresh = 1; 
        DISPLAYS[i].lv_displays =           lv_disp_drv_register(&(DISPLAYS[i].disp_drv));
    }
}

void timer_start() {    
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000)); // 1ms Tick
}


#if USE_BEEP == true
    void beeper_init(){ 

        // Timer von Backlight und Beeper passen nicht zusammen
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_1,
        .freq_hz = 2700,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num = BEEPER_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0
    };
    
    ledc_channel_config(&channel);
    }
#endif
