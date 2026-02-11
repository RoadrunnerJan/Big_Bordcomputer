#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <../lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *gauge_oil_pressure_day;
    lv_obj_t *gauge_oil_pressure_night;
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
    lv_obj_t *pressure_needle_arc;
    lv_obj_t *pressure_black_background_opa_night;
    lv_obj_t *pressure_needle_knop_light_shadow_night;
    lv_obj_t *pressure_max_indicator_night;
    lv_obj_t *pressure_min_indicator_night;
    lv_obj_t *pressure_gauge_image_night;
    lv_obj_t *pressure_gauge_scale_labels_night;
    lv_obj_t *pressure_gauge_scale_night;
    lv_obj_t *pressure_needle_knob_night;
    lv_obj_t *pressure_gauge_value_night;
    lv_obj_t *pressure_gauge_unit_night;
    lv_obj_t *pressure_needle_arc_night;
    lv_obj_t *temperature_black_background;
    lv_obj_t *temperature_needle_knop_light_shadow;
    lv_obj_t *temperature_gauge_image;
    lv_obj_t *temperature_max_indicator;
    lv_obj_t *temperature_min_indicator;
    lv_obj_t *temperature_gauge_scale;
    lv_obj_t *temperature_needle_knob;
    lv_obj_t *temperature_gauge_value;
    lv_obj_t *temperature_gauge_unit;
    lv_obj_t *temperature_needle_arc;
    lv_obj_t *volt_black_background;
    lv_obj_t *volt_needle_knop_light_shadow;
    lv_obj_t *volt_gauge_image;
    lv_obj_t *volt_max_indicator;
    lv_obj_t *volt_min_indicator;
    lv_obj_t *volt_gauge_scale;
    lv_obj_t *volt_needle_knob;
    lv_obj_t *volt_gauge_value;
    lv_obj_t *volt_gauge_unit;
    lv_obj_t *volt_needle_arc;
    lv_obj_t *temp_clock_black_background;
    lv_obj_t *temp_clock_needle_knop_light_shadow;
    lv_obj_t *temp_clock_gauge_image;
    lv_obj_t *temp_clock_min_indicator;
    lv_obj_t *temp_clock_gauge_scale;
    lv_obj_t *temp_clock_needle_knob;
    lv_obj_t *temp_clock_gauge_value;
    lv_obj_t *temp_clock_gauge_unit;
    lv_obj_t *temp_clock_needle_arc;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_GAUGE_OIL_PRESSURE_DAY = 1,
    SCREEN_ID_GAUGE_OIL_PRESSURE_NIGHT = 2,
    SCREEN_ID_GAUGE_OIL_TEMPERATURE = 3,
    SCREEN_ID_GAUGE_VOLTAGE = 4,
    SCREEN_ID_GAUGE_TEMPERATURE_CLOCK = 5,
};

void create_screen_gauge_oil_pressure_day();
void tick_screen_gauge_oil_pressure_day();

void create_screen_gauge_oil_pressure_night();
void tick_screen_gauge_oil_pressure_night();

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