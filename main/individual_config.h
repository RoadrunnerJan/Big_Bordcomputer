/*
    ToDos:
        - Backlight PWM funktioniert nicht
        - Screen Anzahl 3 funktioniert nicht, vier aber schon
        - Goldene Regel Main-Loop vs. Timer beachten (siehe Kommentare)
        - MAcros für Funktionen schreiben
        - Screen Funktionen und Backlight so umarbeiten, dass die Screens auf beliebige Displays gesetzt werden können
        - Kommentare in den Code schreiben
        - Andere GUI für Temp/Uhr
        - Nachtmodus geht noch nicht für alle Displays -> Umschreiben auf Nachtscreens für alle -> muss dann aber in den Tick funktionen berücksichtigt werden


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



/*
#################################################################################
    Presettings for Individual Configuration
#################################################################################
*/
#define NUMBER_OF_DISPLAYS                 3   // up to 4 Displays possible
#define CHIP_USED                          ESP32P4   // ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C6, ESP32P4

/*
#################################################################################
    define Pins
#################################################################################
*/
#if CHIP_USED == ESP32P4
    #define SPI_MODE                            3
    #define TRANS_QUEUE_DEPTH                   1 //10
    // SPI Pins
    #define PIN_SPI_SCLK_1                     30
    #define PIN_SPI_MOSI_1                     29
    #define PIN_SPI_MISO_1                     -1
#ifdef NUMBER_OF_DISPLAYS > 2
    #define PIN_SPI_SCLK_2                     11
    #define PIN_SPI_MOSI_2                     12
    #define PIN_SPI_MISO_2                     -1
#endif

    // Backlight on one common pin for all displays (optional, adjust if you have separate backlight control)
    #define PIN_LCD_BL                          54

    // LCD 1 Pins
    //#define PIN_LCD_1_BL                        54
    #define PIN_LCD_1_CS                        28
    #define PIN_LCD_1_DC                        49
    #define PIN_LCD_1_RST                       50
    #define LCD_1_H_RES                         240
    #define LCD_1_V_RES                         240
    #define LCD_RGB_ELEMENT_ORDER_BGR_1         LCD_RGB_ELEMENT_ORDER_BGR
    #define MALLOC_CAP_1                        MALLOC_CAP_SPIRAM//MALLOC_CAP_DMA //MALLOC_CAP_SPIRAM

    #define LCD_PIXEL_CLOCK_HZ                  40*1000*1000  // 40MHz
    #define LCD_CMD_BITS                        8
    #define LCD_PARAM_BITS                      8
    #define LCD_HOST_1                          SPI2_HOST
    #define LCD_HOST_2                          SPI3_HOST
#endif

#if NUMBER_OF_DISPLAYS > 1 
    #if CHIP_USED == ESP32P4
        // LCD 2 Pins
        //#define PIN_LCD_2_BL                        PIN_LCD_1_BL
        #define PIN_LCD_2_CS                        27
        #define PIN_LCD_2_DC                        PIN_LCD_1_DC
        #define PIN_LCD_2_RST                       PIN_LCD_1_RST
        #define LCD_2_H_RES                         LCD_1_H_RES
        #define LCD_2_V_RES                         LCD_1_V_RES
        #define LCD_RGB_ELEMENT_ORDER_BGR_2         LCD_RGB_ELEMENT_ORDER_BGR
        #define MALLOC_CAP_2                        MALLOC_CAP_DMA
    #endif
#endif

#if NUMBER_OF_DISPLAYS > 2
    #if CHIP_USED == ESP32P4
        // LCD 3 Pins
        //#define PIN_LCD_3_BL                        PIN_LCD_1_BL
        #define PIN_LCD_3_CS                        21
        #define PIN_LCD_3_DC                        13
        #define PIN_LCD_3_RST                       PIN_LCD_1_RST
        #define LCD_3_H_RES                         LCD_1_H_RES
        #define LCD_3_V_RES                         LCD_1_V_RES
        #define LCD_RGB_ELEMENT_ORDER_BGR_3         LCD_RGB_ELEMENT_ORDER_BGR
        #define MALLOC_CAP_3                        MALLOC_CAP_DMA
    #endif
#endif

#if NUMBER_OF_DISPLAYS > 3
    #if CHIP_USED == ESP32P4
        // LCD 4 Pins
        //#define PIN_LCD_4_BL                        PIN_LCD_1_BL
        #define PIN_LCD_4_CS                        20
        #define PIN_LCD_4_DC                        PIN_LCD_3_DC
        #define PIN_LCD_4_RST                       PIN_LCD_1_RST
        #define LCD_4_H_RES                         LCD_3_H_RES
        #define LCD_4_V_RES                         LCD_3_V_RES
        #define LCD_RGB_ELEMENT_ORDER_BGR_4         LCD_RGB_ELEMENT_ORDER_BGR
        #define MALLOC_CAP_4                        MALLOC_CAP_DMA
    #endif
#endif

/*
#################################################################################
    Color Settings
#################################################################################
*/

/*
#################################################################################
    Delay Settings
#################################################################################
*/

/*
#################################################################################
    Diverse Settings
#################################################################################
*/
#define EEZ_VALUE_FACTOR                            1000 // Faktor zur Umrechnung von float-Werten in int32_t für die Kommunikation mit LVGL (z.B. 1.23 -> 1230)

#define Task_StepDepth_Screen_1                     4096
#define Task_Priority_Screen_1                      10
#define Task_DelayTime_Screen_1                     20
#define Task_Core_Screen_1                          0

#define COLOR_NIGHT_MODE_HEX                       0xff5a00
#define COLOR_DAY_MODE_HEX                         0xffffff
#define OPACITY_NIGHT_MODE                         60
#define OPACITY_DAY_MODE                           0

#if NUMBER_OF_DISPLAYS > 1
    #define Task_StepDepth_Screen_2                     Task_StepDepth_Screen_1
    #define Task_Priority_Screen_2                      Task_Priority_Screen_1
    #define Task_DelayTime_Screen_2                     100
    #define Task_Core_Screen_2                          Task_Core_Screen_1
#endif
#if NUMBER_OF_DISPLAYS > 2
    #define Task_StepDepth_Screen_3                     Task_StepDepth_Screen_1
    #define Task_Priority_Screen_3                      Task_Priority_Screen_1
    #define Task_DelayTime_Screen_3                     20
    #define Task_Core_Screen_3                          Task_Core_Screen_1
#endif
#if NUMBER_OF_DISPLAYS > 3
    #define Task_StepDepth_Screen_4                     Task_StepDepth_Screen_1
    #define Task_Priority_Screen_4                      Task_Priority_Screen_1
    #define Task_DelayTime_Screen_4                     100
    #define Task_Core_Screen_4                          Task_Core_Screen_1
#endif
