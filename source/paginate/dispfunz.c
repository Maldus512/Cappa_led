/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: dispfunz.c                                                        */
/*                                                                            */
/*      gestione tasti / displeata                                            */
/*                                                                            */
/*  Autore: Maldus(Mattia MALDINI) & Massimo ZANNA                            */
/*                                                                            */
/*  Data  : 07/10/2017      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include "dispfunz.h"
#include "digin.h"
#include "variabili_parametri_sistema.h"



char f_new_pag   = 0;
char f_clear_pag = 0;


PAGINATA *pag_corrente = NULL;
PAGINATA *old_pag      = NULL;




/*----------------------------------------------------------------------------*/
/*  Cambio Pagina Visualizzata                                                */
/*----------------------------------------------------------------------------*/
void Cambio_Pag(PAGINATA *pag)
{
    unsigned char typ;

    old_pag      = pag_corrente;
    pag_corrente = pag;

    typ = pag_corrente->tipo;

    if (typ == TEST)
    {
        f_in_test = 1;
    }
    else
    {
        f_in_test = 0;
    }

    if (typ == PROG_LAV || typ == PROG_MAC || typ == PROG_SET)
        f_in_prog = 1;
    else
        f_in_prog = 0;

    f_clear_pag = 1;
    f_new_pag   = 1;
}

void Indietro() { Cambio_Pag(old_pag); }
