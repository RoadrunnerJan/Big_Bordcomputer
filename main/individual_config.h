#pragma once

/*
#################################################################################
    BASIC PROJECT CONFIGURATION
#################################################################################
*/
/**
 * @brief Core project configuration values.
 *
 * CHIP_USED: Target ESP32 chip variant. When changing chip types, add a new
 * conditional section (#if CHIP_USED == <new_chip>) after the existing section
 * and define all required pins and settings for that chip.
 */
#define CHIP_USED                          ESP32P4 ///< ESP32 variants: ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C6, ESP32P4

/**
 * @brief Feature flags - enable/disable optional modules.
 */
#define USE_BUZZER                         true   // true: enable buzzer alert functionality
#define LOGGING_ENABLED                    true   // true: send debug output via serial logger
#define LOGGING_TAG                        "JRO_BOARD_COMPUTER_LOG" // default ESP_LOG tag
#define TESTMODE_ACTIVE                    true  // true: enable test mode for simulating sensor values and brightness
#define THIRD_BUTTON                       true     // true: enable the third button to switch the last displays

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
     */
    #define NUMBER_OF_DISPLAYS                 4      // up to 4 displays possible
    #define NUMBER_OF_SPI                      2      // for four displays, two SPI hosts are required
    /**
     * @brief SPI bus configuration, used for SPI LCD panels.
     *
     * SPI_MODE: clock polarity/phase mode (mode 3 for GC9A01 displays).
     * TRANS_QUEUE_DEPTH: transaction queue depth for spi bus commands.
     */
    /* ===== SPI CONFIGURATION ===== */
    /**
     * @brief SPI communication parameters for LCD display panels.
     */
    #define SPI_MODE                       3         ///< Clock polarity/phase (mode 3 for GC9A01 displays)
    #define TRANS_QUEUE_DEPTH              1         ///< Number of simultaneous SPI transactions in queue

    /**
     * @brief SPI 1 bus configuration (first SPI host for displays 1-2).
     */
    #define PIN_SPI_1_SCLK                 30         ///< Serial Clock pin for SPI 1
    #define PIN_SPI_1_MOSI                 29         ///< Master Out Slave In pin for SPI 1
    #define PIN_SPI_1_MISO                 -1         ///< Master In Slave Out (unused, set to -1)
    #define SPI_1_MAX_TRANSFER_SZ          (240 * 240 * sizeof(uint16_t))  ///< Max transfer size for 240x240 display
    #define SPI_1_QUADWP_IO_NUM            -1         ///< Quad Write Protect (unused, set to -1)
    #define SPI_1_QUADHD_IO_NUM            -1         ///< Quad Hold (unused, set to -1)
    #define SPI_1_INTR_FLAGS               (ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3)  ///< Interrupt flags
    #define SPI_1_DMA                      SPI_DMA_CH_AUTO  ///< Automatic DMA channel selection

    /**
     * @brief SPI 2 bus configuration (second SPI host for displays 3-4, optional).
     */
    #if NUMBER_OF_SPI > 1
        #define PIN_SPI_2_SCLK             11         ///< Serial Clock pin for SPI 2
        #define PIN_SPI_2_MOSI             12         ///< Master Out Slave In pin for SPI 2
        #define PIN_SPI_2_MISO             -1         ///< Master In Slave Out (unused, set to -1)
        #define SPI_2_MAX_TRANSFER_SZ      (240 * 240 * sizeof(uint16_t))  ///< Max transfer size for 240x240 display
        #define SPI_2_QUADWP_IO_NUM        -1         ///< Quad Write Protect (unused, set to -1)
        #define SPI_2_QUADHD_IO_NUM        -1         ///< Quad Hold (unused, set to -1)
        #define SPI_2_INTR_FLAGS           (ESP_INTR_FLAG_IRAM | ESP_INTR_FLAG_LEVEL3)  ///< Interrupt flags
        #define SPI_2_DMA                  SPI_DMA_CH_AUTO  ///< Automatic DMA channel selection
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
    #define LCD_PIXEL_CLOCK_HZ             (70 * 1000 * 1000)  // 60 MHz
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
    #define LCD_1_MALLOC_CAP               (MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL ) // MALLOC_CAP_SPIRAM
    #define LCD_1_BUFFER_FACTOR            10
    #define LCD_1_SCREEN_ID                SCREEN_ID_GAUGE_CLOCK_TEMPERATURE // SCREEN_ID_GAUGE_TEMPERATURE_CLOCK
    #define LCD_1_COLOR_FORMAT              LV_COLOR_FORMAT_RGB565_SWAPPED
    #define LCD_1_RENDER_MODE              LV_DISPLAY_RENDER_MODE_PARTIAL

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
        #define LCD_2_MALLOC_CAP           (MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL ) // MALLOC_CAP_SPIRAM
        #define LCD_2_BUFFER_FACTOR        10
        #define LCD_2_SCREEN_ID            SCREEN_ID_GAUGE_OIL_TEMPERATURE
        #define LCD_2_COLOR_FORMAT          LV_COLOR_FORMAT_RGB565_SWAPPED
        #define LCD_2_RENDER_MODE          LV_DISPLAY_RENDER_MODE_PARTIAL
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
        #define LCD_3_MALLOC_CAP           (MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL ) // MALLOC_CAP_SPIRAM
        #define LCD_3_BUFFER_FACTOR         1
        #define LCD_3_SPI_HOST              LCD_HOST_2
        #define LCD_3_SCREEN_ID            SCREEN_ID_GAUGE_OIL_PRESSURE
        #define LCD_3_COLOR_FORMAT          LV_COLOR_FORMAT_RGB565_SWAPPED
        #define LCD_3_RENDER_MODE          LV_DISPLAY_RENDER_MODE_FULL
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
        #define LCD_4_MALLOC_CAP           (MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL ) // MALLOC_CAP_SPIRAM
        #define LCD_4_BUFFER_FACTOR         8
        #define LCD_4_SPI_HOST              LCD_HOST_2
        #define LCD_4_SCREEN_ID            SCREEN_ID_GAUGE_VOLTAGE
        #define LCD_4_COLOR_FORMAT          LV_COLOR_FORMAT_RGB565_SWAPPED
        #define LCD_4_RENDER_MODE          LV_DISPLAY_RENDER_MODE_PARTIAL
    #endif

    /**
     * @brief PWM sensor input on a digital-capable GPIO.
     */
    #define PWM_SENSOR_PIN                 3          ///< GPIO pin receiving PWM pulses from Hella sensor

    /**
     * @brief PWM/ADC sensor input selector switch configuration.
     */
    #define PWM_ADC_SWITCH_PIN             16         ///< GPIO pin for PWM/ADC mode selection (high=PWM, low=ADC)
    #define PWM_ADC_SWITCH_MODE            GPIO_MODE_INPUT         ///< Configure as digital input
    #define PWM_ADC_SWITCH_PULL_UP_EN      GPIO_PULLUP_DISABLE     ///< No internal pull-up resistor
    #define PWM_ADC_SWITCH_PULL_DOWN_EN    GPIO_PULLDOWN_DISABLE   ///< No internal pull-down resistor
    #define PWM_ADC_SWITCH_INTR_TYPE       GPIO_INTR_DISABLE       ///< No interrupt on level change

    /**
     * @brief Time adjustment button GPIO configurations.
     */
    #define BUTTON_CLOCK_MINUTE_PIN        17         ///< GPIO pin for minute adjustment button
    #define BUTTON_CLOCK_HOUR_PIN          18         ///< GPIO pin for hour adjustment button
    #define BUTTON_CLOCK_MINUTE_SHORT_MS   50         ///< Debounce time for minute button in milliseconds
    #define BUTTON_CLOCK_MINUTE_LONG_MS    500        ///< Long press threshold for minute button
    #define BUTTON_CLOCK_MINUTE_ACTIVE_LEVEL 0        ///< Active level: 0=active low, 1=active high
    #define BUTTON_CLOCK_HOUR_SHORT_MS     50         ///< Debounce time for hour button in milliseconds
    #define BUTTON_CLOCK_HOUR_LONG_MS      500        ///< Long press threshold for hour button
    #define BUTTON_CLOCK_HOUR_ACTIVE_LEVEL 0          ///< Active level: 0=active low, 1=active high

    // if defined - this is a menu button to switch the displays and the designs
    #define BUTTON_THIRD_PIN               33         ///< GPIO pin for third button (optional, used for switching displays)
    #define BUTTON_THIRD_SHORT_MS          50         ///< Debounce time for third button in milliseconds
    #define BUTTON_THIRD_LONG_MS           500        ///< Long press threshold for third button
    #define BUTTON_THIRD_ACTIVE_LEVEL      0          ///< Active level: 0=active low, 1=active high

    #if USE_BUZZER == true
        /**
         * @brief Buzzer output GPIO pin configuration.
         */
        #define BUZZER_PIN                 15         ///< GPIO pin for buzzer PWM output
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
 * LED_SPEED: LEDC speed mode (low=slower/lower noise, high=faster/more power)
 * LED_TIMER: LEDC timer index (supports multiple independent timers)
 * LED_DUTY_RESOLUTION: PWM duty cycle resolution in bits (8-bit = 256 levels)
 * LED_FREQ: PWM frequency for LED (25 kHz prevents visible flicker)
 */
#define LED_SPEED                          LEDC_LOW_SPEED_MODE
#define LED_TIMER                          LEDC_TIMER_0
#define LED_DUTY_RESOLUTION                LEDC_TIMER_8_BIT     // 0-255
#define LED_DUTY_RES_VALUE                 256
#define LED_FREQ                           25000                // 25 kHz
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
 * BRIGHTNESS_DAY_MAX_V: min battery voltage to treat as day mode.
 * BRIGHTNESS_NIGHT_MIN/MAX: brightness range in night mode.
 * BRIGHTNESS_NIGHT_MIN/MAX_V: battery voltage range mapping for night mode.
 */
#define BRIGHTNESS_AUTO_ENABLE             true    ///< Enable automatic brightness adjustment based on ambient light
#define BRIGHTNESS_DAY                     100       ///< Default daytime brightness level (0-100%)
#define BRIGHTNESS_DAY_MAX_V               0.05      ///< Battery voltage threshold for day mode (in volts)
#define BRIGHTNESS_NIGHT_MIN               20        ///< Minimum brightness in night mode (0-100%)
#define BRIGHTNESS_NIGHT_MIN_V             2.29      ///< Battery voltage mapping point for minimum night brightness
#define BRIGHTNESS_NIGHT_MAX               40        ///< Maximum brightness in night mode (0-100%)
#define BRIGHTNESS_NIGHT_MAX_V             10.74     ///< Battery voltage mapping point for maximum night brightness

/*
#################################################################################
    DISPLAY & TIMING SETTINGS
#################################################################################
*/
/**
 * @brief Display rendering and initialization timing parameters.
 */
#define EEZ_VALUE_FACTOR_1                 1000       ///< Scaling factor for float-to-integer conversion in LVGL
#define EEZ_VALUE_FACTOR_2                 1000       ///< Scaling factor for float-to-integer conversion in LVGL
#define EEZ_VALUE_FACTOR_3                 100       ///< Scaling factor for float-to-integer conversion in LVGL
#define EEZ_VALUE_FACTOR_4                 1000       ///< Scaling factor for float-to-integer conversion in LVGL
#define GAUGE_ON_DELAY_MS                  1200      ///< Delay before gauges become active after boot (milliseconds)
#define BUZZER_ON_DELAY_MS                 5000      ///< Delay before buzzer activation is allowed (milliseconds)
#define MAIN_TASK_FINISHED_DELAY           5000      ///< Delay for main task completion (milliseconds)

/*
#################################################################################
    FREERTOS TASK CONFIGURATION (FOR EACH DISPLAY)
#################################################################################
*/
/**
 * @brief Display 1 FreeRTOS task configuration parameters.
 *
 * TASK_*_STEPDEPTH_SCREEN: Stack size in bytes
 * TASK_*_PRIORITY_SCREEN: Task priority (higher = more important)
 * TASK_*_DELAYTIME_SCREEN: Delay between screen updates in milliseconds
 * TASK_*_CORE_SCREEN: CPU core assignment (0 or 1 on dual-core ESP32)
 */
#define TASK_1_STEPDEPTH_SCREEN            4096       ///< Stack depth for display 1 task
#define TASK_1_PRIORITY_SCREEN             10        ///< Task priority for display 1
#define TASK_1_DELAYTIME_SCREEN            200       ///< Update interval for display 1 (milliseconds)
#define TASK_1_CORE_SCREEN                 0         ///< CPU core for display 1 task

#if NUMBER_OF_DISPLAYS > 1
    /**
     * @brief Display 2 FreeRTOS task configuration parameters.
     */
    #define TASK_2_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_2_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_2_DELAYTIME_SCREEN        100        ///< Update interval for display 2 (milliseconds)
    #define TASK_2_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

#if NUMBER_OF_DISPLAYS > 2
    /**
     * @brief Display 3 FreeRTOS task configuration parameters.
     */
    #define TASK_3_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_3_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_3_DELAYTIME_SCREEN        150        ///< Update interval for display 3 (milliseconds)
    #define TASK_3_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

#if NUMBER_OF_DISPLAYS > 3
    /**
     * @brief Display 4 FreeRTOS task configuration parameters.
     */
    #define TASK_4_STEPDEPTH_SCREEN        TASK_1_STEPDEPTH_SCREEN
    #define TASK_4_PRIORITY_SCREEN         TASK_1_PRIORITY_SCREEN
    #define TASK_4_DELAYTIME_SCREEN        100        ///< Update interval for display 4 (milliseconds)
    #define TASK_4_CORE_SCREEN             TASK_1_CORE_SCREEN
#endif

/*
#################################################################################
    BUZZER CONFIGURATION (only active when USE_BUZZER == true)
#################################################################################
*/
/**
 * @brief Buzzer alarm and PWM output configuration (only if USE_BUZZER == true).
 *
 * Defines temperature thresholds for buzzer activation, PWM parameters,
 * and FreeRTOS task settings for the buzzer alert system.
 */
#if USE_BUZZER == true
    #define BUZZER_TEMP_MIN                3          ///< Temperature threshold for cold weather alert (°C)
    #define BUZZER_BEEPING_VALUE           255        ///< PWM duty cycle for beep sound (0-255, max volume)
    #define BUZZER_QUIET_VALUE             0          ///< PWM duty cycle for silence (0=off)
    #define BUZZER_TASK_STEPDEPTH          8192       ///< Stack size for buzzer task in bytes
    #define BUZZER_TASK_PRIORITY           20         ///< Task priority (higher than display tasks)
    #define BUZZER_TASK_CORE               0          ///< CPU core for buzzer task
    #define BUZZER_BEEP_ON_TIME            150        ///< Beep duration in milliseconds
    #define BUZZER_BEEP_OFF_TIME           400        ///< Silence duration between beeps in milliseconds

    /**
     * @brief Buzzer LEDC PWM parameters.
     */
    #define BUZZER_SETTING_SPEED_MODE      LEDC_LOW_SPEED_MODE   ///< Speed mode for PWM timer
    #define BUZZER_SETTING_DUTY_RES        LEDC_TIMER_13_BIT     ///< 13-bit duty resolution (8192 levels)
    #define BUZZER_SETTING_TIMER           LEDC_TIMER_1          ///< Timer index
    #define BUZZER_SETTING_FREQ_HZ         2700                  ///< Frequency for audible beep tone (Hz)
    #define BUZZER_SETTING_CLK_CFG         LEDC_AUTO_CLK         ///< Automatic clock selection
    #define BUZZER_SETTING_CHANNEL         LEDC_CHANNEL_1        ///< PWM channel
    #define BUZZER_SETTING_INTR_TYPE       LEDC_INTR_DISABLE     ///< No interrupt on PWM events
    #define BUZZER_SETTING_TIMER_SEL       LEDC_TIMER_1          ///< Timer selection
    #define BUZZER_SETTING_DUTY            0                     ///< Initial duty cycle (0=off)
    #define BUZZER_SETTING_HPOINT          0                     ///< Output high point
#endif

/*
#################################################################################
    PWM SENSOR CONFIGURATION (Hella 6PP 010 378-201)
#################################################################################
*/
/**
 * @brief PWM sensor general settings and pulse configuration.
 *
 * Hella 6PP sensor transmits three multiplex PWM signals:
 * - Diagnostic pulse (ID 0): sensor health status
 * - Temperature pulse (ID 1): oil temperature reading
 * - Pressure pulse (ID 2): oil pressure reading
 */
// PWM Sensor General Settings
#define PWM_SENSOR_RESOLUTION_MHZ          10        ///< Timer resolution (10 MHz = 100ns per tick)
#define PWM_SENSOR_PRESCALE                1         ///< Timer prescaler
#define PWM_SENSOR_NEG_EDGE                1         ///< Count negative (falling) edges
#define PWM_SENSOR_POS_EDGE                1         ///< Count positive (rising) edges
#define PWM_SENSOR_PULL_UP                 1         ///< Enable internal pull-up on input pin

// Diagnostic Pulse (Pulse ID 0)
/**
 * @brief Diagnostic pulse configuration for sensor health check.
 */
#define PWM_SENSOR_DIAG_PULSE_ID           0         ///< Pulse ID for diagnostic signal
#define PWM_SENSOR_DIAG_PERIOD_MIN         900       ///< Minimum period in clock ticks (nanoseconds/100)
#define PWM_SENSOR_DIAG_PERIOD_MAX         1100      ///< Maximum period for valid diagnostic pulse
#define PWM_SENSOR_DIAG_VALUE_MIN          150       ///< Minimum pulse width threshold
#define PWM_SENSOR_DIAG_VALUE_MAX          800       ///< Maximum pulse width for valid range

// Temperature Pulse (Pulse ID 1) - from datasheet
/**
 * @brief Temperature sensor pulse configuration from Hella datasheet.
 *
 * Equation: Temperature = (PWM_VALUE - 50) / 4050 * PWM_SENSOR_TEMP_CALC_VALUE_2 + PWM_SENSOR_TEMP_CALC_VALUE_1
 */
#define PWM_SENSOR_TEMP_PULSE_ID           1         ///< Pulse ID for temperature signal
#define PWM_SENSOR_TEMP_PERIOD_MIN         3900      ///< Minimum period in clock ticks
#define PWM_SENSOR_TEMP_PERIOD_MAX         4200      ///< Maximum period for valid temperature pulse
#define PWM_SENSOR_TEMP_VALUE_MIN          50        ///< Minimum pulse width (0°C)
#define PWM_SENSOR_TEMP_VALUE_MAX          4050      ///< Maximum pulse width (150°C)
#define PWM_SENSOR_TEMP_CALC_VALUE_1       -896.0    ///< Temperature offset constant
#define PWM_SENSOR_TEMP_CALC_VALUE_2       19.2      ///< Temperature slope (must not be zero)

// Pressure Pulse (Pulse ID 2) - from datasheet
/**
 * @brief Pressure sensor pulse configuration from Hella datasheet.
 *
 * Equation: Pressure = (PWM_VALUE - 50) / 4050 * PWM_SENSOR_PRES_CALC_VALUE_2 + PWM_SENSOR_PRES_CALC_VALUE_1
 */
#define PWM_SENSOR_PRES_PULSE_ID           2         ///< Pulse ID for pressure signal
#define PWM_SENSOR_PRES_PERIOD_MIN         3900      ///< Minimum period in clock ticks
#define PWM_SENSOR_PRES_PERIOD_MAX         4200      ///< Maximum period for valid pressure pulse
#define PWM_SENSOR_PRES_VALUE_MIN          50        ///< Minimum pulse width (0 bar)
#define PWM_SENSOR_PRES_VALUE_MAX          4050      ///< Maximum pulse width (6 bar)
#define PWM_SENSOR_PRES_CALC_VALUE_1       64.0      ///< Pressure offset constant
#define PWM_SENSOR_PRES_CALC_VALUE_2       384       ///< Pressure slope (must not be zero)

#define PWM_SENSOR_MAX_SENSOR_COUNT        100       ///< Maximum number of sensors on PWM bus

/**
 * @brief PWM/ADC selector for sensor input mode.
 */
#define PWM_ADC_SWTICH_VALUE_PWM           true      ///< true=use PWM sensor mode, false=use ADC sensor mode

/*
#################################################################################
    I2C CONFIGURATION (RTC DS3231)
#################################################################################
*/
/**
 * @brief I2C bus GPIO pins and clock configuration for RTC communication.
 */
#define I2C_SDA_PIN                        9         ///< Serial Data pin for I2C bus
#define I2C_SCL_PIN                        6         ///< Serial Clock pin for I2C bus
#define I2C_CLK_SRC                        I2C_CLK_SRC_DEFAULT  ///< Default clock source
#define I2C_PORT                           I2C_NUM_0 ///< I2C controller number
#define I2C_GLITCH_IGNORE                  7         ///< Glitch filter threshold (clock cycles)
#define I2C_INT_PULLUP_ENB                 false     ///< Use external pull-ups (not internal)
#define RTC_ADDR_LENGTH                    I2C_ADDR_BIT_LEN_7  ///< 7-bit I2C addressing
#define RTC_SCL_SPEED_HZ                   100000    ///< I2C clock speed (100 kHz standard mode)

/**
 * @brief I2C device addresses for connected sensors.
 */
#define RTC_DS3231_ADDR                    0x68      ///< DS3231 RTC I2C address (0x68 = default)

/*
#################################################################################
    ADC CONFIGURATION
#################################################################################
*/
/**
 * @brief ADC unit setup and hardware configuration.
 *
 * Two ADC units (ADC1, ADC2) with independent channels for different sensors.
 * Bit width and attenuation settings apply to all channels on each unit.
 */
// ADC Setup
#define ADC_UNIT_NUMBER                   2         ///< Number of ADC units used (1 or 2)
#define ADC_UNIT_1_BITWIDTH               ADC_BITWIDTH_DEFAULT  ///< ADC1 resolution (default = 12-bit)
#define ADC_UNIT_2_BITWIDTH               ADC_BITWIDTH_DEFAULT  ///< ADC2 resolution (default = 12-bit)
#define ADC_UNIT_1_ATTEN                  ADC_ATTEN_DB_12  ///< ADC1 attenuation (±3.3V range)
#define ADC_UNIT_2_ATTEN                  ADC_ATTEN_DB_12  ///< ADC2 attenuation (±3.3V range)

/**
 * @brief Oil pressure sensor ADC configuration.
 */
#define ADC_OIL_PRESSURE_UNIT_ID          ADC_UNIT_1
#define ADC_OIL_PRESSURE_BITWIDTH         ADC_BITWIDTH_DEFAULT
#define ADC_OIL_PRESSURE_ATTEN            ADC_ATTEN_DB_12
#define ADC_OIL_PRESSURE_CHANNEL          ADC_CHANNEL_3

/**
 * @brief Oil temperature sensor ADC configuration.
 */
#define ADC_OIL_TEMPERATURE_UNIT_ID       ADC_UNIT_1
#define ADC_OIL_TEMPERATURE_BITWIDTH      ADC_BITWIDTH_DEFAULT
#define ADC_OIL_TEMPERATURE_ATTEN         ADC_ATTEN_DB_12
#define ADC_OIL_TEMPERATURE_CHANNEL       ADC_CHANNEL_6

/**
 * @brief Outdoor temperature sensor ADC configuration.
 */
#define ADC_OUT_TEMPERATURE_UNIT_ID       ADC_UNIT_1
#define ADC_OUT_TEMPERATURE_BITWIDTH      ADC_BITWIDTH_DEFAULT
#define ADC_OUT_TEMPERATURE_ATTEN         ADC_ATTEN_DB_12
#define ADC_OUT_TEMPERATURE_CHANNEL       ADC_CHANNEL_7

/**
 * @brief Battery 12V voltage divider ADC configuration.
 */
#define ADC_OIL_12V_UNIT_ID               ADC_UNIT_2
#define ADC_OIL_12V_BITWIDTH              ADC_BITWIDTH_DEFAULT
#define ADC_OIL_12V_ATTEN                 ADC_ATTEN_DB_12
#define ADC_OIL_12V_CHANNEL               ADC_CHANNEL_4

/**
 * @brief Ambient brightness sensor ADC configuration.
 */
#define ADC_AMBI_UNIT_ID              ADC_UNIT_2
#define ADC_AMBI_BITWIDTH             ADC_BITWIDTH_DEFAULT
#define ADC_AMBI_ATTEN                ADC_ATTEN_DB_12
#define ADC_AMBI_CHANNEL              ADC_CHANNEL_5

/**
 * @brief 3.3V reference voltage ADC configuration (for system diagnostics).
 */
#define ADC_3V3_UNIT_ID               ADC_UNIT_2
#define ADC_3V3_BITWIDTH              ADC_BITWIDTH_DEFAULT
#define ADC_3V3_ATTEN                 ADC_ATTEN_DB_12
#define ADC_3V3_CHANNEL               ADC_CHANNEL_3

/**
 * @brief ADC reference voltage and measurement configuration.
 *
 * ADC_MAX_V_VALID: Maximum valid voltage reading (anything above indicates error)
 * ADC_ADS_REF_V: Reference voltage for ADC calculations (typical 3.3V)
 * ADC_FAIL_VALUE: Default value returned on sensor failures
 */
// LSB (Least Significant Bit) values for different ranges
#define ADC_MAX_V_VALID                    3.25f     ///< Maximum valid ADC voltage (3.25V = overcurrent)
#define ADC_ADS_REF_V_MIN_VALID            1.3f      ///< min ADC reference voltage for valid readings (below this, readings are unreliable)
#define ADC_ADS_REF_V                      3.3f      ///< ADC reference voltage (typically 3.3V)
#define ADC_FAIL_VALUE                     -99.0f    ///< Error return value for failed readings

/**
 * @brief Voltage divider pull-up and pull-down resistor values.
 *
 * Used for calculating actual voltage from ADC readings.
 * Formula: V_actual = V_adc * (R_up + R_down) / R_down
 */
// Pull-up Resistor Values
#define ADC_VOLT_PULLUP                10000.0f      ///< Ohms - main voltage divider pull-up
#define ADC_VOLT_PULLDOWN              1500.0f       ///< Ohms - main voltage divider pull-down
#define ADC_VOLT_BEL_PULLUP            10000.0f      ///< Ohms - brightness feedback pull-up
#define ADC_VOLT_BEL_PULLDOWN          2200.0f       ///< Ohms - brightness feedback pull-down
#define ADC_TEMP_PULLUP                680.0f        ///< Ohms - temperature sensor pull-up
#define ADC_PRES_PULLUP                680.0f        ///< Ohms - pressure sensor pull-up
#define ADC_OUT_TEMP_PULLUP            4700.0f       ///< Ohms - outdoor temperature pull-up
#define ADC_3V3_PULLUP                 1000.0f       ///< Ohms - 3.3V reference pull-up
#define ADC_3V3_PULLDOWN               1000.0f       ///< Ohms - 3.3V reference pull-down

/**
 * @brief Sensor failure detection thresholds.
 *
 * Readings outside these ranges indicate sensor malfunction or disconnection.
 */
// Failure Detection Thresholds
#define ADC_TEMP_VAL_TO_FAIL_MIN       -50           ///< Minimum valid oil temperature (°C)
#define ADC_PRES_VAL_TO_FAIL_MIN       0             ///< Minimum valid oil pressure (bar)
#define ADC_PRES_VAL_TO_FAIL_MAX       250.0f        ///< Maximum valid oil pressure (bar)
#define ADC_OUT_TEMP_VAL_TO_FAIL_MIN   0             ///< Minimum valid outdoor temperature range
#define ADC_OUT_TEMP_VAL_TO_FAIL_MAX   150000.0f     ///< Maximum valid outdoor temperature range

/**
 * @brief Pressure sensor resistance range mapping.
 *
 * DS3231-compatible resistance values for pressure calculation.
 */
// Pressure Resistance Range Values
#define ADC_PRES_VAL_MIN_R             10.0f         ///< Ohms - minimum sensor resistance (0 bar)
#define ADC_PRES_VAL_MAX_R             184.0f        ///< Ohms - maximum sensor resistance (6 bar)

/*
#################################################################################
    SENSOR VALUE LIMITS & DEFAULTS
#################################################################################
*/
/**
 * @brief Default and range limit values for sensor readings.
 *
 * These values define the operating range and default initialization for all
 * sensor measurements in the system.
 */
#define VALUE_DEFAULT_PRES                 0.0       ///< Default oil pressure on startup (bar)
#define VALUE_DEFAULT_TEMP                 0         ///< Default oil temperature on startup (°C)
#define VALUE_DEFAULT_VOLT                 8.0       ///< Default battery voltage on startup (volts)
#define VALUE_DEFAULT_OUT_TEMP             0         ///< Default outdoor temperature on startup (°C)
#define VALUE_DEFAULT_BRIGHT               BRIGHTNESS_DAY  ///< Default brightness (day mode)
#define VALUE_DEFAULT_NIGHT_MODE           false     ///< Night mode off by default

/**
 * @brief Minimum valid sensor values (below indicates error or disconnection).
 */
#define VALUE_MIN_PRES                     VALUE_DEFAULT_PRES  ///< Minimum valid pressure (0 bar)
#define VALUE_MIN_TEMP                     VALUE_DEFAULT_TEMP  ///< Minimum valid temperature (0°C)
#define VALUE_MIN_VOLT                     VALUE_DEFAULT_VOLT  ///< Minimum valid voltage (8V - automotive minimum)
#define VALUE_MIN_OUT_TEMP                 -30       ///< Minimum valid outdoor temperature (-30°C)

/**
 * @brief Maximum valid sensor values (above indicates error or over-range).
 */
#define VALUE_MAX_PRES                     6.0       ///< Maximum valid pressure (6 bar)
#define VALUE_MAX_TEMP                     150       ///< Maximum valid temperature (150°C)
#define VALUE_MAX_VOLT                     16.0      ///< Maximum valid voltage (16V - charging system max)
#define VALUE_MAX_OUT_TEMP                 50        ///< Maximum valid outdoor temperature (50°C)

/*
#################################################################################
    IMPROVE SENSOR VALUE QUALITY
#################################################################################
*/
/**
 * @brief Sensor value oversampling counts and exponential filter coefficients.
 *
 * Oversampling: number of readings to average per update cycle.
 * Filter (alpha): exponential moving average coefficient (0-1, lower = more smoothing).
 *  New_value = alpha * current + (1-alpha) * previous
 */
#define VALUE_OVERSAMPLING_OIL_PRES        3         ///< Average 3 pressure readings
#define VALUE_OVERSAMPLING_OIL_TEMP        5         ///< Average 5 temperature readings
#define VALUE_OVERSAMPLING_VOLT            5         ///< Average 5 voltage readings
#define VALUE_OVERSAMPLING_OUT_TEMP        5         ///< Average 5 outdoor temperature readings
#define VALUE_OVERSAMPLING_BRIGHT          8         ///< Average 8 brightness readings

/**
 * @brief Exponential moving average filter coefficients for noise reduction.
 *
 * Lower values provide more smoothing but slower response to changes.
 * Range: 0.0 (very smooth, very slow) to 1.0 (no filtering, responsive).
 */
#define FILTER_ALPHA_OIL_PRES              0.1f      ///< Pressure smoothing factor
#define FILTER_ALPHA_OIL_TEMP              0.05f//0.1f      ///< Temperature smoothing factor
#define FILTER_ALPHA_VOLT                  0.05f//0.1f     ///< Voltage smoothing factor
#define FILTER_ALPHA_OUT_TEMP              0.02f//0.1f      ///< Outdoor temperature smoothing factor
#define FILTER_ALPHA_BEL                   0.02f//0.05f      ///< Brightness smoothing factor

#define NBR_DECIMALS_OIL_PRES              2
#define NBR_DECIMALS_OIL_TEMP              2
#define NBR_DECIMALS_VOLT                  2
#define NBR_DECIMALS_BEL_VOLT              2
#define NBR_DECIMALS_OUT_TEMP              2

/**
 * @brief Sensor measurement timing configuration.
 *
 * Defines how often sensor values are read and processed for each display/subsystem.
 */
#define MAIN_TICK_TIME_DELAY_MS            10                              ///< Main loop tick interval (milliseconds)
#define MEASURE_DELAY_TIME_OUT_TEMP_MS     (MAIN_TICK_TIME_DELAY_MS * 25)  ///< Display 1 update interval (250ms)
#define MEASURE_DELAY_TIME_OIL_TEMP_MS     (MAIN_TICK_TIME_DELAY_MS * 20)  ///< Display 2 update interval (200ms)
#define MEASURE_DELAY_TIME_OIL_PRES_MS     (MAIN_TICK_TIME_DELAY_MS *  2)  ///< Display 3 update interval (20ms)
#define MEASURE_DELAY_TIME_VOLT_MS         (MAIN_TICK_TIME_DELAY_MS * 10)  ///< Display 4 update interval (100ms)
#define MEASURE_DELAY_TIME_BRIGHT_MS       (MAIN_TICK_TIME_DELAY_MS * 10)  ///< Brightness update interval (100ms)
#define MEASURE_DELAY_TIME_BRIGHT_TEST_MS  (MAIN_TICK_TIME_DELAY_MS * 200) ///< Test mode brightness interval (1000ms)

/*
#################################################################################
    Enable Testmode Settings
#################################################################################
*/
/**
 * @brief Test mode button activation sequence parameters.
 *
 * Test mode is activated via a specific sequence of button presses within a timeout window.
 * This prevents accidental activation while maintaining flexibility for deliberate use.
 */
#define TESTMODE_ACTIVATE_TIMEOUT_MS      15000     ///< Time window for completing button sequence (15 seconds)
/**
 * @brief Button press counts required for each state transition in test mode activation.
 *
 * Sequence state transitions:
 * - State 0: First minute button press (decrease)
 * - State 0->1: After 2 total presses of minute button
 * - State 1->2: After 1 press of hour button (decrease)
 * - State 2->3: After 2 more presses of minute button (increase)
 * - State 3->4: After 1 press of hour button (increase) -> test mode toggles
 */
#define TESTMODE_ACTIVATE_BUTTON_1_COUNT  2         ///< Press minute button 2 times to reach state 1
#define TESTMODE_ACTIVATE_BUTTON_2_COUNT  1         ///< Press hour button 1 time to reach state 2
#define TESTMODE_ACTIVATE_BUTTON_3_COUNT  2         ///< Press minute button 2 times to reach state 3
#define TESTMODE_ACTIVATE_BUTTON_4_COUNT  1         ///< Press hour button 1 time to toggle test mode
