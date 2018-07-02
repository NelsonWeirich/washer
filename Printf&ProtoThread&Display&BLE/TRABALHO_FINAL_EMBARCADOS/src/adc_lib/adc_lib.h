 /**
  * \file adc_lib.h
  * \brief Biblioteca do ADC
  * \details Funções para manipulação do ADC para uso
  * de entrada analógica.
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 25/06/2018 16:45:19
  * \copyright GNU Public License
  */


#ifndef ADC_LIB_H_
#define ADC_LIB_H_

#include <asf.h>
#include "adc_configure.h"
#include "adc_temp.h"

//CHANGED: Definido o pino do adc. EXT1[3] - PB00_AIN8 - ADC+
#define SENSOR_NIVEL_PIN      PIN_PB00B_ADC_AIN8 /*!< Pino para conexão do potenciômetro. */

//CHANGED: Definido valores que devem vir do adc
//Valores a serem compardos no main com o valor que sai do adc.
//Tipo nivel baixo o adc retorna 500, logo compara com 500.
#define SENSOR_NIVEL_ZERO     0
#define SENSOR_NIVEL_BAIXO    512
#define SENSOR_NIVEL_MEDIO    1023
#define SENSOR_NIVEL_ALTO     1540
#define SENSOR_NIVEL_FULL     2047

void initSensor_NivelAgua(void);   //inicializa os sensores
int  valorAtualSensor(int Sensor); //retorna o nivel da agua

#endif /* ADC_LIB_H_ */
