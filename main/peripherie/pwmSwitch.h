#pragma once

/*
 * ============================================================================
 * PWM/ADC SWITCH - Sensor Input Selection
 * ============================================================================
 * GPIO switch to toggle between PWM sensor and I2C ADC input modes
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - GPIO-based sensor mode selection
 *      - Mode change detection and logging
 *
 */

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF GPIO Driver ===== */
#include "driver/gpio.h"
#include "esp_system.h"

/* ===== Utilities ===== */
#include "../logging/logging.h"


/* ===== Switch State ===== */
extern bool pwmSW_Value;                  // Current switch state (true=PWM, false=ADC)
extern gpio_config_t pwmSW_conf;          // GPIO configuration


/* ===== Function Declarations ===== */

/**
 * Initialize PWM/ADC selector GPIO pin
 */
void init_pwmSW(void);

/**
 * Read current sensor input selector state
 * @return true if PWM sensors selected, false if I2C ADC selected
 */
bool read_pwmSW(void);

/**
 * Inline accessor for current sensor input mode
 * @return true for PWM sensor, false for I2C ADC
 */
inline bool isPWM(void) { return pwmSW_Value; }