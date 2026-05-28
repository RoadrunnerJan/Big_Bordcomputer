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

screen_gauge_oil_pressure_state_t screen_gauge_oil_pressure_state;
screen_gauge_oil_temperature_state_t screen_gauge_oil_temperature_state;
screen_gauge_voltage_state_t screen_gauge_voltage_state;
screen_gauge_temperature_clock_state_t screen_gauge_temperature_clock_state;
screen_gauge_clock_temperature_state_t screen_gauge_clock_temperature_state;

// Global state variables

lv_style_t pressure_gauge_scale_max_main_style;
static bool pressure_gauge_scale_max_main_style_initialized;
lv_style_t pressure_gauge_scale_min_main_style;
static bool pressure_gauge_scale_min_main_style_initialized;
lv_style_t temperature_gauge_scale_max_main_style;
static bool temperature_gauge_scale_max_main_style_initialized;
lv_style_t temperature_gauge_scale_min_main_style;
static bool temperature_gauge_scale_min_main_style_initialized;
lv_style_t voltage_gauge_scale_max_main_style;
static bool voltage_gauge_scale_max_main_style_initialized;
lv_style_t voltage_gauge_scale_min_main_style;
static bool voltage_gauge_scale_min_main_style_initialized;
lv_style_t TempClock_gauge_scale_min_main_style;
static bool TempClock_gauge_scale_min_main_style_initialized;
lv_style_t ClockTemp_gauge_scale_max_main_style;
static bool ClockTemp_gauge_scale_max_main_style_initialized;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_gauge_oil_pressure() {
    screen_gauge_oil_pressure_state_t *state = &screen_gauge_oil_pressure_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_pressure = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pressure_black_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pressure_black_background = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_image
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.pressure_gauge_image = obj;
            lv_obj_set_pos(obj, 88, 68);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_oil_can);
            lv_image_set_scale(obj, 160);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pressure_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_value = obj;
            lv_obj_set_pos(obj, 99, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // pressure_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pressure_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_label_set_text_static(obj, "bar");
        }
        {
            // pressure_gauge_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.pressure_gauge_scale = obj;
            lv_obj_set_pos(obj, 6, 6);
            lv_obj_set_size(obj, 228, 228);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, 0, 6000);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 31);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_draw_ticks_on_top(obj, true);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[8] = {
                "0",
                "1",
                "2",
                "3",
                "4",
                "5",
                "6",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->max = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->max, 5400, 6000);
                {
                    if (!pressure_gauge_scale_max_main_style_initialized) {
                        lv_style_init(&pressure_gauge_scale_max_main_style);
                        pressure_gauge_scale_max_main_style_initialized = true;
                        lv_style_set_arc_width(&pressure_gauge_scale_max_main_style, 16);
                        lv_style_set_arc_color(&pressure_gauge_scale_max_main_style, lv_color_hex(0xff0000));
                    }
                    lv_scale_set_section_style_main(obj, state->max, &pressure_gauge_scale_max_main_style);
                }
            }
            {
                state->min = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->min, 0, 600);
                {
                    if (!pressure_gauge_scale_min_main_style_initialized) {
                        lv_style_init(&pressure_gauge_scale_min_main_style);
                        pressure_gauge_scale_min_main_style_initialized = true;
                        lv_style_set_arc_width(&pressure_gauge_scale_min_main_style, 16);
                        lv_style_set_arc_color(&pressure_gauge_scale_min_main_style, lv_color_hex(0xff0000));
                    }
                    lv_scale_set_section_style_main(obj, state->min, &pressure_gauge_scale_min_main_style);
                }
            }
            lv_obj_set_style_pad_radial(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 2, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 16, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_INDICATOR);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // pressure_gauge_needle
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.pressure_gauge_needle = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // pressure_gauge_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.pressure_gauge_knob = obj;
                    lv_obj_set_pos(obj, 97, 97);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_oil_pressure();
}

void tick_screen_gauge_oil_pressure() {
    screen_gauge_oil_pressure_state_t *state = &screen_gauge_oil_pressure_state;
    (void)state;
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
        int32_t new_val = get_var_lvgl_value_oil_pressure();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.pressure_gauge_needle), objects.pressure_gauge_needle, 100, new_val);
    }
}

void create_screen_gauge_oil_temperature() {
    screen_gauge_oil_temperature_state_t *state = &screen_gauge_oil_temperature_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_oil_temperature = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temperature_black_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temperature_black_background = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_image
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.temperature_gauge_image = obj;
            lv_obj_set_pos(obj, 88, 61);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_oil_can_temp);
            lv_image_set_scale(obj, 160);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_value = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // temperature_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "°C");
        }
        {
            // temperature_gauge_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.temperature_gauge_scale = obj;
            lv_obj_set_pos(obj, 6, 6);
            lv_obj_set_size(obj, 228, 228);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, 0, 150000);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 31);
            lv_scale_set_major_tick_every(obj, 6);
            lv_scale_set_draw_ticks_on_top(obj, true);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[7] = {
                "0",
                "30",
                "60",
                "90",
                "120",
                "150",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->max = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->max, 120000, 150000);
                {
                    if (!temperature_gauge_scale_max_main_style_initialized) {
                        lv_style_init(&temperature_gauge_scale_max_main_style);
                        temperature_gauge_scale_max_main_style_initialized = true;
                        lv_style_set_arc_width(&temperature_gauge_scale_max_main_style, 16);
                        lv_style_set_arc_color(&temperature_gauge_scale_max_main_style, lv_color_hex(0xff0000));
                    }
                    lv_scale_set_section_style_main(obj, state->max, &temperature_gauge_scale_max_main_style);
                }
            }
            {
                state->min = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->min, 0, 50000);
                {
                    if (!temperature_gauge_scale_min_main_style_initialized) {
                        lv_style_init(&temperature_gauge_scale_min_main_style);
                        temperature_gauge_scale_min_main_style_initialized = true;
                        lv_style_set_arc_width(&temperature_gauge_scale_min_main_style, 16);
                        lv_style_set_arc_color(&temperature_gauge_scale_min_main_style, lv_color_hex(0x0000fa));
                    }
                    lv_scale_set_section_style_main(obj, state->min, &temperature_gauge_scale_min_main_style);
                }
            }
            lv_obj_set_style_pad_radial(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 2, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 16, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_INDICATOR);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // temperature_gauge_needle
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.temperature_gauge_needle = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // temperature_gauge_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.temperature_gauge_knob = obj;
                    lv_obj_set_pos(obj, 97, 97);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_oil_temperature();
}

void tick_screen_gauge_oil_temperature() {
    screen_gauge_oil_temperature_state_t *state = &screen_gauge_oil_temperature_state;
    (void)state;
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
        int32_t new_val = get_var_lvgl_value_oil_temperature();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.temperature_gauge_needle), objects.temperature_gauge_needle, 100, new_val);
    }
}

void create_screen_gauge_voltage() {
    screen_gauge_voltage_state_t *state = &screen_gauge_voltage_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_voltage = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // voltage_black_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.voltage_black_background = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_image
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.volt_gauge_image = obj;
            lv_obj_set_pos(obj, 84, 64);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_volt);
            lv_image_set_scale(obj, 160);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // volt_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_value = obj;
            lv_obj_set_pos(obj, 93, 183);
            lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // volt_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.volt_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "V");
        }
        {
            // voltage_gauge_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.voltage_gauge_scale = obj;
            lv_obj_set_pos(obj, 6, 6);
            lv_obj_set_size(obj, 228, 228);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, 8000, 16000);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 17);
            lv_scale_set_major_tick_every(obj, 4);
            lv_scale_set_draw_ticks_on_top(obj, true);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[6] = {
                "8",
                "10",
                "12",
                "14",
                "16",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->max = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->max, 15000, 16000);
                {
                    if (!voltage_gauge_scale_max_main_style_initialized) {
                        lv_style_init(&voltage_gauge_scale_max_main_style);
                        voltage_gauge_scale_max_main_style_initialized = true;
                        lv_style_set_arc_width(&voltage_gauge_scale_max_main_style, 16);
                        lv_style_set_arc_color(&voltage_gauge_scale_max_main_style, lv_color_hex(0xff0000));
                    }
                    lv_scale_set_section_style_main(obj, state->max, &voltage_gauge_scale_max_main_style);
                }
            }
            {
                state->min = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->min, 0, 11000);
                {
                    if (!voltage_gauge_scale_min_main_style_initialized) {
                        lv_style_init(&voltage_gauge_scale_min_main_style);
                        voltage_gauge_scale_min_main_style_initialized = true;
                        lv_style_set_arc_width(&voltage_gauge_scale_min_main_style, 16);
                        lv_style_set_arc_color(&voltage_gauge_scale_min_main_style, lv_color_hex(0xff0000));
                    }
                    lv_scale_set_section_style_main(obj, state->min, &voltage_gauge_scale_min_main_style);
                }
            }
            lv_obj_set_style_pad_radial(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 2, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 16, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_INDICATOR);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // voltage_gauge_needle
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.voltage_gauge_needle = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // voltage_gauge_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.voltage_gauge_knob = obj;
                    lv_obj_set_pos(obj, 97, 97);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_voltage();
}

void tick_screen_gauge_voltage() {
    screen_gauge_voltage_state_t *state = &screen_gauge_voltage_state;
    (void)state;
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
        int32_t new_val = get_var_lvgl_value_voltage();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.voltage_gauge_needle), objects.voltage_gauge_needle, 100, new_val);
    }
}

void create_screen_gauge_temperature_clock() {
    screen_gauge_temperature_clock_state_t *state = &screen_gauge_temperature_clock_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_temperature_clock = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // TempClock_black_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.temp_clock_black_background = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_image
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.temp_clock_gauge_image = obj;
            lv_obj_set_pos(obj, 106, 66);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_temperature);
            lv_image_set_scale(obj, 180);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // TempClock_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_value = obj;
            lv_obj_set_pos(obj, 75, 183);
            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // TempClock_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_clock_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "°C");
        }
        {
            // TempClock_gauge_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.temp_clock_gauge_scale = obj;
            lv_obj_set_pos(obj, 6, 6);
            lv_obj_set_size(obj, 228, 228);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, -30000, 50000);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 41);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_draw_ticks_on_top(obj, true);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[10] = {
                "-30",
                "-20",
                "-10",
                "0",
                "10",
                "20",
                "30",
                "40",
                "50",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->min = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->min, -30000, 4000);
                {
                    if (!TempClock_gauge_scale_min_main_style_initialized) {
                        lv_style_init(&TempClock_gauge_scale_min_main_style);
                        TempClock_gauge_scale_min_main_style_initialized = true;
                        lv_style_set_arc_width(&TempClock_gauge_scale_min_main_style, 16);
                        lv_style_set_arc_color(&TempClock_gauge_scale_min_main_style, lv_color_hex(0x0000fa));
                    }
                    lv_scale_set_section_style_main(obj, state->min, &TempClock_gauge_scale_min_main_style);
                }
            }
            lv_obj_set_style_pad_radial(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 2, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 16, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_INDICATOR);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // TempClock_gauge_needle
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.temp_clock_gauge_needle = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // TempClock_gauge_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.temp_clock_gauge_knob = obj;
                    lv_obj_set_pos(obj, 97, 97);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_temperature_clock();
}

void tick_screen_gauge_temperature_clock() {
    screen_gauge_temperature_clock_state_t *state = &screen_gauge_temperature_clock_state;
    (void)state;
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
        int32_t new_val = get_var_lvgl_value_temperature();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.temp_clock_gauge_needle), objects.temp_clock_gauge_needle, 100, new_val);
    }
}

void create_screen_gauge_clock_temperature() {
    screen_gauge_clock_temperature_state_t *state = &screen_gauge_clock_temperature_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_clock_temperature = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // ClockTemp_black_background_opa
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.clock_temp_black_background_opa = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_image
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.clock_temp_gauge_image = obj;
            lv_obj_set_pos(obj, 85, 43);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_clock);
            lv_image_set_scale(obj, 110);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 999, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ClockTemp_gauge_unit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_unit = obj;
            lv_obj_set_pos(obj, 95, 150);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "°C");
        }
        {
            // ClockTemp_gauge_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_temp_gauge_value = obj;
            lv_obj_set_pos(obj, 90, 175);
            lv_obj_set_size(obj, 60, 50);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff3c00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // ClockTemp_gauge_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.clock_temp_gauge_scale = obj;
            lv_obj_set_pos(obj, 6, 6);
            lv_obj_set_size(obj, 228, 228);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, 0, 600);
            lv_scale_set_angle_range(obj, 360);
            lv_scale_set_rotation(obj, 270);
            lv_scale_set_total_tick_count(obj, 61);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[13] = {
                "12",
                "1",
                "2",
                "3",
                "4",
                "5",
                " ",
                "7",
                "8",
                "9",
                "10",
                "11",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->max = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->max, 255, 345);
                {
                    if (!ClockTemp_gauge_scale_max_main_style_initialized) {
                        lv_style_init(&ClockTemp_gauge_scale_max_main_style);
                        ClockTemp_gauge_scale_max_main_style_initialized = true;
                        lv_style_set_arc_width(&ClockTemp_gauge_scale_max_main_style, 16);
                        lv_style_set_arc_color(&ClockTemp_gauge_scale_max_main_style, lv_color_hex(theme_colors[active_theme_index][2]));
                    }
                    lv_scale_set_section_style_main(obj, state->max, &ClockTemp_gauge_scale_max_main_style);
                }
            }
            lv_obj_set_style_pad_radial(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radial_offset(obj, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 2, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 16, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_INDICATOR);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &ui_font_oswald_22, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ClockTemp_gauge_needle_minute
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.clock_temp_gauge_needle_minute = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // ClockTemp_gauge_needle_hour
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.clock_temp_gauge_needle_hour = obj;
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // ClockTemp_gauge_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.clock_temp_gauge_knob = obj;
                    lv_obj_set_pos(obj, 97, 97);
                    lv_obj_set_size(obj, 34, 34);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(theme_colors[active_theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_clock_temperature();
}

void tick_screen_gauge_clock_temperature() {
    screen_gauge_clock_temperature_state_t *state = &screen_gauge_clock_temperature_state;
    (void)state;
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
        int32_t new_val = get_var_lvgl_value_clock_minute();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.clock_temp_gauge_needle_minute), objects.clock_temp_gauge_needle_minute, 100, new_val);
    }
    {
        int32_t new_val = get_var_lvgl_value_clock_hour();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.clock_temp_gauge_needle_hour), objects.clock_temp_gauge_needle_hour, 65, new_val);
    }
}

void create_screen_gauge_g_force() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gauge_g_force = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // gforce_black_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.gforce_black_background = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // gforce_ring_0.2g
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.gforce_ring_0_2g = obj;
                    lv_obj_set_pos(obj, 80, 80);
                    lv_obj_set_size(obj, 50, 50);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_ring_0.4g
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.gforce_ring_0_4g = obj;
                    lv_obj_set_pos(obj, 55, 55);
                    lv_obj_set_size(obj, 100, 100);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_ring_0.6g
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.gforce_ring_0_6g = obj;
                    lv_obj_set_pos(obj, 30, 30);
                    lv_obj_set_size(obj, 150, 150);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 75, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_ring_0.8g
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.gforce_ring_0_8g = obj;
                    lv_obj_set_pos(obj, 5, 5);
                    lv_obj_set_size(obj, 200, 200);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_line_vertical
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.gforce_line_vertical = obj;
                    lv_obj_set_pos(obj, 0, 105);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 210, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_line_horizontal
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.gforce_line_horizontal = obj;
                    lv_obj_set_pos(obj, 105, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 0, 210 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // gforce_label_.2g
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gforce_label__2g = obj;
                    lv_obj_set_pos(obj, 92, 72);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_oswald_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0.2g");
                }
                {
                    // gforce_label_.4g
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gforce_label__4g = obj;
                    lv_obj_set_pos(obj, 91, 46);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_oswald_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0.4g");
                }
                {
                    // gforce_label_.6g
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gforce_label__6g = obj;
                    lv_obj_set_pos(obj, 92, 20);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_oswald_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0.6g");
                }
                {
                    // gforce_label_.8g
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gforce_label__8g = obj;
                    lv_obj_set_pos(obj, 92, -5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_oswald_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0.8g");
                }
                {
                    // gforce_knob
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.gforce_knob = obj;
                    lv_obj_set_pos(obj, 100, 100);
                    lv_obj_set_size(obj, 10, 10);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_spread(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_gauge_g_force();
}

void tick_screen_gauge_g_force() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_gauge_oil_pressure,
    tick_screen_gauge_oil_temperature,
    tick_screen_gauge_voltage,
    tick_screen_gauge_temperature_clock,
    tick_screen_gauge_clock_temperature,
    tick_screen_gauge_g_force,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 6) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "oswald_22", &ui_font_oswald_22 },
    { "oswald_36", &ui_font_oswald_36 },
    { "oswald_16", &ui_font_oswald_16 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;
void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    {
        screen_gauge_oil_pressure_state_t *state = &screen_gauge_oil_pressure_state;
        (void)state;
        lv_obj_set_style_bg_color(objects.pressure_black_background, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.pressure_gauge_unit, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.pressure_gauge_scale, lv_color_hex(theme_colors[theme_index][3]), LV_PART_ITEMS);
        lv_obj_set_style_line_color(objects.pressure_gauge_scale, lv_color_hex(theme_colors[theme_index][4]), LV_PART_INDICATOR);
        lv_obj_set_style_text_color(objects.pressure_gauge_scale, lv_color_hex(theme_colors[theme_index][5]), LV_PART_INDICATOR);
        lv_obj_set_style_line_color(objects.pressure_gauge_needle, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.pressure_gauge_knob, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(objects.pressure_gauge_knob, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.pressure_gauge_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        screen_gauge_oil_temperature_state_t *state = &screen_gauge_oil_temperature_state;
        (void)state;
        lv_obj_set_style_bg_color(objects.temperature_black_background, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.temperature_gauge_unit, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.temperature_gauge_scale, lv_color_hex(theme_colors[theme_index][3]), LV_PART_ITEMS);
        lv_obj_set_style_line_color(objects.temperature_gauge_scale, lv_color_hex(theme_colors[theme_index][4]), LV_PART_INDICATOR);
        lv_obj_set_style_text_color(objects.temperature_gauge_scale, lv_color_hex(theme_colors[theme_index][5]), LV_PART_INDICATOR);
        lv_obj_set_style_line_color(objects.temperature_gauge_needle, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.temperature_gauge_knob, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(objects.temperature_gauge_knob, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.temperature_gauge_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        screen_gauge_voltage_state_t *state = &screen_gauge_voltage_state;
        (void)state;
        lv_obj_set_style_bg_color(objects.voltage_black_background, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.volt_gauge_unit, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.voltage_gauge_scale, lv_color_hex(theme_colors[theme_index][3]), LV_PART_ITEMS);
        lv_obj_set_style_line_color(objects.voltage_gauge_scale, lv_color_hex(theme_colors[theme_index][4]), LV_PART_INDICATOR);
        lv_obj_set_style_text_color(objects.voltage_gauge_scale, lv_color_hex(theme_colors[theme_index][5]), LV_PART_INDICATOR);
        lv_obj_set_style_line_color(objects.voltage_gauge_needle, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.voltage_gauge_knob, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(objects.voltage_gauge_knob, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.voltage_gauge_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        screen_gauge_temperature_clock_state_t *state = &screen_gauge_temperature_clock_state;
        (void)state;
        lv_obj_set_style_bg_color(objects.temp_clock_black_background, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.temp_clock_gauge_unit, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.temp_clock_gauge_scale, lv_color_hex(theme_colors[theme_index][3]), LV_PART_ITEMS);
        lv_obj_set_style_line_color(objects.temp_clock_gauge_scale, lv_color_hex(theme_colors[theme_index][4]), LV_PART_INDICATOR);
        lv_obj_set_style_text_color(objects.temp_clock_gauge_scale, lv_color_hex(theme_colors[theme_index][5]), LV_PART_INDICATOR);
        lv_obj_set_style_line_color(objects.temp_clock_gauge_needle, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.temp_clock_gauge_knob, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(objects.temp_clock_gauge_knob, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.temp_clock_gauge_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        screen_gauge_clock_temperature_state_t *state = &screen_gauge_clock_temperature_state;
        (void)state;
        lv_obj_set_style_bg_color(objects.clock_temp_black_background_opa, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.clock_temp_gauge_unit, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_style_set_arc_color(&ClockTemp_gauge_scale_max_main_style, lv_color_hex(theme_colors[theme_index][2]));
        lv_obj_set_style_line_color(objects.clock_temp_gauge_scale, lv_color_hex(theme_colors[theme_index][3]), LV_PART_ITEMS);
        lv_obj_set_style_line_color(objects.clock_temp_gauge_scale, lv_color_hex(theme_colors[theme_index][4]), LV_PART_INDICATOR);
        lv_obj_set_style_text_color(objects.clock_temp_gauge_scale, lv_color_hex(theme_colors[theme_index][5]), LV_PART_INDICATOR);
        lv_obj_set_style_line_color(objects.clock_temp_gauge_needle_minute, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.clock_temp_gauge_needle_hour, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.clock_temp_gauge_knob, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(objects.clock_temp_gauge_knob, lv_color_hex(theme_colors[theme_index][8]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.clock_temp_gauge_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        lv_obj_set_style_bg_color(objects.gforce_black_background, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.gforce_ring_0_2g, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.gforce_ring_0_4g, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.gforce_ring_0_6g, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(objects.gforce_ring_0_8g, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_outline_color(objects.gforce_line_vertical, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.gforce_line_vertical, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_outline_color(objects.gforce_line_horizontal, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_line_color(objects.gforce_line_horizontal, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.gforce_label__2g, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.gforce_label__2g, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.gforce_label__4g, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.gforce_label__4g, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.gforce_label__6g, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.gforce_label__6g, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(objects.gforce_label__8g, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.gforce_label__8g, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(objects.gforce_knob, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(objects.gforce_knob, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    lv_obj_invalidate(objects.gauge_oil_pressure);
    lv_obj_invalidate(objects.gauge_oil_temperature);
    lv_obj_invalidate(objects.gauge_voltage);
    lv_obj_invalidate(objects.gauge_temperature_clock);
    lv_obj_invalidate(objects.gauge_clock_temperature);
    lv_obj_invalidate(objects.gauge_g_force);
}
uint32_t theme_colors[2][11] = {
    { 0xffffffff, 0xff000000, 0xff000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xff2f2f2f, 0xff1a1a1a, 0xffff3c00, 0xffff3c00 },
    { 0xffff3c00, 0xffff3c00, 0xff1e0700, 0xffff3c00, 0xffff3c00, 0xffff3c00, 0xffff3c00, 0xff222121, 0xff151515, 0xffffffff, 0xffffffff },
};

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_gauge_oil_pressure();
    create_screen_gauge_oil_temperature();
    create_screen_gauge_voltage();
    create_screen_gauge_temperature_clock();
    create_screen_gauge_clock_temperature();
    create_screen_gauge_g_force();
}