#pragma once
#include "../individual_config.h"
#include "i2cFunctions.h"

/* ===== Button Library ===== */
#include "iot_button.h"
#include "button_gpio.h"
#include "freertos/FreeRTOS.h"
#include <sys/time.h>

#if THIRD_BUTTON == true
    #define NUMBER_OF_BUTTONS 3
#else
    #define NUMBER_OF_BUTTONS 2
#endif

/* ===== Testmode Activation Values ===== */
/**
 * @brief Global test mode activation flag.
 */
extern bool testmode_activated;

/**
 * @brief Timestamp of last testmode activation sequence start.
 */
extern TickType_t testmode_activation_time;

/**
 * @brief Counter for consecutive button presses in activation sequence.
 */
extern int testmode_activation_count;

/**
 * @brief Current state in testmode activation sequence.
 */
extern int testmode_activation_state;

/* ===== Time Adjustment Buttons ===== */
/**
 * @brief Button configuration for hour and minute adjustment buttons.
 *
 * Index: [0] = Hour button, [1] = Minute button
 */
extern button_config_t cfg_time[NUMBER_OF_BUTTONS];

/**
 * @brief GPIO configuration for hour and minute adjustment buttons.
 *
 * Index: [0] = Hour button, [1] = Minute button
 */
extern button_gpio_config_t gpio_cfg_time[NUMBER_OF_BUTTONS];

/**
 * @brief Button handles for hour and minute adjustment buttons.
 *
 * Index: [0] = Hour button, [1] = Minute button
 */
extern button_handle_t btn_time[NUMBER_OF_BUTTONS];


/**
 * @brief Initialize the time adjustment buttons and callbacks.
 *
 * Configures GPIO buttons for hour and minute adjustment with interrupt handlers.
 */
void init_time_buttons(void);

/**
 * @brief Get the state of testmode activation.
 *
 * @return true if test mode is currently active, false otherwise
 */
inline bool is_testmode_activated(void) {
    #if TESTMODE_ACTIVE == true
        return true;
    #else
        return testmode_activated;
    #endif
}