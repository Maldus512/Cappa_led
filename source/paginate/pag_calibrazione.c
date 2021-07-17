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
#include <stdlib.h>
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
    if (f_new_pag == 1)
    {
        f_pwm_on = 0;
        clear_digout_all();

        f_new_pag = 0;
    }

    if (f_clear_pag || f_100ms)
    {
        if (f_100ms) {
            toggle_digout(OUT_LED5);
        }
        
        set_digout(OUT_LEDP3);
        set_digout(OUT_LEDP4);
        
        if (f_pwm_on)
        {
            set_digout(OUT_LED1P2);
            clear_digout(OUT_LED2P2);
        }
        else
        {
            set_digout(OUT_LED2P2);
            clear_digout(OUT_LED1P2);
        }

        
        size_t i = 0;
        for (i = 0; i < 4; i++) {
            if ((parmac.velocita_accensione & (1 << i)) > 0) {
                set_digout(OUT_LED4 - i);
            } else {
                clear_digout(OUT_LED4 - i);
            }
        }

        f_100ms     = 0;
        f_clear_pag = 0;
    }
}



static void keyboard_processor(char cKey)
{
    // gestione tasti senza repeat ========================================== //
    if (cKey != 0 && cKey != 0xFF && OneShot)
    {
        switch (cKey)
        {

            case P_DX:
                setVelocita(parmac_get_speed(0));
                phasecut_toggle();
                break;

            case P_SX:
                phasecut_disable();
                saveParMac(parmac);
                Cambio_Pag(PAG_PRINCIPALE);
                break;

            case P_PIU:
                if (parmac.velocita_accensione < 10) {
                    parmac.velocita_accensione++;
                    setVelocita(parmac_get_speed(0));
                }
                f_clear_pag = 1;
                break;

            case P_MENO:
                if (parmac.velocita_accensione > 0) {
                    parmac.velocita_accensione--;
                    setVelocita(parmac_get_speed(0));
                }
                f_clear_pag = 1;
                break;
                
            case P_PIU_MENO_SU:
            case P_PIU_MENO_GIU:
                Cambio_Pag(PAG_CONFIG);
                phasecut_disable();
                break;

            default:
                break;
        }
    }
}

PAGINATA pag_calibrazione_struct = {
    .d_processor = display_processor,
    .k_processor = keyboard_processor,
    .tipo        = DEF,
};

PAGINATA *PAG_CALIBRAZIONE = &pag_calibrazione_struct;
