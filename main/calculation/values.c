#include "values.h"

bool pres_value_set = false;
bool temp_value_set = false;
bool volt_value_set = false;
bool outside_temperature_set = false;

double value_oil_pressure = VALUE_DEFAULT_PRES;
double value_oil_temperature = VALUE_DEFAULT_TEMP;
double value_volt = VALUE_DEFAULT_VOLT;
double value_outside_temperature = VALUE_DEFAULT_OUT_TEMP;
int value_brightness = VALUE_DEFAULT_BRIGHT;
bool night_mode_active = VALUE_DEFAULT_NIGHT_MODE;

char output_string[20];

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

void reset_brightness(){
    value_brightness = BRIGHTNESS_DAY;
    night_mode_active = VALUE_DEFAULT_NIGHT_MODE;
}

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
                    if (value_outside_temperature >= 10 || value_outside_temperature <= -10) // Alle Werte zwischen -10 und 10 mit einer Nachkommastelle gerundet auf .5 darstellen
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

void calcBrightness(float value)
{
    // 2.29-10.74V entsprechen 1-80% Helligkeit, 0 entspricht 100%
    if (value < BRIGHTNESS_DAY_MIN_V ) 
    {
        value_brightness = BRIGHTNESS_DAY;
        night_mode_active = false;
    }
    else {
        night_mode_active = true;
        value_brightness = (value - BRIGHTNESS_NIGHT_MIN_V) / (BRIGHTNESS_NIGHT_MAX_V - BRIGHTNESS_NIGHT_MIN_V) * BRIGHTNESS_NIGHT_MAX;
        if (value_brightness > BRIGHTNESS_NIGHT_MAX) value_brightness = BRIGHTNESS_NIGHT_MAX;
        if (value_brightness < BRIGHTNESS_NIGHT_MIN) value_brightness = BRIGHTNESS_NIGHT_MIN;
    }
}

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

char* get_output_string() {
    return output_string;
}

int getBrightness() {
    return value_brightness;
}

bool getNightModeActive() {
    return night_mode_active;
}
