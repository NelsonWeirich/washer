/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#include <asf.h>
#include "timer-driver.h"


#include <conf_quick_start_callback.h>
#include "conf_test.h"
#include "conf_clocks.h"

uint8_t CONF_TC_MODULE;

struct tc_module tc_instance;

void timer_config(uint8_t timer_num, uint16_t period_ms)
{
	struct tc_config config_tc;
	
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_8_bit.period = period_ms;
	config_tc.counter_8_bit.compare_capture_channel[0] = 50;
	config_tc.counter_8_bit.compare_capture_channel[1] = 54;
	CONF_TC_MODULE = timer_num;
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	tc_enable(&tc_instance);
}

void timer_start(uint8_t timer_num){
	if (CONF_TC_MODULE == timer_num)
		tc_start_counter(&tc_instance);
}

void timer_stop(uint8_t timer_num){
	if (CONF_TC_MODULE == timer_num)
		tc_stop_counter(&tc_instance);
}

uint32_t timer_count(uint8_t timer_num){
	return tc_get_count_value(&tc_instance);
}

void timer_delay(uint8_t timer_num, uint16_t period_ms){
	
}