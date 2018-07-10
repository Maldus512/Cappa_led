/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: ciclo.h                                                           */
/*                                                                            */
/*      gestione CICLO centralina                                             */
/*                                                                            */
/*  Autore: Maldus (Mattia MALDINI) & Massimo ZANNA                           */
/*                                                                            */
/*  Data  : 25/03/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/04/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef __CICLO_H__
#define	__CICLO_H__

typedef enum
{
            BASE = 0,
            TRIGGER,
            TEMPORIZZATA,
            TRIGGER_BASE,
            UNDEFINED,
} MODE;

#define S_1_2       0
#define S_3_4       1


#define DELAY           1000
#define DELAY_TRIGGER   2000
#define DELAY_TEMPORIZZATA   5000
#define DELAY_INIBIZIONE    60000UL

extern uint8_t f_allarme_sonde;
extern uint8_t f_allarme_configurazione;



void gt_allarmi(MODE mode);
void gt_ciclo(MODE mode);
MODE readConfiguration();

#endif
