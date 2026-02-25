file(GLOB_RECURSE LVGL_UI_SRCS "pwm_sensor_functions.c" "${CMAKE_CURRENT_LIST_DIR}/lvgl/*/src/ui/*.c")

idf_component_register(SRCS "main.c" "lvgl/display_functions" "lvgl/Logos/Logo" "lvgl/Logos/jro" "lvgl/variableFunctions" "logging" "pwm_sensor_functions" ${LVGL_UI_SRCS}
                       PRIV_REQUIRES spi_flash driver lvgl
                       INCLUDE_DIRS "")