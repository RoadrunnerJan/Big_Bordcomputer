/**
 * @file ledBacklight.h
 * @brief LED backlight PWM driver for LCD display brightness control.
 *
 * Manages PWM-based brightness control for SPI LCD displays using ESP32's LEDC module.
 * Supports percentage-based brightness control (0-100%).
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - LEDC PWM configuration for display brightness
 *      - Percentage-based brightness control (0-100%)
 */

#include "../individual_config.h"
#include "driver/ledc.h"

/* ===== External Configuration ===== */
extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

/* ===== Function Declarations ===== */

/**
 * @brief Initialize LED backlight PWM configuration.
 *
 * Sets up LEDC timer and channel based on individual_config.h settings.
 */
void init_lcd_backlight_pwm(void);

/**
 * @brief Set LCD brightness level.
 *
 * @param percentage Brightness level (0-100%)
 */
void set_lcd_brightness(uint8_t percentage); 