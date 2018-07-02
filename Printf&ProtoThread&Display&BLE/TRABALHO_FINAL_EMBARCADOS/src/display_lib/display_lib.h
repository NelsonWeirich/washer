/**
 * \file display_lib.h
 * \brief Biblioteca do display
 * \details Funções para manipulação do Display
 *
 * \author Eduardo Capellari Culau
 * \author Nelson Roberto Weirich Junior
 *
 * \date 26/06/2018 15:23:33
 * \copyright GNU Public License
 */

#include <asf.h>
#include <stdio.h>
#include <conf_spinctrl.h>
#include <conf_sysfont.h>

#ifndef INCFILE1_H_
#define INCFILE1_H_

/*! Opções do menu */
enum spinner_options{OPT_MODO = 0, OPT_AGUA, OPT_SECAR, OPT_OK};
/*! Opções do submenu MODO */
enum spinner_modo_suboptions{MODO_OPT_NORMAL = 0, MODO_OPT_RAPIDO, MODO_OPT_PESADO};
/*! Opções do submenu NIVEL */
typedef enum spinner_agua_suboptions{AGUA_OPT_BAIXO = 0, AGUA_OPT_MEDIO, AGUA_OPT_ALTO} spinner_agua_t;
/*! Opções do submenu SECAR */
enum spinner_seca_suboptions{SECA_OPT_MORNO = 0, SECA_OPT_QUENTE, SECA_OPT_VAPOR};
/*! Opções do botão OK */
enum spinner_ok_suboptions{OK_OPT_FALSE = 0, OK_OPT_TRUE};

/*! Estados de operação da máquina. */
typedef enum subEstado{
	ENCHER,
	ESVAZIAR,
	BATER,
	MOLHO,
	ENXAGUAR,
	CENTRIFUGAR,
	SECANDO,
	FAZENDO_NADA
}EXECUTANDO_t;

//Functions.
void init_OLED_display(struct gfx_mono_spinctrl_spincollection *spinners);
void mostraMenuDisplay (struct gfx_mono_spinctrl_spincollection *spinners);
void clearDisplay (void);
void clearLine (gfx_coord_t Y, gfx_coord_t X);
void printString (const char* string, gfx_coord_t X, gfx_coord_t Y);
void concatString (const char* string, gfx_coord_t X, gfx_coord_t Y);
void printExecutionSate(EXECUTANDO_t exec_state);

#endif /* INCFILE1_H_ */
