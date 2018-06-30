/*
 * CFile1.c
 *
 * Created: 26/06/2018 15:23:33
 *  Author: Eduardo Culau
 */ 

//Inclui a biblioteca
#include "display_lib.h"

//Todas as string que serem colocadas no display.
PROGMEM_DECLARE(char, spinner_modo[]) = "Modo:";
PROGMEM_DECLARE(char, spinner_agua[]) = "�gua:";
PROGMEM_DECLARE(char, spinner_secar[]) = "Secar:";
PROGMEM_DECLARE(char, spinCHC_modo_normal[]) = "Nornal";
PROGMEM_DECLARE(char, spinCHC_modo_rapido[]) = "R�pido";
PROGMEM_DECLARE(char, spinCHC_modo_pesado[]) = "Pesado";
PROGMEM_DECLARE(char, spinCHC_agua_baixo[]) = "Baixo";
PROGMEM_DECLARE(char, spinCHC_agua_medio[]) = "Medio";
PROGMEM_DECLARE(char, spinCHC_agua_alto[]) = "Alto";
PROGMEM_DECLARE(char, spinCHC_secar_morno[]) = "Morno";
PROGMEM_DECLARE(char, spinCHC_secar_quente[]) = "Quente";
PROGMEM_DECLARE(char, spinCHC_secar_vapor[]) = "Vapor";

//Op��es para o modo.
PROGMEM_STRING_T spinner_choices_modo[] = {
	spinCHC_modo_normal,
	spinCHC_modo_rapido,
	spinCHC_modo_pesado,
};

//Op��es para a agua.
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
//struct gfx_mono_spinctrl_spincollection modo_collection;
//struct gfx_mono_spinctrl_spincollection agua_collection;
//struct gfx_mono_spinctrl_spincollection secar_collection;
//struct gfx_mono_spinctrl_spincollection spinners;

//Inicializa o display, com tudo. Inicializando tudo e setando os spinners.
void init_OLED_display(struct gfx_mono_spinctrl_spincollection *spinners){
	
	//Inicializa o GFX
	gfx_mono_init();
	
	// Initialize spinners
	gfx_mono_spinctrl_init(&modo, SPINTYPE_STRING, spinner_modo,
	spinner_choices_modo, 0, 2, 0); //Titulo do modo, com as op��es do modo. Sendo 3 op��es.
	gfx_mono_spinctrl_init(&agua, SPINTYPE_STRING, spinner_agua,
	spinner_choices_agua, 0, 2, 0); //Titulo do modo, com as op��es do modo. Sendo 3 op��es.
	gfx_mono_spinctrl_init(&secar, SPINTYPE_STRING, spinner_secar,
	spinner_choices_secar, 0, 2, 0); //Titulo do modo, com as op��es do modo. Sendo 3 op��es.

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