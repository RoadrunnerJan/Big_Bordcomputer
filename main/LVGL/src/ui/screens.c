#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static lv_meter_scale_t * scale0;
static lv_meter_scale_t * scale1;
static lv_meter_indicator_t * indicator2;
static lv_meter_scale_t * scale3;
static lv_meter_scale_t * scale4;
static lv_meter_indicator_t * indicator5;
static lv_meter_scale_t * scale6;
static lv_meter_scale_t * scale7;
static lv_meter_indicator_t * indicator8;
static lv_meter_scale_t * scale9;
static lv_meter_scale_t * scale10;
static lv_meter_indicator_t * indicator11;
static lv_meter_scale_t * scale12;
static lv_meter_scale_t * scale13;
static lv_meter_indicator_t * indicator14;
static lv_meter_scale_t * scale15;
static lv_meter_scale_t * scale16;
static lv_meter_indicator_t * indicator17;
static lv_meter_scale_t * scale18;
static lv_meter_scale_t * scale19;
static lv_meter_indicator_t * indicator20;
static lv_meter_scale_t * scale21;
static lv_meter_scale_t * scale22;
static lv_meter_indicator_t * indicator23;
static lv_meter_scale_t * scale24;
static lv_meter_scale_t * scale25;
static lv_meter_indicator_t * indicator26;
static lv_meter_scale_t * scale27;
static lv_meter_indicator_t * indicator28;
static lv_meter_scale_t * scale29;
static lv_meter_scale_t * scale30;
static lv_meter_indicator_t * indicator31;
static lv_meter_scale_t * scale32;
static lv_meter_indicator_t * indicator33;

void create_screen_gauge_oil_pressure() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_pressure = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pressure_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pressure_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_needle_knop_lightShadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_needle_knop_light_shadow = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_max_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pressure_max_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 14);
            lv_arc_set_bg_end_angle(obj, 39);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_min_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pressure_min_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 141);
            lv_arc_set_bg_end_angle(obj, 166);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_image
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_gauge_image = obj;
            lv_obj_set_pos(obj, 88, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_oil_can);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_scale_labels
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.pressure_gauge_scale_labels = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale0 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 15);
                lv_meter_set_scale_range(obj, scale, 0, 6, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_value = obj;
            lv_obj_set_pos(obj, 99, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // pressure_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_label_set_text(obj, "bar");
        }
        {
            // pressure_gauge_scale
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.pressure_gauge_scale = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale1 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 15);
                lv_meter_set_scale_range(obj, scale, 0, 6000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffffffff), -15);
                    indicator2 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // pressure_needle_knob
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_needle_knob = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_oil_pressure();
}

void tick_screen_gauge_oil_pressure() {
    {
        const char *new_val = get_var_lvgl_value_oil_pressure_string();
        const char *cur_val = lv_label_get_text(objects.pressure_gauge_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pressure_gauge_value;
            lv_label_set_text(objects.pressure_gauge_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.pressure_gauge_scale)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_oil_pressure();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.pressure_gauge_scale;
                lv_meter_set_indicator_value(objects.pressure_gauge_scale, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_oil_pressure_night() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_pressure_night = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pressure_black_background_opa_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pressure_black_background_opa_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_needle_knop_lightShadow_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_needle_knop_light_shadow_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_max_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pressure_max_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 14);
            lv_arc_set_bg_end_angle(obj, 39);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_min_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.pressure_min_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 141);
            lv_arc_set_bg_end_angle(obj, 166);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_image_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_gauge_image_night = obj;
            lv_obj_set_pos(obj, 88, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_oil_can);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_scale_labels_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.pressure_gauge_scale_labels_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale3 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 15);
                lv_meter_set_scale_range(obj, scale, 0, 6, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_value_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_value_night = obj;
            lv_obj_set_pos(obj, 99, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // pressure_gauge_unit_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_unit_night = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_label_set_text(obj, "bar");
        }
        {
            // pressure_gauge_scale_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.pressure_gauge_scale_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale4 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 15);
                lv_meter_set_scale_range(obj, scale, 0, 6000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffff2800), -15);
                    indicator5 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // pressure_needle_knob_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.pressure_needle_knob_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_oil_pressure_night();
}

void tick_screen_gauge_oil_pressure_night() {
    {
        const char *new_val = get_var_lvgl_value_oil_pressure_string();
        const char *cur_val = lv_label_get_text(objects.pressure_gauge_value_night);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pressure_gauge_value_night;
            lv_label_set_text(objects.pressure_gauge_value_night, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.pressure_gauge_scale_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_oil_pressure();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.pressure_gauge_scale_night;
                lv_meter_set_indicator_value(objects.pressure_gauge_scale_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_oil_temperature() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_temperature = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temperature_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temperature_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_needle_knop_lightShadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_needle_knop_light_shadow = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_max_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temperature_max_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 348);
            lv_arc_set_bg_end_angle(obj, 40);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_min_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temperature_min_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 140);
            lv_arc_set_bg_end_angle(obj, 223);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_image
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_gauge_image = obj;
            lv_obj_set_pos(obj, 88, 61);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_oil_can_temp);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_scale_labels
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temperature_gauge_scale_labels = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale6 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 6, 5, 18, lv_color_hex(0xffffffff), 20);
                lv_meter_set_scale_range(obj, scale, 0, 150, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_value = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // temperature_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // temperature_gauge_scale
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temperature_gauge_scale = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale7 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 6, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 0, 150000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffffffff), -15);
                    indicator8 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // temperature_needle_knob
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_needle_knob = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_oil_temperature();
}

void tick_screen_gauge_oil_temperature() {
    {
        const char *new_val = get_var_lvgl_value_oil_temperature_string();
        const char *cur_val = lv_label_get_text(objects.temperature_gauge_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temperature_gauge_value;
            lv_label_set_text(objects.temperature_gauge_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temperature_gauge_scale)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_oil_temperature();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temperature_gauge_scale;
                lv_meter_set_indicator_value(objects.temperature_gauge_scale, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_oil_temperature_night() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_temperature_night = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temperature_black_background_opa_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temperature_black_background_opa_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_needle_knop_lightShadow_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_needle_knop_light_shadow_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_max_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temperature_max_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 348);
            lv_arc_set_bg_end_angle(obj, 40);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_min_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temperature_min_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 140);
            lv_arc_set_bg_end_angle(obj, 223);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_image_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_gauge_image_night = obj;
            lv_obj_set_pos(obj, 88, 61);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_oil_can_temp);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_scale_labels_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temperature_gauge_scale_labels_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale9 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 6, 5, 18, lv_color_hex(0xffff2800), 20);
                lv_meter_set_scale_range(obj, scale, 0, 150, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_value_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_value_night = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // temperature_gauge_unit_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_unit_night = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // temperature_gauge_scale_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temperature_gauge_scale_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale10 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 6, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 0, 150000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffff2800), -15);
                    indicator11 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // temperature_needle_knob_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temperature_needle_knob_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_oil_temperature_night();
}

void tick_screen_gauge_oil_temperature_night() {
    {
        const char *new_val = get_var_lvgl_value_oil_temperature_string();
        const char *cur_val = lv_label_get_text(objects.temperature_gauge_value_night);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temperature_gauge_value_night;
            lv_label_set_text(objects.temperature_gauge_value_night, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temperature_gauge_scale_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_oil_temperature();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temperature_gauge_scale_night;
                lv_meter_set_indicator_value(objects.temperature_gauge_scale_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_voltage() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_voltage = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // volt_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.volt_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_needle_knop_lightShadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_needle_knop_light_shadow = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_max_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.volt_max_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 7);
            lv_arc_set_bg_end_angle(obj, 39);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_min_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.volt_min_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 140);
            lv_arc_set_bg_end_angle(obj, 237);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_image
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_gauge_image = obj;
            lv_obj_set_pos(obj, 84, 64);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_volt);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_scale_labels
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.volt_gauge_scale_labels = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale12 = scale;
                lv_meter_set_scale_ticks(obj, scale, 17, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 4, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 8, 16, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_value = obj;
            lv_obj_set_pos(obj, 93, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // volt_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "V");
        }
        {
            // volt_gauge_scale
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.volt_gauge_scale = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale13 = scale;
                lv_meter_set_scale_ticks(obj, scale, 17, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 4, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 8000, 16000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffffffff), -15);
                    indicator14 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // volt_needle_knob
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_needle_knob = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_voltage();
}

void tick_screen_gauge_voltage() {
    {
        const char *new_val = get_var_lvgl_value_voltage_string();
        const char *cur_val = lv_label_get_text(objects.volt_gauge_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.volt_gauge_value;
            lv_label_set_text(objects.volt_gauge_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.volt_gauge_scale)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_voltage();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.volt_gauge_scale;
                lv_meter_set_indicator_value(objects.volt_gauge_scale, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_voltage_night() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_voltage_night = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // volt_black_background_opa_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.volt_black_background_opa_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_needle_knop_lightShadow_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_needle_knop_light_shadow_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_max_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.volt_max_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 7);
            lv_arc_set_bg_end_angle(obj, 39);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_min_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.volt_min_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 140);
            lv_arc_set_bg_end_angle(obj, 237);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_image_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_gauge_image_night = obj;
            lv_obj_set_pos(obj, 84, 64);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_volt);
            lv_img_set_zoom(obj, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_scale_labels_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.volt_gauge_scale_labels_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale15 = scale;
                lv_meter_set_scale_ticks(obj, scale, 17, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 4, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 8, 16, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_value_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_value_night = obj;
            lv_obj_set_pos(obj, 93, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // volt_gauge_unit_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_unit_night = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "V");
        }
        {
            // volt_gauge_scale_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.volt_gauge_scale_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale16 = scale;
                lv_meter_set_scale_ticks(obj, scale, 17, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 4, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 8000, 16000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffff2800), -15);
                    indicator17 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // volt_needle_knob_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.volt_needle_knob_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_voltage_night();
}

void tick_screen_gauge_voltage_night() {
    {
        const char *new_val = get_var_lvgl_value_voltage_string();
        const char *cur_val = lv_label_get_text(objects.volt_gauge_value_night);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.volt_gauge_value_night;
            lv_label_set_text(objects.volt_gauge_value_night, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.volt_gauge_scale_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_voltage();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.volt_gauge_scale_night;
                lv_meter_set_indicator_value(objects.volt_gauge_scale_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_temperature_clock() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_temperature_clock = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // TempClock_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temp_clock_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_needle_knop_lightShadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_needle_knop_light_shadow = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_min_indicator
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temp_clock_min_indicator = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 141);
            lv_arc_set_bg_end_angle(obj, 243);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_image
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_gauge_image = obj;
            lv_obj_set_pos(obj, 106, 66);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_temperature);
            lv_img_set_zoom(obj, 180);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_scale_labels
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temp_clock_gauge_scale_labels = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale18 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, -20, 40, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_value = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // TempClock_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // TempClock_gauge_scale
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temp_clock_gauge_scale = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale19 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, -20000, 40000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffffffff), -15);
                    indicator20 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // TempClock_needle_knob
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_needle_knob = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_temperature_clock();
}

void tick_screen_gauge_temperature_clock() {
    {
        const char *new_val = get_var_lvgl_value_clock();
        const char *cur_val = lv_label_get_text(objects.temp_clock_gauge_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temp_clock_gauge_value;
            lv_label_set_text(objects.temp_clock_gauge_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temp_clock_gauge_scale)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_temperature();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temp_clock_gauge_scale;
                lv_meter_set_indicator_value(objects.temp_clock_gauge_scale, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_temperature_clock_night() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_temperature_clock_night = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // TempClock_black_background_opa_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temp_clock_black_background_opa_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_needle_knop_lightShadow_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_needle_knop_light_shadow_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_min_indicator_Night
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temp_clock_min_indicator_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_start_angle(obj, 141);
            lv_arc_set_bg_end_angle(obj, 243);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_image_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_gauge_image_night = obj;
            lv_obj_set_pos(obj, 106, 66);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_temperature);
            lv_img_set_zoom(obj, 180);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_scale_labels_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temp_clock_gauge_scale_labels_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale21 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, -20, 40, 260, 140);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_value_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_value_night = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // TempClock_gauge_unit_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_unit_night = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // TempClock_gauge_scale_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.temp_clock_gauge_scale_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale22 = scale;
                lv_meter_set_scale_ticks(obj, scale, 31, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, -20000, 40000, 260, 140);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffff2800), -15);
                    indicator23 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // TempClock_needle_knob_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.temp_clock_needle_knob_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_temperature_clock_night();
}

void tick_screen_gauge_temperature_clock_night() {
    {
        const char *new_val = get_var_lvgl_value_clock();
        const char *cur_val = lv_label_get_text(objects.temp_clock_gauge_value_night);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temp_clock_gauge_value_night;
            lv_label_set_text(objects.temp_clock_gauge_value_night, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.temp_clock_gauge_scale_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_temperature();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.temp_clock_gauge_scale_night;
                lv_meter_set_indicator_value(objects.temp_clock_gauge_scale_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_clock_temperature() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_clock_temperature = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // ClockTemp_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_temp_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_scale_hour_labels
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_hour_labels = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale24 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 0, 12, 360, 270);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_12
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.clock_temp_gauge_12 = obj;
            lv_obj_set_pos(obj, 99, 26);
            lv_obj_set_size(obj, 43, 44);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "12");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_image
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_gauge_image = obj;
            lv_obj_set_pos(obj, 85, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_clock);
            lv_img_set_zoom(obj, 100);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Clock_Temp_six_blacking
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_temp_six_blacking = obj;
            lv_obj_set_pos(obj, 74, 204);
            lv_obj_set_size(obj, 91, 36);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_value = obj;
            lv_obj_set_pos(obj, 90, 175);
            lv_obj_set_size(obj, 60, 50);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // ClockTemp_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // ClockTemp_needle_knop_lightShadow
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_needle_knop_light_shadow = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_scale_hour
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_hour = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale25 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 0, 600, 360, 270);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 8, lv_color_hex(0xffffffff), -45);
                    indicator26 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_line_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_scale_minute
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_minute = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale27 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffffffff));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffffffff), 17);
                lv_meter_set_scale_range(obj, scale, 0, 60, 360, 270);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffffffff), -15);
                    indicator28 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_line_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_needle_knob
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_needle_knob = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_clock_temperature();
}

void tick_screen_gauge_clock_temperature() {
    {
        const char *new_val = get_var_lvgl_value_temperature_string();
        const char *cur_val = lv_label_get_text(objects.clock_temp_gauge_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.clock_temp_gauge_value;
            lv_label_set_text(objects.clock_temp_gauge_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.clock_temp_gauge_scale_hour)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_clock_hour();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.clock_temp_gauge_scale_hour;
                lv_meter_set_indicator_value(objects.clock_temp_gauge_scale_hour, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.clock_temp_gauge_scale_minute)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_clock_minute();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.clock_temp_gauge_scale_minute;
                lv_meter_set_indicator_value(objects.clock_temp_gauge_scale_minute, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}

void create_screen_gauge_clock_temperature_night() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_clock_temperature_night = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // ClockTemp_gauge_scale_hour_labels_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_hour_labels_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale29 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 0, 12, 360, 270);
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_12_Night
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.clock_temp_gauge_12_night = obj;
            lv_obj_set_pos(obj, 99, 26);
            lv_obj_set_size(obj, 43, 44);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "12");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_image_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_gauge_image_night = obj;
            lv_obj_set_pos(obj, 85, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_clock);
            lv_img_set_zoom(obj, 100);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Clock_Temp_six_blacking_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_temp_six_blacking_night = obj;
            lv_obj_set_pos(obj, 74, 204);
            lv_obj_set_size(obj, 91, 36);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_value_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_value_night = obj;
            lv_obj_set_pos(obj, 90, 175);
            lv_obj_set_size(obj, 60, 50);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // ClockTemp_black_background_opa_Night
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_temp_black_background_opa_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_unit_Night
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_unit_night = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°C");
        }
        {
            // ClockTemp_needle_knop_lightShadow_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_needle_knop_light_shadow_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_scale_hour_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_hour_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale30 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 0, 600, 360, 270);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 8, lv_color_hex(0xffff2800), -45);
                    indicator31 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_line_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_scale_minute_Night
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.clock_temp_gauge_scale_minute_night = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                scale32 = scale;
                lv_meter_set_scale_ticks(obj, scale, 61, 2, 10, lv_color_hex(0xffff2800));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 5, 18, lv_color_hex(0xffff2800), 17);
                lv_meter_set_scale_range(obj, scale, 0, 60, 360, 270);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 5, lv_color_hex(0xffff2800), -15);
                    indicator33 = indicator;
                }
            }
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff2800), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_line_opa(obj, 0, LV_PART_TICKS | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_time(obj, 600, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_needle_knob_Night
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.clock_temp_needle_knob_night = obj;
            lv_obj_set_pos(obj, 49, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_knob);
            lv_img_set_zoom(obj, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(obj, 155, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gauge_clock_temperature_night();
}

void tick_screen_gauge_clock_temperature_night() {
    {
        const char *new_val = get_var_lvgl_value_temperature_string();
        const char *cur_val = lv_label_get_text(objects.clock_temp_gauge_value_night);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.clock_temp_gauge_value_night;
            lv_label_set_text(objects.clock_temp_gauge_value_night, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.clock_temp_gauge_scale_hour_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_clock_hour();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.clock_temp_gauge_scale_hour_night;
                lv_meter_set_indicator_value(objects.clock_temp_gauge_scale_hour_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        lv_meter_indicator_t *indicator;
        
        lv_ll_t *indicators = &((lv_meter_t *)objects.clock_temp_gauge_scale_minute_night)->indicator_ll;
        int index = 0;
        for (indicator = _lv_ll_get_tail(indicators); index > 0 && indicator != NULL; indicator = _lv_ll_get_prev(indicators, indicator), index--);
        
        if (indicator) {
            int32_t new_val = get_var_lvgl_value_clock_minute();
            int32_t cur_val = indicator->start_value;
            if (new_val != cur_val) {
                tick_value_change_obj = objects.clock_temp_gauge_scale_minute_night;
                lv_meter_set_indicator_value(objects.clock_temp_gauge_scale_minute_night, indicator, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_gauge_oil_pressure,
    tick_screen_gauge_oil_pressure_night,
    tick_screen_gauge_oil_temperature,
    tick_screen_gauge_oil_temperature_night,
    tick_screen_gauge_voltage,
    tick_screen_gauge_voltage_night,
    tick_screen_gauge_temperature_clock,
    tick_screen_gauge_temperature_clock_night,
    tick_screen_gauge_clock_temperature,
    tick_screen_gauge_clock_temperature_night,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_gauge_oil_pressure();
    create_screen_gauge_oil_pressure_night();
    create_screen_gauge_oil_temperature();
    create_screen_gauge_oil_temperature_night();
    create_screen_gauge_voltage();
    create_screen_gauge_voltage_night();
    create_screen_gauge_temperature_clock();
    create_screen_gauge_temperature_clock_night();
    create_screen_gauge_clock_temperature();
    create_screen_gauge_clock_temperature_night();
}

