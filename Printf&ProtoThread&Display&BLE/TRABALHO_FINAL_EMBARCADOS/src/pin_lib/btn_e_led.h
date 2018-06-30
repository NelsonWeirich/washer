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

//Inicializa todos os btns e os leds.
void init_OLED_btnLed(void);
void inicializa_btn(void);
void inicializa_led(void);

int isBTN_UP(uint8_t btn);
int isBTN_DOWN(uint8_t btn);

#endif /* BTN_E_LED_H_ */