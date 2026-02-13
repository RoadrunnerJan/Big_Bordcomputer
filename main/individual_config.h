/*
#################################################################################
    Presettings for Individual Configuration
#################################################################################
*/
#define NUMBER_OF_DISPLAYS                 4   // up to 4 Displays possible
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
#define EEZ_VALUE_FACTOR                            100000 // Faktor zur Umrechnung von float-Werten in int32_t für die Kommunikation mit LVGL (z.B. 1.23 -> 1230)