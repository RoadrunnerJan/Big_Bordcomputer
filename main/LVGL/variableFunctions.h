#pragma once

/*
 * ============================================================================
 * LVGL VARIABLE FUNCTIONS - Display Variable Management
 * ============================================================================
 * Manages LVGL variables for gauge display values and strings
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - LVGL variable declarations for sensor values
 *      - String formatting for display output
 *
 */

/* ===== Standard Library Includes ===== */
#include <inttypes.h>
#include <string.h>

/* ===== External Variable Declarations ===== */
extern double lvgl_value_temperature;
extern char lvgl_value_clock[100];
extern double lvgl_value_oil_pressure;
extern int32_t lvgl_value_oil_temperature;
extern double lvgl_value_voltage;
extern int32_t lvgl_value_clock_hour;
extern int32_t lvgl_value_clock_minute;
extern char lvgl_value_temperature_string[100];
extern char lvgl_value_voltage_string[100];
extern char lvgl_value_oil_temperature_string[100];
extern char lvgl_value_oil_pressure_string[100];

/* ===== Function Declarations ===== */

/**
 * Get oil pressure string value
 * @return Pointer to oil pressure display string
 */
extern const char *get_var_lvgl_value_oil_pressure_string();

/**
 * Set oil pressure string value
 * @param value New oil pressure string value
 */
extern void set_var_lvgl_value_oil_pressure_string(const char *value);

/**
 * Get oil temperature string value
 * @return Pointer to oil temperature display string
 */
extern const char *get_var_lvgl_value_oil_temperature_string();

/**
 * Set oil temperature string value
 * @param value New oil temperature string value
 */
extern void set_var_lvgl_value_oil_temperature_string(const char *value);

/**
 * Get voltage string value
 * @return Pointer to voltage display string
 */
extern const char *get_var_lvgl_value_voltage_string();

/**
 * Set voltage string value
 * @param value New voltage string value
 */
extern void set_var_lvgl_value_voltage_string(const char *value);

/**
 * Get temperature string value
 * @return Pointer to temperature display string
 */
extern const char *get_var_lvgl_value_temperature_string();

/**
 * Set temperature string value
 * @param value New temperature string value
 */
extern void set_var_lvgl_value_temperature_string(const char *value);

/**
 * Get voltage numeric value
 * @return Current voltage value
 */
extern double get_var_lvgl_value_voltage();

/**
 * Set voltage numeric value
 * @param value New voltage value
 */
extern void set_var_lvgl_value_voltage(double value);

/**
 * Get oil temperature numeric value
 * @return Current oil temperature value
 */
extern int32_t get_var_lvgl_value_oil_temperature();

/**
 * Set oil temperature numeric value
 * @param value New oil temperature value
 */
extern void set_var_lvgl_value_oil_temperature(int32_t value);

/**
 * Get oil pressure numeric value
 * @return Current oil pressure value
 */
extern double get_var_lvgl_value_oil_pressure();

/**
 * Set oil pressure numeric value
 * @param value New oil pressure value
 */
extern void set_var_lvgl_value_oil_pressure(double value);

/**
 * Get temperature numeric value
 * @return Current temperature value
 */
extern double get_var_lvgl_value_temperature();

/**
 * Set temperature numeric value
 * @param value New temperature value
 */
extern void set_var_lvgl_value_temperature(double value);

/**
 * Get clock string value
 * @return Pointer to clock display string
 */
extern const char *get_var_lvgl_value_clock();

/**
 * Set clock string value
 * @param value New clock string value
 */
extern void set_var_lvgl_value_clock(const char *value);

/**
 * Get clock hour value
 * @return Current clock hour
 */
extern int32_t get_var_lvgl_value_clock_hour();

/**
 * Set clock hour value
 * @param value New clock hour
 */
extern void set_var_lvgl_value_clock_hour(int32_t value);

/**
 * Get clock minute value
 * @return Current clock minute
 */
extern int32_t get_var_lvgl_value_clock_minute();

/**
 * Set clock minute value
 * @param value New clock minute
 */
extern void set_var_lvgl_value_clock_minute(int32_t value);