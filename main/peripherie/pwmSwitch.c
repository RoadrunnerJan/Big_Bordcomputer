#include "pwmSwitch.h"

bool pwmSW_Value = false;

gpio_config_t pwmSW_conf = {0};

void init_pwmSW() {
    pwmSW_conf.pin_bit_mask = (1ULL << PWM_ADC_SWITCH_PIN);
    pwmSW_conf.mode = PWM_ADC_SWITCH_MODE,
    pwmSW_conf.pull_up_en = PWM_ADC_SWITCH_PULL_UP_EN,
    pwmSW_conf.pull_down_en = PWM_ADC_SWITCH_PULL_DOWN_EN,
    pwmSW_conf.intr_type = PWM_ADC_SWITCH_INTR_TYPE;
    gpio_config(&pwmSW_conf);
    read_pwmSW();
}

bool read_pwmSW(){
    bool value = gpio_get_level(PWM_ADC_SWITCH_PIN);
    if (value == PWM_ADC_SWTICH_VALUE_PWM && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to PWM");
        return true;
    }
    else if (value == !PWM_ADC_SWTICH_VALUE_PWM && value != pwmSW_Value) {
        pwmSW_Value = value;
        printWarningLog("Sensor reading switched to ADC");
        return true;
    }
    return false;
}