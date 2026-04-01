/*
 * ============================================================================
 * LED BACKLIGHT CONTROL - PWM Driver Implementation
 * ============================================================================
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

#include "ledBacklight.h"

/* ===== Global PWM Configuration ===== */
ledc_timer_config_t ledc_timer = {0};
ledc_channel_config_t ledc_channel = {0};


/* ===== Function Implementations ===== */

/**
 * Initialize LED backlight PWM configuration
 * Configures LEDC timer and channel for LCD brightness control
 */
void init_lcd_backlight_pwm(void)
{
    // Configure timer
    ledc_timer.speed_mode       = LED_SPEED;
    ledc_timer.timer_num        = LED_TIMER;
    ledc_timer.duty_resolution  = LED_DUTY_RESOLUTION;
    ledc_timer.freq_hz          = LED_FREQ;
    ledc_timer.clk_cfg          = LED_CLK;

    // Configure PWM channel
    ledc_channel.speed_mode    = LED_SPEED;
    ledc_channel.channel       = LED_CHANNEL;
    ledc_channel.timer_sel     = LED_TIMER;
    ledc_channel.intr_type     = LED_INTR;
    ledc_channel.gpio_num      = LED_GPIO;
    ledc_channel.duty          = LED_START_BRIGHT;
    ledc_channel.hpoint        = LED_H_POINT;

    // Apply configuration
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
}


/**
 * Set LCD brightness level (0-100%)
 * Converts percentage to duty cycle value
 */
void set_lcd_brightness(uint8_t percentage)
{
    // Clamp percentage to valid range
    if (percentage > 100) {
        percentage = 100;
    }

    // Calculate duty value from percentage
    uint32_t duty = (LED_DUTY_RES_VALUE * percentage) / 100;

    // Apply duty cycle
    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}