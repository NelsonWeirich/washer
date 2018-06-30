/*
 * usart_lib.h
 *
 * Created: 25/06/2018 16:32:36
 *  Author: Eduardo Culau
 */ 

#include <asf.h>

#ifndef USART_LIB_H_
#define USART_LIB_H_

//Declara a instancia do uart.
struct usart_module usart_instance;

#define MAX_RX_BUFFER_LENGTH   100

//Funções de callback.
void usart_read_callback(struct usart_module *const usart_module);
void usart_write_callback(struct usart_module *const usart_module);

void configure_usart(void);
void configure_usart_callbacks(void);

#endif /* USART_LIB_H_ */