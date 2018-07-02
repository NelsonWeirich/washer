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

void initSensor_NivelAgua(void) {
// 	// Configuration struct
//   struct adc_config config_adc;
// 	// Initialize the ADC configuration struct
//   adc_get_config_defaults(&config_adc);
// 	// Change the ADC module configuration to suilt the application
// #if (!SAML21) && (!SAML22) && (!SAMC21)
//   config_adc.gain_factor = ADC_GAIN_FACTOR_DIV2;
// #endif
//   config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
//   config_adc.reference = ADC_REFERENCE_INTVCC1;
// #if (SAMC21)
//   config_adc.positive_input = ADC_POSITIVE_INPUT_PIN5;
// #else
//   config_adc.positive_input = ADC_POSITIVE_INPUT_PIN6;
// #endif
//   config_adc.resolution = ADC_RESOLUTION_12BIT;
//   // Set ADC configurations
// #if (SAMC21)
//   adc_init(&adc_instance, ADC1, &config_adc);
// #else
//   adc_init(&adc_instance, ADC, &config_adc);
// #endif
//   // Enable the ADC module
//   adc_enable(&adc_instance);
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

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>

struct adc_sync_descriptor ADC_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(PB00, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PB00, PINMUX_PB00B_ADC_AIN8);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void system_init(void)
{
	init_mcu();

	ADC_0_init();
}
