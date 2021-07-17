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



int display_led_config()
{
    int    i   = 0, change_led;
    OUTPUT led = OUT_LED1;
    if (parmac.timer_start == 15 && parmac.timer_stop == 15)
    {
        change_led = 1;
    }
    else if (parmac.timer_start == 0 && parmac.timer_stop == 0)
    {
        change_led = 2;
    }
    else if (parmac.timer_start == 15 && parmac.timer_stop == 0)
    {
        change_led = 3;
    }
    else if (parmac.timer_start == 0 && parmac.timer_stop == 15)
    {
        change_led = 4;
    }
    else
    {
        change_led = 0;
    }

    for (i = 0; i < 4; i++)
    {
        if (i < change_led)
        {
            set_digout(led);
        }
        else
        {
            clear_digout(led);
        }
        led++;
    }

    return 0;
}

static void display_processor()
{
    if (f_new_pag == 1)
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

        display_led_config();

        f_500ms     = 0;
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

            case P_DX: /* --------------------------------------------- */
                saveParMac(parmac);
                Cambio_Pag(PAG_CALIBRAZIONE);
                break;

            case P_SX: /* --------------------------------------------- */
                saveParMac(parmac);
                Cambio_Pag(PAG_CALIBRAZIONE);
                break;

            case P_PIU: /* -------------------------------------------- */
                if (parmac.timer_start == 15 && parmac.timer_stop == 15)
                {
                    parmac.timer_start = 0;
                    parmac.timer_stop  = 0;
                }
                else if (parmac.timer_start == 0 && parmac.timer_stop == 0)
                {
                    parmac.timer_start = 15;
                    parmac.timer_stop  = 0;
                }
                else if (parmac.timer_start == 15 && parmac.timer_stop == 0)
                {
                    parmac.timer_start = 0;
                    parmac.timer_stop  = 15;
                }
                else if (parmac.timer_start == 0 && parmac.timer_stop == 15)
                {
                    Nop();
                }
                else
                {
                    parmac.timer_start = 15;
                    parmac.timer_stop  = 15;
                }

                f_clear_pag = 1;
                break;

            case P_MENO: /* ------------------------------------------- */
                if (parmac.timer_start == 15 && parmac.timer_stop == 15)
                {
                    Nop();
                }
                else if (parmac.timer_start == 0 && parmac.timer_stop == 0)
                {
                    parmac.timer_start = 15;
                    parmac.timer_stop  = 15;
                }
                else if (parmac.timer_start == 15 && parmac.timer_stop == 0)
                {
                    parmac.timer_start = 0;
                    parmac.timer_stop  = 0;
                }
                else if (parmac.timer_start == 0 && parmac.timer_stop == 15)
                {
                    parmac.timer_start = 15;
                    parmac.timer_stop  = 0;
                }
                else
                {
                    parmac.timer_start = 15;
                    parmac.timer_stop  = 15;
                }

                f_clear_pag = 1;
                break;

            default:
                break;
        }
    }
}

PAGINATA pag_config_struct = {
    .d_processor = display_processor,
    .k_processor = keyboard_processor,
    .tipo        = DEF,
};

PAGINATA *PAG_CONFIG = &pag_config_struct;
