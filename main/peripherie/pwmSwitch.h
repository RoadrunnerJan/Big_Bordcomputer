/**
 * @file pwmSwitch.h
 * @brief PWM/ADC input mode selector.
 *
 * GPIO switch to toggle between PWM sensor and I2C ADC input modes.
 * Allows switching sensor input source at runtime.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - GPIO-based sensor mode selection
 *      - Mode change detection and logging
 */

#pragma once

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
 * @brief Initialize PWM/ADC selector GPIO pin.
 *
 * Configures GPIO for reading the sensor input mode selector switch.
 */
void init_pwmSW(void);

/**
 * @brief Read current sensor input selector state.
 *
 * Detects changes in sensor input mode and logs state transitions.
 *
 * @return true if state changed, false if unchanged
 */
bool read_pwmSW(void);

/**
 * @brief Get current sensor input mode.
 *
 * @return true for PWM sensor mode, false for I2C ADC mode
 */
inline bool isPWM(void) { return pwmSW_Value; }