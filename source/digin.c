/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: digin.c                                                           */
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

#include <stdio.h>

#include "HardwareProfile.h"
#include "digin.h"





/*----------------------------------------------------------------------------*/
/*  Ingressi digitali filtrati                                                */
/*----------------------------------------------------------------------------*/
unsigned char P1_BUF;

DI_FILTER DI_P1;

unsigned char T_FILT;





/*----------------------------------------------------------------------------*/
/*  void init_Digin_filter(DI_FILTER *,unsigned char,unsigned char)           */
/*----------------------------------------------------------------------------*/
void Init_Digin_Filter (DI_FILTER *DI_Filter, unsigned char type, unsigned char level, unsigned char antirimbalzo)
{
    T_FILT = antirimbalzo;    // valore di DEFAULT prima di caricare "t_antirimbalzo_input"
    
    typedef union tagDI_INP
    {
        unsigned char din;
        struct INP
        {
            unsigned char b0:1;
            unsigned char b1:1;
            unsigned char b2:1;
            unsigned char b3:1;
            unsigned char b4:1;
            unsigned char b5:1;
            unsigned char b6:1;
            unsigned char b7:1;
            unsigned char b8:1;
        }inp;
    }DI_INP;
    
    DI_INP di_type;
    DI_INP di_level;
    
    di_type.din = type;
    di_level.din = level;
    
    DI_Filter->I_0_old = di_level.inp.b0;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt0 = T_FILT;
    DI_Filter->type0   = di_type.inp.b0 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_1_old = di_level.inp.b1;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt1 = T_FILT;
    DI_Filter->type1   = di_type.inp.b1 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_2_old = di_level.inp.b2;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt2 = T_FILT;
    DI_Filter->type2   = di_type.inp.b2 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_3_old = di_level.inp.b3;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt3 = T_FILT;
    DI_Filter->type3   = di_type.inp.b3 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_4_old = di_level.inp.b4;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt4 = T_FILT;
    DI_Filter->type4   = di_type.inp.b4 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_5_old = di_level.inp.b5;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt5 = T_FILT;
    DI_Filter->type5   = di_type.inp.b5 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_6_old = di_level.inp.b6;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt6 = T_FILT;
    DI_Filter->type6   = di_type.inp.b6 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_7_old = di_level.inp.b7;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt7 = T_FILT;
    DI_Filter->type7   = di_type.inp.b7 ;   /* 0 = ingresso dig */
    
    DI_Filter->I_8_old = di_level.inp.b8;   /* 1 = attivo basso 0 = attivo alto */
    DI_Filter->flt8 = T_FILT;
    DI_Filter->type8   = di_type.inp.b8 ;   /* 0 = ingresso dig */
}





/*----------------------------------------------------------------------------*/
/*  void Digin_filter(DI_FILTER * DI_Filter, unsigned char din)               */
/*----------------------------------------------------------------------------*/
void Digin_filter (DI_FILTER *DI_Filter, unsigned char din)
{
    typedef union tagDI_INP
    {
        unsigned char din;
        struct INP
        {
            unsigned char b0:1;
            unsigned char b1:1;
            unsigned char b2:1;
            unsigned char b3:1;
            unsigned char b4:1;
            unsigned char b5:1;
            unsigned char b6:1;
            unsigned char b7:1;
        }inp;
    }DI_INP;
    
    DI_INP di_in;
    
    di_in.din = din;
    
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 0                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_0_old == di_in.inp.b0)
    {
        DI_Filter->flt0 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt0 == 0)
        {
            DI_Filter->I_0_old = di_in.inp.b0;
            
            if (!DI_Filter->type0)
            {
                if (DI_Filter->I_0_old)
                    DI_Filter->IN_0 = TRUE;
                else
                    DI_Filter->IN_0 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_0_old)
                    DI_Filter->IN_0++;
            }
            DI_Filter->flt0 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 1                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_1_old == di_in.inp.b1)
    {
        DI_Filter->flt1 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt1 == 0)
        {
            DI_Filter->I_1_old = di_in.inp.b1;
            
            if (!DI_Filter->type1)
            {
                if (DI_Filter->I_1_old)
                    DI_Filter->IN_1 = TRUE;
                else
                    DI_Filter->IN_1 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_1_old)
                    DI_Filter->IN_1++;
            }
            DI_Filter->flt1 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 2                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_2_old == di_in.inp.b2)
    {
        DI_Filter->flt2 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt2 == 0)
        {
            DI_Filter->I_2_old = di_in.inp.b2;
            
            if (!DI_Filter->type2)
            {
                if (DI_Filter->I_2_old)
                    DI_Filter->IN_2 = TRUE;
                else
                    DI_Filter->IN_2 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_2_old)
                    DI_Filter->IN_2++;
            }
            DI_Filter->flt2 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 3                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_3_old == di_in.inp.b3)
    {
        DI_Filter->flt3 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt3 == 0)
        {
            DI_Filter->I_3_old = di_in.inp.b3;
            if (!DI_Filter->type3)
            {
                if (DI_Filter->I_3_old)
                    DI_Filter->IN_3 = TRUE;
                else
                    DI_Filter->IN_3 = FALSE;
            }
            else
            {
                if(!DI_Filter->I_3_old)
                    DI_Filter->IN_3++;
            }
            DI_Filter->flt3 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 4                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_4_old == di_in.inp.b4)
    {
        DI_Filter->flt4 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt4 == 0)
        {
            DI_Filter->I_4_old = di_in.inp.b4;
            
            if (!DI_Filter->type4)
            {
                if (DI_Filter->I_4_old)
                    DI_Filter->IN_4 = TRUE;
                else
                    DI_Filter->IN_4 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_4_old)
                    DI_Filter->IN_4++;
            }
            DI_Filter->flt4 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 5                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_5_old == di_in.inp.b5)
    {
        DI_Filter->flt5 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt5 == 0)
        {
            DI_Filter->I_5_old = di_in.inp.b5;
            
            if (!DI_Filter->type5)
            {
                if (DI_Filter->I_5_old)
                    DI_Filter->IN_5 = TRUE;
                else
                    DI_Filter->IN_5 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_5_old)
                    DI_Filter->IN_5++;
            }
            DI_Filter->flt5 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 6                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_6_old == di_in.inp.b6)
    {
        DI_Filter->flt6 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt6 == 0)
        {
            DI_Filter->I_6_old = di_in.inp.b6;
            
            if (!DI_Filter->type6)
            {
                if (DI_Filter->I_6_old)
                    DI_Filter->IN_6 = TRUE;
                else
                    DI_Filter->IN_6 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_6_old)
                    DI_Filter->IN_6++;
            }
            DI_Filter->flt6 = T_FILT;
        }
    }
    /*------------------------------------------------------------------------*/
    /* filtro sul bit 7                                                       */
    /*------------------------------------------------------------------------*/
    if (DI_Filter->I_7_old == di_in.inp.b7)
    {
        DI_Filter->flt7 = T_FILT;
    }
    else
    {
        if (--DI_Filter->flt7 == 0)
        {
            DI_Filter->I_7_old = di_in.inp.b7;
            
            if (!DI_Filter->type7)
            {
                if (DI_Filter->I_7_old)
                    DI_Filter->IN_7 = TRUE;
                else
                    DI_Filter->IN_7 = FALSE;
            }
            else
            {
                if (!DI_Filter->I_7_old)
                    DI_Filter->IN_7++;
            }
            DI_Filter->flt7 = T_FILT;
        }
    }
}





/* Funzione: digitalRead
 * Lettura di un pin digitale di input (8 in tutto).
 * --------
 *  i: 
 */
uint8_t digitalRead(input i, DI_FILTER *di_filter)
{
    switch (i)
    {
        case BUTTON1:
            return di_filter->IN_0;
            break;
        case BUTTON2:
            return di_filter->IN_1;
            break;
        case BUTTON3:
            return di_filter->IN_2;
            break;
        case BUTTON4:
            return di_filter->IN_3;
            break;
    }
    return 0;
}