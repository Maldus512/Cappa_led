/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: timers.h                                                          */
/*                                                                            */
/*      gestione TIMERS                                                       */
/*                                                                            */
/*  Autore: Maldus (Mattia MALDINI) & Massimo ZANNA                           */
/*                                                                            */
/*  Data  : 25/03/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef __TIMER_H__
#define	__TIMER_H__

void Init_Timers (void);

unsigned long long getTimestamp();

void initTimer1 (void);
void initTimer2 (void);
void initTimer3 (void);

extern char     f_100ms;
extern char     f_500ms;

extern char     f_blink;
extern int      pwm_off_time;
extern char f_update_display;

#endif
