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
  //..
}

/*! \brief Retorna o valor convertido do ADC
 *  \param Sensor inteiro identificador do pino do sensor
 *  \return valor lido do sensor e convertido para um valor entre 0-2047
 */
int  valorAtualSensor(int Sensor){
  static int count = 0, count2 = 0;

// ////////////////////////////////////////
// 	if(0 <= valor_adc < 128 ){
// 		return SENSOR_NIVEL_ZERO; /*!< 0 */
// 	}else
//
// 	if(128 <= valor_adc < 700){
// 		return SENSOR_NIVEL_BAIXO; /*!< 512 */
// 	}else
//
// 	if(700 <= valor_adc < 1128){
// 		return SENSOR_NIVEL_MEDIO; /*!< 1023 */
// 	}else
//
// 	if(1128 <= valor_adc < 1700){
// 		return SENSOR_NIVEL_ALTO; /*!< 1540 */
// 	}else
//
// 	if(1700 <= valor_adc){
// 		return SENSOR_NIVEL_FULL; /*!< 2047 */
// 	}

  if(count2 > 250){
    if(count > SENSOR_NIVEL_FULL){
      count = 0;
    }else{
      count++;
    }
    count2 = 0;
  }else{
    count2++;
  }
  return count;
}
