/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#ifndef PWM_DRIVER_INCLUDED
#define PWM_DRIVER_INCLUDED

#include "tcc.h"
#include <conf_quick_start.h>

// Variaveis globais de configuração
struct tcc_config tcc_configur[2];
struct tcc_module tcc_instance[2];

// Configura pwm
void pwm_config(uint8_t pwm_num, uint8_t pin); 
// Liga pwm
void pwm_on(uint8_t pwm_num);
// Desliga pwm
void pwm_off(uint8_t pwm_num);
// Define duty cicle do pwm
void pwm_set(uint8_t pwm_num, uint16_t duty);

#endif