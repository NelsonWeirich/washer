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

/*! Store ADC samples in buffer asynchronously */
#define ADC_SAMPLES 128
uint16_t adc_result_buffer[ADC_SAMPLES];

volatile bool adc_read_done = false;

/*! Function callback of the ADC */
void adc_complete_callback (struct adc_module *const module) {
	adc_read_done = true;
}

void configure_adc(void) {
	// Configuration struct
  struct adc_config config_adc;
	// Initialize the ADC configuration struct
  adc_get_config_defaults(&config_adc);
	// Change the ADC module configuration to suilt the application
#if (!SAML21) && (!SAML22) && (!SAMC21)
  config_adc.gain_factor = ADC_GAIN_FACTOR_DIV2;
#endif
  config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
  config_adc.reference = ADC_REFERENCE_INTVCC1;
#if (SAMC21)
  config_adc.positive_input = ADC_POSITIVE_INPUT_PIN5;
#else
  config_adc.positive_input = ADC_POSITIVE_INPUT_PIN6;
#endif
  config_adc.resolution = ADC_RESOLUTION_12BIT;
  // Set ADC configurations
#if (SAMC21)
  adc_init(&adc_instance, ADC1, &config_adc);
#else
  adc_init(&adc_instance, ADC, &config_adc);
#endif
  // Enable the ADC module
  adc_enable(&adc_instance);
}

/*! Register and enable the ADC Read Buffer Complete callback handler */
void configure_adc_callbacks(void) {
	adc_register_callback(&adc_instance, adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
  adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
}

//CHANGED
/*! Inicializa o sensor */
void initSensor_NivelAgua(void){
	configure_adc();
	configure_adc_callbacks();
}

/*! \brief Retorna o valor convertido do ADC
 *  \param Sensor inteiro identificador do pino do sensor
 *  \return valor lido do sensor e convertido para um valor entre 0-2047
 */
int  valorAtualSensor(int Sensor){
	//Le do adc.
	// static int count = 0, count2 = 0;
	// Start an asynchronous ADC conversion
	adc_read_buffer_job(&adc_instance, adc_result_buffer, ADC_SAMPLES);

  // Wait until the asynchronous conversion is complete
	while (adc_read_done == false) {}

	if(zero <= valor_adc < 128 ){
		return SENSOR_NIVEL_ZERO /*!< 0 */
	}else

	if(128 <= valor_adc < 700){
		return SENSOR_NIVEL_BAIXO /*!< 512 */
	}else

	if(700 <= valor_adc < 1128){
		return SENSOR_NIVEL_MEDIO /*!< 1023 */
	}else

	if(1128 <= valor_adc < 1700){
		return SENSOR_NIVEL_ALTO /*!< 1540 */
	}else

	if(1700 <= valor_adc){
		return SENSOR_NIVEL_FULL /*!< 2047 */
	}

	// if(count2 > 250){
	// 	if(count > 600){
	// 		count = 0;
	// 	}else{
	// 		count++;
	// 	}
	// 	count2 = 0;
	// }else{
	// 	count2++;
	// }
	// return count;
}
