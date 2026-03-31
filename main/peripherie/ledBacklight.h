// Funktionen, um das Backlight der SPI Displays per PWM zu dimmen

#pragma once
#include "../individual_config.h"
#include "driver/ledc.h"

extern ledc_timer_config_t ledc_timer;
extern ledc_channel_config_t ledc_channel;

void init_lcd_backlight_pwm();
void set_lcd_brightness(uint8_t percentage); 