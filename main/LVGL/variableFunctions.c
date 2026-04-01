/*
 * ============================================================================
 * LVGL VARIABLE FUNCTIONS - Display Variable Management Implementation
 * ============================================================================
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

/* ===== Includes ===== */
#include "variableFunctions.h"

/* ===== Global Variable Definitions ===== */

/* ===== Sensor Value Variables ===== */
double lvgl_value_temperature      = 0.0;
char lvgl_value_clock[100]         = { 0 };
double lvgl_value_oil_pressure     = 0.0;
int32_t lvgl_value_oil_temperature = 0;
double lvgl_value_voltage          = 8.0;
int32_t lvgl_value_clock_hour      = 0;
int32_t lvgl_value_clock_minute    = 0;

/* ===== Display String Variables ===== */
char lvgl_value_temperature_string[100]      = { 0 };
char lvgl_value_voltage_string[100]          = { 0 };
char lvgl_value_oil_temperature_string[100]  = { 0 };
char lvgl_value_oil_pressure_string[100]     = { 0 };

/* ===== Function Implementations ===== */

/**
 * Get oil pressure string value
 * @return Pointer to oil pressure display string
 */
const char *get_var_lvgl_value_oil_pressure_string() {
    return lvgl_value_oil_pressure_string;
}

/**
 * Set oil pressure string value with safe copy
 * @param value New oil pressure string value
 */
void set_var_lvgl_value_oil_pressure_string(const char *value) {
    strncpy(lvgl_value_oil_pressure_string, value, sizeof(lvgl_value_oil_pressure_string) / sizeof(char));
    lvgl_value_oil_pressure_string[sizeof(lvgl_value_oil_pressure_string) / sizeof(char) - 1] = 0;
}

/**
 * Get oil temperature string value
 * @return Pointer to oil temperature display string
 */
const char *get_var_lvgl_value_oil_temperature_string() {
    return lvgl_value_oil_temperature_string;
}

/**
 * Set oil temperature string value with safe copy
 * @param value New oil temperature string value
 */
void set_var_lvgl_value_oil_temperature_string(const char *value) {
    strncpy(lvgl_value_oil_temperature_string, value, sizeof(lvgl_value_oil_temperature_string) / sizeof(char));
    lvgl_value_oil_temperature_string[sizeof(lvgl_value_oil_temperature_string) / sizeof(char) - 1] = 0;
}

/**
 * Get voltage string value
 * @return Pointer to voltage display string
 */
const char *get_var_lvgl_value_voltage_string() {
    return lvgl_value_voltage_string;
}

/**
 * Set voltage string value with safe copy
 * @param value New voltage string value
 */
void set_var_lvgl_value_voltage_string(const char *value) {
    strncpy(lvgl_value_voltage_string, value, sizeof(lvgl_value_voltage_string) / sizeof(char));
    lvgl_value_voltage_string[sizeof(lvgl_value_voltage_string) / sizeof(char) - 1] = 0;
}

/**
 * Get temperature string value
 * @return Pointer to temperature display string
 */
const char *get_var_lvgl_value_temperature_string() {
    return lvgl_value_temperature_string;
}

/**
 * Set temperature string value with safe copy
 * @param value New temperature string value
 */
void set_var_lvgl_value_temperature_string(const char *value) {
    strncpy(lvgl_value_temperature_string, value, sizeof(lvgl_value_temperature_string) / sizeof(char));
    lvgl_value_temperature_string[sizeof(lvgl_value_temperature_string) / sizeof(char) - 1] = 0;
}

/**
 * Get voltage numeric value
 * @return Current voltage value
 */
double get_var_lvgl_value_voltage() {
    return lvgl_value_voltage;
}

/**
 * Set voltage numeric value
 * @param value New voltage value
 */
void set_var_lvgl_value_voltage(double value) {
    lvgl_value_voltage = value;
}

/**
 * Get oil temperature numeric value
 * @return Current oil temperature value
 */
int32_t get_var_lvgl_value_oil_temperature() {
    return lvgl_value_oil_temperature;
}

/**
 * Set oil temperature numeric value
 * @param value New oil temperature value
 */
void set_var_lvgl_value_oil_temperature(int32_t value) {
    lvgl_value_oil_temperature = value;
}

/**
 * Get oil pressure numeric value
 * @return Current oil pressure value
 */
double get_var_lvgl_value_oil_pressure() {
    return lvgl_value_oil_pressure;
}

/**
 * Set oil pressure numeric value
 * @param value New oil pressure value
 */
void set_var_lvgl_value_oil_pressure(double value) {
    lvgl_value_oil_pressure = value;
}

/**
 * Get temperature numeric value
 * @return Current temperature value
 */
double get_var_lvgl_value_temperature() {
    return lvgl_value_temperature;
}

/**
 * Set temperature numeric value
 * @param value New temperature value
 */
void set_var_lvgl_value_temperature(double value) {
    lvgl_value_temperature = value;
}

/**
 * Get clock string value
 * @return Pointer to clock display string
 */
const char *get_var_lvgl_value_clock() {
    return lvgl_value_clock;
}

/**
 * Set clock string value with safe copy
 * @param value New clock string value
 */
void set_var_lvgl_value_clock(const char *value) {
    strncpy(lvgl_value_clock, value, sizeof(lvgl_value_clock) / sizeof(char));
    lvgl_value_clock[sizeof(lvgl_value_clock) / sizeof(char) - 1] = 0;
}

/**
 * Get clock hour value
 * @return Current clock hour
 */
int32_t get_var_lvgl_value_clock_hour() {
    return lvgl_value_clock_hour;
}

/**
 * Set clock hour value
 * @param value New clock hour
 */
void set_var_lvgl_value_clock_hour(int32_t value) {
    lvgl_value_clock_hour = value;
}

/**
 * Get clock minute value
 * @return Current clock minute
 */
int32_t get_var_lvgl_value_clock_minute() {
    return lvgl_value_clock_minute;
}

/**
 * Set clock minute value
 * @param value New clock minute
 */
void set_var_lvgl_value_clock_minute(int32_t value) {
    lvgl_value_clock_minute = value;
}