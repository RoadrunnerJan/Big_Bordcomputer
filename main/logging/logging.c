#include "logging.h"

void printLog(const char *message) {
    #if LOGGING_ENABLED == true
        ESP_LOGI(LOGGING_TAG, "%s", message);
    #endif
}

void printErrorLog(const char *message) {
    #if LOGGING_ENABLED == true
        ESP_LOGE(LOGGING_TAG, "%s", message);
    #endif
}

void printWarningLog(const char *message) {
    #if LOGGING_ENABLED == true
        ESP_LOGW(LOGGING_TAG, "%s", message);
    #endif
}
