#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: Gauge_Day
lv_style_t *get_style_gauge_day_MAIN_DEFAULT();
lv_style_t *get_style_gauge_day_TICKS_DEFAULT();
void add_style_gauge_day(lv_obj_t *obj);
void remove_style_gauge_day(lv_obj_t *obj);

// Style: Gauge_Night
void add_style_gauge_night(lv_obj_t *obj);
void remove_style_gauge_night(lv_obj_t *obj);

// Style: Digits
void add_style_digits(lv_obj_t *obj);
void remove_style_digits(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/