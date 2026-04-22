/**
 * @file buzzer.h
 * @brief Buzzer control module for audio warnings via PWM.
 *
 * Generates audio alerts via PWM-controlled buzzer for temperature warnings.
 * Configured using LEDC (LED PWM Controller) for precise frequency control.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - LEDC PWM configuration for audio output
 *      - Temperature alert beeping patterns
 */

#pragma once

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF PWM Driver ===== */
#include "driver/ledc.h"


/* ===== PWM Configuration ===== */
extern ledc_timer_config_t buz_timer;
extern ledc_channel_config_t buz_channel;


/* ===== Function Declarations ===== */

/**
 * @brief Initialize buzzer PWM hardware.
 *
 * Configures LEDC timer and channel for audio output using settings from configuration.
 */
void buzzer_init(void);

/**
 * @brief Generate beep by setting PWM duty cycle.
 *
 * @param duty PWM duty cycle value (0 = silent, higher = louder)
 */
void buzzer_beep(uint16_t duty);