// #define log_enabled


#ifdef log_enabled
    static const char *TAG = "BC_BIG_E36";

    void printLog(const char *message) {
        ESP_LOGI(TAG, "%s", message);
    }

    void printErrorLog(const char *message) {
        ESP_LOGE(TAG, "%s", message);
    }

    void printWarningLog(const char *message) {
        ESP_LOGW(TAG, "%s", message);
    }
#else
    void printLog(const char *message) {
        (void)message; // Verhindert "unused parameter" Warnung
    }

    void printErrorLog(const char *message) {
        (void)message; // Verhindert "unused parameter" Warnung
    }

    void printWarningLog(const char *message) {
        (void)message; // Verhindert "unused parameter" Warnung
    }
#endif
