#include "ledBacklight.h"

ledc_timer_config_t ledc_timer = {0};
ledc_channel_config_t ledc_channel = {0};

void init_lcd_backlight_pwm() {
    ledc_timer.speed_mode =       LED_SPEED;
    ledc_timer.timer_num =        LED_TIMER;
    ledc_timer.duty_resolution =  LED_DUTY_RESOLUTION;
    ledc_timer.freq_hz =          LED_FREQ;              
    ledc_timer.clk_cfg =          LED_CLK;
    ledc_channel.speed_mode =     LED_SPEED;
    ledc_channel.channel =        LED_CHANNEL;
    ledc_channel.timer_sel =      LED_TIMER;
    ledc_channel.intr_type =      LED_INTR;
    ledc_channel.gpio_num =       LED_GPIO;
    ledc_channel.duty =           LED_START_BRIGHT;
    ledc_channel.hpoint =         LED_H_POINT;
    
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
}

void set_lcd_brightness(uint8_t percentage) {
    if (percentage > 100) percentage = 100;
    uint32_t duty = (LED_DUTY_RES_VALUE * percentage) / 100;
    
    ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duty);
    ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}