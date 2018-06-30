/*
 * IncFile1.h
 *
 * Created: 26/06/2018 15:24:15
 *  Author: Eduardo Culau
 */ 

//Bibliotecas para fazer as coisas.
#include <asf.h>
#include <stdio.h>
#include <conf_spinctrl.h>
#include <conf_sysfont.h>

#ifndef INCFILE1_H_
#define INCFILE1_H_

enum spinner_options{OPT_MODO = 0, OPT_AGUA, OPT_SECAR, OPT_OK};
enum spinner_modo_suboptions{MODO_OPT_NORMAL = 0, MODO_OPT_RAPIDO, MODO_OPT_PESADO};
enum spinner_agua_suboptions{AGUA_OPT_BAIXO = 0, AGUA_OPT_MEDIO, AGUA_OPT_ALTO};
enum spinner_seca_suboptions{SECA_OPT_MORNO = 0, SECA_OPT_QUENTE, SECA_OPT_VAPOR};
enum spinner_ok_suboptions{OK_OPT_FALSE = 0, OK_OPT_TRUE};

//Functions.
void init_OLED_display(struct gfx_mono_spinctrl_spincollection *spinners);
void mostraMenuDisplay (struct gfx_mono_spinctrl_spincollection *spinners);
void clearDisplay (void);
void clearLine (gfx_coord_t Y, gfx_coord_t X);
void printString (const char* string, gfx_coord_t X, gfx_coord_t Y);
void concatString (const char* string, gfx_coord_t X, gfx_coord_t Y);


#endif /* INCFILE1_H_ */