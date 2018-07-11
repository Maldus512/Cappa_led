/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: keyb.c                                                            */
/*                                                                            */
/*      gestione TASTIERA matrice 4x3 max - 3x3 usati                         */
/*                                                                            */
/*  Autore: Massimo ZANNA & Sabbiolino(Fabio BARALDI) & Maldus(Mattia MALDINI)*/
/*                                                                            */
/*  Data  : 08/11/2005      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "HardwareProfile.h"
#include "variabili_parametri_sistema.h"
#include "digin.h"
#include "keyb.h"

#define NUM_RIGHE   3       // uscite
#define NUM_COLONNE 4       // ingressi



unsigned char tasto;

unsigned char           incremento = 0;
unsigned int            Key_repeat_cnt = 0;
unsigned int            Key_stop_cnt = 0;

char                    f_on_retro_lcd;

unsigned char           OneShot = 0;

unsigned char           DEBOUNCE_PULSANTI = 1;  // 20*001-0020ms

unsigned char           T1_PULSANTI = 30;       // 20*030-0600ms
unsigned char           T2_PULSANTI = 60;       // 20*060-1200
unsigned char           T3_PULSANTI = 90;       // 20*090-1800
unsigned char           T4_PULSANTI = 120;      // 20*120-2400
unsigned char           T5_PULSANTI = 150;      // 20*150-3000
unsigned char           T6_PULSANTI = 250;      // 20*250-5000ms

unsigned char           n_rip_tas;
unsigned long           n_rip_tas_ko;





/*----------------------------------------------------------------------------*/
/*  Combinazioni matrice tastiera permesse                                    */
/*----------------------------------------------------------------------------*/

const KEYB Ckeyboard[] = //          NR  STD HSW
{
    {0x05, 0x0003}, //          05  P_MENO + P_PIU  [T]
    
    {0x01, 0x0008}, //          01  P_SX            [S]
    {0x02, 0x0004}, //          02  P_DX            [D]
    {0x03, 0x0001}, //          03  P_PIU           [+]
    {0x04, 0x0002}, //          04  P_MENO          [-]

    {0, 0}
};





/*----------------------------------------------------------------------------*/
/*  Gestione TASTIERA                                                         */
/*----------------------------------------------------------------------------*/
unsigned char KeyBoard(void)
{
    unsigned int nKey = 0;
    unsigned char cKey = 0;
    unsigned char x = 0;
    
    n_rip_tas = 0;
    
//    if (pag_corrente == NULL)
//        return(0);
        
    nKey = InKey ();
    
    
    
    
    
    
    if (nKey) // CP se ho premuto un tasto
    {
        cKey = 0xFF; // inizializzo codice tasto a un valore NON VALIDO
        
        while (Ckeyboard[x].cKey) // ricerco CODICE TASTO VALIDO
        {
            //fino a fine vettore
            if (Ckeyboard[x].cKey == nKey)
            {
                cKey = Ckeyboard[x].nKey;
                break;
            }
            x++;
        }
        
        /*----------------------------------------------------------------*/
        /* aggiorna solo se il codice tasto VALIDO                        */
        /*----------------------------------------------------------------*/
        if (cKey != 0xFF)
        {
            /*------------------------------------------------------------*/
            /* se il tasto e' uguale al precedente gestisce il repeat     */
            /*------------------------------------------------------------*/
            if (cKey == cOldKey)
            {
                OneShot = 0;
                Key_repeat_cnt++;
                Key_stop_cnt = Key_repeat_cnt / 5; // => decimi sec (20msec * 5 = 100msec = 0,1sec) !!!! ToDO
//////                Key_stop_cnt++;     // => decimi sec (20msec * 5 = 100msec = 0,1sec) !!!! ToDO

                if (Key_repeat_cnt > DEBOUNCE_PULSANTI)
                {
                    if (Key_repeat_cnt < T1_PULSANTI)
                    {
                        t_ms_tasto_repeat = 800;
                    }
                    else
                    {
                        if (Key_repeat_cnt < T2_PULSANTI)
                        {
                            t_ms_tasto_repeat = 600;
                        }
                        else
                        {
                            if (Key_repeat_cnt < T3_PULSANTI)
                            {
                                t_ms_tasto_repeat = 400;
                            }
                            else
                            {
                                if (Key_repeat_cnt < T4_PULSANTI)
                                {
                                    t_ms_tasto_repeat = 200;
                                }
                                else
                                {
                                    if (Key_repeat_cnt < T5_PULSANTI)
                                    {
                                        t_ms_tasto_repeat = 100;
                                    }
                                        if (Key_repeat_cnt < T6_PULSANTI)
                                        {
                                            t_ms_tasto_repeat = 80;
                                        }
                                        else
                                        {
                                        t_ms_tasto_repeat = 20;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else // tasto != cOldKey
            {
                incremento = 0;
                Key_repeat_cnt = 0;
                Key_stop_cnt = 0;
                
                OneShot = 1;
            }
        }
        else // combinazione tasti non valida => azzero i repeat
        {
            incremento = 0;
            Key_repeat_cnt = 0;
            Key_stop_cnt = 0;
            f_no_tasto = 0;
            OneShot = 0;
        }
        
        /* Memorizza sempre ultimo tasto premuto */
        cOldKey = cKey;
        cAttKey = cKey; // !!!!
    }
    else // nessun tasto premuto
    {
        if (cOldKey != 0xFF)
        {
            //per gestire eventi al rilascio
//            pag_corrente->k_processor(0);
        }
        /* Reset repeat counter se nessun tasto premuto */
        incremento = 0;
        Key_repeat_cnt = 0;
        Key_stop_cnt = 0;
        f_no_tasto = 0;
        OneShot = 0;
        cOldKey = 0xFF;
    }
    return (cKey);
//    return (0);
}





/*----------------------------------------------------------------------------*/
/*  Gestione "scansione" Rig e Col matrice - NB: non sente 2 tasti stessa Col */
/*----------------------------------------------------------------------------*/
unsigned int InKey(void)
{
    unsigned int nKey = 0x0000;
    
    nKey |= digitalRead(BUTTON4, &DI_P1);
    nKey |= digitalRead(BUTTON3, &DI_P1) << 1;
    nKey |= digitalRead(BUTTON2, &DI_P1) << 2;
    nKey |= digitalRead(BUTTON1, &DI_P1) << 3;

//    nKey = ~nKey; 
    return (nKey);
}