/**
 * \file adc_lib.c
 * \brief Biblioteca do ADC
 * \details Funções para manipulação do ADC para uso
 * de entrada analógica.
 *
 * \author Eduardo Capellari Culau
 * \author Nelson Roberto Weirich Junior
 *
 * \date 29/06/2018 16:24:32
 * \copyright GNU Public License
 */

//Incluir a lib
#include "adc_lib.h"

/*! Store ADC driver state */
struct adc_module adc_instance;

//CHANGED
/*! Inicializa o sensor */
void initSensor_NivelAgua(void){
  // Configuration struct
  struct adc_config config_adc;

  // Initialize the ADC configuration struct
  adc_get_config_defaults(&config_adc);

  // config_adc.clock_source    = GCLK_GENERATOR_1;
  // config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;
  // config_adc.reference       = ADC_REFERENCE_INT1V;
  config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN8; //SENSOR_NIVEL_PIN;
  config_adc.negative_input  = ADC_NEGATIVE_INPUT_GND;
  config_adc.sample_length    = 1;

  system_voltage_reference_enable(ADC_REFERENCE_INT1V);

  // Set ADC configurations defaults
  adc_init(&adc_instance, ADC, &config_adc);

  // ADC->AVGCTRL.reg = ADC_AVGCTRL_ADJRES(2) | ADC_AVGCTRL_SAMPLENUM_4;
  // Enable the ADC module
  adc_enable(&adc_instance);
}

/*! \brief Retorna o valor convertido do ADC
 *  \param Sensor inteiro identificador do pino do sensor
 *  \return valor lido do sensor e convertido para um valor entre 0-2047
 */
int  valorAtualSensor(int Sensor){
	uint16_t valor_adc;

	//Start conversion
	adc_start_conversion(&adc_instance);

  // Wait until the conversion is complete
	do {

	}	while (adc_read(&adc_instance, &valor_adc) == STATUS_BUSY);

  int count = 0, count2 = 0;

  if(count2 > 250){
  	if(count > 600){
  		count = 0;
  	}else{
  		count++;
  	}
  	count2 = 0;
  }else{
  	count2++;
  }
  return count;
////////////////////////////////////////
	if(0 <= valor_adc < 128 ){
		return SENSOR_NIVEL_ZERO; /*!< 0 */
	}else

	if(128 <= valor_adc < 700){
		return SENSOR_NIVEL_BAIXO; /*!< 512 */
	}else

	if(700 <= valor_adc < 1128){
		return SENSOR_NIVEL_MEDIO; /*!< 1023 */
	}else

	if(1128 <= valor_adc < 1700){
		return SENSOR_NIVEL_ALTO; /*!< 1540 */
	}else

	if(1700 <= valor_adc){
		return SENSOR_NIVEL_FULL; /*!< 2047 */
	}

}
