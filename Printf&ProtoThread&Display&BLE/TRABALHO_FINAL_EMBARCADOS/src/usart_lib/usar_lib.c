 /**
  * \file usart_lib.c
  * \brief Biblioteca da usart
  * \details Funções para manipulação da porta serial
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 25/06/2018 16:32:17
  * \copyright GNU Public License
  */

#include "usart_lib.h"

/*! Armazena os dados recebidos em um buffer */
volatile uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

/*! Funções de callback. */
void usart_read_callback(struct usart_module *const usart_module)
{
	usart_write_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
}

void usart_write_callback(struct usart_module *const usart_module)
{
	usart_read_buffer_job(&usart_instance, (uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
}

void configure_usart(void)
{
	//Gerar a config padrao.
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	//Seta os pinos.
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;

	//Seta o printf. Ele vai usar as nossas interruption.
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);

	//Habilita.
	usart_enable(&usart_instance);
}

void configure_usart_callbacks(void)
{
	//Setar o callBack
	usart_register_callback(&usart_instance, usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_instance, usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);


	//Habilita o callback.
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
}
