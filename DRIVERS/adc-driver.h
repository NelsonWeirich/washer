/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#ifndef ADC_DRIVER_INCLUDED
#define ADC_DRIVER_INCLUDED

#include "tc.h"
#include "conf_test.h"
#include "adc.h"

// Configura adc
void adc_config(uint8_t adc_num, uint8_t adc_chan, uint8_t adc_res, uint16_t adc_freq);
// Le o valor de adc
uint16_t adc_read(uint8_t adc_num, uint8_t adc_chan);

#endif