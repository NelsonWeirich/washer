/** Nelson Weirich e Eduardo Culau
 *
 */
#include <asf.h>
#include "pwm-driver.h"

void pwm_config(uint8_t pwm_num, uint8_t pin) {
	
	//! [setup_config_defaults]
	tcc_get_config_defaults(&tcc_configur[pwm_num], CONF_PWM_MODULE);
	//! [setup_config_defaults]

	//! [setup_change_config]
	tcc_configur[pwm_num].counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1;
	tcc_configur[pwm_num].counter.period = 0xFFFF;
	tcc_configur[pwm_num].compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	tcc_configur[pwm_num].compare.match[CONF_PWM_CHANNEL] = (0xFFFF / 4);
	//! [setup_change_config]

	//! [setup_change_config_pwm]
	tcc_configur[pwm_num].pins.enable_wave_out_pin[CONF_PWM_OUTPUT] = true;
	tcc_configur[pwm_num].pins.wave_out_pin[CONF_PWM_OUTPUT]        = pin;
	tcc_configur[pwm_num].pins.wave_out_pin_mux[CONF_PWM_OUTPUT]    = CONF_PWM_OUT_MUX;
	//! [setup_change_config_pwm]

	//! [setup_set_config]
	tcc_init(&tcc_instance[pwm_num], CONF_PWM_MODULE, &tcc_configur[pwm_num]);
	//! [setup_set_config]
}

	
// ligar
void pwm_on(uint8_t pwm_num) {
	// Obtém modulo relativo ao pwm_num
	const struct tcc_module *const module_inst = &tcc_instance[pwm_num];
	
	// Verifica
	Assert(module_inst);
	Assert(module_inst->hw);

	// Obtém referência para o modulo pwm
	Tcc *const tcc_module = module_inst->hw;

	while (tcc_module->SYNCBUSY.reg & TCC_SYNCBUSY_ENABLE) {
		// Sincronização
	}

	// Desabilita o modulo pwm
	tcc_module->CTRLA.reg |= TCC_CTRLA_ENABLE;
	
	// old
	// tcc_enable(&tcc_instance[pwm_num]);
}
 
// desligar
void pwm_off(uint8_t pwm_num) {
	// Obtém modulo relativo ao pwm_num
	const struct tcc_module *const module_inst = &tcc_instance[pwm_num];
	
	// Verifica
	Assert(module_inst);
	Assert(module_inst->hw);

	// Obtém referência para o modulo pwm
	Tcc *const tcc_module = module_inst->hw;

	while (tcc_module->SYNCBUSY.reg & TCC_SYNCBUSY_ENABLE) {
		// Sincronização
	}

	// Desabilita interrupção
	tcc_module->INTENCLR.reg = TCC_INTENCLR_MASK;
	// Limpa flag de interrupção
	tcc_module->INTFLAG.reg = TCC_INTFLAG_MASK;

	// Desabilita o modulo pwm
	tcc_module->CTRLA.reg  &= ~TC_CTRLA_ENABLE;
	
	// old
	// tcc_disable(&tcc_instance[pwm_num]);
}

void pwm_set(uint8_t pwm_num, uint16_t duty) {
	tcc_configur[pwm_num].compare.match[CONF_PWM_CHANNEL] = duty;
	tcc_init(&tcc_instance[pwm_num], CONF_PWM_MODULE, &tcc_configur[pwm_num]);
}
