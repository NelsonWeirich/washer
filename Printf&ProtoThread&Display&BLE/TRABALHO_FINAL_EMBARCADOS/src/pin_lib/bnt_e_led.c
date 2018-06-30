/*
 * bnt_e_led.c
 *
 * Created: 25/06/2018 17:53:00
 *  Author: Eduardo Culau
 */ 

//Inclue a biblioteca
#include <asf.h>

#include "btn_e_led.h"

//Configurar os pinos.
struct port_config config_port_pin;

//Inicializa todos os btns e os leds.
void init_OLED_btnLed(void){
	inicializa_btn();
	inicializa_led();
}

//Inicializa os btns.
void inicializa_btn(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);
	//Seta como entrada e pull-UP
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	//Seta os btn do modo configurado.
	port_pin_set_config(BUTTON_1_PIN, &config_port_pin);
	port_pin_set_config(BUTTON_2_PIN, &config_port_pin);
//	port_pin_set_config(BUTTON_3_PIN, &config_port_pin);
}

//Inicializa os leds.
void inicializa_led(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);	
	//Seta como saida.
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	//Seta os leds.
	port_pin_set_config(LED_1_PIN, &config_port_pin);
	//port_pin_set_config(LED_2_PIN, &config_port_pin);
	port_pin_set_config(LED_3_PIN, &config_port_pin);
}

//Retorna 1 se o btn n�o esta precionado.
int isBTN_UP(uint8_t btn){
	return (port_pin_get_input_level(btn));
}

//Retorna 1 se o btn estiver precionado.
int isBTN_DOWN(uint8_t btn){
	return (!port_pin_get_input_level(btn));
}