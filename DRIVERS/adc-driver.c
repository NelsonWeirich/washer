/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#include <asf.h>
#include "adc-driver.h"

void adc_configure(uint8_t adc_num, uint8_t adc_res, uint16_t adc_freq) {
		
	adc_get_config_defaults(&config_vec[adc_num]);
		
	config_vec[adc_num].clock_source = adc_freq; //GCLK_GENERATOR_1;
	config_vec[adc_num].resolution = adc_res;
	config_vec[adc_num].positive_input = ADC_POSITIVE_INPUT_TEMP;

	adc_init(&adc_instance_vec[adc_num], ADC, &config_vec[adc_num]);
		
	ADC->AVGCTRL.reg = ADC_AVGCTRL_ADJRES(2) | ADC_AVGCTRL_SAMPLENUM_4;
		
	adc_enable(&adc_instance_vec[adc_num]);
}

uint16_t adc_reader(uint8_t adc_num, uint8_t adc_chan) {
	uint16_t adc_result = 0;
	
	adc_instance_vec[adc_num].reference = adc_chan;
	adc_start_conversion(&adc_instance_vec[adc_num]);
	while((adc_get_status(&adc_instance_vec[adc_num]) & ADC_STATUS_RESULT_READY) != 1);
	
	adc_read(&adc_instance_vec[adc_num], &adc_result);
	
	return adc_result;
}



