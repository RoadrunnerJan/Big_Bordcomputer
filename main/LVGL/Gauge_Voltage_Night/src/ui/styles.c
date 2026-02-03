#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: Gauge_Day
//

void init_style_gauge_day_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_gauge_day_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_gauge_day_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_gauge_day_TICKS_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffffffff));
};

lv_style_t *get_style_gauge_day_TICKS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_gauge_day_TICKS_DEFAULT(style);
    }
    return style;
};

void add_style_gauge_day(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_gauge_day_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_gauge_day_TICKS_DEFAULT(), LV_PART_TICKS | LV_STATE_DEFAULT);
};

void remove_style_gauge_day(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_gauge_day_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_gauge_day_TICKS_DEFAULT(), LV_PART_TICKS | LV_STATE_DEFAULT);
};

//
// Style: Gauge_Night
//

void add_style_gauge_night(lv_obj_t *obj) {
    (void)obj;
};

void remove_style_gauge_night(lv_obj_t *obj) {
    (void)obj;
};

//
// Style: Digits
//

void add_style_digits(lv_obj_t *obj) {
    (void)obj;
};

void remove_style_digits(lv_obj_t *obj) {
    (void)obj;
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_gauge_day,
        add_style_gauge_night,
        add_style_digits,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_gauge_day,
        remove_style_gauge_night,
        remove_style_digits,
    };
    remove_style_funcs[styleIndex](obj);
}

