
#include <asf.h>
#include "timer-driver.h"

#include "tc.h"
#include "conf_test.h"
#include "conf_clocks.h"

// flag de erro global para TC3  
volatile uint8_t TC3_error = 0;
 
void init_TC3(int tempo) {
    // configura o timer/counter para piscar o led
    // configura clock
    REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3;
    REG_PM_APBCMASK |= PM_APBCMASK_TC3; // habilita TC3 bus clock
    
    // configura TC3 (contador 16b por padrao) -- periodo
    REG_TC3_CTRLA |= TC_CTRLA_PRESCALER_DIV64;
    
    // habilita interrupacoes
    REG_TC3_INTENSET = TC_INTENSET_OVF | TC_INTENSET_ERR;
    
    // periodo
    TC3->COUNT8.PER.reg = TC_COUNT8_PER_PER(tempo);
    
    // habilita TC3
    REG_TC3_CTRLA |= TC_CTRLA_ENABLE;
    while( TC3->COUNT8.STATUS.bit.SYNCBUSY == 1){} // espera para TC3 ser habilitado
}
 
void enable_interrupt_time() {
    NVIC_EnableIRQ(TC3_IRQn);
}
 
void TC3_Handler() {
    // overflow gera interrupcao
    if ( TC3->COUNT8.INTFLAG.bit.OVF == 1) {
        // tratamento da interrupção   
        
        REG_TC3_INTFLAG = TC_INTFLAG_OVF;
    }
    
    // erro gera interrupcao
    else if (TC3->COUNT8.INTFLAG.bit.ERR == 1) {
        TC3_error = 1;
        REG_TC3_INTFLAG = TC_INTFLAG_ERR;
    }
}