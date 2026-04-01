#pragma once

/*
 * ============================================================================
 * BUZZER CONTROL - Audio Alert Driver
 * ============================================================================
 * Generates audio alerts via PWM-controlled buzzer for temperature warnings
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - LEDC PWM configuration for audio output
 *      - Temperature alert beeping patterns
 *
 */

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF PWM Driver ===== */
#include "driver/ledc.h"


/* ===== PWM Configuration ===== */
extern ledc_timer_config_t buz_timer;
extern ledc_channel_config_t buz_channel;


/* ===== Function Declarations ===== */

/**
 * Initialize buzzer PWM hardware
 * Sets up LEDC configuration for audio output
 */
void buzzer_init(void);

/**
 * Generate beep by setting PWM duty cycle
 * @param duty PWM duty value (0-max value from configuration)
 */
void buzzer_beep(uint16_t duty);