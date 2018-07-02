 /**
  * \file usart_lib.h
  * \brief Biblioteca da usart
  * \details Funções para manipulação da porta serial
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 25/06/2018 16:32:36
  * \copyright GNU Public License
  */

#include <asf.h>

#ifndef USART_LIB_H_
#define USART_LIB_H_

/*! Instancia do usart. */
struct usart_module usart_instance;

#define MAX_RX_BUFFER_LENGTH   100 /*!< Tamanho máximo do buffer receptor. */

//Funções de callback.
void usart_read_callback(struct usart_module *const usart_module);
void usart_write_callback(struct usart_module *const usart_module);

void configure_usart(void);
void configure_usart_callbacks(void);

#endif /* USART_LIB_H_ */
