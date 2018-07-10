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





char           out_mom[3];
char           buf_stato_in_out[3];
char                    fhw_agg_mom_out;










/*----------------------------------------------------------------------------*/
/*  aggiornamento out x test HW con buffer "out_mom"                          */
/*----------------------------------------------------------------------------*/
void agg_out_mom (void)
{
    if (fhw_agg_mom_out==1)
    {
        OUT_01 = out_mom[0];
        OUT_02 = out_mom[1];
        OUT_03 = out_mom[2];
    }
}





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
            
        default:
            break;
    }
}





/*----------------------------------------------------------------------------*/
/*  void set_digout(unsigned char dig)                                        */
/*----------------------------------------------------------------------------*/
void set_digout (OUTPUT dig)
{
    switch (dig)
    {
        case OUT_TRIAC:
            OUT_01 = 1;
            break;
            
        case OUT_RELE1:
            OUT_02 = 1;
            break;
            
        case OUT_RELE2:
            OUT_03 = 1;
            break;
                
        default:
            break;
    }
}





/*----------------------------------------------------------------------------*/
/*  void clear_digout(unsigned char dig)                                      */
/*----------------------------------------------------------------------------*/
void clear_digout (OUTPUT dig)
{
    switch (dig)
    {
        case 1:
            OUT_01 = 0;
            break;
            
        case 2: 
            OUT_02 = 0;
            break;
            
        case 3: 
            OUT_03 = 0;
            break;
            
        default:
            break;
    }
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
    if (f_in_test==0)
    {
        OUT_01 = 0; // 01
        OUT_02 = 0; // 02
        OUT_03 = 0; // 03
    }
    
    if (f_in_test==1)
    {
        OUT_01 = 0; // 01
        OUT_02 = 0; // 02
        OUT_03 = 0; // 03
    }
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
}




void Read_stato_out(void)
{
    if (get_digout(1)==0)
    {
        buf_stato_in_out[0] = '0';
    }
    else
    {
        buf_stato_in_out[0] = '1';       
    }
    
    if (get_digout(2)==0)
    {
        buf_stato_in_out[1] = '0';
    }
    else
    {
        buf_stato_in_out[1] = '1';       
    }
    
    if (get_digout(3)==0)
    {
        buf_stato_in_out[2] = '0';
    }
    else
    {
        buf_stato_in_out[2] = '1';       
    }
}
