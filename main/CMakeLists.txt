file(GLOB_RECURSE LVGL_UI_SRCS "${CMAKE_CURRENT_LIST_DIR}/lvgl/*/src/ui/*.c")

idf_component_register(SRCS "hello_world_main.c" ${LVGL_UI_SRCS}
                       PRIV_REQUIRES spi_flash driver lvgl
                       INCLUDE_DIRS "")