#pragma once

/*
 * ============================================================================
 * LED BACKLIGHT CONTROL - PWM Driver for LCD Displays
 * ============================================================================
 * Manages PWM-based brightness control for SPI LCD displays
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - LEDC PWM configuration for display brightness
 *      - Percentage-based brightness control (0-100%)
 *
 */

#include "../individual_config.h"
#include "driver/ledc.h"

/* ===== External Configuration ===== */
extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

/* ===== Function Declarations ===== */

/**
 * Initialize LED backlight PWM configuration
 * Sets up LEDC timer and channel based on individual_config.h settings
 */
void init_lcd_backlight_pwm(void);

/**
 * Set LCD brightness level
 * @param percentage Brightness level (0-100%)
 */
void set_lcd_brightness(uint8_t percentage); 