#include "buzzer.h"

ledc_timer_config_t buz_timer = {0};
ledc_channel_config_t buz_channel = {0};

void buzzer_init(){ 
    buz_timer.speed_mode = LEDC_LOW_SPEED_MODE;
    buz_timer.duty_resolution = LEDC_TIMER_13_BIT;
    buz_timer.timer_num = LEDC_TIMER_1;
    buz_timer.freq_hz = 2700;
    buz_timer.clk_cfg = LEDC_AUTO_CLK;
    buz_channel.gpio_num = BEEPER_PIN;
    buz_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    buz_channel.channel = LEDC_CHANNEL_1;
    buz_channel.intr_type = LEDC_INTR_DISABLE;
    buz_channel.timer_sel = LEDC_TIMER_1;
    buz_channel.duty = 0;
    buz_channel.hpoint = 0;

    ledc_timer_config(&buz_timer);
    ledc_channel_config(&buz_channel);
}

void buzzer_beep(uint16_t duty){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}