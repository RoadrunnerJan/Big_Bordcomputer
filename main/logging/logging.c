/*
 * ============================================================================
 * LOGGING MODULE - Debug Output Implementation
 * ============================================================================
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

#include "logging.h"


/* ===== Function Implementations ===== */

/**
 * Print informational log message
 * Output only if LOGGING_ENABLED is true in individual_config.h
 */
void printLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGI(LOGGING_TAG, "%s", message);
#endif
}


/**
 * Print error log message
 * Output only if LOGGING_ENABLED is true in individual_config.h
 */
void printErrorLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGE(LOGGING_TAG, "%s", message);
#endif
}


/**
 * Print warning log message
 * Output only if LOGGING_ENABLED is true in individual_config.h
 */
void printWarningLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGW(LOGGING_TAG, "%s", message);
#endif
}
