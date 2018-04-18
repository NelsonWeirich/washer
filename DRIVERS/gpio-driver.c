/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#include <asf.h>
#include "gpio-driver.h"

void porta_config(uint8_t port_num, uint8_t pin, uint8_t dir) {
	// Obtém pino relativo ao led_num
	const uint8_t gpio_pin = port[port_num];
	// Obtém a configuração relativa ao led_num
	struct port_config *config = &config_pin[port_num];
	port_get_config_defaults(&config);
		
	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);

	pinmux_config.mux_position = SYSTEM_PINMUX_GPIO;
	pinmux_config.direction    = dir;
	pinmux_config.input_pull   = (enum system_pinmux_pin_pull)config->input_pull;
	pinmux_config.powersave    = config->powersave;

	system_pinmux_pin_set_config(gpio_pin, &pinmux_config);
	
	// old
	// port[port_num] = pin;
	
	// port_get_config_defaults(&config_pin[port_num]);

	// config_pin[port_num].direction  = dir;
	// port_pin_set_config(pin, &config_pin[port_num]);
}

void porta_write(uint8_t port_num, uint8_t val) {
	// Obtém pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
		
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));
	
	if (val) {
		port_base->OUTSET.reg = pin_mask;
	} else {
		port_base->OUTCLR.reg = pin_mask;
	}
	
	// old
	// if (val) {
		// port_pin_set_output_level(port[port_num], !true);
	// } else {
		// port_pin_set_output_level(port[port_num], !false);
	// }
}

void porta_read(uint8_t port_num, uint8_t *val) {
	// Obtém pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	if (port_base->OUT.reg & pin_mask)
		*val = 1;
	else
		*val = 0;
	
	// old
	// if (port_pin_get_output_level(port[port_num])) {
		// *val = 1;
	// }
}

void porta_toggle(uint8_t port_num) {
	// Obtém pino relativo ao port_num
	const uint8_t gpio_pin = port[port_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	// Alterna o nível de saída do pino
	port_base->OUTTGL.reg = pin_mask;
	
	// old
	// port_pin_toggle_output_level(port[port_num]);
}

int porta_dir(uint8_t port_num, uint8_t dir) {
	// Obtém a configuração relativa ao led_num
	struct port_config *config = &config_pin[port_num];
		
	config->direction = dir;
	
	// old
	// int dir;
	// dir = config_pin[port_num].direction;
}
