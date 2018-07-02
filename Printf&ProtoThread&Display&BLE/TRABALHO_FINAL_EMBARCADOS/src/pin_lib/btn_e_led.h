 /**
  * \file btn_e_led.h
  * \brief Biblioteca dos botões e LEDs
  * \details Funções para manipulação dos botões e LEDs conectados à placa
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 25/06/2018 17:53:21
  * \copyright GNU Public License
  */


#ifndef BTN_E_LED_H_
#define BTN_E_LED_H_

// CHANGED: Redefinida a macro led_on e led_off por causa da lógica invertida da ASF
#define LED_ON(led_gpio)  LED_Off(led_gpio) /*!< Redefinição da macro LED_On devido à lógica invertida */
#define LED_OFF(led_gpio) LED_On(led_gpio) /*!< Redefinição da macro LED_Off devido à lógica invertida */

//OLED1_BTNS_LEDS ==> OLED conectado na parte de baixo.
#define BUTTON_1_PIN           PIN_PA28
#define BUTTON_2_PIN           PIN_PA02
#define BUTTON_3_PIN           PIN_PA03  //Nao funciona
#define LED_1_PIN              PIN_PA12
#define LED_2_PIN              PIN_PA13	 //Nao funciona.
#define LED_3_PIN              PIN_PA15

//CHANGED: Definido os pinos corretos dos btns e dos led conectados na placa.
#define BTN_TAMPA_PIN		  PIN_PB06 /*!< Botão de contato indica a tampa aberta. */
#define LED_MOTOR_PIN		  PIN_PA20 /*!< LED amarelo indica motor em funcionamento. */
#define LED_SECADOR_PIN   PIN_PA21 /*!< LED vermelho indica a secadora. */
#define LED_VALVULA_PIN		PIN_PB05 /*!< LED azul indica a válvula (entrada de água). */
#define LED_BOMBA_PIN     PIN_PB15 /*!< LED verde indica a bomba. (saída de água). */

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
