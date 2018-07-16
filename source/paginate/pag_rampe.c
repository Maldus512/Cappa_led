/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: pag_dummy.c                                                       */
/*                                                                            */
/*      gestione "pagina" (visualizzazione & KEY): dummy                      */
/*                                                                            */
/*  Autore: Maldus(Mattia MALDINI) & Massimo ZANNA                            */
/*                                                                            */
/*  Data  : 07/10/2017      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/
#include <string.h>
#include "HardwareProfile.h"

#include "dispfunz.h"
#include "timer.h"
#include "keyb.h"
#include "variabili_parametri_sistema.h"
#include "digout.h"
#include "variabili_parametri_macchina.h"
#include "peripherals.h"


static void display_processor()
{
    int i;
    OUTPUT led;
    if (f_new_pag==1)
    {
        f_pwm_on = 0;
        clear_digout_all();
        
        f_new_pag = 0;
    }
    
    if (f_clear_pag || f_500ms)
    {
        if (f_500ms) 
        {
            toggle_digout(OUT_LED5);
        }
        
        led = OUT_LED1;
        for (i = 0; i < 4; i++) {
            if (i <= parmac.rampa) {
                set_digout(led);
            }
            else {
                clear_digout(led);
            }
            led++;
        }

        
        f_500ms = 0;
        f_clear_pag = 0;
    }

}



static void keyboard_processor(char cKey)
{
    int *rampa;
    rampa = rampe_velocita_50hz[parmac.rampa];
    
    // gestione tasti senza repeat ========================================== //
    if (cKey != 0 && cKey != 0xFF && OneShot)
    {
        switch (cKey)
        {

            case P_DX: /* --------------------------------------------- */
                Indietro();
                break;

            case P_SX: /* --------------------------------------------- */
                Indietro();
                break;

            case P_PIU: /* -------------------------------------------- */

                if (parmac.rampa < NUM_RAMPE-1)
                    parmac.rampa++;

                saveParMac(parmac);
                f_clear_pag = 1;
                break;

            case P_MENO: /* ------------------------------------------- */
                if (parmac.rampa > 0)
                    parmac.rampa--;

                saveParMac(parmac);
                f_clear_pag = 1;
                break;

            default:
                break;
        }
    }
}

PAGINATA pag_rampe_struct =
{
    .d_processor = display_processor,
    .k_processor = keyboard_processor,
    .tipo = DEF,
};

PAGINATA *PAG_RAMPE = &pag_rampe_struct;
