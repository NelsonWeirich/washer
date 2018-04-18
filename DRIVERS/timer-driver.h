/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#ifndef TIMER_DRIVER_INCLUDED
#define TIMER_DRIVER_INCLUDED

#include "tc.h"
#include <conf_quick_start_callback.h>
#include "conf_test.h"
#include "conf_clocks.h"

// Configura timer
void timer_config(uint8_t timer_num, uint16_t period_ms);
// Inicia contagem
void timer_start(uint8_t timer_num);
// Para contagem
void timer_stop(uint8_t timer_num);
// Retorna o valor do contador
uint32_t timer_count(uint8_t timer_num);
// Define um tempo de espera
void timer_delay(uint8_t timer_num, uint16_t period_ms);


#endif