#pragma once

/*
 * ============================================================================
 * SENSOR VALUE CALCULATION & MANAGEMENT
 * ============================================================================
 * Handles sensor value processing, filtering, range validation, and display
 * String formatting for oil pressure, temperature, voltage, and brightness
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - Low-pass filter for sensor smoothing
 *      - Range validation and error handling
 *      - Automatic day/night mode detection
 *      - Formatted output string generation
 *
 */

#include "../individual_config.h"
#include "../lvgl/src/ui/screens.h"
#include "esp_system.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* ===== Sensor Value State Flags ===== */
extern bool pres_value_set;              // Oil pressure value initialized
extern bool temp_value_set;              // Oil temperature value initialized
extern bool volt_value_set;              // Battery voltage value initialized
extern bool outside_temperature_set;     // Outdoor temperature value initialized

/* ===== Sensor Values (Global) ===== */
extern double value_oil_pressure;        // Current oil pressure (bar)
extern double value_oil_temperature;     // Current oil temperature (°C)
extern double value_volt;                // Current battery voltage (V)
extern double value_outside_temperature; // Current outdoor temperature (°C)
extern int value_brightness;             // Current display brightness (0-100)
extern float brightness_filtered;        // Filtered brightness value for smoothing
extern bool night_mode_active;           // Day/night mode flag

extern float value_oil_pressure_array[VALUE_OVERSAMPLING_OIL_PRES];           // Array for oil pressure value filtering
extern float value_oil_temperature_array[VALUE_OVERSAMPLING_OIL_TEMP];      // Array for oil temperature value filtering
extern float value_volt_array[VALUE_OVERSAMPLING_VOLT];         // Array for voltage value filtering
extern float value_outside_temperature_array[VALUE_OVERSAMPLING_OUT_TEMP];     // Array for outdoor temperature value filtering
extern float value_brightness_array[VALUE_OVERSAMPLING_BRIGHT];             // Array for brightness value filtering

extern int value_oil_pressure_array_idx;      // Index for oil pressure value array
extern int value_oil_temperature_array_idx;       // Index for oil temperature value array
extern int value_volt_array_idx;          // Index for voltage value array
extern int value_outside_temperature_array_idx;      // Index for outdoor temperature value array
extern int value_brightness_array_idx;   // Index for brightness value array

extern bool new_value_available_oil_pres;
extern bool new_value_available_oil_temp;
extern bool new_value_available_volt;
extern bool new_value_available_out_temp;
extern bool new_value_available_bright;

/* ===== Display Output ===== */
extern char output_string_outside_temperature[20]; // Formatted value string for LVGL display
extern char output_string_oil_pressure[20];        // Formatted value string for LVGL display
extern char output_string_oil_temperature[20];     // Formatted value string for LVGL display
extern char output_string_volt[20];                // Formatted value string for LVGL display

/* ===== Inline Functions ===== */

/**
 * Low-pass filter for sensor value smoothing
 * Uses exponential moving average to reduce noise
 * @param new_value_us New sensor reading
 * @param pre_value_us Previous filtered value
 * @return Filtered value
 */
inline double calc_filter(double new_value_us, double pre_value_us, double alpha) {
    return (new_value_us * alpha) + (pre_value_us * (1.0f - alpha));
}

/* ===== Function Declarations ===== */

/**
 * Reset sensor values to defaults for specified screen
 * @param screenSelection Screen ID (from screens.h)
 */
void reset_values(int screenSelection);

/**
 * Reset brightness to default day mode value
 */
void reset_brightness(void);

/**
 * Calculate and validate sensor value with range checking and filtering
 * Updates global sensor value variable and output_string
 * @param screenSelection Screen ID corresponding to sensor type
 * @param new_value Raw sensor value to process
 */
void calculate_value(int screenSelection, double new_value);

/**
 * Get current sensor value by screen type
 * @param screenSelection Screen ID
 * @return Current value for the sensor
 */
double get_value_by_screen_id(int screenSelection);

/**
 * Calculate brightness level from voltage with automatic day/night mode detection
 * Range: 2.29-10.74V = 5-40% brightness (night), <1.0V = 80% (day)
 * @param value Battery voltage reading
 */
void calcBrightness(float value);

/**
 * Get formatted output string for current sensor value
 * @param screenSelection Screen ID
 * @return Pointer to output string (valid for one sensor reading)
 */
char* get_output_string_by_screen_id(int screenSelection);

/**
 * Get current brightness level percentage
 * @return Brightness (0-100)
 */
int getBrightness(void);

/**
 * Get current day/night mode state
 * @return true if night mode active, false if day mode
 */
bool getNightModeActive(void);

/**
 * Get if night mode changed
 * @return true if night mode active changed, false if not
 */
bool getNightModechanged(void);

/**
 * Get current output temperature set state
 * @return true if output temperature is set, false otherwise
 */
bool getOutputTemperatureSet();

/**
 * Get if the oversampling was successfull so that the lvgl should get updatedfor current sensor value
 * @param screenSelection Screen ID
 * @return true if value got calculated
 */
bool updateLVGLScreen(int screenSelection);