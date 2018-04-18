/** Nelson Roberto Weirich Junior
  * Eduardo Capellari Culau
  *
  */
#ifndef GPIO_DRIVER_INCLUDED
#define GPIO_DRIVER_INCLUDED

// Variaveis globais de configuração
int port[50];
struct port_config config_pin[50];

// Configura porta
void porta_config(uint8_t port_num, uint8_t pin, uint8_t dir); 
// Escreve na porta
void porta_write(uint8_t port_num, uint8_t val); 
// Le da porta
void porta_read(uint8_t port_num, uint8_t *val); 
// Alterna o valor da porta
void porta_toggle(uint8_t port_num); 
// Obtém a direção da porta
int porta_dir(uint8_t port_num, uint8_t dir);

#endif