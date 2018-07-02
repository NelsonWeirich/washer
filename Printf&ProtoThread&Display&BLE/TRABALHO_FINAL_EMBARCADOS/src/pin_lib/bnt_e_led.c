 /**
  * \file btn_e_led.c
  * \brief Biblioteca dos botões e LEDs
  * \details Funções para manipulação dos botões e LEDs conectados à placa
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 25/06/2018 17:53:00
  * \copyright GNU Public License
  */

#include <asf.h>

#include "btn_e_led.h"

/*! Configuração dos pinos da porta */
struct port_config config_port_pin;

/*! Inicializa os botões e os LEDs */
void init_OLED_btnLed(void){
	inicializa_btn();
	inicializa_led();
}

/*! Inicializa os botões. */
void inicializa_btn(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);
	//Seta como entrada e pull-UP
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	//Seta os btn do modo configurado.
	port_pin_set_config(BUTTON_1_PIN, &config_port_pin);
	port_pin_set_config(BUTTON_2_PIN, &config_port_pin);
}

/*! Inicializa os leds. */
void inicializa_led(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);
	//Seta como saida.
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	//Seta os leds.
	port_pin_set_config(LED_1_PIN, &config_port_pin);
	LED_OFF(LED_1_PIN);
	port_pin_set_config(LED_3_PIN, &config_port_pin);
	LED_OFF(LED_3_PIN);
}

//****************************************************

/*! Inicializa os botões e os LEDs externos (lateral). */
void init_external_btnLed(void){
	inicializa_exeternal_btn();
	inicializa_external_led();
}

/*! Inicializa os botões externos. */
void inicializa_exeternal_btn(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);
	//Seta como entrada e pull-UP
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	//Seta os btn do modo configurado.
	port_pin_set_config(BTN_TAMPA_PIN, &config_port_pin);
}

/*! Inicializa os LEDs externos. */
void inicializa_external_led(void){
	//Apaga a config.
	port_get_config_defaults(&config_port_pin);
	//Seta como saida.
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	//Seta os leds.
	port_pin_set_config(LED_MOTOR_PIN, &config_port_pin);
	LED_OFF(LED_MOTOR_PIN);
	port_pin_set_config(LED_SECADOR_PIN, &config_port_pin);
	LED_OFF(LED_SECADOR_PIN);
	port_pin_set_config(LED_VALVULA_PIN, &config_port_pin);
	LED_OFF(LED_VALVULA_PIN);
	port_pin_set_config(LED_BOMBA_PIN, &config_port_pin);
	LED_OFF(LED_BOMBA_PIN);
}

//**************************************************

/*! \brief Testa se botão não pressionado.
 *  \param btn o identificador do pino do botão.
 *  \return 1 caso botão não pressionado.
 */
int isBTN_UP(uint8_t btn){
	return (port_pin_get_input_level(btn));
}

/*! \brief Testa se botão pressionado.
 *  \param btn o identificador do pino do botão.
 *  \return 1 caso botão pressionado.
 */
int isBTN_DOWN(uint8_t btn){
	return (!port_pin_get_input_level(btn));
}
