/*
 * ============================================================================
 * I2C INTERFACE - RTC & ADC Device Communication Implementation
 * ============================================================================
 *
 * Author: Jan Niklas Rodewald (JRO)
 * Date: 01.04.2026
 *
 * ============================================================================
 * CHANGELOG
 * ============================================================================
 * v1.0 (01.04.2026) - Initial implementation
 *      - DS3231 real-time clock interface
 *      - ADS1115 ADC for analog sensor readings
 *      - NTC temperature table interpolation
 *      - Button control for time adjustment
 *      - Dual ADC support for enhanced sensor coverage
 *
 */

#include "i2cFunctions.h"

i2c_master_bus_config_t bus_cfg = {0};
i2c_master_bus_handle_t bus_handle = NULL;

/* RTC (DS3231) Configuration */
i2c_device_config_t ds3231_cfg = {0};
i2c_master_dev_handle_t ds3231_handle = NULL;

/* ADC (ADS1115) Configuration */
i2c_device_config_t ads_cfg[NUMBER_OF_ADS1115_DEVICES] = {0};
i2c_master_dev_handle_t ads_handle[NUMBER_OF_ADS1115_DEVICES];

/* Time adjustment buttons: [0] = Hour, [1] = Minute */
button_config_t cfg_time[2] = {0};
button_gpio_config_t gpio_cfg_time[2] = {0};
button_handle_t btn_time[2] = {0};

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

bool testmode_activated = false;
TickType_t testmode_activation_time = 0;
int testmode_activation_count = 0;
int testmode_activation_state = 0;

/**
 * ADC reference voltage for resistance calculations.
 * Defaults to ADC_ADS_REF_V, but can be updated dynamically via get_i2c_adc_reference_voltage().
 */
float reference_voltage = ADC_ADS_REF_V;

/**
 * Initialize I2C bus and attach RTC and ADC devices.
 *
 * Sets up DS3231 and ADS1115 devices on the I2C bus, including multi-device support.
 */
void init_i2c() {
    // Configure I2C bus
    bus_cfg.clk_source = I2C_CLK_SRC;
    bus_cfg.i2c_port = I2C_PORT;
    bus_cfg.scl_io_num = I2C_SCL_PIN;
    bus_cfg.sda_io_num = I2C_SDA_PIN;
    bus_cfg.glitch_ignore_cnt = I2C_GLITCH_IGNORE;
    bus_cfg.flags.enable_internal_pullup = I2C_INT_PULLUP_ENB;

    // Configure RTC (DS3231)
    ds3231_cfg.dev_addr_length = RTC_ADDR_LENGTH;
    ds3231_cfg.device_address = RTC_DS3231_ADDR;
    ds3231_cfg.scl_speed_hz = RTC_SCL_SPEED_HZ;
    
    // Configure ADC (ADS1115) devices
    for (int i = 0; i < NUMBER_OF_ADS1115_DEVICES; i++) {
        ads_cfg[i].dev_addr_length = ADC_ADS1115_ADDR_LENGTH;
        ads_cfg[i].scl_speed_hz = ADC_ADS1115_SCL_SPEED_HZ; // ADS1115 supports up to 400kHz
    }
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ds3231_cfg, &ds3231_handle));

    // ADS1115
    ads_cfg[0].device_address = ADC_ADS1115_1_ADDR;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg[0], &ads_handle[0]));

    #if NUMBER_OF_ADS1115_DEVICES > 1
        ads_cfg[1].device_address = ADC_ADS1115_2_ADDR;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ads_cfg[1], &ads_handle[1]));
    #endif
}

inline uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
inline uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) | (val % 10); }

void sync_rtc_to_system() {
    uint8_t data[7];
    uint8_t reg = 0x00;  // RTC start register (Seconds)

    // Read 7 bytes of time data
    i2c_master_transmit_receive(ds3231_handle, &reg, 1, data, 7, 1000);

    struct tm tm = {
        .tm_sec  = bcd2dec(data[0] & 0x7F),
        .tm_min  = bcd2dec(data[1]),
        .tm_hour = bcd2dec(data[2] & 0x3F), // 24-hour format
        .tm_mday = bcd2dec(data[4]),
        .tm_mon  = bcd2dec(data[5] & 0x1F) - 1, // tm_mon is 0-11
        .tm_year = bcd2dec(data[6]) + 100,      // tm_year is years since 1900
    };

    // Convert to Unix timestamp
    time_t t = mktime(&tm);
    
    // Set ESP32 system time
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);
}

/**
 * Write the given time struct into the DS3231 RTC.
 *
 * @param time Pointer to struct tm containing the desired time to set.
 * @return ESP_OK on success, error code otherwise.
 */
esp_err_t ds3231_set_time(struct tm *time) {
    uint8_t data[8];
    data[0] = 0x00;  // RTC register address (Seconds)
    
    data[1] = dec2bcd(time->tm_sec);
    data[2] = dec2bcd(time->tm_min);
    data[3] = dec2bcd(time->tm_hour); // Bit 6 must be 0 for 24-hour format
    data[4] = dec2bcd(time->tm_wday + 1); // Day of week (1-7)
    data[5] = dec2bcd(time->tm_mday);
    data[6] = dec2bcd(time->tm_mon + 1); // DS3231 uses 1-12
    data[7] = dec2bcd(time->tm_year % 100); // Only last two digits (e.g., 26 for 2026)

    // Send 8 bytes (register address + 7 bytes of time data)
    return i2c_master_transmit(ds3231_handle, data, 8, -1);
}

/**
 * Button callback for single-click forward adjustments.
 *
 * Implements the activation sequence for test mode:
 * 1) minute minus twice
 * 2) hour minus once
 * 3) minute plus twice
 * 4) hour plus once -> toggle test mode
 * All within TESTMODE_ACTIVATE_TIMEOUT_MS (7 seconds).
 */
static void button_event_cb(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour + 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour incremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 4) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_4_COUNT) {
                    testmode_activation_state = -1;
                    testmode_activation_count = 0;
                    testmode_activated = !testmode_activated; // Toggle test mode
                    printWarningLog(testmode_activated == true ? "Test mode ACTIVATED!" : "Test mode DEACTIVATED!");
                }
            }
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min + 1 + 60) % 60;
        if (timeinfo.tm_min == 0) { 
            timeinfo.tm_hour = (timeinfo.tm_hour + 1) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour incremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute incremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == 3) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_3_COUNT) {
                    testmode_activation_state = 4;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }

    ds3231_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

/**
 * Button callback for single-click backward adjustments.
 *
 * Handles the reverse time-decrement path as part of the testmode activation sequence.
 */
static void button_event_cb_back(void *btn_handle, void *usr_data) {
    int button_id = (int)usr_data;
    time_t now;
    struct tm timeinfo;
    char log_msg[50];
    
    // Get current ESP system time
    time(&now);
    localtime_r(&now, &timeinfo);

    if (button_id == BUTTON_CLOCK_HOUR_PIN) {
        timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
        snprintf(log_msg, sizeof(log_msg), "Hour decremented: %d", timeinfo.tm_hour);
        printLog(log_msg);

        if (testmode_activation_state == 2) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_2_COUNT) {
                    testmode_activation_state = 3;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    } else if (button_id == BUTTON_CLOCK_MINUTE_PIN) {
        timeinfo.tm_min = (timeinfo.tm_min - 1 + 60) % 60;
        if (timeinfo.tm_min == 59) { 
            timeinfo.tm_hour = (timeinfo.tm_hour - 1 + 24) % 24;
            snprintf(log_msg, sizeof(log_msg), "Hour decremented due to minute: %d", timeinfo.tm_hour);
            printLog(log_msg);
        }
        timeinfo.tm_sec = 0; // Reset seconds when setting time
        snprintf(log_msg, sizeof(log_msg), "Minute decremented: %d", timeinfo.tm_min);
        printLog(log_msg);

        if (testmode_activation_state == -1) {
            testmode_activation_state = 0;
            testmode_activation_time = xTaskGetTickCount();
            testmode_activation_count = 1;
        }
        else if (testmode_activation_state == 0) {
            if (xTaskGetTickCount() - testmode_activation_time < pdMS_TO_TICKS(TESTMODE_ACTIVATE_TIMEOUT_MS)) {
                testmode_activation_count++;
                if (testmode_activation_count >= TESTMODE_ACTIVATE_BUTTON_1_COUNT) {
                    testmode_activation_state = 2;
                    testmode_activation_count = 0;
                }
            } 
            else {
                testmode_activation_time = 0;
                testmode_activation_count = 0;
                testmode_activation_state = -1;
            }
        }
        else {
            testmode_activation_time = 0;
            testmode_activation_count = 0;
            testmode_activation_state = -1;
        }
    }

    // Write to RTC
    ds3231_set_time(&timeinfo);
    
    // Synchronize system time (so ESP32 knows immediately)
    struct timeval tv = { .tv_sec = mktime(&timeinfo), .tv_usec = 0 };
    settimeofday(&tv, NULL);
}

void init_time_buttons() {

    cfg_time[0].short_press_time = BUTTON_CLOCK_MINUTE_SHORT_MS;
    cfg_time[0].long_press_time = BUTTON_CLOCK_MINUTE_LONG_MS;
    gpio_cfg_time[0].gpio_num = BUTTON_CLOCK_HOUR_PIN;
    gpio_cfg_time[0].active_level = BUTTON_CLOCK_MINUTE_ACTIVE_LEVEL;    
    cfg_time[1].short_press_time = BUTTON_CLOCK_HOUR_SHORT_MS;
    cfg_time[1].long_press_time = BUTTON_CLOCK_HOUR_LONG_MS;
    gpio_cfg_time[1].gpio_num = BUTTON_CLOCK_MINUTE_PIN;
    gpio_cfg_time[1].active_level = BUTTON_CLOCK_HOUR_ACTIVE_LEVEL;

    iot_button_new_gpio_device(&cfg_time[0], &gpio_cfg_time[0], &btn_time[0]);
    iot_button_register_cb(btn_time[0], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_register_cb(btn_time[0], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_HOUR_PIN);
    iot_button_new_gpio_device(&cfg_time[1], &gpio_cfg_time[1], &btn_time[1]);
    iot_button_register_cb(btn_time[1], BUTTON_SINGLE_CLICK, NULL, button_event_cb, (void*)BUTTON_CLOCK_MINUTE_PIN);
    iot_button_register_cb(btn_time[1], BUTTON_LONG_PRESS_START, NULL, button_event_cb_back, (void*)BUTTON_CLOCK_MINUTE_PIN);
}

/**
 * Read raw ADC data from ADS1115 on a specific channel.
 *
 * @param dev ADS1115 device handle.
 * @param channel ADC channel index (0..3).
 * @param pga_setting PGA configuration bits.
 * @return Signed 16-bit ADC conversion value.
 */
int16_t read_ads1115(i2c_master_dev_handle_t dev, uint8_t channel, uint16_t pga_setting) {
    // Ensure channel is only 0-3
    uint16_t mux = (0x04 | (channel & 0x03)) << 12; // 0x4000, 0x5000, 0x6000 or 0x7000
    uint16_t pga = (pga_setting & 0x07) << 9;
    
    // Bit 15: OS = 1 (Start conversion)
    // Bit 8: Mode = 1 (Single-shot mode)
    // Bits 7-5: Data Rate = 100 (128 SPS)
    // Bits 4-0: Default values (0x03)
    uint16_t config = 0x8000 | mux | pga | 0x0100 | 0x0080 | 0x0003;
    
    uint8_t tx_buf[3] = { 0x01, (uint8_t)(config >> 8), (uint8_t)(config & 0xFF) };

    // 1. Send configuration
    ESP_ERROR_CHECK(i2c_master_transmit(dev, tx_buf, 3, -1));

    // 2. Wait (128 SPS requires ~8ms, 15ms is absolutely safe)
    vTaskDelay(pdMS_TO_TICKS(15)); 

    // 3. Read conversion result register
    uint8_t reg_addr = 0x00;
    uint8_t rx_buf[2];
    ESP_ERROR_CHECK(i2c_master_transmit_receive(dev, &reg_addr, 1, rx_buf, 2, -1));

    return (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
}

// Linear interpolation for oil temperature table
/**
 * Interpolate temperature from oil NTC table.
 *
 * @param r_measured Measured resistance in Ohm.
 * @return Interpolated temperature in °C or ADC_FAIL_VALUE for invalid.
 */
float interpolate_temp(float r_measured) {
    if (r_measured >= oil_temp_table[0].res) return oil_temp_table[0].temp;
    if (r_measured <= oil_temp_table[OIL_TABLE_SIZE-1].res) return oil_temp_table[OIL_TABLE_SIZE-1].temp;

    for (int i = 0; i < OIL_TABLE_SIZE - 1; i++) {
        if (r_measured <= oil_temp_table[i].res && r_measured > oil_temp_table[i+1].res) {
            float r_range = oil_temp_table[i+1].res - oil_temp_table[i].res;
            float t_range = oil_temp_table[i+1].temp - oil_temp_table[i].temp;
            return oil_temp_table[i].temp + (r_measured - oil_temp_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

// Linear interpolation for outdoor temperature table
/**
 * Interpolate temperature from outside NTC table.
 *
 * @param r_measured Measured resistance in Ohm.
 * @return Interpolated temperature in °C or ADC_FAIL_VALUE for invalid.
 */
float interpolate_outside_temp(float r_measured) {
    if (r_measured >= outside_temperature_table[0].res) return outside_temperature_table[0].temp;
    if (r_measured <= outside_temperature_table[OUTSIDE_TABLE_SIZE-1].res) return outside_temperature_table[OUTSIDE_TABLE_SIZE-1].temp;

    for (int i = 0; i < OUTSIDE_TABLE_SIZE - 1; i++) {
        if (r_measured <= outside_temperature_table[i].res && r_measured > outside_temperature_table[i+1].res) {
            float r_range = outside_temperature_table[i+1].res - outside_temperature_table[i].res;
            float t_range = outside_temperature_table[i+1].temp - outside_temperature_table[i].temp;
            return outside_temperature_table[i].temp + (r_measured - outside_temperature_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

// Linear interpolation for pressure table
/**
 * Interpolate pressure from outside NTC table.
 *
 * @param r_measured Measured resistance in Ohm.
 * @return Interpolated pressure in bar or ADC_FAIL_VALUE for invalid.
 */
float interpolate_pressure(float r_measured) {
    if (r_measured <= pressure_table[0].res) return pressure_table[0].temp;
    if (r_measured >= pressure_table[PRESSURE_TABLE_SIZE-1].res) return pressure_table[PRESSURE_TABLE_SIZE-1].temp;

    if(r_measured >= pressure_table[PRESSURE_TABLE_SIZE - 1].res){
        float r_range = pressure_table[PRESSURE_TABLE_SIZE - 1].res - pressure_table[PRESSURE_TABLE_SIZE - 2].res;
        float t_range = pressure_table[PRESSURE_TABLE_SIZE - 1].temp - pressure_table[PRESSURE_TABLE_SIZE - 2].temp;
        return pressure_table[PRESSURE_TABLE_SIZE - 1].temp + (r_measured - pressure_table[PRESSURE_TABLE_SIZE - 1].res) * (t_range / r_range);
    }

    for (int i = 0; i < PRESSURE_TABLE_SIZE - 1; i++) {
        if (r_measured >= pressure_table[i].res && r_measured < pressure_table[i+1].res) {
            float r_range = pressure_table[i+1].res - pressure_table[i].res;
            float t_range = pressure_table[i+1].temp - pressure_table[i].temp;
            return pressure_table[i].temp + (r_measured - pressure_table[i].res) * (t_range / r_range);
        }
    }
    return ADC_FAIL_VALUE;
}

/**
 * Convert raw ADS1115 value to resistance, with validation.
 *
 * @param raw Raw ADC sample from ADS1115.
 * @param r_pullup Pull-up resistance value in Ohms.
 * @return Calculated resistance in Ohms or ADC_FAIL_VALUE on error.
 */
float raw_to_res_safe(int16_t raw, float r_pullup) {
    float v_adc = (raw * LSB_4096) / 1000.0f;
    // Check: If voltage approaches 3.3V -> sensor open or broken cable
    if (v_adc >= ADC_MAX_V_VALID || v_adc <= 0.01f) return ADC_FAIL_VALUE; // Error signal
    return ((v_adc * r_pullup) / (reference_voltage - v_adc) ) - 100.0;  // -100 Ohm becuse a resistor with 100 ohm is in row with the sensor to protect against short circuit
}

float get_i2c_adc_volt() {
    // Read battery voltage (board voltage with divider)
    int16_t raw = read_ads1115(ads_handle[0], ADC_VOLT_ADS_CHANNEL, ADC_VOLT_ADS_PGA);
    float v_board = (raw * LSB_2048) / 1000.0f;
    v_board = v_board * ((ADC_VOLT_ADS_PULLUP + ADC_VOLT_ADS_PULLDOWN) / ADC_VOLT_ADS_PULLDOWN);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC board voltage: %.2f V | ADC value: %.2f", v_board, (raw * LSB_2048) / 1000.0f);
    printLog(log_msg);
    return v_board;
}

float get_i2c_adc_volt_bel() {
    // Read brightness/light sensor voltage
    int16_t raw = read_ads1115(ads_handle[0], ADC_VOLT_BEL_ADS_CHANNEL, ADC_VOLT_BEL_ADS_PGA);
    float v_bel = (raw * LSB_4096) / 1000.0f; 
    v_bel = v_bel * ((ADC_VOLT_BEL_ADS_PULLUP + ADC_VOLT_BEL_ADS_PULLDOWN) / ADC_VOLT_BEL_ADS_PULLDOWN); // Teiler 10k/2.2k
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC brightness: %.2f V | ADC value: %.2f", v_bel, (raw * LSB_4096) / 1000.0f);
    printLog(log_msg);
    return v_bel;
}

float get_i2c_adc_oil_temp() {
    // Read oil temperature
    int16_t raw = read_ads1115(ads_handle[0], ADC_TEMP_ADS_CHANNEL, ADC_TEMP_ADS_PGA);
    float oil_t = raw_to_res_safe(raw, ADC_TEMP_ADS_PULLUP);
    if (oil_t < ADC_TEMP_ADS_VAL_TO_FAIL_MIN) oil_t = ADC_FAIL_VALUE; // Error (open circuit)
    else oil_t = interpolate_temp(oil_t);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC oil temperature: %.1f °C | resistor value: %.2f", oil_t, raw_to_res_safe(raw, ADC_TEMP_ADS_PULLUP));
    printLog(log_msg);
    return oil_t;
}

float get_i2c_adc_oil_press() {
    // Read oil pressure
    int16_t raw = read_ads1115(ads_handle[0], ADC_PRES_ADS_CHANNEL, ADC_PRES_ADS_PGA);
    float oil_p = raw_to_res_safe(raw, ADC_PRES_ADS_PULLUP);
    if (oil_p < ADC_PRES_ADS_VAL_TO_FAIL_MIN || oil_p > ADC_PRES_ADS_VAL_TO_FAIL_MAX) oil_p = ADC_FAIL_VALUE; // Error or implausible reading
    else oil_p = interpolate_pressure(oil_p);
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "Measured ADC oil pressure: %.1f bar | resistor value: %.2f", oil_p, raw_to_res_safe(raw, ADC_PRES_ADS_PULLUP));
    printLog(log_msg);
    return oil_p;
}

float get_i2c_adc_outside_temp() {
    #if NUMBER_OF_ADS1115_DEVICES > 1
        // Read outdoor temperature
        int16_t raw = read_ads1115(ads_handle[1], ADC_OUT_TEMP_ADS_CHANNEL, ADC_OUT_TEMP_ADS_PGA); 
        float outside_t = raw_to_res_safe(raw, ADC_OUT_TEMP_ADS_PULLUP); 
        if (outside_t < ADC_OUT_TEMP_ADS_VAL_TO_FAIL_MIN || outside_t > ADC_OUT_TEMP_ADS_VAL_TO_FAIL_MAX) outside_t = ADC_FAIL_VALUE; 
        else outside_t = interpolate_outside_temp(outside_t);
        char log_msg[100];
        snprintf(log_msg, sizeof(log_msg), "Measured ADC outside temperature: %.1f °C | resistor value: %.2f", outside_t, raw_to_res_safe(raw, ADC_OUT_TEMP_ADS_PULLUP));
        printLog(log_msg);
        return outside_t;
    #else 
        return ADC_FAIL_VALUE;
    #endif
}

/**
 * Measure and update the ADC reference voltage dynamically.
 *
 * Reads the reference voltage from the second ADS1115 device (if available)
 * and updates the global reference_voltage variable for use in raw_to_res_safe().
 * If the measurement is out of valid range, defaults to ADC_ADS_REF_V.
 */
void get_i2c_adc_reference_voltage(void) {
    #if NUMBER_OF_ADS1115_DEVICES > 1
        int16_t raw = read_ads1115(ads_handle[1], ADC_VOLT_REF_CHANNEL, ADC_VOLT_REF_PGA);
        float v_ref = (raw * LSB_4096) / 1000.0f;
        if (v_ref <= ADC_ADS_REF_V_TO_FAIL_MIN || v_ref >= ADC_ADS_REF_V_TO_FAIL_MAX) {
            reference_voltage = ADC_ADS_REF_V; // Invalid reading
        }
        else {
            reference_voltage = v_ref; // Valid reading
        }
        char log_msg[50];
        snprintf(log_msg, sizeof(log_msg), "Measured ADC reference voltage: %.2f V", v_ref);
        //printLog(log_msg);
    #else
        reference_voltage = ADC_ADS_REF_V; // Return default reference voltage if second ADS1115 is not present
    #endif
}