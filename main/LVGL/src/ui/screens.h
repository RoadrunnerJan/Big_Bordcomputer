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
    SCREEN_ID_GAUGE_OIL_TEMPERATURE = 2,
    SCREEN_ID_GAUGE_VOLTAGE = 3,
    SCREEN_ID_GAUGE_TEMPERATURE_CLOCK = 4,
    SCREEN_ID_GAUGE_CLOCK_TEMPERATURE = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *gauge_oil_pressure;
    lv_obj_t *gauge_oil_temperature;
    lv_obj_t *gauge_voltage;
    lv_obj_t *gauge_temperature_clock;
    lv_obj_t *gauge_clock_temperature;
    lv_obj_t *pressure_black_background;
    lv_obj_t *pressure_gauge_image;
    lv_obj_t *pressure_gauge_scale;
    lv_obj_t *pressure_gauge_needle;
    lv_obj_t *pressure_gauge_knob;
    lv_obj_t *pressure_gauge_value;
    lv_obj_t *pressure_gauge_unit;
    lv_obj_t *temperature_black_background;
    lv_obj_t *temperature_gauge_image;
    lv_obj_t *temperature_gauge_scale;
    lv_obj_t *temperature_gauge_needle;
    lv_obj_t *temperature_gauge_knob;
    lv_obj_t *temperature_gauge_value;
    lv_obj_t *temperature_gauge_unit;
    lv_obj_t *voltage_black_background;
    lv_obj_t *volt_gauge_image;
    lv_obj_t *voltage_gauge_scale;
    lv_obj_t *voltage_gauge_needle;
    lv_obj_t *voltage_gauge_knob;
    lv_obj_t *volt_gauge_value;
    lv_obj_t *volt_gauge_unit;
    lv_obj_t *temp_clock_black_background;
    lv_obj_t *temp_clock_gauge_image;
    lv_obj_t *temp_clock_gauge_scale;
    lv_obj_t *temp_clock_gauge_needle;
    lv_obj_t *temp_clock_gauge_knob;
    lv_obj_t *temp_clock_gauge_value;
    lv_obj_t *temp_clock_gauge_unit;
    lv_obj_t *clock_temp_black_background_opa;
    lv_obj_t *clock_temp_gauge_image;
    lv_obj_t *clock_temp_gauge_scale;
    lv_obj_t *clock_temp_gauge_needle_minute;
    lv_obj_t *clock_temp_gauge_needle_hour;
    lv_obj_t *clock_temp_gauge_knob;
    lv_obj_t *clock_temp_gauge_unit;
    lv_obj_t *clock_temp_gauge_value;
} objects_t;

extern objects_t objects;

typedef struct {
    lv_scale_section_t *max;
    lv_scale_section_t *min;
} screen_gauge_oil_pressure_state_t;

typedef struct {
    lv_scale_section_t *max;
    lv_scale_section_t *min;
} screen_gauge_oil_temperature_state_t;

typedef struct {
    lv_scale_section_t *max;
    lv_scale_section_t *min;
} screen_gauge_voltage_state_t;

typedef struct {
    lv_scale_section_t *min;
} screen_gauge_temperature_clock_state_t;

typedef struct {
    lv_scale_section_t *max;
} screen_gauge_clock_temperature_state_t;

extern screen_gauge_oil_pressure_state_t screen_gauge_oil_pressure_state;
extern screen_gauge_oil_temperature_state_t screen_gauge_oil_temperature_state;
extern screen_gauge_voltage_state_t screen_gauge_voltage_state;
extern screen_gauge_temperature_clock_state_t screen_gauge_temperature_clock_state;
extern screen_gauge_clock_temperature_state_t screen_gauge_clock_temperature_state;

void create_screen_gauge_oil_pressure();
void tick_screen_gauge_oil_pressure();

void create_screen_gauge_oil_temperature();
void tick_screen_gauge_oil_temperature();

void create_screen_gauge_voltage();
void tick_screen_gauge_voltage();

void create_screen_gauge_temperature_clock();
void tick_screen_gauge_temperature_clock();

void create_screen_gauge_clock_temperature();
void tick_screen_gauge_clock_temperature();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
    THEME_ID_DAY,
    THEME_ID_NIGHT,
};
enum Colors {
    COLOR_ID_NEEDLE,
    COLOR_ID_KNOB_SHADOW,
    COLOR_ID_BACKGROUND,
    COLOR_ID_MINOR_TICKS,
    COLOR_ID_MAJOR_TICKS,
    COLOR_ID_LABELS,
    COLOR_ID_UNIT,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][7];
extern uint32_t active_theme_index;

// Global state variables

extern lv_style_t pressure_gauge_scale_max_main_style;
extern lv_style_t pressure_gauge_scale_min_main_style;
extern lv_style_t temperature_gauge_scale_max_main_style;
extern lv_style_t temperature_gauge_scale_min_main_style;
extern lv_style_t voltage_gauge_scale_max_main_style;
extern lv_style_t voltage_gauge_scale_min_main_style;
extern lv_style_t TempClock_gauge_scale_min_main_style;
extern lv_style_t ClockTemp_gauge_scale_max_main_style;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/