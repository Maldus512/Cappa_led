/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: variabili_parametri_sistema.c                                     */
/*                                                                            */
/*      ciclo macchina                                                        */
/*                                                                            */
/*  Autore: Massimo Zanna                                                     */
/*                                                                            */
/*  Data  : 30/06/2016      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 14/03/2018      REV  : 01.2                                       */
/*                                                                            */
/******************************************************************************/

#include "HardwareProfile.h"
#include "variabili_parametri_sistema.h"


/* -------------------------------------------------------------------------- */
/*  parametri x visualizzazione                                               */
/* -------------------------------------------------------------------------- */
//
unsigned char           flag = 0;

unsigned char           n_azz = 0;
unsigned char           n_var = 0;
unsigned int            scorr = 0;
unsigned int            n_scorr = 0;
char                    f_off_on = 0;
char                    fab_off_on = 0;
char                    f_vis = 0;


/* -------------------------------------------------------------------------- */
/*  parametri x operazoni generiche                                           */
/* -------------------------------------------------------------------------- */
//
 char           f_azzeramento_ram = 0;      // flag di richiesta AZZERAMENTO RAM
 char           var_check_ram = 0;          // valore ritorno usando operazioni su RAM I2C

 char           f_in_prog = 0;              // flag che segnala che sono nelle pagine di programmazione


/*----------------------------------------------------------------------------*/
/* Variabili gestione Hardware & Software                                     */
/*----------------------------------------------------------------------------*/
//
 char           f_in_test = 0;              // flag che segnala che sono nelle pagine di test



// TASTIERA ----------------------------------------------------------------- //
unsigned int                        mem_tasto[20]; 
unsigned char                       cOldKey = 0;
unsigned char                       cAttKey = 0;

unsigned char                       cTkey = 0;                      // codice tasto touch premuto
unsigned char                       cBTkey = 0;                     

unsigned char                       sense_touch_x = 0;              // senso "di scorrimento" tocco touch X (LEFT/RIGHT)
unsigned char                       sense_touch_y = 0;              // senso "di scorrimento" tocco touch Y (UP/DOWN)
unsigned char                       old_x_touch = 0;                // vecchio valore di X sul TOUCH
unsigned char                       old_y_touch = 0;                // vecchio valore di Y sul TOUCH

unsigned int                        ct_dec_press_bt_key = 0;        // counter decimi secondi BT o KEY premuti

unsigned char                       ver_pack_unpack_par_hsw = 0;    // 000      ver.pack/unpack utilizzata per i PARAMETRI RISERVATI HSW

unsigned int            t_ms_tasto_repeat = 0;          // msec tempo ripetizione tasto premuto
unsigned int            ct_ms_tasto_repeat = 0;         // counter msec tempo ripetizione tasto premuto

unsigned char           f_no_tasto = 0;


/*----------------------------------------------------------------------------*/
/* Parametri per TEST                                                         */
/*----------------------------------------------------------------------------*/
//
unsigned char                       ct_auto_off_test_out = 0;       // secondi per poi AUTO OFF TEST USCITE
unsigned char                       f_auto_off_test_out = 0;        // flag secondi per poi AUTO OFF TEST USCITE