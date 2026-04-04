#pragma once

/*
#################################################################################
    BASIC PROJECT CONFIGURATION
#################################################################################
*/
/**
 * @brief Core project configuration values.
 *
 * CHIP_USED: Target ESP32 chip variant switch. By changing this please add a new section after #if CHIP_USED == ESP32P4
 * for this new chip and add its corresponding pins and settings 
 */
#define CHIP_USED                          ESP32P4 // ESP32 variants: ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C6, ESP32P4

/**
 * @brief Feature flags - enable/disable optional modules.
 */
#define USE_BUZZER                         false  // true: enable buzzer alert functionality
#define LOGGING_ENABLED                    true   // true: send debug output via serial logger
#define LOGGING_TAG                        "JRO_BOARD_COMPUTER_LOG" // default ESP_LOG tag


/*
#################################################################################
    HARDWARE PIN CONFIGURATION
#################################################################################
*/
#if CHIP_USED == ESP32P4
    /**
     * @brief Core project configuration values.
     *
     * NUMBER_OF_DISPLAYS: Number of independent LCD panels attached.
     * NUMBER_OF_SPI: Number of SPI host controllers used for displays.
     * NUMBER_OF_ADS1115_DEVICES: Number of ADS1115 ADC chips on I2C bus.
     */
    #define NUMBER_OF_DISPLAYS                 4      // up to 4 displays possible
    #define NUMBER_OF_SPI                      2      // for four displays, two SPI hosts are required
    #define NUMBER_OF_ADS1115_DEVICES          2      // number of ADS1115 ADC devices on I2C
    /**
     * @brief SPI bus configuration, used for SPI LCD panels.
     *
     * SPI_MODE: clock polarity/phase mode (mode 3 for GC9A01 displays).
     * TRANS_QUEUE_DEPTH: transaction queue depth for spi bus commands.
     */
    /* ===== SPI CONFIGURATION ===== */
    #define SPI_MODE                       3
    #define TRANS_QUEUE_DEPTH              1      // Number of simultaneous elements on bus

    // SPI 1 Pins
    #define PIN_SPI_1_SCLK                 30
    #define PIN_SPI_1_MOSI                 29
    #define PIN_SPI_1_MISO                 -1
    #define SPI_1_MAX_TRANSFER_SZ          (240 * 240 * sizeof(uint16_t))
    #define SPI_1_QUADWP_IO_NUM            -1
    #define SPI_1_QUADHD_IO_NUM            -1
    #define SPI_1_INTR_FLAGS               (ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3)
    #define SPI_1_DMA                      SPI_DMA_CH_AUTO

    // SPI 2 Pins (optional, only if NUMBER_OF_SPI > 1)
    #if NUMBER_OF_SPI > 1
        #define PIN_SPI_2_SCLK             11
        #define PIN_SPI_2_MOSI             12
        #define PIN_SPI_2_MISO             -1
        #define SPI_2_MAX_TRANSFER_SZ      (240 * 240 * sizeof(uint16_t))
        #define SPI_2_QUADWP_IO_NUM        -1
        #define SPI_2_QUADHD_IO_NUM        -1
        #define SPI_2_INTR_FLAGS           (ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3)
        #define SPI_2_DMA                  SPI_DMA_CH_AUTO
    #endif

    /**
     * @brief Common LCD panel configuration, shared by all displays.
     *
     * LCD_PIXEL_CLOCK_HZ: SPI clock for display pixel writes.
     * LCD_CMD_BITS / LCD_PARAM_BITS: command parameter bit width for panel driver.
     * LCD_HOST_n: SPI host mapping.
     * PIN_LCD_BL: common backlight GPIO for all panels.
     */
    /* ===== LCD COMMON CONFIGURATION ===== */
    #define LCD_PIXEL_CLOCK_HZ             (40 * 1000 * 1000)  // 40 MHz
    #define LCD_CMD_BITS                   8
    #define LCD_PARAM_BITS                 8
    #define LCD_HOST_1                     SPI2_HOST
    #define LCD_HOST_2                     SPI3_HOST
    #define PIN_LCD_BL                     47     // Common backlight pin for all displays

    /* ===== LCD 1 PINS ===== */
    #define LCD_1_SPI_HOST                 LCD_HOST_1
    #define PIN_LCD_1_CS                   28
    #define PIN_LCD_1_DC                   49
    #define PIN_LCD_1_RST                  50
    #define LCD_1_H_RES                    240
    #define LCD_1_V_RES                    240
    #define LCD_1_RGB_ELEMENT_ORDER_BGR    LCD_RGB_ELEMENT_ORDER_BGR
    #define LCD_1_MIRROR_X                 false
    #define LCD_1_MIRROR_Y                 true
    #define LCD_1_INVERT_COLOR             true
    #define LCD_1_MALLOC_CAP                MALLOC_CAP_SPIRAM
    #define LCD_1_BUFFER_FACTOR             2
    #define LCD_1_SCREEN_ID                SCREEN_ID_GAUGE_CLOCK_TEMPERATURE

    /* ===== LCD 2 PINS ===== */
    #if NUMBER_OF_DISPLAYS > 1
        #define LCD_2_SPI_HOST             LCD_HOST_1
        #define PIN_LCD_2_CS               27
        #define PIN_LCD_2_DC               PIN_LCD_1_DC
        #define PIN_LCD_2_RST              PIN_LCD_1_RST
        #define LCD_2_H_RES                LCD_1_H_RES
        #define LCD_2_V_RES                LCD_1_V_RES
        #define LCD_2_RGB_ELEMENT_ORDER_BGR LCD_RGB_ELEMENT_ORDER_BGR
        #define LCD_2_MIRROR_X             false
        #define LCD_2_MIRROR_Y             true
        #define LCD_2_INVERT_COLOR         true
        #define LCD_2_MALLOC_CAP            MALLOC_CAP_DMA
        #define LCD_2_BUFFER_FACTOR         2
        #define LCD_2_SCREEN_ID            SCREEN_ID_GAUGE_OIL_TEMPERATURE
    #endif

    /* ===== LCD 3 PINS ===== */
    #if NUMBER_OF_DISPLAYS > 2
        #define PIN_LCD_3_CS               21
        #define PIN_LCD_3_DC               13
        #define PIN_LCD_3_RST              PIN_LCD_1_RST
        #define LCD_3_H_RES                LCD_1_H_RES
        #define LCD_3_V_RES                LCD_1_V_RES
        #define LCD_3_RGB_ELEMENT_ORDER_BGR LCD_RGB_ELEMENT_ORDER_BGR
        #define LCD_3_MIRROR_X             false
        #define LCD_3_MIRROR_Y             true
        #define LCD_3_INVERT_COLOR         true
        #define LCD_3_MALLOC_CAP            MALLOC_CAP_DMA
        #define LCD_3_BUFFER_FACTOR         2
        #if NUMBER_OF_SPI > 1
            #define LCD_3_SPI_HOST         LCD_HOST_2
        #else
            #define LCD_3_SPI_HOST         LCD_HOST_1
        #endif
        #define LCD_3_SCREEN_ID            SCREEN_ID_GAUGE_OIL_PRESSURE
    #endif

    /* ===== LCD 4 PINS ===== */
    #if NUMBER_OF_DISPLAYS > 3
        #define PIN_LCD_4_CS               20
        #define PIN_LCD_4_DC               PIN_LCD_3_DC
        #define PIN_LCD_4_RST              PIN_LCD_1_RST
        #define LCD_4_H_RES                LCD_3_H_RES
        #define LCD_4_V_RES                LCD_3_V_RES
        #define LCD_4_RGB_ELEMENT_ORDER_BGR LCD_RGB_ELEMENT_ORDER_BGR
        #define LCD_4_MIRROR_X             false
        #define LCD_4_MIRROR_Y             true
        #define LCD_4_INVERT_COLOR         true
        #define LCD_4_MALLOC_CAP            MALLOC_CAP_DMA
        #define LCD_4_BUFFER_FACTOR         2
        #if NUMBER_OF_SPI > 1
            #define LCD_4_SPI_HOST         LCD_HOST_2
        #else
            #define LCD_4_SPI_HOST         LCD_HOST_1
        #endif
        #define LCD_4_SCREEN_ID            SCREEN_ID_GAUGE_VOLTAGE
    #endif

    /* ===== SENSOR PIN ===== */
    #define PWM_SENSOR_PIN                 3

    /* ===== PERIPHERAL PINS ===== */
    #define PWM_ADC_SWITCH_PIN             16
    #define PWM_ADC_SWITCH_MODE            GPIO_MODE_INPUT
    #define PWM_ADC_SWITCH_PULL_UP_EN      GPIO_PULLUP_DISABLE
    #define PWM_ADC_SWITCH_PULL_DOWN_EN    GPIO_PULLDOWN_DISABLE
    #define PWM_ADC_SWITCH_INTR_TYPE       GPIO_INTR_DISABLE

    /**
     * @brief Time adjustment button definition and debounce timing.
     *
     * BUTTON_CLOCK_*_PIN: GPIO pin for short/long press clock adjust.
     * BUTTON_CLOCK_*_*_MS: Short/long press thresholds in milliseconds.
     * BUTTON_CLOCK_*_ACTIVE_LEVEL: GPIO active level (0 = active low).
     */
    /* ===== BUTTON PINS ===== */
    #define BUTTON_CLOCK_MINUTE_PIN        17
    #define BUTTON_CLOCK_HOUR_PIN          18
    #define BUTTON_CLOCK_MINUTE_SHORT_MS   50
    #define BUTTON_CLOCK_MINUTE_LONG_MS    500
    #define BUTTON_CLOCK_MINUTE_ACTIVE_LEVEL 0
    #define BUTTON_CLOCK_HOUR_SHORT_MS     50
    #define BUTTON_CLOCK_HOUR_LONG_MS      500
    #define BUTTON_CLOCK_HOUR_ACTIVE_LEVEL 0

    #if USE_BUZZER == true
        #define BUZZER_PIN                 15
    #endif

#endif

/*
#################################################################################
    BACKLIGHT (LED PWM) CONFIGURATION
#################################################################################
*/
/**
 * @brief LEDC PWM settings for display backlight brightness control.
 *
 * LED_SPEED: LEDC speed mode (low or high) for timer/channel.
 * LED_TIMER: LEDC timer index.
 * LED_DUTY_RESOLUTION: PWM duty resolution (e.g., 8-bit gives 0-255 range).
 * LED_DUTY_RES_VALUE: Duty scaling value.
 * LED_FREQ: PWM frequency for LED backlight (flicker-free constant lighting).
 * LED_GPIO: Neupin for PWM output to backlight.
 */
#define LED_SPEED                          LEDC_LOW_SPEED_MODE
#define LED_TIMER                          LEDC_TIMER_0
#define LED_DUTY_RESOLUTION                LEDC_TIMER_8_BIT     // 0-255
#define LED_DUTY_RES_VALUE                 256
#define LED_FREQ                           5000                  // 5 kHz (flicker-free)
#define LED_CLK                            LEDC_AUTO_CLK
#define LED_CHANNEL                        LEDC_CHANNEL_0
#define LED_INTR                           LEDC_INTR_DISABLE
#define LED_GPIO                           PIN_LCD_BL
#define LED_START_BRIGHT                   0
#define LED_H_POINT                        0

/*
#################################################################################
    BRIGHTNESS SETTINGS
#################################################################################
*/
/**
 * @brief Auto-brightness thresholds and manual defaults.
 *
 * BRIGHTNESS_DAY: default daytime brightness percent.
 * BRIGHTNESS_DAY_MIN_V: min battery voltage to treat as day mode.
 * BRIGHTNESS_NIGHT_MIN/MAX: brightness range in night mode.
 * BRIGHTNESS_NIGHT_MIN/MAX_V: battery voltage range mapping for night mode.
 */
#define BRIGHTNESS_DAY                     100
#define BRIGHTNESS_DAY_MIN_V               1.0
#define BRIGHTNESS_NIGHT_MIN               5
#define BRIGHTNESS_NIGHT_MIN_V             2.29
#define BRIGHTNESS_NIGHT_MAX               40
#define BRIGHTNESS_NIGHT_MAX_V             10.74

/*
#################################################################################
    DISPLAY & TIMING SETTINGS
#################################################################################
*/
#define EEZ_VALUE_FACTOR                   1000  // Factor for float-to-int conversion for LVGL
#define GAUGE_ON_DELAY_SEC                1
#define BUZZER_ON_DELAY_SEC                5
#define MAIN_TASK_FINISHED_DELAY           5000

/*
#################################################################################
    FREERTOS TASK CONFIGURATION (FOR EACH DISPLAY)
#################################################################################
*/
#define TASK_1_STEPDEPTH_SCREEN            4096
#define TASK_1_PRIORITY_SCREEN             10
#define TASK_1_DELAYTIME_SCREEN            200
#define TASK_1_CORE_SCREEN                 0

#if NUMBER_OF_DISPLAYS > 1
    #define TASK_2_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_2_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_2_DELAYTIME_SCREEN        100
    #define TASK_2_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

#if NUMBER_OF_DISPLAYS > 2
    #define TASK_3_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_3_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_3_DELAYTIME_SCREEN        150
    #define TASK_3_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

#if NUMBER_OF_DISPLAYS > 3
    #define TASK_4_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_4_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_4_DELAYTIME_SCREEN        100
    #define TASK_4_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

/*
#################################################################################
    BUZZER CONFIGURATION (only active when USE_BUZZER == true)
#################################################################################
*/
#if USE_BUZZER == true
    #define BUZZER_TEMP_MIN                3       // Alert when temperature < 3°C
    #define BUZZER_BEEPING_VALUE           255     // max 255
    #define BUZZER_QUIET_VALUE             0
    #define BUZZER_TASK_STEPDEPTH          8192
    #define BUZZER_TASK_PRIORITY           20
    #define BUZZER_TASK_CORE               0
    #define BUZZER_BEEP_ON_TIME            150
    #define BUZZER_BEEP_OFF_TIME           400

    #define BUZZER_SETTING_SPEED_MODE      LEDC_LOW_SPEED_MODE
    #define BUZZER_SETTING_DUTY_RES        LEDC_TIMER_13_BIT
    #define BUZZER_SETTING_TIMER           LEDC_TIMER_1
    #define BUZZER_SETTING_FREQ_HZ         2700
    #define BUZZER_SETTING_CLK_CFG         LEDC_AUTO_CLK
    #define BUZZER_SETTING_CHANNEL         LEDC_CHANNEL_1
    #define BUZZER_SETTING_INTR_TYPE       LEDC_INTR_DISABLE
    #define BUZZER_SETTING_TIMER_SEL       LEDC_TIMER_1
    #define BUZZER_SETTING_DUTY            0
    #define BUZZER_SETTING_HPOINT          0
#endif

/*
#################################################################################
    PWM SENSOR CONFIGURATION (Hella 6PP 010 378-201)
#################################################################################
*/
#define FILTER_ALPHA                       0.1f

// PWM Sensor General Settings
#define PWM_SENSOR_RESOLUTION_MHZ          10
#define PWM_SENSOR_PRESCALE                1
#define PWM_SENSOR_NEG_EDGE                1
#define PWM_SENSOR_POS_EDGE                1
#define PWM_SENSOR_PULL_UP                 1

// Diagnostic Pulse (Pulse ID 0)
#define PWM_SENSOR_DIAG_PULSE_ID           0
#define PWM_SENSOR_DIAG_PERIOD_MIN         900
#define PWM_SENSOR_DIAG_PERIOD_MAX         1100
#define PWM_SENSOR_DIAG_VALUE_MIN          150
#define PWM_SENSOR_DIAG_VALUE_MAX          800

// Temperature Pulse (Pulse ID 1) - from datasheet
#define PWM_SENSOR_TEMP_PULSE_ID           1
#define PWM_SENSOR_TEMP_PERIOD_MIN         3900
#define PWM_SENSOR_TEMP_PERIOD_MAX         4200
#define PWM_SENSOR_TEMP_VALUE_MIN          50
#define PWM_SENSOR_TEMP_VALUE_MAX          4050
#define PWM_SENSOR_TEMP_CALC_VALUE_1       -896.0
#define PWM_SENSOR_TEMP_CALC_VALUE_2       19.2    // Must not be zero

// Pressure Pulse (Pulse ID 2) - from datasheet
#define PWM_SENSOR_PRES_PULSE_ID           2
#define PWM_SENSOR_PRES_PERIOD_MIN         3900
#define PWM_SENSOR_PRES_PERIOD_MAX         4200
#define PWM_SENSOR_PRES_VALUE_MIN          50
#define PWM_SENSOR_PRES_VALUE_MAX          4050
#define PWM_SENSOR_PRES_CALC_VALUE_1       64.0
#define PWM_SENSOR_PRES_CALC_VALUE_2       384     // Must not be zero

#define PWM_SENSOR_MAX_SENSOR_COUNT        100

// PWM/ADC Switch Pin Configuration
#define PWM_ADC_SWTICH_VALUE_PWM           true

/*
#################################################################################
    I2C CONFIGURATION (RTC DS3231 & ADS1115 ADCs)
#################################################################################
*/
#define I2C_SDA_PIN                        9
#define I2C_SCL_PIN                        6
#define I2C_CLK_SRC                        I2C_CLK_SRC_DEFAULT
#define I2C_PORT                           I2C_NUM_0
#define I2C_GLITCH_IGNORE                  7
#define I2C_INT_PULLUP_ENB                 false
#define RTC_ADDR_LENGTH                    I2C_ADDR_BIT_LEN_7
#define RTC_SCL_SPEED_HZ                   100000

// I2C Device Addresses
#define RTC_DS3231_ADDR                    0x68
#define ADC_ADS1115_1_ADDR                 0x48
#define ADC_ADS1115_2_ADDR                 0x49
#define ADC_ADS1115_ADDR_LENGTH            RTC_ADDR_LENGTH
#define ADC_ADS1115_SCL_SPEED_HZ           400000

/*
#################################################################################
    ADC (ADS1115) CONFIGURATION
#################################################################################
*/
// LSB (Least Significant Bit) values for different ranges
#define LSB_2048                           0.0625f
#define LSB_4096                           0.125f
#define ADC_MAX_V_VALID                    3.25f
#define ADC_ADS_REF_V                      3.3f
#define ADC_FAIL_VALUE                     -99.0f

// ADC Channel Assignments
#define ADC_VOLT_ADS_CHANNEL               0       // Battery voltage
#define ADC_VOLT_BEL_ADS_CHANNEL           1       // Brightness/Light sensor
#define ADC_TEMP_ADS_CHANNEL               2       // oil temperature
#define ADC_PRES_ADS_CHANNEL               3       // Oil pressure
#define ADC_OUT_TEMP_ADS_CHANNEL           0       // Outdoor temperature
#define ADC_VOLT_REF_CHANNEL               1       // Reference voltage reading (only in Version 4.2)

// Programmable Gain Amplifier (PGA) Settings
#define ADC_VOLT_ADS_PGA                   0x02
#define ADC_VOLT_BEL_ADS_PGA               0x01
#define ADC_TEMP_ADS_PGA                   0x01
#define ADC_PRES_ADS_PGA                   0x01
#define ADC_OUT_TEMP_ADS_PGA               0x01
#define ADC_VOLT_REF_PGA                   0x01

// Pull-up Resistor Values
#define ADC_VOLT_ADS_PULLUP                10000.0f
#define ADC_VOLT_ADS_PULLDOWN              1500.0f
#define ADC_VOLT_BEL_ADS_PULLUP            10000.0f
#define ADC_VOLT_BEL_ADS_PULLDOWN          2200.0f
#define ADC_TEMP_ADS_PULLUP                680.0f
#define ADC_PRES_ADS_PULLUP                680.0f
#define ADC_OUT_TEMP_ADS_PULLUP            4700.0f

// Failure Detection Thresholds
#define ADC_TEMP_ADS_VAL_TO_FAIL_MIN       -50
#define ADC_PRES_ADS_VAL_TO_FAIL_MIN       0
#define ADC_PRES_ADS_VAL_TO_FAIL_MAX       250.0f
#define ADC_OUT_TEMP_ADS_VAL_TO_FAIL_MIN   0
#define ADC_OUT_TEMP_ADS_VAL_TO_FAIL_MAX   150000.0f
#define ADC_ADS_REF_V_TO_FAIL_MIN          ADC_ADS_REF_V - 0.5f
#define ADC_ADS_REF_V_TO_FAIL_MAX          ADC_ADS_REF_V + 0.5f

// Pressure Resistance Range Values
#define ADC_PRES_ADS_VAL_MIN_R             10.0f
#define ADC_PRES_ADS_VAL_MAX_R             184.0f

/*
#################################################################################
    SENSOR VALUE LIMITS & DEFAULTS
#################################################################################
*/
#define VALUE_DEFAULT_PRES                 0.0
#define VALUE_DEFAULT_TEMP                 0
#define VALUE_DEFAULT_VOLT                 8.0
#define VALUE_DEFAULT_OUT_TEMP             0
#define VALUE_DEFAULT_BRIGHT               BRIGHTNESS_DAY
#define VALUE_DEFAULT_NIGHT_MODE           false

#define VALUE_MIN_PRES                     VALUE_DEFAULT_PRES
#define VALUE_MIN_TEMP                     VALUE_DEFAULT_TEMP
#define VALUE_MIN_VOLT                     VALUE_DEFAULT_VOLT
#define VALUE_MIN_OUT_TEMP                 -30

#define VALUE_MAX_PRES                     6.0
#define VALUE_MAX_TEMP                     150
#define VALUE_MAX_VOLT                     16.0
#define VALUE_MAX_OUT_TEMP                 70

/*
#################################################################################
    Enable Testmode Settings
#################################################################################
*/
#define TESTMODE_ACTIVATE_TIMEOUT_MS      7000
#define TESTMODE_ACTIVATE_BUTTON_1_COUNT  2 // Press minute button 2 times within timeout to decrease minute
#define TESTMODE_ACTIVATE_BUTTON_2_COUNT  1 // Press hour button 1 times within timeout to decrease hour
#define TESTMODE_ACTIVATE_BUTTON_3_COUNT  2 // Press minute button 2 times within timeout to increase minute
#define TESTMODE_ACTIVATE_BUTTON_4_COUNT  1 // Press hour button 1 times within timeout to increase hour and (de-)activate test mode
