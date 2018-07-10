/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: peripherals.c                                                     */
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

#include <stdint.h>
#include "HardwareProfile.h"
#include "peripherals.h"
#include "variabili_parametri_macchina.h"
#include "digout.h"
#include "timer.h"


static int velocita_pwm;
unsigned char n_set_out_run = 0;

char f_pwm_on = 0;


/*Velocita' da 0 a 100. Da 90 in su si considera 100*/
void setVelocita(int velocita) {
    velocita_pwm = velocita;
}


void Init_ZeroCrossing(void)
{
//    CNENBbits.CNIEB7 = 1;
//    CNPUB = 0;
//    CNPDB = 0;
//    IFS1bits.CNIF = 0;
//    IPC4bits.CNIP = 0x06;
//    IEC1bits.CNIE = 1;
    IOCPBbits.IOCPB7    = 1;    /* Interrupt trigger su transizioni low-to-high */
    IOCNBbits.IOCNB7    = 1;    /* Interrupt trigger su transizioni high-to-low */
    
    IOCPUBbits.IOCPUB7  = 0;    /* Disabilitare il pull-up interno */
    IOCPDBbits.IOCPDB7  = 0;    /* Disabilitare il pull-down interno */
    
    IPC4bits.IOCIP      = 0x05; /* maximum priority */
    
    IFS1bits.IOCIF      = 0;    /* Interrupt flag */
    PADCONbits.IOCON    = 1;    /* Interrupt-on-change enable bit */
    IEC1bits.IOCIE      = 1;    /* Interrupt enable bit globale */
    
    
    
//    CORCONbits.IPL3     = 0;    /* CPU Priority Level ???? !!!! ToDO */
    
}





void __attribute__((interrupt, no_auto_psv)) _IOCInterrupt()
//void __attribute__((interrupt, no_auto_psv)) _CNInterrupt()
{
    static uint8_t zero_xing_old = 0;
    unsigned char rit_val_pwm = 0;
    
    if(n_set_out_run==50)
        LED_RUN = ~LED_RUN;
    
    if(n_set_out_run==51) // ~ 1500ns
        LED_RUN = 1;
    
    
    if (f_pwm_on) // < 5usec
    {
        if (velocita_pwm >= 90)
        {
            TRIAC = 1;
        }
        else
        {
            if (ZERO_XING != zero_xing_old)
            {
                TRIAC = 0;
                rit_val_pwm = velocita_pwm;//rampe_velocita_50hz[parmac.rampa][parmac.vel_ventola];
                pwm_off_time = 100 - rit_val_pwm;
                
                if (pwm_off_time <= 10)
                {
                    /* Se e' zero intendo che deve partire subito. Per indicarlo
                     lo metto almeno a 1, se no il timer non vede la differenza e 
                     non fa nulla */
                    pwm_off_time = 1;
                }
                else if (pwm_off_time > 90)
                {
                    /* Se dovressi stare fermo per piu' di 9 ms spegniti direttamente*/
                    TRIAC = 0;
                    pwm_off_time = 0;
                }
                zero_xing_old = ZERO_XING;
            }
        }
    }
    
    if(n_set_out_run==51)
        LED_RUN = 0;
    
//    IFS1bits.CNIF = 0;
    IFS1bits.IOCIF      = 0;
}
