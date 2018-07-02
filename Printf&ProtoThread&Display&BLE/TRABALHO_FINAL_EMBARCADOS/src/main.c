/**
 * \file main.c
 * \brief Aplicação principal.
 * \details Apllicação da lavadora.
 *
 * \author Eduardo Capellari Culau
 * \author Nelson Roberto Weirich Junior
 *
 * \date 25/06/2018
 * \copyright GNU Public License
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

/*! Estados da maquina. */
typedef enum ESTADOS{
	PEGANDO_DADOS = 0,
	EXECUTANDO,
	TAMPA_ABERTA,
	ESPERA,
	FINALIZADO
} ESTADO_t;

ESTADO_t ESTADO = PEGANDO_DADOS;

EXECUTANDO_t EXECUTION = FAZENDO_NADA;

/*! Variaveis de nível de água */
typedef enum NIVEL__da_AGUA{
	BAIXO = SENSOR_NIVEL_BAIXO, /*!< Nível baixo */
	MEDIO = SENSOR_NIVEL_MEDIO, /*!< Nível médio */
	ALTO  = SENSOR_NIVEL_ALTO,  /*!< Nível alto */
} NIVEL_t;

NIVEL_t NIVEL_AGUA   = BAIXO;
int     NIVEL_SENSOR = SENSOR_NIVEL_ZERO;

/*! Modos de lavagem */
typedef enum MODO_EXECUTAR{
	NORMAL = 0,
	RAPIDO,
	PESADO,
} MODE_t;

MODE_t MODO = NORMAL;

/*! Modos de secagem */
typedef enum SECAR_EXECUTAR{
	MORNO = 0,
	QUENTE,
	VAPOR,
} SECA_t;

SECA_t SECAR = MORNO;

/*! Estrutura para uso do do menu */
struct gfx_mono_spinctrl_spincollection spinners;
int16_t selecionado[4];

/*! Estrutura do timer */
struct timer { int start, interval; };

//Timer espirou?
//static int timer_expired(struct timer *t)
//{ return (int)(++ t->start >= t->interval); }

//Setar o timer.
//static void timer_set(struct timer *t, int interval)
//{ t->interval = interval; t->start = 0;}

//Tempo de espera da protothread
//#define TIMEOUT 10

//Tempo maximo do sistema. Substituir pelo modulo timer.
//Tempo para encher e esvaziar é infinito, dependem do sensor de nível de água.
#define TIME_BATER       70000
#define TIME_MOLHO       70000
#define TIME_ENXAGUAR    70000
#define TIME_CENTRIFUGAR 70000
#define TIME_SECANDO     70000

//Btn usados para controlar o menu.
#define bt1 BUTTON_1_PIN /*!< Botão de seleção esquerdo */
#define bt2 BUTTON_2_PIN /*!< Botão de seleção direito */

//Btn usado para pegar se a tampa esta aberta.
#define bt_tampa BTN_TAMPA_PIN /*!< Botão da tampa */
//Leds usados para indicar que os componentes foram ligados.
#define l_motor   LED_MOTOR_PIN /*!< LED do motor */
#define l_secador LED_SECADOR_PIN /*!< LED da secaodra */
#define l_valvula LED_VALVULA_PIN /*!< LED da válvula */
#define l_bomba   LED_BOMBA_PIN /*!< LED da bomba */

//Sensor nivel adc.
#define POTENTIOMETER SENSOR_NIVEL_PIN

//LED usado para indicar se esta executando;
//Estao sendo usados para testes.
#define l1  LED_1_PIN
#define l3  LED_3_PIN

/*! \brief Gerencia o conteúdo do display
 *  Coordena o que aparece no display e a interação do usuário com o mesmo.
 *  \param pt ponteiro de estrutura pt (pThread)
 */
PT_THREAD(pt_gerenciaDisplay(struct pt *pt))
{
	static uint8_t OK_pressed;
	//Inicia a protothread.
	PT_BEGIN(pt);

	//Espera algo, acao dos botoes
	PT_WAIT_UNTIL(pt, isBTN_DOWN(bt1) || isBTN_DOWN(bt2));

		//Se esta no estado de MENU, a pessoa pode escolher as opcoes.
		if(ESTADO == PEGANDO_DADOS){
			//Proximo
			if(isBTN_DOWN(bt1)){
				gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_DOWN, selecionado);
			}
			//Enter
			if(isBTN_DOWN(bt2)){
				OK_pressed = gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_ENTER, selecionado);
				//FIXME: variavel OK_pressed nao resetada ao finalizar cada estado
			}
			//Pegar quando foi selecionado o OK (clicando enter com o spinner no OK.)
			if(OK_pressed == GFX_MONO_SPINCTRL_EVENT_FINISH){
				selecionado[OPT_OK] = OK_OPT_TRUE; OK_pressed = !GFX_MONO_SPINCTRL_EVENT_FINISH;
				clearDisplay(); printString("EXECUTANDO:", 0, 10); printString("PAUSAR         PARAR", 0, 25);
			}

		}else

		//Quando estiver executnado.
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
			//Continuar
			if(isBTN_DOWN(bt1)){
				ESTADO = EXECUTANDO;
				printString("EXECUTANDO:", 0, 10);
				printExecutionSate(EXECUTION);
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

		if(ESTADO == FINALIZADO){
			//Parar
			if(isBTN_DOWN(bt2)){
				ESTADO = PEGANDO_DADOS;
				clearDisplay(); mostraMenuDisplay(&spinners);
			}
		}

		//Espera para nao pegar muitos cliques.
		delay_ms(500);

	//Rerorna para da protothread.
	PT_YIELD(pt);

	//Fim da protothread.
	PT_END(pt);
}

//Pega os dados que a pessoa digitou no display.
/*! \brief Armazena os dados selecionados pelo usuário
 *  Captura e armazena os dados que o usuário selecionou na tela.
 *  \param pt ponteiro de estrutura pt (pThread)
 */
PT_THREAD(pt_pegaDados(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);

	//Sempre pegar os dados e os processa.
	while(1){

		if(ESTADO == PEGANDO_DADOS){
			//Pega as opcoes do display.
			MODO       = (MODE_t ) selecionado[OPT_MODO];
			NIVEL_AGUA = (NIVEL_t) selecionado[OPT_AGUA];
			SECAR      = (SECA_t ) selecionado[OPT_SECAR];

			//Ajusta o nivel, pois ele deve ser um valor.
			switch( (spinner_agua_t) NIVEL_AGUA){
				case  AGUA_OPT_BAIXO: NIVEL_AGUA = BAIXO; break;
				case  AGUA_OPT_MEDIO: NIVEL_AGUA = MEDIO; break;
				case  AGUA_OPT_ALTO : NIVEL_AGUA = ALTO; break;
				default             : NIVEL_AGUA = SENSOR_NIVEL_FULL; break;
			}

			//Pega o OK.
			if(selecionado[OPT_OK] == OK_OPT_TRUE){
				ESTADO = EXECUTANDO;
				selecionado[OPT_OK] = OK_OPT_FALSE;
			}
		}

		//Testes, da pra tirar isso.
		if(MODO == PESADO){
			LED_ON(l1);
		}else{
			LED_OFF(l1);
		}
		if(ESTADO == EXECUTANDO){
			LED_ON(l3);
		}else{
			LED_OFF(l3);
		}

		//Pegar se a tampa esta aberta.
		//CHANGED: Removido o negado do btn
		if(ESTADO == EXECUTANDO && isBTN_UP(bt_tampa) ){
			ESTADO = TAMPA_ABERTA;
			printString("---TAMPA ABERTA---", 10, 10);
			printString("------         PARAR", 0, 25);
		}

		if(ESTADO == TAMPA_ABERTA && isBTN_DOWN(bt_tampa)){
			ESTADO = EXECUTANDO;
			printString("EXECUTANDO:", 0, 10);
			printExecutionSate(EXECUTION);
			printString("PAUSAR         PARAR", 0, 25);
		}

		//Pega o nivel de agua do ADC.
		NIVEL_SENSOR = valorAtualSensor(POTENTIOMETER);

		//Rerorna para da protothread.
		PT_YIELD(pt);
	}
	//Fim da protothread.
	PT_END(pt);
}

/*! \brief Controla a execução do sistema
 *  Controla os estados de execução do sistema em funcionamento. Por exemplo:
 *  Encher, bater,  centrifugar, ...
 *  \param pt ponteiro de estrutura pt (pThread)
 */
PT_THREAD(pt_contorlaExecution(struct pt *pt))
{
	static int time;
	static EXECUTANDO_t Prev_State = PEGANDO_DADOS;

	//Inicia a protothread.
	PT_BEGIN(pt);

	//Sempre pegar os dados e os processas.
	while(1){
		//Modo de execucao.
		//Enxe->Bate->Esvazia->Enxe->Molho->Esvazia->Enxee->Encagua->Esvazia->Centrifufa->Seca.
		//REVIEW: Modificar a sequencia para encher, bater, molho, bater, esvaziar, encher, molho, esvaziar, enxaguar, centrifugar, secar

		//Se tiver executando faz algo, senao  nao tem execucao para controlar.
		if(ESTADO == EXECUTANDO){
			//Controla os subestados. Vai de subestado em subestado.
			switch(EXECUTION){

				case FAZENDO_NADA:
					//Iniciou agora, logo zera o tempo e seta algo para executar.
					time = 0; EXECUTION = ENCHER; Prev_State = FAZENDO_NADA; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
				break;

				case ENCHER:
				//BUG: Fica no estado de encher infinito quando configurado: pesado, medio, vapor
					//Espera ate a agua chegar no valor do nivel selecionado.
					//Se tiver enchendo, temos de saber se encheu para bater ou para fazer outra etapa.
					if(NIVEL_SENSOR >= NIVEL_AGUA){
						//Verificar o que esta sendo feito antes.
						if(Prev_State == FAZENDO_NADA){
							EXECUTION = BATER; Prev_State = BATER; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
						}else

						if(Prev_State == BATER){
							EXECUTION = MOLHO; Prev_State = MOLHO; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
						}else

						if(Prev_State == MOLHO){
							EXECUTION = ENXAGUAR; Prev_State = ENXAGUAR; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
						}
						time = 0;  //Zera o timer.
					}
				break;

				case ESVAZIAR:
					//Espera ate esvaziar.
					if(NIVEL_SENSOR <= SENSOR_NIVEL_ZERO){
						//Verificar o que esta sendo feito antes.
						if(Prev_State == BATER || Prev_State == MOLHO){
							EXECUTION = ENCHER; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
						}else

						if(Prev_State == ENXAGUAR){
							EXECUTION = CENTRIFUGAR; Prev_State = FAZENDO_NADA;printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
						}
						time = 0;  //Zera o timer.
					}
				break;

				case BATER:
					//So espera o tempo acabar.
					if((time > TIME_BATER && MODO == RAPIDO) || (time > 2*TIME_BATER && MODO == NORMAL) || (time > 3*TIME_BATER && MODO == PESADO)){
						EXECUTION = ESVAZIAR; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
					}
				break;

				case MOLHO:
					//So espera o tempo acabar.
					if((time > TIME_MOLHO && MODO == RAPIDO) || (time > 2*TIME_MOLHO && MODO == NORMAL) || (time > 3*TIME_MOLHO && MODO == PESADO)){
						EXECUTION = ESVAZIAR; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
					}
				break;

				case ENXAGUAR:
					//So espera o tempo acabar.
					if((time > TIME_ENXAGUAR && MODO == RAPIDO) || (time > 2*TIME_ENXAGUAR && MODO == NORMAL) || (time > 3*TIME_ENXAGUAR && MODO == PESADO)){
						EXECUTION = ESVAZIAR; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
					}
				break;

				case CENTRIFUGAR:
					//So espera o tempo acabar.
					if((time > TIME_CENTRIFUGAR && MODO == RAPIDO) || (time > 2*TIME_CENTRIFUGAR && MODO == NORMAL) || (time > 3*TIME_CENTRIFUGAR && MODO == PESADO)){
						EXECUTION = SECANDO; time = 0; printExecutionSate(EXECUTION);  //Usado para imprimir o subestado atual.
					}
				break;

				case SECANDO:
					//So espera o tempo acabar.
					if((time > TIME_SECANDO && SECAR == MORNO) || (time > 2*TIME_SECANDO && SECAR == QUENTE) || (time > 3*TIME_SECANDO && SECAR == VAPOR)){
						EXECUTION = FAZENDO_NADA; ESTADO = FINALIZADO; 	printString("---FINALIZADO---", 10, 10); printString("------         PARAR", 0, 25);
					}
				break;

				default:
					concatString("ERRO", 70, 10);  //Usado para imprimir o subestado atual.
				break;
			}

			//Independente do estado o tempo, sempre avanca.
			//Time do sistema. Se der tempo subistituir pelo TIMER do uC (usando o modulo do timer).
			//Nao usar as functions de delay pq elas travam o uC.
			time++;

		}else

		//Se o estado estiver parado, tem que resetar a execucao.
		if(ESTADO == PEGANDO_DADOS){
			EXECUTION = FAZENDO_NADA;
		}
		//Retorna para da protothread.
		PT_YIELD(pt);
	}
	//Fim da protothread.
	PT_END(pt);
}

/*! \brief Controle dos componentes
 *  Aciona os componentes conforme o que estiver ocorrendo no momento.
 *  \param pt ponteiro de estrutura pt (pThread)
 */
PT_THREAD(pt_controlaComponentes(struct pt *pt))
{
	//Inicia a protothread.
	PT_BEGIN(pt);

	while(1){
		//***MOTOR***
		//Estado executando, logo verifica se é para o ligar o motor.
		if(ESTADO == EXECUTANDO && ( EXECUTION == BATER || EXECUTION == CENTRIFUGAR || EXECUTION == SECANDO )){
			LED_ON(l_motor);
		}else{
			LED_OFF(l_motor);
		}

		//***VALVULA***
		//Estado executando, logo verifica se é para colocar agua.
		if(ESTADO == EXECUTANDO && ( EXECUTION == ENCHER || (EXECUTION == SECANDO && SECAR == VAPOR)) ){
			LED_ON(l_valvula);
		}else{
			LED_OFF(l_valvula);
		}

		//***BOMBA***
		//Estado executando, logo verifica se é para o bomba retirar agua.
		if(ESTADO == EXECUTANDO && ( EXECUTION == CENTRIFUGAR || EXECUTION == ESVAZIAR)){
			LED_ON(l_bomba);
		}else{
			LED_OFF(l_bomba);
		}

		//***SECAR***
		//Estado executando, liga quando tiver que secar.
		if(ESTADO == EXECUTANDO && ( EXECUTION == SECANDO) ){
			LED_ON(l_secador);
		}else{
			LED_OFF(l_secador);
		}

		//Rerorna para da protothread.
		PT_YIELD(pt);
	}

	//Fim da protothread.
	PT_END(pt);
}

/*! \brief Função principal
 *  Inciializa o sistema e o mantém em funcionameno por tempo indeterminado.
 */
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

	//Configura o ADC.
	initSensor_NivelAgua();

	//Configura
	configure_usart();
	configure_usart_callbacks();

	//Ativa o intr do sistema
	system_interrupt_enable_global();

	//Gasta tempo e Inicial. Tempo para abrir o terminal e poder ver desde o inicio.
	for(int wt = 0; wt<1000000;wt++){}
	printf("START....................\n\n");

	//Cria as pThread. E Inicializa.
  struct pt pt_gD, pt_pD, pt_cC, pt_cE;
	PT_INIT(&pt_gD); PT_INIT(&pt_pD); PT_INIT(&pt_cC); PT_INIT(&pt_cE);


	//Fica executado para sempre as protoThreads.
	while(1){
		//Fica trocando entre as protothreads.
		pt_gerenciaDisplay(&pt_gD);
		pt_pegaDados(&pt_pD);
		pt_contorlaExecution(&pt_cE);
		pt_controlaComponentes(&pt_cC);
	}

}
