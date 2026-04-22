#pragma once

/**
 * @file logging.h
 * @brief Logging module for debug output control.
 *
 * Provides logging functions with compile-time enable/disable support.
 * Outputs informational messages, errors, and warnings via ESP-IDF ESP_LOG macros.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - Info, error, and warning log functions
 *      - Compile-time enable/disable support
 */

#include "../individual_config.h"
#include "esp_log.h"

/* ===== Function Declarations ===== */

/**
 * @brief Print informational log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 *
 * @param message Log message string to display
 */
void printLog(const char *message);

/**
 * @brief Print error log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 *
 * @param message Error message string to display
 */
void printErrorLog(const char *message);

/**
 * @brief Print warning log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 *
 * @param message Warning message string to display
 */
void printWarningLog(const char *message);
