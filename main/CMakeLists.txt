file(GLOB_RECURSE LVGL_UI_SRCS "${CMAKE_CURRENT_LIST_DIR}/lvgl/src/ui/*.c")
file(GLOB_RECURSE PERIPHERIE_SRCS "${CMAKE_CURRENT_LIST_DIR}/peripherie/*.c")

idf_component_register( SRCS
                        "main.c"
                        "lvgl/variableFunctions"
                        "logging/logging"
                        "simulation/testSimulation"
                        "calculation/values"
                        ${PERIPHERIE_SRCS}
                        ${LVGL_UI_SRCS}
                       PRIV_REQUIRES spi_flash driver espressif__button lvgl
                       INCLUDE_DIRS "")