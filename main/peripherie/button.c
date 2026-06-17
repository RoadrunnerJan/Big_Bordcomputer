#include "button.h"

/* Time adjustment buttons: [0] = Hour, [1] = Minute, optional: [2] = Button for switching displays */
button_config_t cfg_time[NUMBER_OF_BUTTONS] = {0};
button_gpio_config_t gpio_cfg_time[NUMBER_OF_BUTTONS] = {0};
button_handle_t btn_time[NUMBER_OF_BUTTONS] = {0};

bool testmode_activated = false;
TickType_t testmode_activation_time = 0;
int testmode_activation_count = 0;
int testmode_activation_state = -1;


/**
 * @brief Button callback for forward time adjustments and test mode activation.
 *
 * Implements the forward path of test mode activation sequence:
 * - Increments hour or minute based on button pressed
 * - Checks if button sequence matches testmode activation pattern (states 3-4)
 * - Toggles test mode when final activation condition is met
 * - Synchronizes updated time to both RTC and system clock
 *
 * Activation sequence (within TESTMODE_ACTIVATE_TIMEOUT_MS):
 * 1. Press minute button twice (decrease, state 0-1)
 * 2. Press hour button once (decrease, state 1-2)
 * 3. Press minute button twice (increase, state 2-3)
 * 4. Press hour button once (increase, state 3-4) -> toggles test mode
 *
 * @param btn_handle Button handle (unused)
 * @param usr_data Button ID as void pointer (BUTTON_CLOCK_HOUR_PIN or BUTTON_CLOCK_MINUTE_PIN)
 */
static void button_event_cb(void *btn_handle, void *usr_data) {
    setIsCheckPossible(false);
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour + 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour incremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 4) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_4_COUNT) {
                    testmode_activation_state = -1;
                    testmode_activation_count = 0;
                    testmode_activated = !testmode_activated; // Toggle test mode
                    printWarningLog(testmode_activated == true ? "Test mode ACTIVATED!" : "Test mode DEACTIVATED!");
                }
            }
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min + 1 + 60) % 60;
        if (timeinfo.tm_min == 0) { 
            timeinfo.tm_hour = (timeinfo.tm_hour + 1) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour incremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute incremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == 3) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_3_COUNT) {
                    testmode_activation_state = 4;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }
    #if THIRD_BUTTON == true
        else if (button_id == BUTTON_THIRD_PIN) {
            // Optional: Handle third button for switching displays or other functions

        }
    #endif

    rtc_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);

    // Update last execution time for hours
    rtc_set_last_executionTime(&tv);
    setIsCheckPossible(true);
}

/**
 * @brief Button callback for backward time adjustments and test mode activation.
 *
 * Implements the backward path of test mode activation sequence:
 * - Decrements hour or minute based on button pressed
 * - Checks if button sequence matches testmode activation pattern (states 0-2)
 * - Transitions through activation states when conditions are met
 * - Synchronizes updated time to both RTC and system clock
 *
 * Activation sequence (within TESTMODE_ACTIVATE_TIMEOUT_MS):
 * 1. First button press initializes activation counter (state -1 to 0)
 * 2. Subsequent presses increment counter until TESTMODE_ACTIVATE_BUTTON_1_COUNT is reached
 * 3. Progresses through states 0 -> 2 -> 3 before final state 4 completion
 *
 * @param btn_handle Button handle (unused)
 * @param usr_data Button ID as void pointer (BUTTON_CLOCK_HOUR_PIN or BUTTON_CLOCK_MINUTE_PIN)
 */
static void button_event_cb_back(void *btn_handle, void *usr_data) {
    setIsCheckPossible(false);
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour decremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 2) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_2_COUNT) {
                    testmode_activation_state = 3;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min - 1 + 60) % 60;
        if (timeinfo.tm_min == 59) { 
            timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour decremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute decremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == -1) {
            testmode_activation_state = 0;
            testmode_activation_time = xTaskGetTickCount();
            testmode_activation_count = 1;
        }
        else if (testmode_activation_state == 0) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_1_COUNT) {
                    testmode_activation_state = 2;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }
    #if THIRD_BUTTON == true
        else if (button_id == BUTTON_THIRD_PIN) {
            // Optional: Handle third button for switching displays or other functions

        }
    #endif

    // Write to RTC
    rtc_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);

    // Update last execution time for hours
    rtc_set_last_executionTime(&tv);
    setIsCheckPossible(true);
}

/**
 * @brief Initialize time adjustment buttons with callbacks.
 *
 * Configures GPIO-based buttons for hour and minute time adjustments.
 * Registers single-click handlers for time increment and long-press handlers
 * for time decrement. Each button is independently configured with its own
 * debounce timing and active level settings.
 *
 * Called during system initialization to enable runtime time adjustments
 * and test mode activation via button sequences.
 */
void init_time_buttons() {

    cfg_time[0].short_press_time = BUTTON_CLOCK_MINUTE_SHORT_MS;
    cfg_time[0].long_press_time = BUTTON_CLOCK_MINUTE_LONG_MS;
    gpio_cfg_time[0].gpio_num = BUTTON_CLOCK_HOUR_PIN;
    gpio_cfg_time[0].active_level = BUTTON_CLOCK_MINUTE_ACTIVE_LEVEL;    
    cfg_time[1].short_press_time = BUTTON_CLOCK_HOUR_SHORT_MS;
    cfg_time[1].long_press_time = BUTTON_CLOCK_HOUR_LONG_MS;
    gpio_cfg_time[1].gpio_num = BUTTON_CLOCK_MINUTE_PIN;
    gpio_cfg_time[1].active_level = BUTTON_CLOCK_HOUR_ACTIVE_LEVEL;
    #if THIRD_BUTTON == true
        cfg_time[2].short_press_time = BUTTON_THIRD_SHORT_MS;
        cfg_time[2].long_press_time = BUTTON_THIRD_LONG_MS;
        gpio_cfg_time[2].gpio_num = BUTTON_THIRD_PIN;
        gpio_cfg_time[2].active_level = BUTTON_THIRD_ACTIVE_LEVEL;
    #endif

    iot_button_new_gpio_device(&cfg_time[0], &gpio_cfg_time[0], &btn_time[0]);
    iot_button_register_cb(btn_time[0], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_register_cb(btn_time[0], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_new_gpio_device(&cfg_time[1], &gpio_cfg_time[1], &btn_time[1]);
    iot_button_register_cb(btn_time[1], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
    iot_button_register_cb(btn_time[1], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_MINUTE_PIN);
    #if THIRD_BUTTON == true
        iot_button_new_gpio_device(&cfg_time[2], &gpio_cfg_time[2], &btn_time[2]);
        iot_button_register_cb(btn_time[2], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_THIRD_PIN);
        iot_button_register_cb(btn_time[2], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_THIRD_PIN);
    #endif
}
