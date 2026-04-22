/**
 * @file values.c
 * @brief Sensor value calculation and management implementation.
 *
 * Handles real-time processing of sensor values including low-pass filtering,
 * range validation, error detection, and formatted output for display.
 * Supports multiple sensor types with independent filtering and state management.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - Low-pass filter for sensor smoothing
 *      - Range validation and error handling
 *      - Automatic day/night mode detection
 *      - Formatted output string generation
 */

#include "values.h"
#include "../logging/logging.h"


/* ===== Global Sensor Value State Flags ===== */
bool pres_value_set            = false;   // Oil pressure value initialized
bool temp_value_set            = false;   // Oil temperature value initialized
bool volt_value_set            = false;   // Battery voltage value initialized
bool outside_temperature_set   = false;   // Outdoor temperature value initialized
bool bright_value_set          = false;   // bright value initialized

/* ===== Global Sensor Values ===== */
double value_oil_pressure      = VALUE_DEFAULT_PRES;
double value_oil_temperature   = VALUE_DEFAULT_TEMP;
double value_volt              = VALUE_DEFAULT_VOLT;
double value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
int value_brightness           = VALUE_DEFAULT_BRIGHT;
float brightness_filtered      = 0;
bool night_mode_active         = VALUE_DEFAULT_NIGHT_MODE;

/* ===== Value Arrays for Oversampling ===== */
float value_oil_pressure_array[VALUE_OVERSAMPLING_OIL_PRES] = {0.0};
float value_oil_temperature_array[VALUE_OVERSAMPLING_OIL_TEMP] = {0.0};
float value_volt_array[VALUE_OVERSAMPLING_VOLT] = {0.0};
float value_outside_temperature_array[VALUE_OVERSAMPLING_OUT_TEMP] = {0.0};
float value_brightness_array[VALUE_OVERSAMPLING_BRIGHT] = {0.0};

int value_brightness_array_idx = 0;
int value_outside_temperature_array_idx = 0;
int value_oil_temperature_array_idx = 0;
int value_oil_pressure_array_idx = 0;
int value_volt_array_idx = 0;

bool new_value_available_oil_pres = false;
bool new_value_available_oil_temp = false;
bool new_value_available_volt     = false;
bool new_value_available_out_temp = false;
bool new_value_available_bright   = false;

/* ===== Display Output ===== */
char output_string_outside_temperature[20]; // Formatted value string for LVGL display
char output_string_oil_pressure[20];        // Formatted value string for LVGL display
char output_string_oil_temperature[20];     // Formatted value string for LVGL display
char output_string_volt[20];                // Formatted value string for LVGL display


/* ===== Function Implementations ===== */

/**
 * @brief Reset sensor values to defaults for specified screen/gauge.
 *
 * Resets the sensor value, state flag, display string, and oversampling array
 * to their default/initial states. Used during mode transitions or sensor resets.
 *
 * @param screenSelection Screen ID from screens.h to identify which sensor to reset
 *                        (-1 resets all sensors)
 */
void reset_values(int screenSelection) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            value_oil_pressure = VALUE_DEFAULT_PRES;
            pres_value_set = false;
            snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%s", "---");
            new_value_available_oil_pres = false;
            for (int i = 0; i < VALUE_OVERSAMPLING_OIL_PRES; i++) {
                value_oil_pressure_array[i] = 0;
            }
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            value_oil_temperature = VALUE_DEFAULT_TEMP;
            temp_value_set = false;
            snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%s", "---");
            new_value_available_oil_temp = false;
            for (int i = 0; i < VALUE_OVERSAMPLING_OIL_TEMP; i++) {
                value_oil_temperature_array[i] = 0;
            }
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            value_volt = VALUE_DEFAULT_VOLT;
            volt_value_set = false;
            snprintf(output_string_volt, sizeof(output_string_volt), "%s", "---");
            new_value_available_volt = false;
            for (int i = 0; i < VALUE_OVERSAMPLING_VOLT; i++) {
                value_volt_array[i] = 0;
            }
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
            outside_temperature_set = false;
            snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%s", "---");
            new_value_available_out_temp = false;
            for (int i = 0; i < VALUE_OVERSAMPLING_OUT_TEMP; i++) {
                value_outside_temperature_array[i] = 0;
            }
            break;
        default:
            value_oil_pressure = VALUE_DEFAULT_PRES;
            value_oil_temperature = VALUE_DEFAULT_TEMP;
            value_volt = VALUE_DEFAULT_VOLT;
            value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
            pres_value_set = false;
            temp_value_set = false;
            volt_value_set = false;
            outside_temperature_set = false;
            snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%s", "---");
            snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%s", "---");
            snprintf(output_string_volt, sizeof(output_string_volt), "%s", "---");
            snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%s", "---");
            new_value_available_oil_pres = false;
            new_value_available_oil_temp = false;
            new_value_available_volt = false;
            new_value_available_out_temp = false;
            for (int i = 0; i < VALUE_OVERSAMPLING_OIL_PRES; i++) {
                value_oil_pressure_array[i] = 0;
            }
            for (int i = 0; i < VALUE_OVERSAMPLING_OIL_TEMP; i++) {
                value_oil_temperature_array[i] = 0;
            }
            for (int i = 0; i < VALUE_OVERSAMPLING_VOLT; i++) {
                value_volt_array[i] = 0;
            }
            for (int i = 0; i < VALUE_OVERSAMPLING_OUT_TEMP; i++) {
                value_outside_temperature_array[i] = 0;
            }
            break;
    }
}

/**
 * @brief Reset brightness to default day mode value and disable night mode.
 *
 * Resets display brightness to BRIGHTNESS_DAY setting and clears night mode state.
 * Used during startup or when returning from night mode.
 */
void reset_brightness(void) {
    value_brightness = BRIGHTNESS_DAY;
    night_mode_active = VALUE_DEFAULT_NIGHT_MODE;
    bright_value_set = false;
    for (int i = 0; i < VALUE_OVERSAMPLING_BRIGHT; i++) {
        value_brightness_array[i] = 0;
    }
    value_brightness_array_idx = 0;
    new_value_available_bright = true;
}

/**
 * @brief Calculate and validate sensor value with range checking and filtering.
 *
 * Processes raw sensor input with:
 * - Error detection (ADC_FAIL_VALUE check)
 * - Range validation (min/max clamping)
 * - Exponential moving average filtering
 * - Formatted string generation for display
 * - Oversampling aggregation
 *
 * Updates global sensor value variable and output string for LVGL display.
 *
 * @param screenSelection Screen ID identifying the sensor type to process
 * @param value Raw sensor value to process
 */
void calculate_value(int screenSelection, double value) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            if (value == ADC_FAIL_VALUE) {
                value_oil_pressure = VALUE_MIN_PRES;
                snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%s", "---");
                pres_value_set = false;
            }
            else { 
                if (!pres_value_set) {
                    value_oil_pressure = value;
                    pres_value_set = true;
                } else {
                    if (value < VALUE_MIN_PRES) {
                        value = VALUE_MIN_PRES;
                        snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%s%.1f", "<", VALUE_MIN_PRES);
                    } else if (value >= VALUE_MIN_PRES && value <= VALUE_MAX_PRES) {
                        snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%.1f", value_oil_pressure);
                    } else if (value > VALUE_MAX_PRES) {
                        value = VALUE_MAX_PRES;
                        snprintf(output_string_oil_pressure, sizeof(output_string_oil_pressure), "%s%.1f", ">", VALUE_MAX_PRES);
                    }

                    if (value_oil_pressure_array_idx >= VALUE_OVERSAMPLING_OIL_PRES) { // VALUE_OVERSAMPLING_OIL_PRES = 5
                        value_oil_pressure_array_idx = 0;
                        float sum = 0.0f;
                        for (int i = 0; i < VALUE_OVERSAMPLING_OIL_PRES; i++) {
                            sum += value_oil_pressure_array[i];
                        }
                        value = sum / (float)VALUE_OVERSAMPLING_OIL_PRES;
                        value_oil_pressure = calc_filter(value, value_oil_pressure, FILTER_ALPHA_OIL_PRES);
                        new_value_available_oil_pres = true;
                    }
                    else {
                        value_oil_pressure_array[value_oil_pressure_array_idx] = value;
                        value_oil_pressure_array_idx = (value_oil_pressure_array_idx + 1);
                    }
                }
            }
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if (value == ADC_FAIL_VALUE) {
                value_oil_temperature = VALUE_MIN_TEMP;
                snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%s", "---");
                temp_value_set = false;
            }
            else {
                if (!temp_value_set) {
                    value_oil_temperature = value;
                    temp_value_set = true;
                } else  {
                    if (value < VALUE_MIN_TEMP) {
                        value = VALUE_MIN_TEMP;
                        snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%s%d", "<", VALUE_MIN_TEMP);
                    } else if (value >= VALUE_MIN_TEMP && value <= VALUE_MAX_TEMP) {
                        snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%d", (int)value_oil_temperature);
                    } else if (value > VALUE_MAX_TEMP) {
                        value = VALUE_MAX_TEMP;
                        snprintf(output_string_oil_temperature, sizeof(output_string_oil_temperature), "%s%d", ">", VALUE_MAX_TEMP);
                    }
                    
                    if (value_oil_temperature_array_idx >= VALUE_OVERSAMPLING_OIL_TEMP) { // VALUE_OVERSAMPLING_OIL_TEMP = 5
                        value_oil_temperature_array_idx = 0;
                        float sum = 0.0f;
                        for (int i = 0; i < VALUE_OVERSAMPLING_OIL_TEMP; i++) {
                            sum += value_oil_temperature_array[i];
                        }
                        value = sum / (float)VALUE_OVERSAMPLING_OIL_TEMP;
                        value_oil_temperature = calc_filter(value, value_oil_temperature, FILTER_ALPHA_OIL_TEMP);
                        new_value_available_oil_temp = true;
                    }
                    else {
                        value_oil_temperature_array[value_oil_temperature_array_idx] = value;
                        value_oil_temperature_array_idx = (value_oil_temperature_array_idx + 1);
                    }
                }
            }
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if (value == ADC_FAIL_VALUE) {
                value_volt = VALUE_MIN_VOLT;
                snprintf(output_string_volt, sizeof(output_string_volt), "%s", "---");
                volt_value_set = false;
            }
            else {
                if (!volt_value_set) {
                    value_volt = value;
                    volt_value_set = true;
                } else {
                    if (value < VALUE_MIN_VOLT) {
                        value = VALUE_MIN_VOLT;
                        snprintf(output_string_volt, sizeof(output_string_volt), "%s%.1f", "<", VALUE_MIN_VOLT);
                    } else if (value >= VALUE_MIN_VOLT && value <= VALUE_MAX_VOLT) {
                        snprintf(output_string_volt, sizeof(output_string_volt), "%.1f", value_volt);
                    } else if (value > VALUE_MAX_VOLT) {
                        value = VALUE_MAX_VOLT;
                        snprintf(output_string_volt, sizeof(output_string_volt), "%s%.1f", ">", VALUE_MAX_VOLT);
                    }
                    if (value_volt_array_idx >= VALUE_OVERSAMPLING_VOLT) { // VALUE_OVERSAMPLING_VOLT = 5
                        value_volt_array_idx = 0;
                        float sum = 0.0f;
                        for (int i = 0; i < VALUE_OVERSAMPLING_VOLT; i++) {
                            sum += value_volt_array[i];
                        }
                        value = sum / (float)VALUE_OVERSAMPLING_VOLT;
                        value_volt = calc_filter(value, value_volt, FILTER_ALPHA_VOLT);
                        new_value_available_volt = true;
                    }
                    else {
                        value_volt_array[value_volt_array_idx] = value;
                        value_volt_array_idx = (value_volt_array_idx + 1);
                    }
                }
            }
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if (value == ADC_FAIL_VALUE) {
                value_outside_temperature = 0;
                snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%s", "---");
                outside_temperature_set = false;
            }
            else {
                if (!outside_temperature_set) {
                    value_outside_temperature = value;
                    outside_temperature_set = true;
                } else {
                    if (value < VALUE_MIN_OUT_TEMP) {
                        snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%s%d", "<", VALUE_MIN_OUT_TEMP);
                        value = VALUE_MIN_OUT_TEMP;
                    } else if (value > VALUE_MAX_OUT_TEMP) {
                        snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%s%d", ">", VALUE_MAX_OUT_TEMP);
                        value = VALUE_MAX_OUT_TEMP;
                    } else if (value >= VALUE_MIN_OUT_TEMP && value <= VALUE_MAX_OUT_TEMP) {
                        // Display values between -10 and 10 with one decimal place, rounded to nearest .5
                        if (value_outside_temperature >= 10 || value_outside_temperature <= -10) {
                            snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%d", (int)value_outside_temperature);
                        } else if ((fabs(value_outside_temperature * 10) - (abs((int)value_outside_temperature) * 10)) >= 5) {
                            snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%d.5", (int)value_outside_temperature);
                        } else {
                            snprintf(output_string_outside_temperature, sizeof(output_string_outside_temperature), "%d.0", (int)value_outside_temperature);
                        }
                    }
                    if (value_outside_temperature_array_idx >= VALUE_OVERSAMPLING_OUT_TEMP) { // VALUE_OVERSAMPLING_OUT_TEMP = 5
                        value_outside_temperature_array_idx = 0;
                        float sum = 0.0f;
                        for (int i = 0; i < VALUE_OVERSAMPLING_OUT_TEMP; i++) {
                            sum += value_outside_temperature_array[i];
                        }
                        value = sum / (float)VALUE_OVERSAMPLING_OUT_TEMP;
                        value_outside_temperature = calc_filter(value, value_outside_temperature, FILTER_ALPHA_OUT_TEMP);
                        new_value_available_out_temp = true;
                    }
                    else {
                        value_outside_temperature_array[value_outside_temperature_array_idx] = value;
                        value_outside_temperature_array_idx = (value_outside_temperature_array_idx + 1);
                    }
                }
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Calculate brightness level from voltage with automatic day/night mode detection.
 *
 * Detects and switches between day and night modes based on ambient light sensor voltage.
 * - Day mode   (< 0.05V):      100% brightness (BRIGHTNESS_DAY constant)
 * - Night mode (2.29-10.74V): linear interpolation 5-25% brightness
 * Uses oversampling for stable readings with exponential moving average filtering.
 *
 * @param value Ambient light sensor voltage in volts
 */
void calcBrightness(float value) {
    // Range check and day/night mode selection
    // 2.29-10.74V = Night mode (20-40%), < 0.05V = Day mode (100%)
    value_brightness_array[value_brightness_array_idx] = value; // Store as cents for precision
    value_brightness_array_idx = (value_brightness_array_idx + 1);
    if (value_brightness_array_idx >= VALUE_OVERSAMPLING_BRIGHT) { // VALUE_OVERSAMPLING_BRIGHT = 5
        value_brightness_array_idx = 0;
        float sum = 0.0f;
        for (int i = 0; i < VALUE_OVERSAMPLING_BRIGHT; i++) {
            sum += value_brightness_array[i];
        }
        value = sum / (float)VALUE_OVERSAMPLING_BRIGHT;
        if (value < BRIGHTNESS_DAY_MAX_V) {
            value_brightness = BRIGHTNESS_DAY;
            night_mode_active = false;
            new_value_available_bright = true;
            bright_value_set = false;
        } else {
            if (bright_value_set == false)
            {
                night_mode_active = true;
                new_value_available_bright = true;
                bright_value_set = true;
                value_brightness = BRIGHTNESS_NIGHT_MAX;
            }
            else {
                brightness_filtered = calc_filter(value, brightness_filtered, FILTER_ALPHA_BEL);                
                float night_val = (brightness_filtered - BRIGHTNESS_NIGHT_MIN_V) / (BRIGHTNESS_NIGHT_MAX_V - BRIGHTNESS_NIGHT_MIN_V) * BRIGHTNESS_NIGHT_MAX;

                if (night_val > BRIGHTNESS_NIGHT_MAX) {
                    night_val = BRIGHTNESS_NIGHT_MAX;
                }
                if (night_val < BRIGHTNESS_NIGHT_MIN) {
                    night_val = BRIGHTNESS_NIGHT_MIN;
                }

                value_brightness = (int)night_val;
            }
            char log_msg[50];
            snprintf(log_msg, sizeof(log_msg), "Set Brightness: %d %%", value_brightness);
            printLog(log_msg);
        }
    }
}


/**
 * @brief Get current sensor value by screen type.
 *
 * Retrieves the processed and filtered sensor value associated with a specific gauge screen.
 *
 * @param screenSelection Screen ID identifying the sensor type
 * @return Current sensor value in appropriate units (bar, °C, V, etc.)
 */
double get_value_by_screen_id(int screenSelection) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            return value_oil_pressure;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            return value_oil_temperature;
        case SCREEN_ID_GAUGE_VOLTAGE:
            return value_volt;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            return value_outside_temperature;
        default:
            return 0.0;
    }
}


/**
 * @brief Get formatted output string for current sensor value by screen type.
 *
 * Returns pointer to the display-ready formatted string for the specified gauge.
 * String includes units and range indicators (< or >).
 *
 * @param screenSelection Screen ID identifying the sensor type
 * @return Pointer to formatted output string for LVGL display, or NULL if invalid
 */
char* get_output_string_by_screen_id(int screenSelection) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            return output_string_oil_pressure;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            return output_string_oil_temperature;
        case SCREEN_ID_GAUGE_VOLTAGE:
            return output_string_volt;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            return output_string_outside_temperature;
        default:
            return NULL;
    }
}


/**
 * @brief Get current brightness level percentage.
 *
 * @return Brightness level (0-100%)
 */
int getBrightness(void) {
    return value_brightness;
}

/**
 * @brief Get current day/night mode state.
 *
 * @return true if night mode is active, false if day mode
 */
bool getNightModeActive(void) {
    return night_mode_active;
}

/**
 * @brief Check if night mode state has changed since last query.
 *
 * @return true if night mode state changed, false otherwise
 */
bool getNightModechanged(void) {
    if (new_value_available_bright)
    {
        new_value_available_bright = false;
        return true;
    }
    return false;
}

/**
 * @brief Get current outdoor temperature set state.
 *
 * @return true if outdoor temperature is set and valid, false otherwise
 */
bool getOutputTemperatureSet() {
    return outside_temperature_set;
}

/**
 * @brief Check if new oversampled sensor value is available for screen update.
 *
 * Returns true once per cycle when oversampling buffer is full and average computed.
 * Used to trigger screen refresh with new sensor data.
 *
 * @param screenSelection Screen ID identifying the sensor type
 * @return true if new averaged value available, false otherwise
 */
bool updateLVGLScreen(int screenSelection)
{
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            if (new_value_available_oil_pres)
            {
                new_value_available_oil_pres = false;
                return true;
            }
        break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if (new_value_available_oil_temp)
            {
                new_value_available_oil_temp = false;
                return true;
            }
        break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if (new_value_available_volt)
            {
                new_value_available_volt = false;
                return true;
            }
        break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if (new_value_available_out_temp)
            {
                new_value_available_out_temp = false;
                return true;
            }
        break;
    }
    return false;
}