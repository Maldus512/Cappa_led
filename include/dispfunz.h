/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: dispfunz.h                                                        */
/*                                                                            */
/*      gestione tasti / displeata                                            */
/*                                                                            */
/*  Autore: Maldus(Mattia MALDINI) & Massimo ZANNA                            */
/*                                                                            */
/*  Data  : 07/10/2017      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 24/04/2018      REV  : 01.4                                       */
/*                                                                            */
/******************************************************************************/

#ifndef DISPFUNZ_H
#define	DISPFUNZ_H
#include <string.h>
#include <stdio.h>



typedef enum 
{
    DEF, TEST, PROG_RIS, PROG_MAC, PROG_LAV, PROG_SET
} TIPOPAG;


typedef struct _paginata
{
    void (*d_processor)(void);
    void (*k_processor)(char);
    TIPOPAG tipo;
} PAGINATA;



extern PAGINATA *pag_corrente;

extern PAGINATA *PAG_PRINCIPALE;
extern PAGINATA *PAG_CONFIG;
extern PAGINATA *PAG_CALIBRAZIONE;





extern char    f_clear_pag;
extern char    f_new_pag;




void Cambio_Pag (PAGINATA *pag);
void Indietro();



#endif	/* DISPFUNZ_H */
