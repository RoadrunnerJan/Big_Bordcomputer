#pragma once
#include "../individual_config.h"
#include "driver/i2c_master.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <sys/time.h>

#define LSB_2048 0.0625f
#define LSB_4096 0.125f
#define OIL_TABLE_SIZE (sizeof(oil_temp_table) / sizeof(ntc_table_t))

#define ADC_MAX_V_VALID 3.25f 

#define FILTER_ALPHA 0.1f 

#define BEL_MAX_PLAUSIBLE 16.0f  // Alles darüber ist "Offener Pin / Rauschen"
#define BEL_MIN_PLAUSIBLE 0.8f   // Mindestspannung für "Licht an" (Schutz gegen Kriechströme)
#define BOARD_MIN_PLAUSIBLE 6.0f 
#define BMW_TABLE_SIZE (sizeof(bmw_outside_table) / sizeof(bmw_ntc_table_t))

extern i2c_master_bus_handle_t bus_handle;
extern i2c_master_dev_handle_t ds3231_handle;

extern i2c_master_dev_handle_t ads1_handle;
extern i2c_master_dev_handle_t ads2_handle;

typedef struct {
    int repeat_count;
} button_state_t;

extern button_state_t hour_state;
extern button_state_t min_state;

// ADS1115 Spannungsstufen (LSB in mV)
typedef struct {
    float temp;
    float res;
} ntc_table_t;

extern const ntc_table_t oil_temp_table[];


extern bool value_set[6]; // Flags für die ersten 6 Sensoren

typedef struct {
    float temp;
    float res;
} bmw_ntc_table_t;

extern const bmw_ntc_table_t bmw_outside_table[];


// Globale Variablen für die gefilterten Werte (Initialisierung auf 0)
extern float filtered_v_board; // Startwert, z.B. 8V
extern float filtered_v_bel;
extern float filtered_oil_temp;
extern float filtered_oil_press;
extern float filtered_outside_temp; // Startwert ca. Zimmertemperatur



void init_i2c();
void sync_rtc_to_system();
void init_time_buttons();
float get_i2c_adc_volt();
float get_i2c_adc_volt_bel();
float get_i2c_adc_oil_temp();
float get_i2c_adc_oil_press();
float get_i2c_adc_outside_temp();