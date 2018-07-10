/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: timers.c                                                          */
/*                                                                            */
/*      gestione TIMERS                                                       */
/*                                                                            */
/*  Autore: Maldus (Mattia MALDINI) & Massimo ZANNA                           */
/*                                                                            */
/*  Data  : 03/05/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 10/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include "timer.h"

#include "HardwareProfile.h"
#include "digin.h"
#include "ciclo.h"
#include "keyb.h"
#include "digout.h"
#include "peripherals.h"
#include "variabili_parametri_sistema.h"

unsigned int timer_sonde[4] = {0,0,0,0};
unsigned long timer_inibizione_sonde[4] = {0,0,0,0};

char    f_100ms = 0;
char    f_500ms = 0;

int     pwm_off_time = 0;
char    f_blink = 0;
int     t2counter = 0;
int     ct_sec = 0;
static unsigned long long  secondi = 0;


void Init_Timers()
{
    initTimer1();
    initTimer2();
    initTimer3();
}


unsigned long long getTimestamp() {
    return secondi;
}

void initTimer1 (void)
{
    T1CON           = 0x0000;   /* CONFIG TIMER 1mS */
    PR1             = 16000-1;   /* Load pediod register */
// 60MHz    PR1             = 3750-1;   /* Load pediod register */

    TMR1            = 0x00;     /* clear counter */
    
    T1CONbits.TON   = 1;        /* START TIMER 1 */
    T1CONbits.TCS   = 0;        /* get input from internal oscillator */
    T1CONbits.TGATE = 0;
    
    T1CONbits.TCKPS = 0;       /* prescaler 1:1 */
//    T1CONbits.TCKPS = 1;       /* prescaler 1:8 */
    
    IPC0bits.T1IP   = 0x04;     /* Setup Timer1 interrupt for 1 */
    IFS0bits.T1IF   = 0;        /* Clear the Timer1 interrupt status flag */
    IEC0bits.T1IE   = 1;        /* Enable Timer1 interrupts     */
}

void initTimer2()
{    
    T2CON           = 0x0000;   /* CONFIG TIMER 20ms */
    PR2             = 40000-1;  /* load period register */
//60MHz    PR2             = 9375-1;  /* load period register */

    TMR2            = 0x00;     /* clear counter */
    
    T2CONbits.T32   = 0;        /* Disabilita la modalita' 32 bit */
    
    T2CONbits.TON   = 1;        /* START TIMER 2 */
    T2CONbits.TCS   = 0;        /* get input from internal oscillator */
    
    T2CONbits.TCKPS = 01;       /* prescaler 1:8 */
//    T2CONbits.TCKPS = 02;       /* prescaler 1:64 */
    
    IPC1bits.T2IP   = 0x03;     /* Setup Timer1 interrupt for 1 */
    IFS0bits.T2IF   = 0;        /* Clear the Timer1 interrupt status flag */
    IEC0bits.T2IE   = 1;        /* Enable Timer1 interrupts     */
}

void initTimer3()
{
    T3CON           = 0x0000;   /* CONFIG TIMER 100us */
    PR3             = 200-1;    /* load period register */
//60Mhz    PR3             = 375-1;    /* load period register */

    TMR3            = 0x00;     /* clear counter */
    
    T3CONbits.TON   = 1;        /* START TIMER 1 */
    T3CONbits.TCS   = 0;        /* get input from internal oscillator */
    
    T3CONbits.TCKPS = 1;        /* prescaler 1:8 */
    
    IPC2bits.T3IP   = 0x07;     /* Setup Timer3 interrupt priority */
    IFS0bits.T3IF   = 0;        /* Clear the Timer1 interrupt status flag */
    IEC0bits.T3IE   = 1;        /* Enable Timer1 interrupts     */
}





/*----------------------------------------------------------------------------*/
/*  Timer Interrupt 1 - 1 msec                                                */
/*----------------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T1Interrupt (void)       
{
    uint8_t P1_BUF;
    static int counter_1s = 0;
    
    if(n_set_out_run==1)
        LED_RUN = ~LED_RUN;
    
    if(n_set_out_run==2) // ~12us
        LED_RUN = 1;
    
    
    
    
    
    if (counter_1s++ >= 1000 )
    {
        secondi++;
        counter_1s = 0;
        f_blink = ~f_blink;
        if (n_set_out_run==4)
            LED_RUN = ~LED_RUN;
    }
    
    if (ct_ms_tasto_repeat > 0) {
        ct_ms_tasto_repeat--;
    }
    
    
     /* GT ms ANTIRIMBALZO BIT DI INPUT ====================================== */
    P1_BUF = 0;
    
    P1_BUF |= IN_04; // Leggo IN 04
    P1_BUF = P1_BUF << 1;
    P1_BUF |= IN_03; // Leggo IN 03
    P1_BUF = P1_BUF << 1;
    P1_BUF |= IN_02; // Leggo IN 02
    P1_BUF = P1_BUF << 1;
    P1_BUF |= IN_01; // Leggo IN 01
    
    Digin_filter ((DI_FILTER *) &DI_P1, P1_BUF);
    
    if(n_set_out_run==2)
        LED_RUN = 0;
    
    IFS0bits.T1IF = 0;
}





/*----------------------------------------------------------------------------*/
/*  Timer Interrupt 2 - 20 msec                                               */
/*----------------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T2Interrupt (void)       
{
    static int counter_100ms = 0;
    static int counter_500ms = 0;

    
    if(n_set_out_run==20)
        LED_RUN = ~LED_RUN;
    
    if(n_set_out_run==21) // ~40us
        LED_RUN = 1;
    
    
    
    KeyBoard();
    
    t2counter ++;
    
    
    if (counter_100ms++ >= 5)
    {
        counter_100ms = 0;
        f_100ms = 1;
    }
    
    if (counter_500ms++ >= 25)
    {
        counter_500ms = 0;
        f_500ms = 1;
    }
    
    
    if (t2counter > 50)
    {
        t2counter = 0;
        
        if (ct_sec > 0)
        {
            ct_sec--;
        }
    }
        
    if(n_set_out_run==21)
        LED_RUN = 0;
    
    IFS0bits.T2IF = 0;
}





/*----------------------------------------------------------------------------*/
/*  Timer Interrupt 3 - 100 usec                                              */
/*----------------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T3Interrupt (void)       
{
    static int     triac_on_time = 0;
    
    if(n_set_out_run==100)
        LED_RUN = ~LED_RUN;
    
    if(n_set_out_run==101) // ~720ns
        LED_RUN = 1;
    
    
    
    /*
     In questo timer disabilito gli altri 2 durante l'impulso per accendere il triac;
     * Se non lo faccio a volte viene saltato, per motivi non chiari
     */
    if (f_pwm_on)
    {
        if (pwm_off_time > 0)
        {
            TRIAC = 0;
            pwm_off_time--;
            
            if (pwm_off_time == 0)
            {
                triac_on_time = 1;
                TRIAC = 1;
                IEC0bits.T1IE = 0;
                IEC0bits.T2IE = 0;
            }
        }
        else if (triac_on_time > 0)
        {
            triac_on_time--;
            
            if (triac_on_time == 0)
            {
                TRIAC = 0;
                IEC0bits.T1IE = 1;
                IEC0bits.T2IE = 1;
            }
                
        }
    }
    else
    {
        /* Spegni il triac solo se non sono in massima
         velocita' a casusa di un timer */
        TRIAC = 0;
        IEC0bits.T1IE = 1;
        IEC0bits.T2IE = 1;
    }
    
    if(n_set_out_run==101)
        LED_RUN = 0;
    
    IFS0bits.T3IF = 0;
}
