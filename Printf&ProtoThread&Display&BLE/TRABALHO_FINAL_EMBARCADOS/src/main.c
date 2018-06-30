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

//Definições do pacote. Tamanho, inicio e fim.
#define VB_M 10
#define STX  0x02
#define ETX  0x03

//

//Liga o motor quando for o momento liga-lo.
PT_THREAD(pt_ligaMotor(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga a bomba quando for o momento liga-lo.
PT_THREAD(pt_ligaBomba(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga a bomba quando for o momento liga-lo.
PT_THREAD(pt_liberaValvula(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Liga o secador quando for o momento liga-lo.
PT_THREAD(pt_ligaSecador(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}	

//Mostra as coisas no display.
PT_THREAD(pt_gerenciaDisplay(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//Pega os dados que a pessoa digitou no display.
PT_THREAD(pt_pegaDados(struct pt *pt, char dado))
{
	
	//Inicia a protothread.
	PT_BEGIN(pt);
	
	//Espera algo.
	PT_WAIT_UNTIL(pt, dado == STX);
	
	//Rerorna para da protothread.
	PT_YIELD(pt);
	
	//Fim da protothread.
	PT_END(pt);
}

//PT que recebe. 
PT_THREAD(protothread_decodifica(struct pt *pt, char dado))
{
  
  static int size = 0;
  static unsigned char chk = 0;
  
  PT_BEGIN(pt);
	//Espera receber o STX;
	PT_WAIT_UNTIL(pt, dado == STX);
		//Iniciou a comunicação, logo espera o proximo dado.
		printf("Recebeu um STX. Inciou a comunicacao.\n");
		PT_YIELD(pt);
		
		//Reativou a protothread, logo pega o QTD_DADO.
		size = (int) dado;
		
		//Pegar os proximos size dados (mensagem).
		printf("Iniciando a receber a mesnagem.\n	");
		while(size > 0){
			PT_YIELD(pt);  //Rerorna para pegar o proximo dado.
			printf("%c", dado);
			chk ^= dado;   //Faz o checksum;
			size--;
		}
		//Pegou todos os dados, logo tem que pegar o checksum.
		PT_YIELD(pt);
		printf("\nCHK = %d\n", dado);
		
		//Verificar se o chk está certo.
		if(chk == dado){
			 printf("CheckSum deu certo.\n");
		}else{
			 printf("CheckSum deu errado.\n");
			 //Sai da PT.
			 PT_EXIT(pt);
		}
		
		//Pegou o chk, logo tem que pegar o final (ETX).
		PT_YIELD(pt);
	
		//Verificar se está certo o ETX.
		if( dado == ETX){
			printf("Fim pacote, ETX recebido.\n");
		}else{
			printf("ERRO: ETX não está correto. Falha ao finalizar a comunicacao.\n");	
		}
		chk = 0; //Reseta o checksum;
  PT_END(pt);
}

#define bt1 BUTTON_1_PIN
#define bt2 BUTTON_2_PIN
#define l1  LED_1_PIN
#define l3  LED_3_PIN

int main(void)
{
	//Inicializa
	system_init();
	
	struct gfx_mono_spinctrl_spincollection spinners;
	
	//Configura o display OLED.
	init_OLED_display(&spinners);
	int16_t tmp[5];
	
	while(1){
			gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_DOWN, tmp);
			gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_ENTER, tmp);
	}
	
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
	
	//Vetor com os valores X.
	unsigned char vetor_bytes[VB_M] = {STX, 0x06, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x01, ETX};
	
	//Cria a pThread. E Inicializa.
    struct pt pt;
	PT_INIT(&pt);
	
	//Fica executado para sempre as protoThreads.
	while(1){
		printf("Inicio do vetor.\n");
		for(int i = 0; i < VB_M; i++){
			protothread_decodifica(&pt, vetor_bytes[i]);  //Ver como mudar a execução da protothread.
			//Gasta tempo para cada char.
			for(int wt = 0; wt<900000;wt++){}
		}
		printf("Fim do vetor.\n\n");
		//Gasta tempo para cada vetor.
		for(int wt = 0; wt<1500000;wt++){}
	}
	
}

