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


static unsigned long long timer_start = 0;
static unsigned long long timer_stop  = 0;


static void display_processor()
{
    unsigned int              timer       = 0;
    static unsigned long long last_second = 0;
    static char               blink       = 0;
    int                       i;
    OUTPUT                    led;
    
    set_digout(OUT_LEDP3);
    set_digout(OUT_LEDP4);

    if (timer_start != 0)
    {
        timer = parmac.timer_start - (unsigned int)(getTimestamp() - timer_start);
    }
    else if (timer_stop != 0)
    {
        timer = parmac.timer_stop - (unsigned int)(getTimestamp() - timer_stop);
    }
    else
    {
        timer = 0;
    }

    if (last_second != getTimestamp())
    {
        f_clear_pag = 1;
        last_second = getTimestamp();
    }

    if (f_new_pag == 1)
    {
        phasecut_disable();
        f_new_pag = 0;
    }

    if (f_clear_pag || f_1s)
    {
        if (f_1s)
        {
            blink = 1 - blink;
        }

        if (get_digout(OUT_RELE2))
        {
            set_digout(OUT_LED1P1);
            clear_digout(OUT_LED2P1);
        }
        else
        {
            set_digout(OUT_LED2P1);
            clear_digout(OUT_LED1P1);
        }

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




        led = OUT_LED1;
        if (timer != 0 && blink)
        {
            for (i = 0; i < MAX_RAMPA; i++)
            {
                clear_digout(led);
                led++;
            }
        }
        else
        {
            for (i = 0; i < MAX_RAMPA; i++)
            {
                if (i <= parmac.vel_ventola)
                {
                    set_digout(led);
                }
                else
                {
                    clear_digout(led);
                }

                led++;
            }
        }



        f_1s        = 0;
        f_clear_pag = 0;
    }

    if (timer_start != 0 && getTimestamp() - timer_start >= parmac.timer_start)
    {
        set_digout(OUT_RELE1);
        setVelocita(parmac_get_speed(parmac.vel_ventola));
        timer_start = 0;
        f_pwm_on    = 1;
        f_clear_pag = 1;
    }
    else if (timer_stop != 0 && getTimestamp() - timer_stop >= parmac.timer_stop)
    {
        timer_stop  = 0;
        f_pwm_on    = 0;
        f_clear_pag = 1;
    }
}



static void keyboard_processor(char cKey)
{
    char        f_passwordOk        = 0;
    const char  password[4]         = {P_PIU_MENO_GIU, P_PIU_MENO_SU, P_PIU_MENO_GIU, P_PIU_MENO_SU};
    static char passwordInserita[4] = {0};
    static int  index               = 0;
    int         i;

    if (cKey == 0x00)
    {
        index = 0;
    }

    // gestione tasti senza repeat ========================================== //
    if (OneShot)
    {
        switch (cKey)
        {
            case P_DX: /* --------------------------------------------- */
                if (f_pwm_on && timer_start == 0)
                {
                    if (parmac.timer_stop == 0 && timer_stop == 0)
                    {
                        clear_digout(OUT_RELE1);
                        phasecut_disable();
                    }
                    else if (timer_stop == 0)
                    {
                        setVelocita(100);
                        phasecut_enable();
                        clear_digout(OUT_RELE1);
                        timer_stop = getTimestamp();
                    }
                }
                else
                {
                    if (parmac.timer_start == 0 && timer_start == 0)
                    {
                        set_digout(OUT_RELE1);
                        setVelocita(parmac_get_speed(parmac.vel_ventola));
                        phasecut_enable();
                    }
                    else if (timer_start == 0)
                    {
                        setVelocita(100);
                        phasecut_enable();
                        timer_start = getTimestamp();
                    }
                }
                f_clear_pag = 1;
                break;

            case P_SX: /* --------------------------------------------- */
                if (get_digout(OUT_RELE2))
                {
                    clear_digout(OUT_RELE2);
                }
                else
                {
                    set_digout(OUT_RELE2);
                }
                f_clear_pag = 1;
                break;

            case P_PIU: /* -------------------------------------------- */

                if (timer_start == 0 && timer_stop == 0 && parmac.vel_ventola < MAX_RAMPA - 1)
                {
                    parmac.vel_ventola++;
                    /* Setta la velocita solo se non sono in attesa di un timer*/
                    setVelocita(parmac_get_speed(parmac.vel_ventola));
                }

                f_clear_pag = 1;
                break;

            case P_MENO: /* ------------------------------------------- */
                if (timer_start == 0 && timer_stop == 0 && parmac.vel_ventola > 0)
                {
                    parmac.vel_ventola--;
                    /* Setta la velocita solo se non sono in attesa di un timer*/
                    setVelocita(parmac_get_speed(parmac.vel_ventola));
                }

                f_clear_pag = 1;
                break;

            case P_PIU_MENO_SU:
            case P_PIU_MENO_GIU:
                if (timer_start == 0 && timer_stop == 0)
                {
                    passwordInserita[index++] = cKey;

                    if (index == 4)
                    {
                        index        = 0;
                        f_passwordOk = 1;
                        for (i = 0; i < 4; i++)
                        {
                            if (passwordInserita[i] != password[i])
                            {
                                f_passwordOk = 0;
                                break;
                            }
                        }
                    }
                    if (f_passwordOk && f_pwm_on == 0)
                        Cambio_Pag(PAG_CALIBRAZIONE);
                }
                break;

            default:
                break;
        }
    }
}

PAGINATA pag_principale_struct = {
    .d_processor = display_processor,
    .k_processor = keyboard_processor,
    .tipo        = DEF,
};

PAGINATA *PAG_PRINCIPALE = &pag_principale_struct;
