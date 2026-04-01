#include "pwmSwitch.h"

bool pwmSW_Value = false;

gpio_config_t pwmSW_conf = {0};

void init_pwmSW() {
    pwmSW_conf.pin_bit_mask = (1ULL << PWM_ADC_SWITCH_PIN);
    pwmSW_conf.mode = GPIO_MODE_INPUT,
    pwmSW_conf.pull_up_en = GPIO_PULLUP_DISABLE,
    pwmSW_conf.pull_down_en = GPIO_PULLDOWN_DISABLE,
    pwmSW_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&pwmSW_conf);
    read_pwmSW();
}

bool read_pwmSW(){
    bool value = gpio_get_level(PWM_ADC_SWITCH_PIN);
    if (value == true && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to PWM");
        return true;
    }
    else if (value == false && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to ADC");
        return true;
    }
    return false;
}