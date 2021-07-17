/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: variabili_parametri_macchina.c                                    */
/*                                                                            */
/*      ciclo macchina                                                        */
/*                                                                            */
/*  Autore: Massimo Zanna                                                     */
/*                                                                            */
/*  Data  : 30/04/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef VARIABILI_PARAMETRI_MACCHINA_H
#define	VARIABILI_PARAMETRI_MACCHINA_H

#include <stdlib.h>


#define MAX_RAMPA    5

typedef enum {
    MOTORE_CUSTOM,
    MOTORE_UNO,
    NUMERO_MOTORI
} TIPO_MOTORE;


/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA
{
    unsigned int     vel_ventola;
    unsigned int     velocita_accensione;
    unsigned int     timer_start;
    unsigned int     timer_stop;
};

extern struct PARAMETRI_MACCHINA parmac;


int saveParMac(struct PARAMETRI_MACCHINA p);
int loadParMac(struct PARAMETRI_MACCHINA* p);
void parmac_process_changes(unsigned long timestamp);
void parmac_init(void);
void parmac_watchlist_init(struct PARAMETRI_MACCHINA *p);
void parmac_save_speed(struct PARAMETRI_MACCHINA p);
unsigned int parmac_get_speed(size_t level);

#endif	/* VARIABILI_PARAMETRI_MACCHINA_H */
