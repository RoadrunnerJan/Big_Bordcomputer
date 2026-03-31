// Funktionen, um den Buzzer per PWM anzusteuern

#pragma once
#include "../individual_config.h"
#include "driver/ledc.h"

extern ledc_timer_config_t buz_timer;
extern ledc_channel_config_t buz_channel;

void buzzer_init();
void buzzer_beep(uint16_t duty);