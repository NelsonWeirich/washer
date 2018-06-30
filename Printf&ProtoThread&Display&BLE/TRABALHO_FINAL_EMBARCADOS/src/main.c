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
	TAMPA_ABERTA,
	ESPERA
} ESTADO_t;

ESTADO_t ESTADO = PEGANDO_DADOS;

typedef enum subEstado{
	ENXER,
	ESVAZIAR,
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
	BAIXO = SENSOR_NIVEL_BAIXO,
	MEDIO = SENSOR_NIVEL_MEDIO,
	ALTO  = SENSOR_NIVEL_ALTO,
} NIVEL_t;

NIVEL_t NIVEL_AGUA   = BAIXO;
int     NIVEL_SENSOR = SENSOR_NIVEL_ZERO;

typedef enum MODO_EXECUTAR{
	NORMAL = 0,
	RAPIDO,
	PESADO,
} MODE_t;

MODE_t MODO = NORMAL;

typedef enum SECAR_EXECUTAR{
	MORNO = 0,
	QUENTE,
	VAPOR,
} SECA_t;

SECA_t SECAR = MORNO;

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

//Btn usados para controlar o menu.
#define bt1 BUTTON_1_PIN
#define bt2 BUTTON_2_PIN

//Btn usado para pegar se a tampa esta aberta.
#define bt_tampa BTN_TAMPA_PIN
//Leds usados para indicar que os componentes forma ligados.
#define l_motor   LED_MOTOR_PIN
#define l_secador LED_SECADOR_PIN
#define l_valvula LED_VALVULA_PIN
#define l_bomba   LED_BOMBA_PIN   

//LED usado para indicar se tá executando e se (COLOCAR OUTRA COISA); Só esta sendo usado para testes.
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
				selecionado[OPT_OK] = OK_OPT_TRUE; OK_pressed = !GFX_MONO_SPINCTRL_EVENT_FINISH;
				clearDisplay(); printString("EXECUTANDO:", 0, 10); printString("PAUSAR         PARAR", 0, 25);
			}
			
		}else
		
		//Quando tiver executnado.
		if(ESTADO == EXECUTANDO){
			//Pausar
			if(isBTN_DOWN(bt1)){
				ESTADO = ESPERA;
				printString("---PAUSADO---", 20, 10);
				printString("CONTINUAR      PARAR", 0, 25);
			}else
			//Parar
			if(isBTN_DOWN(bt2)){
				ESTADO = PEGANDO_DADOS;
				clearDisplay(); mostraMenuDisplay(&spinners);
			}
		}else
		
		if(ESTADO == ESPERA){
			//Pausar
			if(isBTN_DOWN(bt1)){
				ESTADO = EXECUTANDO;
				printString("EXECUTANDO:", 0, 10);
				printString("PAUSAR         PARAR", 0, 25);
			}else
			
			//Parar
			if(isBTN_DOWN(bt2)){
				ESTADO = PEGANDO_DADOS;
				clearDisplay(); mostraMenuDisplay(&spinners);
			}
		}else
		
		if(ESTADO == TAMPA_ABERTA){
			//Parar
			if(isBTN_DOWN(bt2)){
				ESTADO = PEGANDO_DADOS;
				clearDisplay(); mostraMenuDisplay(&spinners);
			}
		}
		
		//Espera para não pegar muitos cliques de uma vez só.
		delay_ms(500);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Pega os dados que a pessoa digitou no display.
PT_THREAD(pt_pegaDados(struct pt *pt))
{
	static int alreadyPrint;
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
				selecionado[OPT_OK] = OK_OPT_FALSE;
			}	
		}
		
		//Testes, dá pra tirar isso.
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
		
		//Pegar se a tampa está aberta.
		if(ESTADO == EXECUTANDO && isBTN_UP(bt_tampa) ){
			ESTADO = TAMPA_ABERTA;
			printString("---TAMPA ABERTA---", 10, 10);
			printString("------         PARAR", 0, 25);
		}
		
		if(ESTADO == TAMPA_ABERTA && isBTN_DOWN(bt_tampa)){
			ESTADO = EXECUTANDO;
			printString("EXECUTANDO:", 0, 10);
			printString("PAUSAR         PARAR", 0, 25);
		}
		
		//Fazer logica com os subestados como o batendo, centrifugando, secando e tals.
		
		//Rerorna para da protothread.
		PT_YIELD(pt);
	}
	//Fim da protothread.
	PT_END(pt);
}

//Controla a execução do sistema. Exemplo. Agora tem que enxer, agora bater, agroa centrifugar.
PT_THREAD(pt_contorlaExecution(struct pt *pt))
{
	static int alreadyPrint;
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Sempre pegar os dados e os processas.
	while(1){
		
		//Fazer logica com os subestados como o batendo, centrifugando, secando e tals.
		
		//Rerorna para da protothread.
		PT_YIELD(pt);
	}
	//Fim da protothread.
	PT_END(pt);
}

//Liga os componentes de acordo com o que tem que acontecer no momento.
PT_THREAD(pt_controlaComponentes(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	while(1){
		//***MOTOR***
		//Estado é executnado, logo verifica se é para o motor executar.
		if(ESTADO == EXECUTANDO && ( EXECUTION == BATER || EXECUTION == CENTRIFUGAR || EXECUTION == SECANDO )){
			LED_On(l_motor);
		}else{
			LED_Off(l_motor);
		}
		
		//***VALVULA***
		//Estado é executnado, logo verifica se é para colocar agua.
		if(ESTADO == EXECUTANDO && ( EXECUTION == ENXER) ){
			LED_On(l_bomba);
		}else{
			LED_Off(l_bomba);
		}
		
		//***BOMBA***
		//Estado é executnado, logo verifica se é para o bomba retirar agua.
		if(ESTADO == EXECUTANDO && ( EXECUTION == CENTRIFUGAR || EXECUTION == ESVAZIAR)){
			LED_On(l_bomba);
		}else{
			LED_Off(l_bomba);
		}
		
		//***SECAR***
		//Estado é executnado, liga quando tiver que secar.
		if(ESTADO == EXECUTANDO && ( EXECUTION == SECANDO) ){
			LED_On(l_secador);
		}else{
			LED_Off(l_secador);
		}
		
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
	init_external_btnLed();

	//Configura
	configure_usart();
	configure_usart_callbacks();
	
	//Ativa o intr do systema para pegar o usb.
	system_interrupt_enable_global();
	
	//Gasta tempo e Inicial. Tempo para abrir o terminal e poder ver desde o inicio.
	for(int wt = 0; wt<1000000;wt++){}
	printf("START....................\n\n");		
	
	//Cria a pThread. E Inicializa.
    struct pt pt_gD, pt_pD, pt_cC, pt_cE;
	PT_INIT(&pt_gD); PT_INIT(&pt_pD); PT_INIT(&pt_cC); PT_INIT(&pt_cE);
	
	
	//Fica executado para sempre as protoThreads.
	while(1){
		//Fica trocando entre as protothreads.
		pt_gerenciaDisplay(&pt_gD);
		pt_pegaDados(&pt_pD);
		pt_controlaComponentes(&pt_cC);
		pt_contorlaExecution(&pt_cE);
	}
	
}

