/**
 * @file adc.c
 * @brief ADC interface for sensor readings via internal ADC.
 *
 * Manages analog-to-digital converters from the microcontroller for reading various sensors:
 * oil pressure, oil temperature, battery voltage, and outdoor temperature.
 * Includes NTC thermistor and pressure table interpolation with calibration.
 *
 * @author Jan Niklas Rodewald (JRO)
 * @date 01.04.2026
 *
 * @note CHANGELOG
 * v1.0 (01.04.2026) - Initial implementation
 *      - NTC thermistor table interpolation
 *      - Pressure sensor calibration table
 *      - Voltage divider calculations with dynamic reference
 */

#include "adc.h"

adc_oneshot_unit_init_cfg_t init_config[ADC_UNIT_NUMBER];
adc_oneshot_unit_handle_t adc_handler[ADC_UNIT_NUMBER];
adc_cali_curve_fitting_config_t cali_config[ADC_UNIT_NUMBER];
adc_cali_handle_t cali_handler[ADC_UNIT_NUMBER];
adc_handles_t adc_handles[MAX_ABC_NBR - 1];

const lookup_values_t oil_temp_table[] = {
    // {Temperature in °C, Resistance in Ohms}
    {-15, 7721.35}, {-10, 5720.88}, {-5, 4284.03}, {0, 3240.18}, {5, 2473.6}, 
    {10, 1905.87}, {15, 1404.44}, {20, 1168.64}, {25, 926.71}, {30, 739.98}, 
    {35, 594.9}, {40, 481.52}, {45, 392.57}, {50, 322.17}, {55, 266.19}, 
    {60, 221.17}, {65, 184.72}, {70, 155.29}, {75, 131.38}, {80, 112.08}, 
    {85, 96.4}, {90, 82.96}, {95, 71.44}, {100, 61.92}, {105, 54.01}, 
    {110, 47.24}, {115, 41.42}, {120, 36.51}, {125, 32.38}, {130, 28.81}, 
    {135, 25.7}, {140, 23.0}, {145, 20.66}, {150, 18.59}
};

const lookup_values_t outside_temperature_table[] = {
    // {Temperature in °C, Resistance in Ohms}
    {-15, 36475.0}, {-10, 27665.0}, {-5, 21166.0}, {0, 16330.0}, {5, 12695.0}, 
    {10, 9950.0}, {15, 7855.0}, {20, 6245.0}, {25, 5000.0}, {30, 4028.0}, 
    {35, 3266.0}, {40, 2663.0}, {45, 2185.0}, {50, 1803.0}, {55, 1495.0}, 
    {60, 1247.0}, {65, 1045.0}, {70, 880.0}, {75, 745.0}, {80, 633.0}, 
    {85, 541.0}, {90, 464.0}, {95, 400.0}, {100, 346.0}, {105, 301.0}, 
    {110, 262.0}, {115, 229.0}, {120, 201.0}, {125, 177.0}, {130, 156.0}, 
    {135, 138.0}, {140, 122.0}, {145, 109.0}, {150, 97.0}
};

const lookup_values_t pressure_table[] = {
    // {Pressure/Value 1, Value 2}
    {0.0, 11.0}, {0.5, 29.0}, {1.0, 47.0}, {1.5, 65.0}, {2.0, 82.0}, 
    {2.5, 100.0}, {3.0, 117.0}, {3.5, 134.0}, {4.0, 151.0}, {4.5, 167.0}, {5.0, 184.0}
};



/**
 * @brief Initialize ADC hardware and calibration.
 *
 * Initializes both ADC units with calibration curve fitting.
 * Configures all channels according to configuration defines.
 */
void adc_init() {
    for (int i = 0; i < ADC_UNIT_NUMBER; i++) {
        init_config[i].unit_id =                i == 0 ? ADC_UNIT_1 : ADC_UNIT_2;
        cali_config[i].unit_id =    i == 0 ? ADC_UNIT_1 : ADC_UNIT_2;
        cali_config[i].atten =      i == 0 ? ADC_UNIT_1_ATTEN : ADC_UNIT_2_ATTEN;
        cali_config[i].bitwidth =   i == 0 ? ADC_UNIT_1_BITWIDTH : ADC_UNIT_2_BITWIDTH;

        adc_oneshot_new_unit(&(init_config[i]), &(adc_handler[i]));

        if (adc_cali_create_scheme_curve_fitting(&(cali_config[i]), &(cali_handler[i])) != ESP_OK) {
            cali_handler[i] = NULL;
        }
    }

    for (int i = 0; i < MAX_ABC_NBR; i ++){
        switch(i)
        {
            case ADC_OIL_PRESSURE:
                adc_handles[i].adc_handle = ADC_OIL_PRESSURE_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_OIL_PRESSURE_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_OIL_PRESSURE_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_OIL_PRESSURE_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_OIL_PRESSURE_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_OIL_PRESSURE_ATTEN;
                adc_handles[i].channel =                ADC_OIL_PRESSURE_CHANNEL;
            break;
            case ADC_OIL_TEMPERATURE:  
                adc_handles[i].adc_handle = ADC_OIL_TEMPERATURE_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_OIL_TEMPERATURE_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_OIL_TEMPERATURE_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_OIL_TEMPERATURE_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_OIL_TEMPERATURE_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_OIL_TEMPERATURE_ATTEN;
                adc_handles[i].channel =                ADC_OIL_TEMPERATURE_CHANNEL;
            break;
            case ADC_OUT_TEMPERATURE:            

                adc_handles[i].adc_handle = ADC_OUT_TEMPERATURE_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_OUT_TEMPERATURE_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_OUT_TEMPERATURE_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_OUT_TEMPERATURE_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_OUT_TEMPERATURE_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_OUT_TEMPERATURE_ATTEN;
                adc_handles[i].channel =                ADC_OUT_TEMPERATURE_CHANNEL;
            break;
            case ADC_12V:     
                adc_handles[i].adc_handle = ADC_OIL_12V_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_OIL_12V_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_OIL_12V_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_OIL_12V_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_OIL_12V_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_OIL_12V_ATTEN;
                adc_handles[i].channel =                ADC_OIL_12V_CHANNEL;
            break;
            case ADC_AMBI:    
                adc_handles[i].adc_handle = ADC_AMBI_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_AMBI_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_AMBI_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_AMBI_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_AMBI_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_AMBI_ATTEN;
                adc_handles[i].channel =                ADC_AMBI_CHANNEL;
            break;
            case ADC_3V3:   
                adc_handles[i].adc_handle = ADC_3V3_UNIT_ID == ADC_UNIT_1 ? adc_handler[0] : (ADC_3V3_UNIT_ID == ADC_UNIT_2 ? adc_handler[1] : NULL);
                adc_handles[i].cali_handle = ADC_3V3_UNIT_ID == ADC_UNIT_1 ? cali_handler[0] : (ADC_3V3_UNIT_ID == ADC_UNIT_2 ? cali_handler[1] : NULL);
                adc_handles[i].chan_config.bitwidth =   ADC_3V3_BITWIDTH;
                adc_handles[i].chan_config.atten =      ADC_3V3_ATTEN;
                adc_handles[i].channel =                ADC_3V3_CHANNEL;
            break;
        }
        adc_oneshot_config_channel(adc_handles[i].adc_handle, adc_handles[i].channel, &(adc_handles[i].chan_config));
    }
}

/**
 * @brief Read raw ADC value with calibration.
 *
 * Reads raw value from specified ADC channel and converts to voltage using
 * hardware calibration curve if available.
 *
 * @param adc_sel ADC channel selector (adc_selection enum)
 * @return Voltage value in millivolts, or raw ADC count if uncalibrated
 */
int read_adc_value_raw(adc_selection adc_sel)
{
    int raw = 0;
    int voltage = 0;
    adc_oneshot_read(adc_handles[adc_sel].adc_handle, adc_handles[adc_sel].channel, &raw);
    if (adc_handles[adc_sel].cali_handle) {
        adc_cali_raw_to_voltage(adc_handles[adc_sel].cali_handle, raw, &voltage);
    } else {
        voltage = raw;  // ToDo: Hier muss noch die Umrechnung hin!
    }
    return voltage;
}


/**
 * @brief Interpolate oil temperature from NTC thermistor table.
 *
 * Performs linear interpolation on the oil_temp_table to convert measured
 * resistance value to temperature. Clamps to table boundaries.
 *
 * @param r_measured Measured resistance in Ohms
 * @return Interpolated temperature in °C, or ADC_FAIL_VALUE if out of range
 */
float interpolate_temp(float r_measured) {
    if (r_measured >= oil_temp_table[0].res) return oil_temp_table[0].value;
    if (r_measured <= oil_temp_table[OIL_TABLE_SIZE-1].res) return oil_temp_table[OIL_TABLE_SIZE-1].value;

    for (int i = 0; i < OIL_TABLE_SIZE - 1; i++) {
        if (r_measured <= oil_temp_table[i].res && r_measured > oil_temp_table[i+1].res) {
            float r_range = oil_temp_table[i+1].res - oil_temp_table[i].res;
            float t_range = oil_temp_table[i+1].value - oil_temp_table[i].value;
            return oil_temp_table[i].value + (r_measured - oil_temp_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

/**
 * @brief Interpolate outdoor temperature from NTC thermistor table.
 *
 * Performs linear interpolation on the outside_temperature_table to convert measured
 * resistance value to ambient temperature. Clamps to table boundaries.
 *
 * @param r_measured Measured resistance in Ohms
 * @return Interpolated temperature in °C, or ADC_FAIL_VALUE if out of range
 */
float interpolate_outside_temp(float r_measured) {
    if (r_measured >= outside_temperature_table[0].res) return outside_temperature_table[0].value;
    if (r_measured <= outside_temperature_table[OUTSIDE_TABLE_SIZE-1].res) return outside_temperature_table[OUTSIDE_TABLE_SIZE-1].value;

    for (int i = 0; i < OUTSIDE_TABLE_SIZE - 1; i++) {
        if (r_measured <= outside_temperature_table[i].res && r_measured > outside_temperature_table[i+1].res) {
            float r_range = outside_temperature_table[i+1].res - outside_temperature_table[i].res;
            float t_range = outside_temperature_table[i+1].value - outside_temperature_table[i].value;
            return outside_temperature_table[i].value + (r_measured - outside_temperature_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

/**
 * @brief Interpolate oil pressure from calibration table.
 *
 * Performs linear interpolation on the pressure_table to convert measured
 * resistance to oil pressure in bar. Handles extrapolation beyond table boundaries.
 *
 * @param r_measured Measured resistance in Ohms
 * @return Interpolated pressure in bar, or ADC_FAIL_VALUE if out of range
 */
float interpolate_pressure(float r_measured) {
    if (r_measured <= pressure_table[0].res) return pressure_table[0].value;
    if (r_measured >= pressure_table[PRESSURE_TABLE_SIZE-1].res) return pressure_table[PRESSURE_TABLE_SIZE-1].value;

    if(r_measured >= pressure_table[PRESSURE_TABLE_SIZE - 1].res){
        float r_range = pressure_table[PRESSURE_TABLE_SIZE - 1].res - pressure_table[PRESSURE_TABLE_SIZE - 2].res;
        float t_range = pressure_table[PRESSURE_TABLE_SIZE - 1].value - pressure_table[PRESSURE_TABLE_SIZE - 2].value;
        return pressure_table[PRESSURE_TABLE_SIZE - 1].value + (r_measured - pressure_table[PRESSURE_TABLE_SIZE - 1].res) * (t_range / r_range);
    }

    for (int i = 0; i < PRESSURE_TABLE_SIZE - 1; i++) {
        if (r_measured >= pressure_table[i].res && r_measured < pressure_table[i+1].res) {
            float r_range = pressure_table[i+1].res - pressure_table[i].res;
            float t_range = pressure_table[i+1].value - pressure_table[i].value;
            return pressure_table[i].value + (r_measured - pressure_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

/**
 * @brief Convert raw ADC voltage to sensor resistance with safety checks.
 *
 * Calculates sensor resistance from measured voltage using voltage divider formula.
 * Detects sensor errors (open circuit, short circuit) and returns ADC_FAIL_VALUE.
 * Accounts for 100Ω protective series resistor in sensor circuit.
 *
 * @param raw_voltage Raw ADC reading in millivolts
 * @param r_pullup Pull-up resistor value in Ohms
 * @return Calculated sensor resistance in Ohms, or ADC_FAIL_VALUE on error
 */
float raw_to_res_safe(float raw_voltage, float r_pullup) {
    float v_adc = raw_voltage / 1000.0f;
    // Check: If voltage approaches 3.3V -> sensor open or broken cable
    if (v_adc >= ADC_MAX_V_VALID || v_adc <= 0.01f) return ADC_FAIL_VALUE; // Error signal
    return ((v_adc * r_pullup) / (get_adc_reference_voltage() - v_adc) ) - 100.0;  // -100 Ohm becuse a resistor with 100 ohm is in row with the sensor to protect against short circuit
}

float get_adc_volt() {
    // Read battery voltage (board voltage with divider)
    float raw = (float) read_adc_value_raw(ADC_12V);
    float v_board = raw / 1000.0f; // Convert mV to V
    v_board = v_board * ((ADC_VOLT_PULLUP + ADC_VOLT_PULLDOWN) / ADC_VOLT_PULLDOWN);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC board voltage: %.2f V | ADC value: %.2f V", v_board, raw / 1000.0f);
    printLog(log_msg);
    return v_board;
}

float get_adc_volt_bel() {
    // Read brightness/light sensor voltage
    float raw = (float) read_adc_value_raw(ADC_AMBI);
    float v_bel = raw / 1000.0f; 
    v_bel = v_bel * ((ADC_VOLT_BEL_PULLUP + ADC_VOLT_BEL_PULLDOWN) / ADC_VOLT_BEL_PULLDOWN); // Teiler 10k/2.2k
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC brightness: %.2f V | ADC value: %.2f V", v_bel, raw / 1000.0f);
    printLog(log_msg);
    return v_bel;
}

float get_adc_oil_temp() {
    // Read oil temperature
    float raw = (float) read_adc_value_raw(ADC_OIL_TEMPERATURE);
    float oil_t = raw_to_res_safe(raw, ADC_TEMP_PULLUP);
    if (oil_t < ADC_TEMP_VAL_TO_FAIL_MIN) oil_t = ADC_FAIL_VALUE; // Error (open circuit)
    else oil_t = interpolate_temp(oil_t);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC oil temperature: %.1f °C | resistor value: %.2f", oil_t, raw_to_res_safe(raw, ADC_TEMP_PULLUP));
    printLog(log_msg);
    return oil_t;
}

float get_adc_oil_press() {
    // Read oil pressure
    float raw = (float) read_adc_value_raw(ADC_OIL_PRESSURE);
    float oil_p = raw_to_res_safe(raw, ADC_PRES_PULLUP);
    if (oil_p < ADC_PRES_VAL_TO_FAIL_MIN || oil_p > ADC_PRES_VAL_TO_FAIL_MAX) oil_p = ADC_FAIL_VALUE; // Error or implausible reading
    else oil_p = interpolate_pressure(oil_p);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC oil pressure: %.1f bar | resistor value: %.2f", oil_p, raw_to_res_safe(raw, ADC_PRES_PULLUP));
    printLog(log_msg);
    return oil_p;
}

float get_adc_outside_temp() {
    // Read outdoor temperature
    float raw = (float) read_adc_value_raw(ADC_OUT_TEMPERATURE);
    float outside_t = raw_to_res_safe(raw, ADC_OUT_TEMP_PULLUP);
    if (outside_t < ADC_OUT_TEMP_VAL_TO_FAIL_MIN || outside_t > ADC_OUT_TEMP_VAL_TO_FAIL_MAX) outside_t = ADC_FAIL_VALUE; // Error or implausible reading
    else outside_t = interpolate_outside_temp(outside_t);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC outside temperature: %.1f °C | resistor value: %.2f", outside_t, raw_to_res_safe(raw, ADC_OUT_TEMP_PULLUP));
    printLog(log_msg);
    return outside_t;
}

/**
 * Measure and update the ADC reference voltage dynamically.
 *
 * Reads the reference voltage using the dedicated ADC channel with voltage divider, calculates the actual reference voltage,
 * and updates the global reference_voltage variable for use in raw_to_res_safe().
 */
float get_adc_reference_voltage(void) {
    char log_msg[50];
    float reference_voltage = ((float) read_adc_value_raw(ADC_3V3)) / 1000.0f;
    float volate_divider = (ADC_3V3_PULLUP + ADC_3V3_PULLDOWN) / ADC_3V3_PULLDOWN; // Teiler 1k/1k
    snprintf(log_msg, sizeof(log_msg), "Measured ADC reference voltage: %.2f V", reference_voltage*volate_divider);    
    printLog(log_msg);
    return reference_voltage*volate_divider; // Multiply by voltage divider because of voltage divider on the reference measurement
}