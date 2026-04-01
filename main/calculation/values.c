/*
 * ============================================================================
 * SENSOR VALUE CALCULATION & MANAGEMENT - Implementation
 * ============================================================================
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

#include "values.h"


/* ===== Global Sensor Value State Flags ===== */
bool pres_value_set            = false;   // Oil pressure value initialized
bool temp_value_set            = false;   // Oil temperature value initialized
bool volt_value_set            = false;   // Battery voltage value initialized
bool outside_temperature_set   = false;   // Outdoor temperature value initialized

/* ===== Global Sensor Values ===== */
double value_oil_pressure      = VALUE_DEFAULT_PRES;
double value_oil_temperature   = VALUE_DEFAULT_TEMP;
double value_volt              = VALUE_DEFAULT_VOLT;
double value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
int value_brightness           = VALUE_DEFAULT_BRIGHT;
bool night_mode_active         = VALUE_DEFAULT_NIGHT_MODE;

/* ===== Display Output ===== */
char output_string[20];


/* ===== Function Implementations ===== */

/**
 * Reset sensor values to defaults for specified screen/gauge
 */
void reset_values(int screenSelection) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            value_oil_pressure = VALUE_DEFAULT_PRES;
            pres_value_set = false;
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            value_oil_temperature = VALUE_DEFAULT_TEMP;
            temp_value_set = false;
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            value_volt = VALUE_DEFAULT_VOLT;
            volt_value_set = false;
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
            outside_temperature_set = false;
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
            break;
    }
}


/**
 * Reset brightness to default day mode value and disable night mode
 */
void reset_brightness(void) {
    value_brightness = BRIGHTNESS_DAY;
    night_mode_active = VALUE_DEFAULT_NIGHT_MODE;
}


/**
 * Calculate and validate sensor value with range checking and filtering
 * Updates global sensor value variable and output_string for LVGL display
 */
void calculate_value(int screenSelection, double value) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            if (!pres_value_set) {
                if (value != ADC_FAIL_VALUE)      
                    value_oil_pressure = value;
                pres_value_set = true;
            }
            else if (value == ADC_FAIL_VALUE) {
                value_oil_pressure = VALUE_MIN_PRES;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != ADC_FAIL_VALUE) 
            {
                if (value < VALUE_MIN_PRES) 
                {
                    value = VALUE_MIN_PRES;
                    snprintf(output_string, sizeof(output_string), "%s%.1f", "<", VALUE_MIN_PRES);
                }                
                else if (value >= VALUE_MIN_PRES && value <= VALUE_MAX_PRES) 
                    snprintf(output_string, sizeof(output_string), "%.1f", value_oil_pressure);
                else if (value > VALUE_MAX_PRES)
                {
                    value = VALUE_MAX_PRES;
                    snprintf(output_string, sizeof(output_string), "%s%.1f", ">", VALUE_MAX_PRES);
                }
                value_oil_pressure = calc_filter(value, value_oil_pressure);
            }
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if (!temp_value_set) {
                if (value != ADC_FAIL_VALUE)      
                    value_oil_temperature = value;
                temp_value_set = true;
            }
            else if (value == ADC_FAIL_VALUE) {
                value_oil_temperature = VALUE_MIN_TEMP;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != ADC_FAIL_VALUE) 
            {                
                if (value < VALUE_MIN_TEMP) 
                {
                    value = VALUE_MIN_TEMP;
                    snprintf(output_string, sizeof(output_string), "%s%.1f", "<", VALUE_MIN_VOLT);
                }         
                else if (value >= VALUE_MIN_TEMP && value <= VALUE_MAX_TEMP)
                    snprintf(output_string, sizeof(output_string), "%d", (int)value_oil_temperature);            
                else if (value > VALUE_MAX_TEMP) 
                {
                    value = VALUE_MAX_TEMP;
                    snprintf(output_string, sizeof(output_string), "%s%d", ">", VALUE_MAX_TEMP);
                }
                value_oil_temperature = calc_filter(value, value_oil_temperature);
            }
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if (!volt_value_set) {
                if (value != ADC_FAIL_VALUE)      
                    value_volt = value;
                volt_value_set = true;
            }
            else if (value == ADC_FAIL_VALUE) {
                value_volt = VALUE_MIN_VOLT;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != ADC_FAIL_VALUE) 
            {                
                if (value < VALUE_MIN_VOLT) 
                {
                    value = VALUE_MIN_VOLT;
                    snprintf(output_string, sizeof(output_string), "%s%.1f", "<", VALUE_MIN_VOLT);
                }
                else if (value >= VALUE_MIN_VOLT && value <= VALUE_MAX_VOLT)
                    snprintf(output_string, sizeof(output_string), "%.1f", value_volt);            
                else if (value > VALUE_MAX_VOLT)
                {
                    value = VALUE_MAX_VOLT;
                    snprintf(output_string, sizeof(output_string), "%s%.1f", ">", VALUE_MAX_VOLT);
                }
                value_volt = calc_filter(value, value_volt);
            }
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if (!outside_temperature_set) {
                if (value != ADC_FAIL_VALUE)      
                    value_outside_temperature = value;
                outside_temperature_set = true;
            }
            else if (value == ADC_FAIL_VALUE) {
                value_outside_temperature = 0;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != ADC_FAIL_VALUE) 
            {              
                if (value == ADC_FAIL_VALUE) {
                    value_outside_temperature = VALUE_MIN_OUT_TEMP;
                } 
                else if (value >= VALUE_MIN_OUT_TEMP && value <= VALUE_MAX_OUT_TEMP)
                {                    
                    if (value_outside_temperature >= 10 || value_outside_temperature <= -10) // Display values between -10 and 10 with one decimal place, rounded to nearest .5
                        snprintf(output_string, sizeof(output_string), "%d", (int)value_outside_temperature);
                    else if ((fabs(value_outside_temperature*10) - (abs((int)value_outside_temperature )*10)) >= 5 )
                        snprintf(output_string, sizeof(output_string), "%d.5", (int) value_outside_temperature);
                    else
                        snprintf(output_string, sizeof(output_string), "%d.0", (int) value_outside_temperature);
                } 
                else if (value < VALUE_MIN_OUT_TEMP) {
                    snprintf(output_string, sizeof(output_string), "%s%d", "<", VALUE_MIN_OUT_TEMP);
                    value = VALUE_MIN_OUT_TEMP;
                } 
                else if (value > VALUE_MAX_OUT_TEMP) {
                    snprintf(output_string, sizeof(output_string), "%s%d", ">", VALUE_MAX_OUT_TEMP);
                    value = VALUE_MAX_OUT_TEMP;
                }  
                value_outside_temperature = calc_filter(value, value_outside_temperature);

            }
        break;
        default:
            snprintf(output_string, sizeof(output_string), "%s", "Err");
            break;
    }
}


/**
 * Calculate brightness level from voltage with automatic day/night mode detection
 * Day mode    (< 1.0V):      100% brightness (BRIGHTNESS_DAY constant)
 * Night mode  (2.29-10.74V): 5-40% brightness (linear interpolation)
 * Uses voltage reference divider for battery voltage monitoring
 */
void calcBrightness(float value)
{
    // Range check and day/night mode selection
    // 2.29-10.74V = Night mode (5-40%), < 1.0V = Day mode (100%)
    if (value < BRIGHTNESS_DAY_MIN_V) {
        value_brightness = BRIGHTNESS_DAY;
        night_mode_active = false;
    } else {
        night_mode_active = true;
        // Linear interpolation for night brightness
        value_brightness = (value - BRIGHTNESS_NIGHT_MIN_V) / 
                          (BRIGHTNESS_NIGHT_MAX_V - BRIGHTNESS_NIGHT_MIN_V) * BRIGHTNESS_NIGHT_MAX;
        
        // Clamp to valid range
        if (value_brightness > BRIGHTNESS_NIGHT_MAX) {
            value_brightness = BRIGHTNESS_NIGHT_MAX;
        }
        if (value_brightness < BRIGHTNESS_NIGHT_MIN) {
            value_brightness = BRIGHTNESS_NIGHT_MIN;
        }
    }
}


/**
 * Get current sensor value by screen type
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
 * Get formatted output string for current sensor value
 * Returns pointer to output_string (must be read before next value update)
 */
char* get_output_string(void) {
    return output_string;
}


/**
 * Get current brightness level percentage
 */
int getBrightness(void) {
    return value_brightness;
}


/**
 * Get current day/night mode state
 */
bool getNightModeActive(void) {
    return night_mode_active;
}
