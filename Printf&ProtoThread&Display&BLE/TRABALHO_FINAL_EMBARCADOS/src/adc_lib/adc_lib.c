/*
 * CFile1.c
 *
 * Created: 29/06/2018 16:24:32
 *  Author: Eduardo Culau
 */ 

//Incluir a lib
#include "adc_lib.h"

//Inicializar tudo, mede e tals. //TODO
void initSensor_NivelAgua(void){
	
}

//Aqui dentro tem um if, ela só retorna os defines. //TODO
int  valorAtualSensor(int Sensor){
	//Lê do adc.
	static int count = 0, count2 = 0;
	/*
	
	if(zero > valor_adc < valor_min ){
		return SENSOR_NIVEL_ZERO
	}else
	
	if(valor_min > valor_adc < valor_baixo){
		return SENSOR_NIVEL_BAIXO
	}else
	
	if(valor_baixo > valor_adc < valor_medio){
		return SENSOR_NIVEL_MEDIO
	}else
	
	if(valor_medio > valor_adc < valor_alto){
		return SENSOR_NIVEL_ALTO
	}else
	
	if(valor_alto > valor_adc){
		return SENSOR_NIVEL_FULL
	}
	
	*/
	
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
}
