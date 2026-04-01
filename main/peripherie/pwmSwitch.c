/*
 * ============================================================================
 * PWM/ADC SWITCH - Sensor Input Selection Implementation
 * ============================================================================
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - GPIO-based sensor mode selection
 *      - Mode change detection and logging
 *
 */

#include "pwmSwitch.h"


/* ===== Global Switch State ===== */
bool pwmSW_Value = false;           // Current switch state
gpio_config_t pwmSW_conf = {0};     // GPIO configuration


/* ===== Function Implementations ===== */

/**
 * Initialize PWM/ADC selector GPIO pin
 * Configures GPIO and reads initial state
 */
void init_pwmSW(void)
{
    // Configure GPIO pin
    pwmSW_conf.pin_bit_mask = (1ULL << PWM_ADC_SWITCH_PIN);
    pwmSW_conf.mode         = PWM_ADC_SWITCH_MODE;
    pwmSW_conf.pull_up_en   = PWM_ADC_SWITCH_PULL_UP_EN;
    pwmSW_conf.pull_down_en = PWM_ADC_SWITCH_PULL_DOWN_EN;
    pwmSW_conf.intr_type    = PWM_ADC_SWITCH_INTR_TYPE;

    gpio_config(&pwmSW_conf);
    read_pwmSW();  // Initialize state
}


/**
 * Read current sensor input selector state
 * Detects changes and logs sensor mode switching
 * @return true if state changed, false if unchanged
 */
bool read_pwmSW(void)
{
    bool value = gpio_get_level(PWM_ADC_SWITCH_PIN);

    // Check for PWM mode
    if (value == PWM_ADC_SWTICH_VALUE_PWM && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to PWM");
        return true;
    }
    // Check for ADC mode
    else if (value == !PWM_ADC_SWTICH_VALUE_PWM && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to ADC");
        return true;
    }

    return false;
}