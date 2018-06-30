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

//TODO : Definir pino do adc. Verificar se os modulos estão devidos corretos no asf wizzard.
//Pino do potenciomentor que vai ser o sensor de nivel da agua.
#define SENSOR_NIVEL_PIN      PIN_PB00 //Definir o pino para entrar no ADC. (Verificar manula para ver quais pinos o adc tem acesso e a tensão maxima).
//Dar uma olhada, mas se não me engado era para ser pinos 3 e 4 de cada conection EXT, logo vamos usar a EXT1 ou EXT2, então vai ser PB00 e PB01, ou PA20 e PA11.

//TODO :Definir valores que devem vir do pot.
//Valores a serem compardos no main com o valor que sai do adc. Tipo nível baixo o adc retorna 500, logo compara com 500.
#define SENSOR_NIVEL_ZERO     0
#define SENSOR_NIVEL_BAIXO    500
#define SENSOR_NIVEL_MEDIO    1500
#define SENSOR_NIVEL_ALTO     3000
#define SENSOR_NIVEL_FULL     -1

//Fazer essas funções. //TODO : Fazer funções abaixo.
void initSensor_NivelAgua(void);   //Inicializar tudo, mede e tals.
int  valorAtualSensor(int Sensor);      //Aqui dentro tem um if, ela só retorna os defines.

//Se o adc for por pooling valorAtualSensor deve fazer a medição, se for por DMA, ela deve só ser a variave(memoria) compartilhada.

#endif /* ADC_LIB_H_ */