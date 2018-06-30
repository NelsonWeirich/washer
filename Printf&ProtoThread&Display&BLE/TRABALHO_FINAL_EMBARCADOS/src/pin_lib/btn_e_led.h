/*
 * btn_e_led.h
 *
 * Created: 25/06/2018 17:53:21
 *  Author: Eduardo Culau
 */ 


#ifndef BTN_E_LED_H_
#define BTN_E_LED_H_

//OLED1_BTNS_LEDS ==> OLED conectado na parte de baixo.
#define BUTTON_1_PIN           PIN_PA28
#define BUTTON_2_PIN           PIN_PA02
#define BUTTON_3_PIN           PIN_PA03  //Não funciona
#define LED_1_PIN              PIN_PA12
#define LED_2_PIN              PIN_PA13	 //Não funciona.
#define LED_3_PIN              PIN_PA15

//TODO :Definir os pinos corretos dos btns e dos led conectados na placa. Definir os pinos deles.
//Btns e LEDs externos. Tudos vai ligado em uma porta+ e no gnd-. Os btn ficam em pull-up na porta.
#define BTN_TAMPA_PIN		  PIN_PB12 //Definir pino do btn de pressão. Se der tempo fazer uma interrupção para ele, se não der é só ler dele.
#define LED_MOTOR_PIN		  PIN_PB13 //Definir o pino do led amarelo, indicando que é o motor.
#define LED_SECADOR_PIN       PIN_PB13 //Definir pino do vermelho para o secador. 
#define LED_VALVULA_PIN		  PIN_PB13 //Definir led transparente(azul) para ser a valvula (entrar agua).
#define LED_BOMBA_PIN         PIN_PB13 //Definir led verde para ser a bomba (tira agua).

//Inicializa todos os btns e os leds.
void init_OLED_btnLed(void);
void inicializa_btn(void);
void inicializa_led(void);

//Inicializa todos os btns e os leds exernos.
void init_external_btnLed(void);
void inicializa_exeternal_btn(void);
void inicializa_external_led(void);

int isBTN_UP(uint8_t btn);
int isBTN_DOWN(uint8_t btn);

#endif /* BTN_E_LED_H_ */