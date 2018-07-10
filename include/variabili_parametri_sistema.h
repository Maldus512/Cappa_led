/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: variabili_parametri_sistema.h                                     */
/*                                                                            */
/*      ciclo macchina                                                        */
/*                                                                            */
/*  Autore: Massimo Zanna & Mattia Maldini                                    */
/*                                                                            */
/*  Data  : 30/06/2016      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 19/03/2018      REV  : 01.2                                       */
/*                                                                            */
/******************************************************************************/

#ifndef VARIABILI_PARAMETRI_SISTEMA_H
#define	VARIABILI_PARAMETRI_SISTEMA_H

#include "HardwareProfile.h"


                           //12345678901234561
#define STR_LEN_CHR_16_1    "                \0"
                           //1234567890123456789012345678
#define STR_LEN_CHR_28_1    "                            \0"






/* -------------------------------------------------------------------------- */
/*  parametri x visualizzazione                                               */
/* -------------------------------------------------------------------------- */
//
extern unsigned char           flag;

extern unsigned char           n_azz;
extern unsigned char           n_var;
extern unsigned int            scorr;
extern unsigned int            n_scorr;
extern char                    f_off_on;
extern char                    fab_off_on;
extern char                    f_vis;

/* -------------------------------------------------------------------------- */
/*  parametri x operazoni generiche                                           */
/* -------------------------------------------------------------------------- */

extern char            f_azzeramento_ram;      // flag di richiesta AZZERAMENTO RAM
extern char            var_check_ram;          // valore ritorno usando operazioni su RAM I2C

extern char            f_in_prog;              // flag che segnala che sono nelle pagine di programmazione



/*----------------------------------------------------------------------------*/
/* Variabili gestione Hardware & Software                                     */
/*----------------------------------------------------------------------------*/
extern char    f_in_test;                  // flag che segnala che sono nelle pagine di test






// TASTIERA ----------------------------------------------------------------- //
extern unsigned int                 mem_tasto[20]; 
extern unsigned char                cOldKey;
extern unsigned char                cAttKey;

extern unsigned char                cTkey;                          // codice tasto touch premuto
extern unsigned char                cTkey;                          // codice tasto touch premuto
extern unsigned char                cBTkey;                         // codice tasto BUTTON touch premuto

extern unsigned char                sense_touch_x;                  // senso "di scorrimento" tocco touch X (LEFT/RIGHT)
extern unsigned char                sense_touch_y;                  // senso "di scorrimento" tocco touch Y (UP/DOWN)
extern unsigned char                old_x_touch;                    // vecchio valore di X sul TOUCH
extern unsigned char                old_y_touch;                    // vecchio valore di Y sul TOUCH

extern unsigned int                 ct_dec_press_bt_key;            // counter decimi secondi BT o KEY premuti

extern unsigned char                ver_pack_unpack_par_hsw;        // 000      ver.pack/unpack utilizzata per i PARAMETRI RISERVATI HSW

extern unsigned int            t_ms_tasto_repeat;          // msec tempo ripetizione tasto premuto
extern unsigned int            ct_ms_tasto_repeat;         // counter msec tempo ripetizione tasto premuto

extern unsigned char           f_no_tasto;



/*----------------------------------------------------------------------------*/
/* Parametri per TEST                                                         */
/*----------------------------------------------------------------------------*/
//
extern unsigned char                       ct_auto_off_test_out;       // secondi per poi AUTO OFF TEST USCITE
extern unsigned char                       f_auto_off_test_out;        // flag secondi per poi AUTO OFF TEST USCITE

#endif	/* VARIABILI_PARAMETRI_SISTEMA_H */
