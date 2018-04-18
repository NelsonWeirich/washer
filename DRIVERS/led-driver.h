/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#ifndef LED_DRIVER_INCLUDED
#define LED_DRIVER_INCLUDED

#include "gpio-driver.h" // contém variáveis de uso das portas

//configurar porta como saída
void led_config(uint8_t led_num, uint8_t pin); 
// ligar 
void led_on(uint8_t led_num);     
// desligar 
void led_off(uint8_t led_num);    
// alternar
void led_toggle(uint8_t led_num); 

#endif