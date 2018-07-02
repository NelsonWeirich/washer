 /**
  * \file display_lib.c
  * \brief Biblioteca do Display
  * \details Funções para manipulação do Display
  *
  * \author Eduardo Capellari Culau
  * \author Nelson Roberto Weirich Junior
  *
  * \date 26/06/2018 15:23:33
  * \copyright GNU Public License
  */

#include "display_lib.h"

/*! Todas as string que serão colocadas no display. */
PROGMEM_DECLARE(char, spinner_modo[]) = "Modo:";
PROGMEM_DECLARE(char, spinner_agua[]) = "Nivel:";
PROGMEM_DECLARE(char, spinner_secar[]) = "Secar:";
PROGMEM_DECLARE(char, spinCHC_modo_normal[]) = "Normal";
PROGMEM_DECLARE(char, spinCHC_modo_rapido[]) = "Rapido";
PROGMEM_DECLARE(char, spinCHC_modo_pesado[]) = "Pesado";
PROGMEM_DECLARE(char, spinCHC_agua_baixo[]) = "Baixo";
PROGMEM_DECLARE(char, spinCHC_agua_medio[]) = "Medio";
PROGMEM_DECLARE(char, spinCHC_agua_alto[]) = "Alto";
PROGMEM_DECLARE(char, spinCHC_secar_morno[]) = "Morno";
PROGMEM_DECLARE(char, spinCHC_secar_quente[]) = "Quente";
PROGMEM_DECLARE(char, spinCHC_secar_vapor[]) = "Vapor";

//Opcoes para o modo.
PROGMEM_STRING_T spinner_choices_modo[] = {
	spinCHC_modo_normal,
	spinCHC_modo_rapido,
	spinCHC_modo_pesado,
};

//Opcoes para a agua.
PROGMEM_STRING_T spinner_choices_agua[] = {
	spinCHC_agua_baixo,
	spinCHC_agua_medio,
	spinCHC_agua_alto,
};

//Op��es para secar.
PROGMEM_STRING_T spinner_choices_secar[] = {
	spinCHC_secar_morno,
	spinCHC_secar_quente,
	spinCHC_secar_vapor,
};

//Spinner e collections.
struct gfx_mono_spinctrl modo;
struct gfx_mono_spinctrl agua;
struct gfx_mono_spinctrl secar;

/*! \brief Inicializa o display
 *  Inicializa o display com tudo e seta os spinners.
 *
 * \param spinners um ponteiro da estrutura gfx_mono_spinctrl_spincollection
 *
 */
void init_OLED_display(struct gfx_mono_spinctrl_spincollection *spinners){

	//Inicializa o GFX
	gfx_mono_init();

	// Initialize spinners
	gfx_mono_spinctrl_init(&modo, SPINTYPE_STRING, spinner_modo,
	spinner_choices_modo, 0, 2, 0); //Titulo do modo, com as 3 opcoes do modo.
	gfx_mono_spinctrl_init(&agua, SPINTYPE_STRING, spinner_agua,
	spinner_choices_agua, 0, 2, 0); //Titulo do modo, com as 3 opcoes do modo.
	gfx_mono_spinctrl_init(&secar, SPINTYPE_STRING, spinner_secar,
	spinner_choices_secar, 0, 2, 0); //Titulo do modo, com as 3 opcoes do modo.

	// Initialize spincollection
	gfx_mono_spinctrl_spincollection_init(spinners);
	//gfx_mono_spinctrl_spincollection_init(&agua_collection);
	//gfx_mono_spinctrl_spincollection_init(&secar_collection);

	// Add spinners to spincollection
	gfx_mono_spinctrl_spincollection_add_spinner(&modo, spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&agua, spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&secar, spinners);

	// Show spincollection on screen
	gfx_mono_spinctrl_spincollection_show(spinners);

}

/*! \brief Mostra o menu no display
 *  \param spinners um ponteiro da estrutura gfx_mono_spinctrl_spincollection
 */
void mostraMenuDisplay (struct gfx_mono_spinctrl_spincollection *spinners){
	// Show spincollection on screen
	gfx_mono_spinctrl_spincollection_show(spinners);
}

/*! \brief Limpa display
 *  Reinicia o display. Portanto, apaga a tela atual.
 */
void clearDisplay (void){
		gfx_mono_init();
}

/*! \brief Limpa uma linha do display
 *  \param Y uma variável do tipo gfx_coord_t
 *  \param X uma variável do tipo gfx_coord_t
 */
void clearLine (gfx_coord_t Y, gfx_coord_t X){
	gfx_mono_draw_string("                      ", X, Y, &sysfont);
}

void printString (const char* string, gfx_coord_t X, gfx_coord_t Y){
    clearLine(Y, 0);
	gfx_mono_draw_string(string, X, Y, &sysfont);
}

void concatString (const char* string, gfx_coord_t X, gfx_coord_t Y){
	//clearLine(Y, X);
	gfx_mono_draw_string(string, X, Y, &sysfont);
}

/*! \brief Imprime o estado em execução
 * Imprime o subestado atual de acordo com o parâmetro de entrada.
 * \param exec_state uma variável do estado em execução
 */
void printExecutionSate(EXECUTANDO_t exec_state){
	//Controla os subestados. Vai de subestado em subestado.
	switch(exec_state){

		case FAZENDO_NADA:
			concatString("        ", 70, 10);
		break;

		case ENCHER:
			concatString("ENCHER   ", 70, 10);
		break;

		case BATER:
			concatString("BATER   ", 70, 10);
		break;

		case MOLHO:
			concatString("MOLHO   ", 70, 10);
		break;

		case ENXAGUAR:
			concatString("ENXAGUE ", 70, 10);
		break;

		case ESVAZIAR:
			concatString("ESVAZIAR", 70, 10);
		break;

		case CENTRIFUGAR:
			concatString("CENTRFUG", 70, 10);
		break;

		case SECANDO:
			concatString("SECANDO ", 70, 10);
		break;

		default:
		concatString("ERRO", 70, 10);  //Usado para imprimir o subestado atual.
		break;
	}
}
