/**
 * @file logging.c
 * @brief Logging module debug output implementation.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - Info, error, and warning log functions
 *      - Compile-time enable/disable support
 */

#include "logging.h"


/* ===== Function Implementations ===== */

/**
 * @brief Print informational log message.
 *
 * Output only if LOGGING_ENABLED is true in individual_config.h
 *
 * @param message Log message string to display
 */
void printLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGI(LOGGING_TAG, "%s", message);
#endif
}


/**
 * @brief Print error log message.
 *
 * Output only if LOGGING_ENABLED is true in individual_config.h
 *
 * @param message Error message string to display
 */
void printErrorLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGE(LOGGING_TAG, "%s", message);
#endif
}


/**
 * @brief Print warning log message.
 *
 * Output only if LOGGING_ENABLED is true in individual_config.h
 *
 * @param message Warning message string to display
 */
void printWarningLog(const char *message)
{
#if LOGGING_ENABLED == true
    ESP_LOGW(LOGGING_TAG, "%s", message);
#endif
}
