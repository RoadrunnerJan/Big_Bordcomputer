#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *gauge;
    lv_obj_t *black_background;
    lv_obj_t *needle_knop_light_shadow;
    lv_obj_t *gauge_image;
    lv_obj_t *max_indicator;
    lv_obj_t *min_indicator;
    lv_obj_t *gauge_scale;
    lv_obj_t *needle_knob;
    lv_obj_t *gauge_value;
    lv_obj_t *gauge_unit;
    lv_obj_t *needle_arc;
    lv_obj_t *gauge_unit_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_GAUGE = 1,
};

void create_screen_gauge();
void tick_screen_gauge();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/