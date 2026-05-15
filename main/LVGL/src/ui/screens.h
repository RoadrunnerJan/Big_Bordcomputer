#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_GAUGE_OIL_PRESSURE = 1,
    SCREEN_ID_GAUGE_OIL_PRESSURE_NIGHT = 2,
    SCREEN_ID_GAUGE_OIL_TEMPERATURE = 3,
    SCREEN_ID_GAUGE_OIL_TEMPERATURE_NIGHT = 4,
    SCREEN_ID_GAUGE_VOLTAGE = 5,
    SCREEN_ID_GAUGE_VOLTAGE_NIGHT = 6,
    SCREEN_ID_GAUGE_TEMPERATURE_CLOCK = 7,
    SCREEN_ID_GAUGE_TEMPERATURE_CLOCK_NIGHT = 8,
    SCREEN_ID_GAUGE_CLOCK_TEMPERATURE = 9,
    SCREEN_ID_GAUGE_CLOCK_TEMPERATURE_NIGHT = 10,
    _SCREEN_ID_LAST = 10
};

typedef struct _objects_t {
    lv_obj_t *gauge_oil_pressure;
    lv_obj_t *gauge_oil_pressure_night;
    lv_obj_t *gauge_oil_temperature;
    lv_obj_t *gauge_oil_temperature_night;
    lv_obj_t *gauge_voltage;
    lv_obj_t *gauge_voltage_night;
    lv_obj_t *gauge_temperature_clock;
    lv_obj_t *gauge_temperature_clock_night;
    lv_obj_t *gauge_clock_temperature;
    lv_obj_t *gauge_clock_temperature_night;
    lv_obj_t *pressure_black_background_opa;
    lv_obj_t *pressure_needle_knop_light_shadow;
    lv_obj_t *pressure_max_indicator;
    lv_obj_t *pressure_min_indicator;
    lv_obj_t *pressure_gauge_image;
    lv_obj_t *pressure_gauge_scale_labels;
    lv_obj_t *pressure_gauge_value;
    lv_obj_t *pressure_gauge_unit;
    lv_obj_t *pressure_gauge_scale;
    lv_obj_t *pressure_needle_knob;
    lv_obj_t *pressure_black_background_opa_night;
    lv_obj_t *pressure_needle_knop_light_shadow_night;
    lv_obj_t *pressure_max_indicator_night;
    lv_obj_t *pressure_min_indicator_night;
    lv_obj_t *pressure_gauge_image_night;
    lv_obj_t *pressure_gauge_scale_labels_night;
    lv_obj_t *pressure_gauge_value_night;
    lv_obj_t *pressure_gauge_unit_night;
    lv_obj_t *pressure_gauge_scale_night;
    lv_obj_t *pressure_needle_knob_night;
    lv_obj_t *temperature_black_background_opa;
    lv_obj_t *temperature_needle_knop_light_shadow;
    lv_obj_t *temperature_max_indicator;
    lv_obj_t *temperature_min_indicator;
    lv_obj_t *temperature_gauge_image;
    lv_obj_t *temperature_gauge_scale_labels;
    lv_obj_t *temperature_gauge_value;
    lv_obj_t *temperature_gauge_unit;
    lv_obj_t *temperature_gauge_scale;
    lv_obj_t *temperature_needle_knob;
    lv_obj_t *temperature_black_background_opa_night;
    lv_obj_t *temperature_needle_knop_light_shadow_night;
    lv_obj_t *temperature_max_indicator_night;
    lv_obj_t *temperature_min_indicator_night;
    lv_obj_t *temperature_gauge_image_night;
    lv_obj_t *temperature_gauge_scale_labels_night;
    lv_obj_t *temperature_gauge_value_night;
    lv_obj_t *temperature_gauge_unit_night;
    lv_obj_t *temperature_gauge_scale_night;
    lv_obj_t *temperature_needle_knob_night;
    lv_obj_t *volt_black_background_opa;
    lv_obj_t *volt_needle_knop_light_shadow;
    lv_obj_t *volt_max_indicator;
    lv_obj_t *volt_min_indicator;
    lv_obj_t *volt_gauge_image;
    lv_obj_t *volt_gauge_scale_labels;
    lv_obj_t *volt_gauge_value;
    lv_obj_t *volt_gauge_unit;
    lv_obj_t *volt_gauge_scale;
    lv_obj_t *volt_needle_knob;
    lv_obj_t *volt_black_background_opa_night;
    lv_obj_t *volt_needle_knop_light_shadow_night;
    lv_obj_t *volt_max_indicator_night;
    lv_obj_t *volt_min_indicator_night;
    lv_obj_t *volt_gauge_image_night;
    lv_obj_t *volt_gauge_scale_labels_night;
    lv_obj_t *volt_gauge_value_night;
    lv_obj_t *volt_gauge_unit_night;
    lv_obj_t *volt_gauge_scale_night;
    lv_obj_t *volt_needle_knob_night;
    lv_obj_t *temp_clock_black_background_opa;
    lv_obj_t *temp_clock_needle_knop_light_shadow;
    lv_obj_t *temp_clock_min_indicator;
    lv_obj_t *temp_clock_gauge_image;
    lv_obj_t *temp_clock_gauge_scale_labels;
    lv_obj_t *temp_clock_gauge_value;
    lv_obj_t *temp_clock_gauge_unit;
    lv_obj_t *temp_clock_gauge_scale;
    lv_obj_t *temp_clock_needle_knob;
    lv_obj_t *temp_clock_black_background_opa_night;
    lv_obj_t *temp_clock_needle_knop_light_shadow_night;
    lv_obj_t *temp_clock_min_indicator_night;
    lv_obj_t *temp_clock_gauge_image_night;
    lv_obj_t *temp_clock_gauge_scale_labels_night;
    lv_obj_t *temp_clock_gauge_value_night;
    lv_obj_t *temp_clock_gauge_unit_night;
    lv_obj_t *temp_clock_gauge_scale_night;
    lv_obj_t *temp_clock_needle_knob_night;
    lv_obj_t *clock_temp_black_background_opa;
    lv_obj_t *clock_temp_gauge_scale_hour_labels;
    lv_obj_t *clock_temp_gauge_12;
    lv_obj_t *clock_temp_gauge_image;
    lv_obj_t *clock_temp_six_blacking;
    lv_obj_t *clock_temp_gauge_value;
    lv_obj_t *clock_temp_gauge_unit;
    lv_obj_t *clock_temp_needle_knop_light_shadow;
    lv_obj_t *clock_temp_gauge_scale_hour;
    lv_obj_t *clock_temp_gauge_scale_minute;
    lv_obj_t *clock_temp_needle_knob;
    lv_obj_t *clock_temp_gauge_scale_hour_labels_night;
    lv_obj_t *clock_temp_gauge_12_night;
    lv_obj_t *clock_temp_gauge_image_night;
    lv_obj_t *clock_temp_six_blacking_night;
    lv_obj_t *clock_temp_gauge_value_night;
    lv_obj_t *clock_temp_black_background_opa_night;
    lv_obj_t *clock_temp_gauge_unit_night;
    lv_obj_t *clock_temp_needle_knop_light_shadow_night;
    lv_obj_t *clock_temp_gauge_scale_hour_night;
    lv_obj_t *clock_temp_gauge_scale_minute_night;
    lv_obj_t *clock_temp_needle_knob_night;
} objects_t;

extern objects_t objects;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_oil_pressure_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_oil_pressure_night_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_oil_temperature_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_oil_temperature_night_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_voltage_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_voltage_night_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_temperature_clock_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
} screen_gauge_temperature_clock_night_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
    lv_meter_scale_t *scale2;
    lv_meter_indicator_t *indicator1;
} screen_gauge_clock_temperature_state_t;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_indicator_t *indicator;
    lv_meter_scale_t *scale2;
    lv_meter_indicator_t *indicator1;
} screen_gauge_clock_temperature_night_state_t;

extern screen_gauge_oil_pressure_state_t screen_gauge_oil_pressure_state;
extern screen_gauge_oil_pressure_night_state_t screen_gauge_oil_pressure_night_state;
extern screen_gauge_oil_temperature_state_t screen_gauge_oil_temperature_state;
extern screen_gauge_oil_temperature_night_state_t screen_gauge_oil_temperature_night_state;
extern screen_gauge_voltage_state_t screen_gauge_voltage_state;
extern screen_gauge_voltage_night_state_t screen_gauge_voltage_night_state;
extern screen_gauge_temperature_clock_state_t screen_gauge_temperature_clock_state;
extern screen_gauge_temperature_clock_night_state_t screen_gauge_temperature_clock_night_state;
extern screen_gauge_clock_temperature_state_t screen_gauge_clock_temperature_state;
extern screen_gauge_clock_temperature_night_state_t screen_gauge_clock_temperature_night_state;

void create_screen_gauge_oil_pressure();
void tick_screen_gauge_oil_pressure();

void create_screen_gauge_oil_pressure_night();
void tick_screen_gauge_oil_pressure_night();

void create_screen_gauge_oil_temperature();
void tick_screen_gauge_oil_temperature();

void create_screen_gauge_oil_temperature_night();
void tick_screen_gauge_oil_temperature_night();

void create_screen_gauge_voltage();
void tick_screen_gauge_voltage();

void create_screen_gauge_voltage_night();
void tick_screen_gauge_voltage_night();

void create_screen_gauge_temperature_clock();
void tick_screen_gauge_temperature_clock();

void create_screen_gauge_temperature_clock_night();
void tick_screen_gauge_temperature_clock_night();

void create_screen_gauge_clock_temperature();
void tick_screen_gauge_clock_temperature();

void create_screen_gauge_clock_temperature_night();
void tick_screen_gauge_clock_temperature_night();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/