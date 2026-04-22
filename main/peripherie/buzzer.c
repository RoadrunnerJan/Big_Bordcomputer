/**
 * @file buzzer.c
 * @brief Buzzer control audio alert driver implementation.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - LEDC PWM configuration for audio output
 *      - Temperature alert beeping patterns
 */

#include "buzzer.h"


/* ===== Global PWM Configuration ===== */
ledc_timer_config_t buz_timer = {0};
ledc_channel_config_t buz_channel = {0};


/* ===== Function Implementations ===== */

/**
 * @brief Initialize buzzer PWM hardware.
 *
 * Configures LEDC timer and channel for audio output with settings from configuration.
 */
void buzzer_init(void)
{
    // Configure timer
    buz_timer.speed_mode      = BUZZER_SETTING_SPEED_MODE;
    buz_timer.duty_resolution = BUZZER_SETTING_DUTY_RES;
    buz_timer.timer_num       = BUZZER_SETTING_TIMER;
    buz_timer.freq_hz         = BUZZER_SETTING_FREQ_HZ;
    buz_timer.clk_cfg         = BUZZER_SETTING_CLK_CFG;

    // Configure PWM channel
    buz_channel.gpio_num      = BUZZER_PIN;
    buz_channel.speed_mode    = BUZZER_SETTING_SPEED_MODE;
    buz_channel.channel       = BUZZER_SETTING_CHANNEL;
    buz_channel.intr_type     = BUZZER_SETTING_INTR_TYPE;
    buz_channel.timer_sel     = BUZZER_SETTING_TIMER_SEL;
    buz_channel.duty          = BUZZER_SETTING_DUTY;
    buz_channel.hpoint        = BUZZER_SETTING_HPOINT;

    // Apply configuration
    ledc_timer_config(&buz_timer);
    ledc_channel_config(&buz_channel);
}


/**
 * @brief Generate beep by setting PWM duty cycle.
 *
 * @param duty PWM duty cycle value (0 = silent, max = loudest)
 */
void buzzer_beep(uint16_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}