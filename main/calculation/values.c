#include "values.h"

bool pres_value_set = false;
bool temp_value_set = false;
bool volt_value_set = false;
bool outside_temperature_set = false;

double value_oil_pressure = 0.0;
double value_oil_temperature = 0.0;
double value_volt = 8.0;
double value_outside_temperature = 0.0;
int value_brightness = 0;
bool night_mode_active = false;

char output_string[20];

void reset_values(int screenSelection) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            value_oil_pressure = 0.0;
            pres_value_set = false;
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            value_oil_temperature = 0.0;
            temp_value_set = false;
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            value_volt = 8.0;
            volt_value_set = false;
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            value_outside_temperature = 0.0;
            outside_temperature_set = false;
            break;
        default:
            value_oil_pressure = 0.0;
            value_oil_temperature = 0.0;
            value_volt = 8.0;
            value_outside_temperature = 0.0;
            pres_value_set = false;
            temp_value_set = false;
            volt_value_set = false;
            outside_temperature_set = false;
            break;
    }
}

void reset_brightness(){
    value_brightness = 0;
    night_mode_active = false;
}

void calculate_value(int screenSelection, double value) {
    switch (screenSelection) {
        case SCREEN_ID_GAUGE_OIL_PRESSURE:
            if (!pres_value_set) {
                if (value != -99.0f)      
                    value_oil_pressure = value;
                pres_value_set = true;
            }
            else if (value == -99.0f) {
                value_oil_pressure = 0;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != -99.0f) 
            {
                if (value < 0) 
                {
                    value = 0;
                    snprintf(output_string, sizeof(output_string), "%s", "<0.0");
                }                
                else if (value >= 0.0 && value <= 6.0) 
                    snprintf(output_string, sizeof(output_string), "%.1f", value_oil_pressure);
                else if (value > 6)
                {
                    value = 6.0;
                    snprintf(output_string, sizeof(output_string), "%s", ">6.0");
                }
                value_oil_pressure = calc_filter(value, value_oil_pressure);
            }
            break;
        case SCREEN_ID_GAUGE_OIL_TEMPERATURE:
            if (!temp_value_set) {
                if (value != -99.0f)      
                    value_oil_temperature = value;
                temp_value_set = true;
            }
            else if (value == -99.0f) {
                value_oil_temperature = 0;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != -99.0f) 
            {                
                if (value < 0) 
                {
                    value = 0;
                    snprintf(output_string, sizeof(output_string), "%s", "<0");
                }         
                else if (value >= 0 && value <= 150)
                    snprintf(output_string, sizeof(output_string), "%d", (int)value_oil_temperature);            
                else if (value > 150) 
                {
                    value = 150;
                    snprintf(output_string, sizeof(output_string), "%s", ">150");
                }
                value_oil_temperature = calc_filter(value, value_oil_temperature);
            }
            break;
        case SCREEN_ID_GAUGE_VOLTAGE:
            if (!volt_value_set) {
                if (value != -99.0f)      
                    value_volt = value;
                volt_value_set = true;
            }
            else if (value == -99.0f) {
                value_volt = 8.0;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != -99.0f) 
            {                
                if (value < 8.0) 
                {
                    value = 8.0;
                    snprintf(output_string, sizeof(output_string), "%s", "<8.0");
                }
                else if (value >= 8.0 && value <= 16.0)
                    snprintf(output_string, sizeof(output_string), "%.1f", value_volt);            
                else if (value > 16.0)
                {
                    value = 16.0;
                    snprintf(output_string, sizeof(output_string), "%s", ">16.0");
                }
                value_volt = calc_filter(value, value_volt);
            }
            break;
        case SCREEN_ID_GAUGE_TEMPERATURE_CLOCK:
        case SCREEN_ID_GAUGE_CLOCK_TEMPERATURE:
            if (!outside_temperature_set) {
                if (value != -99.0f)      
                    value_outside_temperature = value;
                outside_temperature_set = true;
            }
            else if (value == -99.0f) {
                value_outside_temperature = 0;
                snprintf(output_string, sizeof(output_string), "%s", "---");
            }
            else if (value != -99.0f) 
            {              
                if (value == -99.0f) {
                    value_outside_temperature = -30.0f;
                } 
                else if (value >= -30.0f && value <= 70.0f)
                {                    
                    if (value_outside_temperature >= 10 || value_outside_temperature <= -10)
                        snprintf(output_string, sizeof(output_string), "%d", (int)value_outside_temperature);
                    else if ((fabs(value_outside_temperature*10) - (abs((int)value_outside_temperature )*10)) >= 5 )
                        snprintf(output_string, sizeof(output_string), "%d.5", (int) value_outside_temperature);
                    else
                        snprintf(output_string, sizeof(output_string), "%d.0", (int) value_outside_temperature);
                } 
                else if (value < -30.0f) {
                    snprintf(output_string, sizeof(output_string), "%s", "<-30");
                    value = -30.0f;
                } 
                else if (value > 70.0f) {
                    snprintf(output_string, sizeof(output_string), "%s", ">70");
                    value = 70.0f;
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
