#include "adc.h"



adc_oneshot_unit_handle_t adc_handle;
adc_cali_handle_t cali_handle = NULL;



void adc_init() {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_2,
    };
    adc_oneshot_new_unit(&init_config, &adc_handle);

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,  // meist 12 Bit
        .atten = ADC_ATTEN_DB_11           // für größere Spannungen (bis ~3.3V)
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_3, &config);

    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_2,
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    adc_cali_create_scheme_curve_fitting(&cali_config, &cali_handle);

}

void read_adc_value() {
    int raw = 0;
    adc_oneshot_read(adc_handle, ADC_CHANNEL_3, &raw);
    printf("ADC raw - voltage reference: %d\n", raw);
    int voltage = 0;
    adc_cali_raw_to_voltage(cali_handle, raw, &voltage);
    printf("Voltage: %d mV\n", voltage*2); // da Spannungsteiler 1:2
}