#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <../lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *gauge_oil_pressure;
    lv_obj_t *gauge_oil_temperature;
    lv_obj_t *gauge_voltage;
    lv_obj_t *gauge_temperature_clock;
    lv_obj_t *pressure_black_background_opa;
    lv_obj_t *pressure_needle_knop_light_shadow;
    lv_obj_t *pressure_max_indicator;
    lv_obj_t *pressure_min_indicator;
    lv_obj_t *pressure_gauge_image;
    lv_obj_t *pressure_gauge_scale_labels;
    lv_obj_t *pressure_gauge_scale;
    lv_obj_t *pressure_needle_knob;
    lv_obj_t *pressure_gauge_value;
    lv_obj_t *pressure_gauge_unit;
    lv_obj_t *temperature_black_background_opa;
    lv_obj_t *temperature_needle_knop_light_shadow;
    lv_obj_t *temperature_max_indicator;
    lv_obj_t *temperature_min_indicator;
    lv_obj_t *temperature_gauge_image;
    lv_obj_t *temperature_gauge_scale_labels;
    lv_obj_t *temperature_gauge_scale;
    lv_obj_t *temperature_needle_knob;
    lv_obj_t *temperature_gauge_value;
    lv_obj_t *temperature_gauge_unit;
    lv_obj_t *volt_black_background_opa;
    lv_obj_t *volt_needle_knop_light_shadow;
    lv_obj_t *volt_max_indicator;
    lv_obj_t *volt_min_indicator;
    lv_obj_t *volt_gauge_image;
    lv_obj_t *volt_gauge_scale_labels;
    lv_obj_t *volt_gauge_scale;
    lv_obj_t *volt_needle_knob;
    lv_obj_t *volt_gauge_value;
    lv_obj_t *volt_gauge_unit;
    lv_obj_t *temp_clock_black_background_opa;
    lv_obj_t *temp_clock_needle_knop_light_shadow;
    lv_obj_t *temp_clock_min_indicator;
    lv_obj_t *temp_clock_gauge_image;
    lv_obj_t *temp_clock_gauge_scale_labels;
    lv_obj_t *temp_clock_gauge_scale;
    lv_obj_t *temp_clock_needle_knob;
    lv_obj_t *temp_clock_gauge_value;
    lv_obj_t *temp_clock_gauge_unit;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_GAUGE_OIL_PRESSURE = 1,
    SCREEN_ID_GAUGE_OIL_TEMPERATURE = 2,
    SCREEN_ID_GAUGE_VOLTAGE = 3,
    SCREEN_ID_GAUGE_TEMPERATURE_CLOCK = 4,
};

void create_screen_gauge_oil_pressure();
void tick_screen_gauge_oil_pressure();

void create_screen_gauge_oil_temperature();
void tick_screen_gauge_oil_temperature();

void create_screen_gauge_voltage();
void tick_screen_gauge_voltage();

void create_screen_gauge_temperature_clock();
void tick_screen_gauge_temperature_clock();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();






#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/