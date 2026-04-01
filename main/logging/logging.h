#pragma once

/*
 * ============================================================================
 * LOGGING MODULE - Debug Output Control
 * ============================================================================
 * Provides logging functions with compile-time enable/disable via LOGGING_ENABLED
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - Info, error, and warning log functions
 *      - Compile-time enable/disable support
 *
 */

#include "../individual_config.h"
#include "esp_log.h"

/* ===== Function Declarations ===== */

/**
 * @brief Print informational log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 * @param message Log message string.
 */
void printLog(const char *message);

/**
 * @brief Print error log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 * @param message Error message string.
 */
void printErrorLog(const char *message);

/**
 * @brief Print warning log message.
 *
 * Output only if LOGGING_ENABLED is true in configuration.
 * @param message Warning message string.
 */
void printWarningLog(const char *message);

/**
 * Print error log message
 * Output only if LOGGING_ENABLED is true
 * @param message Error message string
 */
void printErrorLog(const char *message);

/**
 * Print warning log message
 * Output only if LOGGING_ENABLED is true
 * @param message Warning message string
 */
void printWarningLog(const char *message);
