/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: peripherals.h                                                     */
/*                                                                            */
/*      gestione PERIFERICHE                                                  */
/*                                                                            */
/*  Autore: Maldus (Mattia MALDINI) & Massimo ZANNA                           */
/*                                                                            */
/*  Data  : 30/04/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__



extern unsigned char n_set_out_run;

extern char f_pwm_on;
extern unsigned char p_val_pwm;
extern char f_timer_max_velocita;

void phasecut_enable(void);
void phasecut_disable(void);
void phasecut_toggle(void);
void setVelocita(int velocita);
void Init_ZeroCrossing();

#endif
