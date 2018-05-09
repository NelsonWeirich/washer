/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#include <asf.h>
#include "gpio-driver.h"

void porta_config(uint8_t port_num, uint8_t pin, uint8_t dir) {
	port[port_num] = pin;
	
	// Obt�m pino relativo ao led_num
	const uint8_t gpio_pin = port[port_num];
	// Obt�m a configura��o relativa ao led_num
	struct port_config *config = &config_pin[port_num];
	port_get_config_defaults(config);
		
	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);

	pinmux_config.mux_position = SYSTEM_PINMUX_GPIO;
	pinmux_config.direction    = dir;
	pinmux_config.input_pull   = (enum system_pinmux_pin_pull)config->input_pull;
	pinmux_config.powersave    = config->powersave;

	system_pinmux_pin_set_config(gpio_pin, &pinmux_config);
}

void porta_write(uint8_t port_num, uint8_t val) {
	// Obt�m pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
		
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));
	
	if (val) {
		port_base->OUTCLR.reg = pin_mask;
	} else {
		port_base->OUTSET.reg = pin_mask;
	}
}

void porta_read(uint8_t port_num, uint8_t *val) {
	// Obt�m pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	if (port_base->OUT.reg & pin_mask)
		*val = 1;
	else
		*val = 0;
}

void porta_toggle(uint8_t port_num) {
	// Obt�m pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	// Alterna o n�vel de sa�da do pino
	port_base->OUTTGL.reg = pin_mask;
}

int porta_dir(uint8_t port_num, uint8_t dir) {
	// Obt�m a configura��o relativa ao led_num
	struct port_config *config = &config_pin[port_num];
		
	config->direction = dir;
}
