/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#include <asf.h>
#include "led-driver.h"

void led_config(uint8_t led_num, uint8_t pin) {
	port[led_num] = pin;
	
	//Obtém pino relativo ao led_num
	const uint8_t gpio_pin = port[led_num];
	
	// Obtém a configuração relativa ao led_num
	struct port_config *config = &config_pin[led_num];
	port_get_config_defaults(config);
	
	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);

	pinmux_config.mux_position = SYSTEM_PINMUX_GPIO;
	pinmux_config.direction    = PORT_PIN_DIR_OUTPUT;
	pinmux_config.input_pull   = (enum system_pinmux_pin_pull)config->input_pull;
	pinmux_config.powersave    = config->powersave;

	system_pinmux_pin_set_config(gpio_pin, &pinmux_config);
}

void led_on(uint8_t led_num) {
	// Obtém pino relativo ao led_num
	const uint8_t gpio_pin = port[led_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	// Liga o LED
	port_base->OUTCLR.reg = pin_mask;
}

void led_off(uint8_t led_num) {
	// Obtém pino relativo ao led_num
	const uint8_t gpio_pin = port[led_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	// Desliga o LED
	port_base->OUTSET.reg = pin_mask;
}

void led_toggle(uint8_t led_num) {
	// Obtém pino relativo ao led_num
	const uint8_t gpio_pin = port[led_num];
	
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	// Alterna o nível de saída do led
	port_base->OUTTGL.reg = pin_mask;
}