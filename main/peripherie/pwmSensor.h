/**
 * @file pwmSensor.h
 * @brief PWM sensor reader for Hella 6PP 010 378-201 oil sensor.
 *
 * Decodes PWM pulse signals for oil pressure and temperature readings using
 * MCPWM (Motor Control PWM) capture functionality. Supports multi-pulse sensors
 * with diagnostic feedback.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - MCPWM capture for PWM signal decoding
 *      - Multi-pulse sensor support (temperature, pressure, diagnostic)
 *      - Hella 6PP 010 378-201 sensor integration
 *      - Test mode with serial output
 */

#pragma once

/* ===== Project Configuration ===== */
#include "../individual_config.h"

/* ===== ESP-IDF MCPWM Capture ===== */
#include "driver/mcpwm_cap.h"
#include "esp_system.h"

/* ===== Includes ===== */
#include <inttypes.h>

/* ===== Logging ===== */
#include "../logging/logging.h"


/* ===== PWM Sensor Data Structures ===== */

/**
 * @brief PWM value pair - period and pulse width.
 *
 * Stores timing information captured from a PWM signal.
 */
typedef struct {
    uint32_t period_us;  /**< Full period in microseconds */
    uint32_t value_us;   /**< Pulse width in microseconds */
} value_pair_t;

/**
 * @brief Sensor data from Hella 6PP oil sensor.
 *
 * Contains three separate pulse measurements corresponding to:
 * - Temperature sensor (PWM_SENSOR_TEMP_PULSE_ID)
 * - Pressure sensor (PWM_SENSOR_PRES_PULSE_ID)
 * - Diagnostic pulse (PWM_SENSOR_DIAG_PULSE_ID)
 */
typedef struct {
    value_pair_t temp_us;       /**< Temperature pulse data */
    value_pair_t press_us;      /**< Pressure pulse data */
    value_pair_t diag_us;       /**< Diagnostic pulse data */
    uint32_t update_count;      /**< Counter for data updates */
} sensor_data_t;


/* ===== MCPWM Capture Configuration ===== */
extern mcpwm_cap_timer_handle_t cap_timer;
extern mcpwm_capture_timer_config_t timer_config;
extern mcpwm_cap_channel_handle_t cap_chan;
extern mcpwm_capture_channel_config_t chan_config;
extern mcpwm_capture_event_callbacks_t cbs;

/* ===== Sensor Data ===== */
extern volatile sensor_data_t latest_sensor_values;

/* ===== Pulse Tracking Variables ===== */
extern uint32_t last_pos_edge;      /**< Last positive edge timestamp */
extern int pulse_idx;               /**< Current pulse index (0-2 for 3 sensors) */
extern uint32_t period_us;          /**< Measured period in microseconds */
extern uint32_t width;              /**< Measured pulse width in microseconds */
extern uint32_t last_seen_count;    /**< Counter for timeout detection */
extern int first_init_done;         /**< Initialization flag */


/* ===== Function Declarations ===== */

/**
 * Initialize PWM sensor MCPWM capture hardware
 */
void pwm_sensor_init(void);

/**
 * Get decoded sensor value by pulse ID
 * @param id Pulse ID (PWM_SENSOR_TEMP_PULSE_ID, PWM_SENSOR_PRES_PULSE_ID, etc.)
 * @return Decoded value or ADC_FAIL_VALUE on error
 */
double get_pwm_value(int id);

void pwm_sensor_print(void);