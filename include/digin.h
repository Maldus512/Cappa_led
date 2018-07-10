/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: digin.h                                                           */
/*                                                                            */
/*      gestione INPUT                                                        */
/*                                                                            */
/*  Autore: Massimo ZANNA & Maldus (Mattia MALDINI)                           */
/*                                                                            */
/*  Data  : 22/07/2003      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/04/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef DIGIN_H
#define	DIGIN_H

#include <stdint.h>

#define TRUE        1
#define FALSE       0




// #define T_FILT  4 //    20              /* 20 mS tempo filtro up/down */ mod 02/04/16

typedef struct tagDI_FILTER
{
    unsigned char IN_0;         /* se type=0 stato , se type=1 contatore*/
    unsigned char IN_1;
    unsigned char IN_2;
    unsigned char IN_3;
    unsigned char IN_4;
    unsigned char IN_5;
    unsigned char IN_6;
    unsigned char IN_7;
    unsigned char IN_8;
    
    unsigned char type0:1;      /* 0=ingresso - 1=contatore */
    unsigned char type1:1;
    unsigned char type2:1;
    unsigned char type3:1;
    unsigned char type4:1;
    unsigned char type5:1;
    unsigned char type6:1;
    unsigned char type7:1;
    unsigned char type8:1;
    
    unsigned char I_0_old:1;
    unsigned char I_1_old:1;
    unsigned char I_2_old:1;
    unsigned char I_3_old:1;
    unsigned char I_4_old:1;
    unsigned char I_5_old:1;
    unsigned char I_6_old:1;
    unsigned char I_7_old:1;
    unsigned char I_8_old:1;
    
    unsigned char flt0;
    unsigned char flt1;
    unsigned char flt2;
    unsigned char flt3;
    unsigned char flt4;
    unsigned char flt5;
    unsigned char flt6;
    unsigned char flt7;
    unsigned char flt8;
}DI_FILTER;





typedef enum
{
    BUTTON1 = 0,
            BUTTON2,
            BUTTON3,
            BUTTON4,
} input;

extern DI_FILTER DI_P1;

void Init_Digin_Filter(DI_FILTER*, unsigned char, unsigned char, unsigned char);
uint8_t digitalRead(input i, DI_FILTER* di_filter);
void Digin_filter(DI_FILTER * DI_Filter, unsigned char din);

#endif	/* DIGIN_H */
