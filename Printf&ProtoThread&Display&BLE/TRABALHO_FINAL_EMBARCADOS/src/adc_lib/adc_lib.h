/*
 * adc_lib.h
 *
 * Created: 25/06/2018 16:45:19
 *  Author: Eduardo Culau
 */


#ifndef ADC_LIB_H_
#define ADC_LIB_H_


//Só inclui todas as libs.
#include <asf.h>
#include "adc_configure.h"
#include "adc_temp.h"

//CHANGED : Definido o pino do adc. EXT1[3] - PB00_AIN8 - ADC+
//Pino do potenciomentro que vai ser o sensor de nivel da agua.
#define SENSOR_NIVEL_PIN      PIN_PB00B_ADC_AIN8

//TODO :Definir valores que devem vir do pot.
//Valores a serem compardos no main com o valor que sai do adc.
//Tipo n�vel baixo o adc retorna 500, logo compara com 500.
#define SENSOR_NIVEL_ZERO     0
#define SENSOR_NIVEL_BAIXO    500
#define SENSOR_NIVEL_MEDIO    1500
#define SENSOR_NIVEL_ALTO     3000
#define SENSOR_NIVEL_FULL     -1

//TODO : Fazer fun��es abaixo.
void initSensor_NivelAgua(void);   //Inicializar tudo, mede e tals.
int  valorAtualSensor(int Sensor);      //Aqui dentro tem um if, ela s� retorna os defines.

//Se o adc for por pooling valorAtualSensor deve fazer a medido, se for por DMA, ela deve s� ser a variave(memoria) compartilhada.

#endif /* ADC_LIB_H_ */
