#pragma once
#include "../individual_config.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "../logging/logging.h"

extern bool pwmSW_Value;
extern gpio_config_t pwmSW_conf;

void init_pwmSW();
bool read_pwmSW();

inline bool isPWM() {return pwmSW_Value;};