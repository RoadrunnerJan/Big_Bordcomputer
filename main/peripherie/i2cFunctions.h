#pragma once
#include "../individual_config.h"
#include "driver/i2c_master.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/time.h>

typedef struct {
    float temp;
    float res;
} ntc_table_t;

// i2C settings
extern i2c_master_bus_config_t bus_cfg;
extern i2c_master_bus_handle_t bus_handle;
extern i2c_device_config_t ds3231_cfg;
extern i2c_master_dev_handle_t ds3231_handle;
extern i2c_device_config_t ads_cfg[NUMBER_OF_ADS1115_DEVICES];
extern i2c_master_dev_handle_t ads_handle[NUMBER_OF_ADS1115_DEVICES];

// time button settings
extern button_config_t cfg_time[2]; // 0 = Stunde, 1 = Minute
extern button_gpio_config_t gpio_cfg_time[2];
extern button_handle_t btn_time[2];

extern const ntc_table_t oil_temp_table[];
extern const ntc_table_t outside_temperature_table[];
#define OIL_TABLE_SIZE (sizeof(oil_temp_table) / sizeof(ntc_table_t))
#define OUTSIDE_TABLE_SIZE (sizeof(outside_temperature_table) / sizeof(ntc_table_t))

void init_i2c();
void sync_rtc_to_system();
void init_time_buttons();
float get_i2c_adc_volt();
float get_i2c_adc_volt_bel();
float get_i2c_adc_oil_temp();
float get_i2c_adc_oil_press();
float get_i2c_adc_outside_temp();