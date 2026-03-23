#pragma once
/*
#################################################################################
    Presettings for Individual Configuration
#################################################################################
*/
#define NUMBER_OF_DISPLAYS                 4   // up to 4 Displays possible
#define NUMBER_OF_SPI                      2 // Number of SPI Devices used (for 4 Displays 2 are neccessary)
#define CHIP_USED                          ESP32P4   // ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C6, ESP32P4

#define TESTMODE                          true
#define USE_PWM_SENSOR                    false
#define TESTBRIGHTNESS                    false
#define USE_BEEP                          false
#define CHECK_I2C_DEVICES                 false
/*
#################################################################################
    define Pins
#################################################################################
*/
#if CHIP_USED == ESP32P4
    #define SPI_MODE                            3
    #define TRANS_QUEUE_DEPTH                   1 //10 - Anzahl an Elemente die zeitgleich auf dem Bus liegen dürfen
    // SPI Pins
    #define PIN_SPI_1_SCLK                     30
    #define PIN_SPI_1_MOSI                     29
    #define PIN_SPI_1_MISO                     -1
    #define SPI_1_MAX_TRANSFER_SZ                  240 * 240 * sizeof(uint16_t);
    #define SPI_1_QUADWP_IO_NUM                     -1
    #define SPI_1_QUADHD_IO_NUM                     -1
    #define SPI_1_INTR_FLAGS                        ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3  // Level 3 für hohe Priorität
    #define SPI_1_DMA                             SPI_DMA_CH_AUTO

    #if NUMBER_OF_SPI > 1
        #define PIN_SPI_2_SCLK                     11
        #define PIN_SPI_2_MOSI                     12
        #define PIN_SPI_2_MISO                     -1
        #define SPI_2_MAX_TRANSFER_SZ                   240 * 240 * sizeof(uint16_t);
        #define SPI_2_QUADWP_IO_NUM                     -1
        #define SPI_2_QUADHD_IO_NUM                     -1
        #define SPI_2_INTR_FLAGS                        ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3  // Level 3 für hohe Priorität
        #define SPI_2_DMA                             SPI_DMA_CH_AUTO
    #endif

    // Backlight on one common pin for all displays
    #define PIN_LCD_BL                          47//54 // alle auf ein Backlight pin -> bei 4 Displays wäre eine Transistor lösung am bestne

    // LCD 1 Pins
    #define PIN_LCD_1_CS                        28
    #define PIN_LCD_1_DC                        49
    #define PIN_LCD_1_RST                       50
    #define LCD_1_H_RES                         240
    #define LCD_1_V_RES                         240
    #define LCD_1_RGB_ELEMENT_ORDER_BGR         LCD_RGB_ELEMENT_ORDER_BGR
    #define LCD_1_MIRROR_X            true
    #define LCD_1_MIRROR_Y            false
    #define LCD_1_INVERT_COLOR        true

    #define LCD_1_MALLOC_CAP                        MALLOC_CAP_SPIRAM//MALLOC_CAP_DMA //MALLOC_CAP_SPIRAM
    #define LCD_1_BUFFER_FACTOR                     2
    #define LCD_1_SCREEN_ID                     SCREEN_ID_GAUGE_CLOCK_TEMPERATURE//SCREEN_ID_GAUGE_TEMPERATURE_CLOCK


    #define LCD_PIXEL_CLOCK_HZ                  40*1000*1000  // 40MHz
    #define LCD_CMD_BITS                        8
    #define LCD_PARAM_BITS                      8
    #define LCD_HOST_1                          SPI2_HOST
    #define LCD_HOST_2                          SPI3_HOST

    #define LCD_1_SPI_HOST                      LCD_HOST_1

    #if NUMBER_OF_DISPLAYS > 1 
        #if CHIP_USED == ESP32P4
            // LCD 2 Pins
            //#define PIN_LCD_2_BL                        PIN_LCD_1_BL
            #define PIN_LCD_2_CS                        27
            #define PIN_LCD_2_DC                        PIN_LCD_1_DC
            #define PIN_LCD_2_RST                       PIN_LCD_1_RST
            #define LCD_2_H_RES                         LCD_1_H_RES
            #define LCD_2_V_RES                         LCD_1_V_RES
            #define LCD_2_RGB_ELEMENT_ORDER_BGR         LCD_RGB_ELEMENT_ORDER_BGR
            #define LCD_2_MIRROR_X            true
            #define LCD_2_MIRROR_Y            false
            #define LCD_2_INVERT_COLOR        true
            #define LCD_2_MALLOC_CAP                        MALLOC_CAP_DMA
            #define LCD_2_BUFFER_FACTOR                     2
            #define LCD_2_SPI_HOST                      LCD_HOST_1
            #define LCD_2_SCREEN_ID                     SCREEN_ID_GAUGE_OIL_PRESSURE

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
            #define LCD_3_RGB_ELEMENT_ORDER_BGR         LCD_RGB_ELEMENT_ORDER_BGR
            #define LCD_3_MIRROR_X            true
            #define LCD_3_MIRROR_Y            false
            #define LCD_3_INVERT_COLOR        true
            #define LCD_3_MALLOC_CAP                        MALLOC_CAP_DMA
            #define LCD_3_BUFFER_FACTOR                     2
            #if NUMBER_OF_SPI > 1
                #define LCD_3_SPI_HOST                      LCD_HOST_2
            #else
                #define LCD_3_SPI_HOST                      LCD_HOST_1
            #endif
            #define LCD_3_SCREEN_ID                     SCREEN_ID_GAUGE_OIL_TEMPERATURE

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
            #define LCD_4_RGB_ELEMENT_ORDER_BGR         LCD_RGB_ELEMENT_ORDER_BGR
            #define LCD_4_MIRROR_X                      true
            #define LCD_4_MIRROR_Y                      false
            #define LCD_4_INVERT_COLOR                  true
            #define LCD_4_MALLOC_CAP                        MALLOC_CAP_DMA
            #define LCD_4_BUFFER_FACTOR                     2
            #if NUMBER_OF_SPI > 1
                #define LCD_4_SPI_HOST                      LCD_HOST_2
            #else
                #define LCD_4_SPI_HOST                      LCD_HOST_1
            #endif
            #define LCD_4_SCREEN_ID                     SCREEN_ID_GAUGE_VOLTAGE

        #endif
    #endif

#endif

/*
#################################################################################
    BACKLIGHT Settings
#################################################################################
*/
#define LED_SPEED               LEDC_LOW_SPEED_MODE
#define LED_TIMER               LEDC_TIMER_0
#define LED_DUTY_RESOLUTION     LEDC_TIMER_8_BIT   // 0 bis 8191
    #define LED_DUTY_RES_VALUE  256 // basierend auf LEDC_TIMER_8_BIT // 8191 für 13 Bit, 255 für 8 Bit
#define LED_FREQ                5000                // 5 kHz (flimmerfrei)
#define LED_CLK                 LEDC_AUTO_CLK
#define LED_CHANNEL             LEDC_CHANNEL_0
#define LED_INTR                LEDC_INTR_DISABLE
#define LED_GPIO                PIN_LCD_BL
#define LED_START_BRIGHT        4095 // 50% -> 8191 / 2
#define LED_H_POINT             0

/*
#################################################################################
    Diverse Settings
#################################################################################
*/
#define EEZ_VALUE_FACTOR                            1000 // Faktor zur Umrechnung von float-Werten in int32_t für die Kommunikation mit LVGL (z.B. 1.23 -> 1230)

#define GAUGE_ON_DELAY                              1000
#define DISPLAY_SETUP_DELAY                         500
#define BEEPER_ON_DELAY                             5000
#define MAIN_TASK_FINISHED_DELAY                    5000

#define COLOR_NIGHT_MODE_HEX                       0xff5a00
#define COLOR_DAY_MODE_HEX                         0xffffff
#define OPACITY_NIGHT_MODE                         60
#define OPACITY_DAY_MODE                           0

#define TASK_1_STEPDEPTH_SCREEN                     4096
#define TASK_1_PRIORITY_SCREEN                      10
#define TASK_1_DELAYTIME_SCREEN                     200
#define TASK_1_CORE_SCREEN                          0

#if NUMBER_OF_DISPLAYS > 1
    #define TASK_2_STEPDEPTH_SCREEN                     TASK_1_STEPDEPTH_SCREEN
    #define TASK_2_PRIORITY_SCREEN                      TASK_1_PRIORITY_SCREEN
    #define TASK_2_DELAYTIME_SCREEN                     100
    #define TASK_2_CORE_SCREEN                          TASK_1_CORE_SCREEN
#endif
#if NUMBER_OF_DISPLAYS > 2
    #define TASK_3_STEPDEPTH_SCREEN                     TASK_1_STEPDEPTH_SCREEN
    #define TASK_3_PRIORITY_SCREEN                      TASK_1_PRIORITY_SCREEN
    #define TASK_3_DELAYTIME_SCREEN                     150
    #define TASK_3_CORE_SCREEN                          TASK_1_CORE_SCREEN
#endif
#if NUMBER_OF_DISPLAYS > 3
    #define TASK_4_STEPDEPTH_SCREEN                     TASK_1_STEPDEPTH_SCREEN
    #define TASK_4_PRIORITY_SCREEN                      TASK_1_PRIORITY_SCREEN
    #define TASK_4_DELAYTIME_SCREEN                     100
    #define TASK_4_CORE_SCREEN                          TASK_1_CORE_SCREEN
#endif


/*
#################################################################################
    Beeper Settings
#################################################################################
*/
#if USE_BEEP == true
    #define BEEPER_TEMP_MIN                                 3 // Beept bei < 3 °C
    #define BEEPER_PIN                                      15
    #define BEEPER_BEEPING_VALUE                            0   
    #define BEEPER_QUIET_VALUE                              1
    #define BEEPER_TASK_STEPDEPTH                           8192
    #define BEEPER_TASK_PRIORITY                            20
    #define BEEPER_TASK_DELAYTIME                           1000
    #define BEEPER_TASK_CORE                                0
    #define BEEPER_BEEP_ON_TIME                             150
    #define BEEPER_BEEP_OFF_TIME                            400
#endif

/*
#################################################################################
    Bright Settings
#################################################################################
*/
#define BRIGHTNESS_DAY                                      100
#define BRIGHTNESS_DELAY                                    100


/*
#################################################################################
    Sensor Settings
#################################################################################
*/
#define PWM_SENSOR_PIN                                      3
#define PWM_SENSOR_FILTER_ALPHA                                        0.1f 
#define PWM_SENSOR_RESOLUTION_MHZ                           10
#define PWM_SENSOR_PRESCALE                                 1
#define PWM_SENSOR_NEG_EDGE                                 1
#define PWM_SENSOR_POS_EDGE                                 1
#define PWM_SENSOR_PULL_UP                                  1

// folgende Werte entnommen aus Datenblatt des Sensors Hella 6PP 010 378-201 
#define PWM_SENSOR_DIAG_PULSE_ID                                       0   // zum enum ändern?
#define PWM_SENSOR_DIAG_PERIOD_MIN                                     900
#define PWM_SENSOR_DIAG_PERIOD_MAX                                     1100
#define PWM_SENSOR_DIAG_VALUE_MIN                                      150
#define PWM_SENSOR_DIAG_VALUE_MAX                                      800
#define PWM_SENSOR_TEMP_PULSE_ID                                       1   
#define PWM_SENSOR_TEMP_PERIOD_MIN                                     3900
#define PWM_SENSOR_TEMP_PERIOD_MAX                                     4200
#define PWM_SENSOR_TEMP_VALUE_MIN                                      50
#define PWM_SENSOR_TEMP_VALUE_MAX                                      4050
#define PWM_SENSOR_PRES_PULSE_ID                                       2   
#define PWM_SENSOR_PRES_PERIOD_MIN                                     3900
#define PWM_SENSOR_PRES_PERIOD_MAX                                     4200
#define PWM_SENSOR_PRES_VALUE_MIN                                      50
#define PWM_SENSOR_PRES_VALUE_MAX                                      4050
#define PWM_SENSOR_TEMP_CALC_VALUE_1                                   -896.0
#define PWM_SENSOR_TEMP_CALC_VALUE_2                                   19.2 // != 0
#define PWM_SENSOR_PRES_CALC_VALUE_1                                   64.0
#define PWM_SENSOR_PRES_CALC_VALUE_2                                   384 // != 0
#define PWM_SENSOR_MAX_SENSOR_COUNT                                    100


/*
#################################################################################
    Button Settings
#################################################################################
*/

#define BUTTON_CLOCK_MINUTE_PIN                                         17 
#define BUTTON_CLOCK_HOUR_PIN                                           18
#define PWM_ADC_SWITCH_PIN                                                 16
/*
#################################################################################
    I2C Settings
#################################################################################
*/
#define RTC_I2C_SDA_PIN                                               9
#define RTC_I2C_SCL_PIN                                                 6
#define RTC_DS3231_ADDR                                                 0x68
#define ADC_ADS1115_1_ADDR                                              0x48
#define ADC_ADS1115_2_ADDR                                              0x49

