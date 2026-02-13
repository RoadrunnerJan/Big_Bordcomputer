#include "../includes.h"
#include "../individual_config.h"

esp_lcd_panel_io_handle_t io_handle[NUMBER_OF_DISPLAYS];
esp_lcd_panel_handle_t panel_handle[NUMBER_OF_DISPLAYS];
esp_timer_handle_t periodic_timer;
static lv_disp_drv_t disp_drv[NUMBER_OF_DISPLAYS];
static lv_disp_draw_buf_t draw_buf[NUMBER_OF_DISPLAYS];
static lv_color_t *buf[NUMBER_OF_DISPLAYS];
lv_disp_t *lv_displays[NUMBER_OF_DISPLAYS];

void setUp_Variables() {
    /*
    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++) {
        io_handle[i] = NULL;
        panel_handle[i] = NULL;
        disp_drv[i] = (lv_disp_drv_t){0};
        draw_buf[i] = (lv_disp_draw_buf_t){0};
        buf[i] = NULL;
    }
    periodic_timer = NULL;
    */
}
void move_screen_to_display(lv_obj_t * screen, lv_disp_t * target_disp) {
    if (!screen || !target_disp) return;
    
    // In LVGL 8.3 zieht man einen Screen um, indem man 
    // das Standard-Display setzt und den Screen dort "befestigt"
    lv_disp_t * old_disp = lv_obj_get_disp(screen);
    if(old_disp == target_disp) return;

    // Da man in v8.3 Screens nicht einfach umhängen kann,
    // ist der sicherste Weg, das Display für den Screen-Wechsel vorzubereiten:
    lv_disp_set_default(target_disp);
    lv_scr_load(screen);
}

void set_Displays() {

    lv_disp_set_default(lv_displays[0]);
    ui_init(); // Initialisiert alles auf Display 0
    create_screen_gauge_oil_pressure();
    #if NUMBER_OF_DISPLAYS > 1
        lv_disp_set_default(lv_displays[1]);
        create_screen_gauge_oil_temperature();
        //lv_disp_load_scr(objects.gauge_oil_temperature); 
    #endif
    #if NUMBER_OF_DISPLAYS > 2
        lv_disp_set_default(lv_displays[2]);
        create_screen_gauge_voltage();
    //lv_disp_load_scr(objects.gauge_voltage); 
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        lv_disp_set_default(lv_displays[3]);
        create_screen_gauge_temperature_clock();
        //nadeln[4] = objects.gauge_voltage;


        //lv_disp_load_scr(objects.gauge_temperature_clock); 
    #endif



/*

    //lv_disp_t *dispp = lv_disp_get_default();

    create_screen_gauge_voltage();
    create_screen_gauge_temperature_clock();
    create_screen_gauge_oil_temperature();
    create_screen_gauge_oil_pressure();
    
    lv_theme_t *theme_1 = lv_theme_default_init(lv_displays[0], lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_displays[0], theme_1);    
    lv_theme_t *theme_2 = lv_theme_default_init(lv_displays[1], lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_displays[1], theme_2);    
   


    lv_disp_set_default(lv_displays[0]);
    loadScreen(SCREEN_ID_GAUGE_OIL_PRESSURE);
    lv_disp_set_default(lv_displays[1]);
    loadScreen(SCREEN_ID_GAUGE_OIL_TEMPERATURE);

    //theme = lv_theme_default_init(lv_displays[2], lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    //lv_disp_set_theme(lv_displays[2], theme);    
    //loadScreen(SCREEN_ID_GAUGE_VOLTAGE);
    
    */


/*
    create_screen_gauge_oil_temperature();
    create_screen_gauge_voltage();
    create_screen_gauge_temperature_clock();

    */







    lv_disp_set_default(lv_displays[0]);
    lv_scr_load(objects.gauge_oil_pressure);
    vTaskDelay(pdMS_TO_TICKS(10));

    #if NUMBER_OF_DISPLAYS > 1
        lv_disp_set_default(lv_displays[1]);
        //lv_scr_load_anim(objects.gauge_oil_temperature, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); 
        lv_scr_load(objects.gauge_oil_temperature);
        vTaskDelay(pdMS_TO_TICKS(10));
    #endif

    #if NUMBER_OF_DISPLAYS > 2
        lv_disp_set_default(lv_displays[2]);
        lv_scr_load(objects.gauge_voltage);
        vTaskDelay(pdMS_TO_TICKS(10));
    #endif

    #if NUMBER_OF_DISPLAYS > 3
        lv_disp_set_default(lv_displays[3]);
        lv_scr_load(objects.gauge_temperature_clock);
        vTaskDelay(pdMS_TO_TICKS(10));
    #endif
    
}

/*static void lvgl_flush_cb(esp_lcd_panel_handle_t *panel_handle, const lv_area_t *area, lv_color_t *color_map) {
    // WICHTIG: Hier KEIN lv_disp_flush_ready aufrufen!
    esp_lcd_panel_draw_bitmap(&panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
}*/
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

void spi_init(void) {
    spi_bus_config_t buscfg_1 = {
        .sclk_io_num = PIN_SPI_SCLK_1,
        .mosi_io_num = PIN_SPI_MOSI_1,
        .miso_io_num = PIN_SPI_MISO_1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_1_H_RES * LCD_1_V_RES * sizeof(uint16_t), 
        .intr_flags = ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3, // Level 3 für hohe Priorität
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST_1, &buscfg_1, SPI_DMA_CH_AUTO)); // Enable the DMA feature

    #if NUMBER_OF_DISPLAYS > 2
        spi_bus_config_t buscfg_2 = {
            .sclk_io_num = PIN_SPI_SCLK_2,
            .mosi_io_num = PIN_SPI_MOSI_2,
            .miso_io_num = PIN_SPI_MISO_2,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = LCD_3_H_RES * LCD_3_V_RES * sizeof(uint16_t),     
            .intr_flags = ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3, // Level 3 für hohe Priorität
        };
        ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST_2, &buscfg_2, SPI_DMA_CH_AUTO)); // Enable the DMA feature
    #endif
}

void display_init(void)
{
    set_lcd_brightness(0); 
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_LCD_1_DC,
        .cs_gpio_num = PIN_LCD_1_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = LCD_CMD_BITS, // muss angepasst werden
        .lcd_param_bits = LCD_PARAM_BITS, // muss angepasst werden
        .spi_mode = SPI_MODE, //0
        .trans_queue_depth = TRANS_QUEUE_DEPTH, //10
        .on_color_trans_done = notify_lvgl_flush_ready, // Callback für LVGL
        .user_ctx = &disp_drv[0],      // LVGL Display-Treiber Kontext
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST_1, &io_config, &(io_handle[0])));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_LCD_1_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR_1, // muss angepasst werden
        .bits_per_pixel = 16,
    };
    // Create LCD panel handle for ST7789, with the SPI IO device handle
    ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle[0], &panel_config, &(panel_handle)[0]));
    // Bei gemeinsamen Ressets nur einaml Reset aufrufen
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle[0]));

    #if NUMBER_OF_DISPLAYS > 1
        esp_lcd_panel_io_spi_config_t io_config_2 = {
            .dc_gpio_num = PIN_LCD_2_DC,
            .cs_gpio_num = PIN_LCD_2_CS,
            .pclk_hz = LCD_PIXEL_CLOCK_HZ,
            .lcd_cmd_bits = LCD_CMD_BITS, // muss angepasst werden
            .lcd_param_bits = LCD_PARAM_BITS, // muss angepasst werden
            .spi_mode = SPI_MODE, //0
            .trans_queue_depth = TRANS_QUEUE_DEPTH, //10
            .on_color_trans_done = notify_lvgl_flush_ready, // Callback für LVGL
            .user_ctx = &disp_drv[1],      // LVGL Display-Treiber Kontext
        };
        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST_1, &io_config_2, &io_handle[1]));

        esp_lcd_panel_dev_config_t panel_config_2 = {
            .reset_gpio_num = PIN_LCD_2_RST,
            .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR_2, // muss angepasst werden
            .bits_per_pixel = 16,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle[1], &panel_config_2, &panel_handle[1]));
    #endif
    #if NUMBER_OF_DISPLAYS > 2
        esp_lcd_panel_io_spi_config_t io_config_3 = {
            .dc_gpio_num = PIN_LCD_3_DC,
            .cs_gpio_num = PIN_LCD_3_CS,
            .pclk_hz = LCD_PIXEL_CLOCK_HZ,
            .lcd_cmd_bits = LCD_CMD_BITS, // muss angepasst werden
            .lcd_param_bits = LCD_PARAM_BITS, // muss angepasst werden
            .spi_mode = SPI_MODE, //0
            .trans_queue_depth = TRANS_QUEUE_DEPTH, //10
            .on_color_trans_done = notify_lvgl_flush_ready, // Callback für LVGL
            .user_ctx = &disp_drv[2],      // LVGL Display-Treiber Kontext
        };
        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST_2, &io_config_3, &io_handle[2]));

        esp_lcd_panel_dev_config_t panel_config_3 = {
            .reset_gpio_num = PIN_LCD_3_RST,
            .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR_3, // muss angepasst werden
            .bits_per_pixel = 16,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle[2], &panel_config_3, &panel_handle[2]));
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        esp_lcd_panel_io_spi_config_t io_config_4 = {
            .dc_gpio_num = PIN_LCD_4_DC,
            .cs_gpio_num = PIN_LCD_4_CS,
            .pclk_hz = LCD_PIXEL_CLOCK_HZ,
            .lcd_cmd_bits = LCD_CMD_BITS, // muss angepasst werden
            .lcd_param_bits = LCD_PARAM_BITS, // muss angepasst werden
            .spi_mode = SPI_MODE, //0
            .trans_queue_depth = TRANS_QUEUE_DEPTH, //10
            .on_color_trans_done = notify_lvgl_flush_ready, // Callback für LVGL
            .user_ctx = &disp_drv[3],      // LVGL Display-Treiber Kontext
        };
        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST_2, &io_config_4, &io_handle[3]));

        esp_lcd_panel_dev_config_t panel_config_4 = {
            .reset_gpio_num = PIN_LCD_4_RST,
            .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR_4, // muss angepasst werden
            .bits_per_pixel = 16,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle[3], &panel_config_4, &panel_handle[3]));
    #endif

    for (int i = 0; i < NUMBER_OF_DISPLAYS; i++) {
        // Initialize the LCD panel
        int x_gap = 0; // Setze den horizontalen Gap auf 0
        int y_gap = 0; // Setze den vertikalen Gap auf 0
        esp_lcd_panel_set_gap(panel_handle[i], x_gap, y_gap);
        esp_lcd_panel_disp_on_off(panel_handle[i], false); 

        ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle[i]));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle[i], true)); // Optional: Invertiere die Farben für besseren Kontrast auf manchen Displays
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle[i], true));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle[i], true, false)); // Optional: Spiegeln des Displays horizontal
    
    }
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

void buffer_init() {

    // Puffer allokieren (Wichtig: im internen RAM für Geschwindigkeit)
    //buf = heap_caps_malloc(LCD_1_H_RES * LCD_1_V_RES * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    int buff_factor = 2;

    buf[0] = heap_caps_malloc(LCD_1_H_RES * (LCD_1_V_RES /buff_factor) * sizeof(lv_color_t), MALLOC_CAP_1);
    memset(buf[0], 0, LCD_1_H_RES * (LCD_1_V_RES /buff_factor) * sizeof(lv_color_t));
    lv_disp_draw_buf_init(&draw_buf[0], buf[0], NULL, LCD_1_H_RES * (LCD_1_V_RES /buff_factor));

    #if NUMBER_OF_DISPLAYS > 1
        buf[1] = heap_caps_malloc(LCD_2_H_RES * (LCD_2_V_RES /buff_factor) * sizeof(lv_color_t), MALLOC_CAP_2);
        memset(buf[1], 0, LCD_2_H_RES * (LCD_2_V_RES /buff_factor) * sizeof(lv_color_t));
        lv_disp_draw_buf_init(&draw_buf[1], buf[1], NULL, LCD_2_H_RES * (LCD_2_V_RES /buff_factor));
    #endif
    #if NUMBER_OF_DISPLAYS > 2
        buf[2] = heap_caps_malloc(LCD_3_H_RES * (LCD_3_V_RES /buff_factor) * sizeof(lv_color_t), MALLOC_CAP_3);
        memset(buf[2], 0, LCD_3_H_RES * (LCD_3_V_RES /buff_factor) * sizeof(lv_color_t));
        lv_disp_draw_buf_init(&draw_buf[2], buf[2], NULL, LCD_3_H_RES * (LCD_3_V_RES /buff_factor));
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        buf[3] = heap_caps_malloc(LCD_4_H_RES * (LCD_4_V_RES /buff_factor) * sizeof(lv_color_t), MALLOC_CAP_4);
        memset(buf[3], 0, LCD_4_H_RES * (LCD_4_V_RES /buff_factor) * sizeof(lv_color_t));
        lv_disp_draw_buf_init(&draw_buf[3], buf[3], NULL, LCD_4_H_RES * (LCD_4_V_RES /buff_factor));
    #endif

}

void driver_init() {
    // Treiber registrieren
    lv_disp_drv_init(&disp_drv[0]);
    disp_drv[0].hor_res = LCD_1_H_RES;
    disp_drv[0].ver_res = LCD_1_V_RES;
    disp_drv[0].flush_cb = lvgl_flush_cb;
    disp_drv[0].draw_buf = &draw_buf[0];
    disp_drv[0].user_data = panel_handle[0];
    disp_drv[0].full_refresh = 1; 
    lv_displays[0] = lv_disp_drv_register(&disp_drv[0]);

    #if NUMBER_OF_DISPLAYS > 1
        lv_disp_drv_init(&disp_drv[1]);
        disp_drv[1].hor_res = LCD_2_H_RES;
        disp_drv[1].ver_res = LCD_2_V_RES;
        disp_drv[1].flush_cb = lvgl_flush_cb;
        disp_drv[1].draw_buf = &draw_buf[1];
        disp_drv[1].user_data = panel_handle[1];
        disp_drv[1].full_refresh = 1; 
        lv_displays[1] = lv_disp_drv_register(&disp_drv[1]);
    #endif
    #if NUMBER_OF_DISPLAYS > 2
        lv_disp_drv_init(&disp_drv[2]);
        disp_drv[2].hor_res = LCD_3_H_RES;
        disp_drv[2].ver_res = LCD_3_V_RES;
        disp_drv[2].flush_cb = lvgl_flush_cb;
        disp_drv[2].draw_buf = &draw_buf[2];
        disp_drv[2].user_data = panel_handle[2];
        disp_drv[2].full_refresh = 1; 
        lv_displays[2] = lv_disp_drv_register(&disp_drv[2]);
    #endif
    #if NUMBER_OF_DISPLAYS > 3
        lv_disp_drv_init(&disp_drv[3]);
        disp_drv[3].hor_res = LCD_4_H_RES;
        disp_drv[3].ver_res = LCD_4_V_RES;
        disp_drv[3].flush_cb = lvgl_flush_cb;
        disp_drv[3].draw_buf = &draw_buf[3];
        disp_drv[3].user_data = panel_handle[3];
        disp_drv[3].full_refresh = 1; 
        lv_displays[3] = lv_disp_drv_register(&disp_drv[3]);
    #endif
}

void timer_start() {
    
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000)); // 1ms Tick

}
