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


#define SIZE_PAR_MAC        5 // era 106


extern int old_livello_accesso;

#define MAX_RAMPA    5

extern int rampa_velocita_50hz[MAX_RAMPA];


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
// -------------------------------------------------------------------------------------------------------------------------------  UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    int     vel_ventola;
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

#endif	/* VARIABILI_PARAMETRI_MACCHINA_H */
