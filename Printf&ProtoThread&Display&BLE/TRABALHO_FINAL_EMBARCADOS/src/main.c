/*
NOMES: Eduardo Capellari Culau
       Nelson Weirich Junior 

DATA: 25/06/2018
*/

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>
// #include <conf_spinctrl.h>
// #include <conf_sysfont.h>

//BTNs e LEDs do OLED (conectado na parte de baixo).
#include "pin_lib/btn_e_led.h"

//Display OLED
#include "display_lib/display_lib.h"

//Usart
#include "usart_lib/usart_lib.h"

//ADC
#include "adc_lib/adc_lib.h"

//ProtoThreads
#include "pt_lib/pt.h"

//Estados da maquina.
typedef enum ESTADOS{
	PEGANDO_DADOS = 0,
	EXECUTANDO,
	ESPERA
} ESTADO_t;

ESTADO_t ESTADO = PEGANDO_DADOS;

typedef enum subEstado{
	BATER,
	MOLHO,
	ENXAGUAR,
	CENTRIFUGAR,
	SECANDO,
	FAZENDO_NADA
}EXECUTANDO_t;

EXECUTANDO_t EXECUTION = FAZENDO_NADA;

//Vars
typedef enum NIVEL__da_AGUA{
	BAIXO = 0,
	MEDIO,
	ALTO,
	NIVEL_NADA
} NIVEL_t;

NIVEL_t NIVEL_AGUA = NIVEL_NADA;

typedef enum MODO_EXECUTAR{
	NORMAL = 0,
	RAPIDO,
	PESADO,
	MODO_NADA
} MODE_t;

MODE_t MODO = MODO_NADA;

typedef enum SECAR_EXECUTAR{
	MORNO = 0,
	QUENTE,
	VAPOR,
	SECAR_NADA
} SECA_t;

SECA_t SECAR = SECAR_NADA;

//Usado para pegar fazer o menu e pegar as opções selecionadas.
struct gfx_mono_spinctrl_spincollection spinners;
int16_t selecionado[4];

//Estrutura do timer
struct timer { int start, interval; };

//Timer espirou?
//static int timer_expired(struct timer *t)
//{ return (int)(++ t->start >= t->interval); }

//Setar o timer.
//static void timer_set(struct timer *t, int interval)
//{ t->interval = interval; t->start = 0;}

//Tempo de espera da protothread
//#define TIMEOUT 10

//Liga o motor quando for o momento liga-lo.
PT_THREAD(pt_ligaMotor(struct pt *pt))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, 1);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga a bomba quando for o momento liga-lo.
PT_THREAD(pt_ligaBomba(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, 1);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga a bomba quando for o momento liga-lo.
PT_THREAD(pt_liberaValvula(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, 1);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga o secador quando for o momento liga-lo.
PT_THREAD(pt_ligaSecador(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, 1);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}	

//Btn usados para controlar o menu.
#define bt1 BUTTON_1_PIN
#define bt2 BUTTON_2_PIN
//LED usado para indicar se tá executando e se (COLOCAR OUTRA COISA);
#define l1  LED_1_PIN
#define l3  LED_3_PIN

//Mostra as coisas no display.
PT_THREAD(pt_gerenciaDisplay(struct pt *pt))
{
	static uint8_t OK_pressed;
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, isBTN_DOWN(bt1) || isBTN_DOWN(bt2));
	
		//Se tá no estado de espera, a pessoa pode escolher as opçoes.
		if(ESTADO == PEGANDO_DADOS){
			
			//Proximo
			if(isBTN_DOWN(bt1)){
				gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_DOWN, selecionado);
			}
			//Enter
			if(isBTN_DOWN(bt2)){
				OK_pressed = gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_ENTER, selecionado);
			}
			
			//Pegar quando foi celecionadao o OK (clicando enter com o spinner no OK.)
			if(OK_pressed == GFX_MONO_SPINCTRL_EVENT_FINISH){
				selecionado[OPT_OK] = OK_OPT_TRUE;
				OK_pressed = !GFX_MONO_SPINCTRL_EVENT_FINISH;
			}else{
				selecionado[OPT_OK] = OK_OPT_FALSE;
			}
			
			//Espera para não pegar muitos cliques de uma vez só.
			delay_ms(500);	
		}
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Pega os dados que a pessoa digitou no display.
PT_THREAD(pt_pegaDados(struct pt *pt))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Sempre pegar os dados e os processas.
	while(1){
		
		if(ESTADO == PEGANDO_DADOS){
			//Pega as opções do display.
			MODO       = (MODE_t ) selecionado[OPT_MODO];
			NIVEL_AGUA = (NIVEL_t) selecionado[OPT_AGUA];
			SECAR      = (SECA_t ) selecionado[OPT_SECAR];
			
			//Pega o OK.
			if(selecionado[OPT_OK] == OK_OPT_TRUE){
				ESTADO = EXECUTANDO;
			}	
		}
		
		
		//Testes
		if(MODO == PESADO){
			LED_On(l1);
		}else{
			LED_Off(l1);
		}
		if(ESTADO == EXECUTANDO){
			LED_On(l3);
		}else{
			LED_Off(l3);	
		}
		
		//Código final
	
		//Rerorna para da protothread.
		PT_YIELD(pt);
	}
	//Fim da protothread.
	PT_END(pt);
}

int main(void)
{
	//Inicializa
	system_init();
	
	//Configura o display OLED.
	init_OLED_display(&spinners);
	
	//Configura os btns e os leds do OLED (parte de baixo da placa).
	init_OLED_btnLed();
	
	//Configura os btns e os leds externos (lateral)

	//Configura
	configure_usart();
	configure_usart_callbacks();
	
	//Ativa o intr do systema para pegar o usb.
	system_interrupt_enable_global();
	
	//Gasta tempo e Inicial. Tempo para abrir o terminal e poder ver desde o inicio.
	for(int wt = 0; wt<1000000;wt++){}
	printf("START....................\n\n");		
	
	//Cria a pThread. E Inicializa.
    struct pt pt_gD, pt_pD, pt_lV, pt_lM, pt_lB, pt_lS;
	PT_INIT(&pt_gD); PT_INIT(&pt_pD); PT_INIT(&pt_lV); PT_INIT(&pt_lM); PT_INIT(&pt_lB); PT_INIT(&pt_lS);
	
	
	//Fica executado para sempre as protoThreads.
	while(1){
		//Fica trocando entre as protothreads.
		pt_gerenciaDisplay(&pt_gD);
		pt_pegaDados(&pt_pD);
		pt_liberaValvula(&pt_lV);
		pt_ligaMotor(&pt_lM);
		pt_ligaBomba(&pt_lB);
		pt_ligaSecador(&pt_lS);
		//Gasta tempo para cada vetor.
		//for(int wt = 0; wt<1500;wt++){}
	}
	
}

