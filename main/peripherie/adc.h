#include "esp_adc/adc_oneshot.h"
#include "../individual_config.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "../logging/logging.h"

/**
 * @brief Lookup table entry for sensor calibration.
 *
 * Pairs a physical value with its corresponding electrical resistance.
 */
typedef struct {
    float value;  /**< Temperature (°C) or Pressure (bar) value */
    float res;    /**< Resistance in Ohms */
} lookup_values_t;

/**
 * @brief ADC channel selection enumeration.
 *
 * Identifies which sensor input to read from the ADC.
 */
typedef enum {
    ADC_OIL_PRESSURE = 0,       /**< Oil pressure sensor input */
    ADC_OIL_TEMPERATURE = 1,    /**< Oil temperature sensor input */
    ADC_OUT_TEMPERATURE = 2,    /**< Outdoor temperature sensor input */
    ADC_12V = 3,                /**< Battery voltage (12V supply) input */
    ADC_AMBI = 4,               /**< Ambient light sensor input */
    ADC_3V3 = 5,                /**< 3.3V reference voltage input */
    MAX_ABC_NBR                 /**< Must ALWAYS be the last enum value */
} adc_selection;

/**
 * @brief ADC channel handle and configuration structure.
 *
 * Contains the hardware handles and configuration for a single ADC channel.
 */
typedef struct {
    adc_channel_t channel;                  /**< ESP-IDF ADC channel identifier */
    adc_oneshot_chan_cfg_t chan_config;     /**< Channel configuration */
    adc_oneshot_unit_handle_t adc_handle;   /**< ADC unit handle */
    adc_cali_handle_t cali_handle;          /**< Calibration handle */
} adc_handles_t;

extern adc_oneshot_unit_init_cfg_t init_config[ADC_UNIT_NUMBER];
extern adc_oneshot_unit_handle_t adc_handler[ADC_UNIT_NUMBER];
extern adc_cali_curve_fitting_config_t cali_config[ADC_UNIT_NUMBER];
extern adc_cali_handle_t cali_handler[ADC_UNIT_NUMBER];
extern adc_handles_t adc_handles[MAX_ABC_NBR - 1];

extern const lookup_values_t oil_temp_table[];         /**< Oil temperature calibration table */
extern const lookup_values_t outside_temperature_table[];  /**< Outdoor temperature calibration table */
extern const lookup_values_t pressure_table[];        /**< Oil pressure calibration table */

#define OIL_TABLE_SIZE (sizeof(oil_temp_table) / sizeof(lookup_values_t))
#define OUTSIDE_TABLE_SIZE (sizeof(outside_temperature_table) / sizeof(lookup_values_t))
#define PRESSURE_TABLE_SIZE (sizeof(pressure_table) / sizeof(pressure_table[0]))

/**
 * @brief Initialize ADC hardware and calibration.
 */
void adc_init(void);

/**
 * @brief Read raw calibrated ADC value.
 *
 * @param adc_sel ADC channel selector
 * @return Voltage in millivolts
 */
int read_adc_value_raw(adc_selection adc_sel);

/**
 * @brief Read battery voltage from ADC.
 *
 * Applies voltage divider calculation to convert measured value to actual system voltage.
 *
 * @return Battery voltage in volts
 */
float get_adc_volt(void);

/**
 * @brief Read brightness/light sensor voltage from ADC.
 *
 * Applies voltage divider calculation to convert measured brightness sensor value.
 *
 * @return Brightness voltage in volts (used for day/night mode detection)
 */
float get_adc_volt_bel(void);

/**
 * @brief Read oil temperature from ADC using NTC thermistor calibration.
 *
 * Reads raw ADC value, converts to resistance, and interpolates temperature
 * from calibration table.
 *
 * @return Oil temperature in °C
 */
float get_adc_oil_temp(void);

/**
 * @brief Read oil pressure from ADC using calibration table.
 *
 * Reads raw ADC value, converts to resistance, and interpolates pressure
 * from calibration table.
 *
 * @return Oil pressure in bar
 */
float get_adc_oil_press(void);

/**
 * @brief Read outdoor temperature from ADC using NTC thermistor calibration.
 *
 * Reads raw ADC value, converts to resistance, and interpolates temperature
 * from calibration table.
 *
 * @return Outdoor temperature in °C
 */
float get_adc_outside_temp(void);

/**
 * @brief Measure and update the ADC reference voltage dynamically.
 *
 * Reads the reference voltage from internal adc.
 * Used for accurate voltage divider calculations with varying supply voltage.
 *
 * @return Current reference voltage in volts
 */
float get_adc_reference_voltage(void);
