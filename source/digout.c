/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: digout.c                                                          */
/*                                                                            */
/*      gestione OUTPUT                                                       */
/*                                                                            */
/*  Autore: Massimo ZANNA & Sabbiolino (Fabio BARALDI)                        */
/*                                                                            */
/*  Data  : 13/01/2012      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 24/04/2018      REV  : 01.4                                       */
/*                                                                            */
/******************************************************************************/

#include "HardwareProfile.h"
#include "variabili_parametri_macchina.h"
#include "digout.h"
#include "variabili_parametri_sistema.h"

#include "ciclo.h"


char           buf_stato_in_out[3];
char                    fhw_agg_mom_out;







/*----------------------------------------------------------------------------*/
/*  void update_digout (unsigned char dig, val)                               */
/*----------------------------------------------------------------------------*/
void update_digout (OUTPUT dig_out, unsigned char val)
{
    switch (dig_out)
    {
        case OUT_TRIAC:
            OUT_01 = val;
            break;
            
        case OUT_RELE1:
            OUT_02 = val;
            break;
            
        case OUT_RELE2:
            OUT_03 = val;
            break;
            
        case OUT_LED1P1:
            OUT_04 = val;
            break;
            
        case OUT_LED2P1:
            OUT_05 = val;
            break;
            
        case OUT_LED1P2:
            OUT_06 = val;
            break;
            
        case OUT_LED2P2:
            OUT_07 = val;
            break;
            
        case OUT_LED1:
            OUT_08 = val;
            break;
            
        case OUT_LED2:
            OUT_09 = val;
            break;
            
        case OUT_LED3:
            OUT_10 = val;
            break;
            
        case OUT_LED4:
            OUT_11 = val;
            break;
            
        case OUT_LED5:
            OUT_12 = val;
            break;
            
        default:
            break;
    }
}





/*----------------------------------------------------------------------------*/
/*  void set_digout(unsigned char dig)                                        */
/*----------------------------------------------------------------------------*/
void set_digout (OUTPUT dig)
{
    update_digout(dig, 1);
}





/*----------------------------------------------------------------------------*/
/*  void clear_digout(unsigned char dig)                                      */
/*----------------------------------------------------------------------------*/
void clear_digout (OUTPUT dig)
{
    update_digout(dig, 0);
}





/*----------------------------------------------------------------------------*/
/*  char get_digout(unsigned char dig)                                        */
/*----------------------------------------------------------------------------*/
char get_digout (OUTPUT dig)
{
    switch (dig)
    {
        case OUT_TRIAC:
            return(OUT_01);
            
        case OUT_RELE1:
            return(OUT_02);
            
        case OUT_RELE2:
            return(OUT_03);
            
        default:
            return(0xFF);
    }
}





/*----------------------------------------------------------------------------*/
/*  void clear_digout_all                                                     */
/*                                                                            */
/*  azzera tutte le uscite                                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void clear_digout_all (void)
{
    OUT_01 = 0; // 01
    OUT_02 = 0; // 02
    OUT_03 = 0; // 03
    OUT_04 = 0; // 01
    OUT_05 = 0; // 02
    OUT_06 = 0; // 03
    OUT_07 = 0; // 01
    OUT_08 = 0; // 02
    OUT_09 = 0; // 03
    OUT_10 = 0; // 01
    OUT_11 = 0; // 02
    OUT_12 = 0; // 03
}







/*----------------------------------------------------------------------------*/
/*  void set_digout_all                                                       */
/*                                                                            */
/*  setta tutte le uscite                                                     */
/*----------------------------------------------------------------------------*/
void set_digout_all (void)
{
    OUT_01 = 1; // 01
    OUT_02 = 1; // 02
    OUT_03 = 1; // 03
    OUT_04 = 1; // 01
    OUT_05 = 1; // 02
    OUT_06 = 1; // 03
    OUT_07 = 1; // 01
    OUT_08 = 1; // 02
    OUT_09 = 1; // 03
    OUT_10 = 1; // 01
    OUT_11 = 1; // 02
    OUT_12 = 1; // 03
}


