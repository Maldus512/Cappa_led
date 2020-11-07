/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: variabili_parametri_macchina.c                                    */
/*                                                                            */
/*      ciclo macchina                                                        */
/*                                                                            */
/*  Autore: Massimo Zanna                                                     */
/*                                                                            */
/*  Data  : 30/04/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include <string.h>
#include "variabili_parametri_macchina.h"
#include "i2c_module2.h"

int rampa_velocita_50hz[MAX_RAMPA] = {45, 51, 57, 65, 100};

/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA parmac = {
    // BASE =========================================================== //
    // -------------------------------------------------------------------------------------------------------------------------------
    // UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    .vel_ventola = 0,
    .timer_start = 15,
    .timer_stop  = 15,
};


int saveParMac(struct PARAMETRI_MACCHINA p)
{
    return sequentialWrite_24XX16(MEM_16_B0, 0x00, 0x01, (unsigned char *)&p, sizeof(struct PARAMETRI_MACCHINA));
}

int loadParMac(struct PARAMETRI_MACCHINA *p)
{
    int res = sequentialRead_24XX16(MEM_16_B0, 0x00, 0x01, (unsigned char *)p, sizeof(struct PARAMETRI_MACCHINA));
    if (p->timer_start > 15)
    {
        p->timer_start = 15;
    }
    if (p->timer_stop > 15)
    {
        p->timer_stop = 15;
    }
    if (p->vel_ventola < 0 || p->vel_ventola >= MAX_RAMPA)
        p->vel_ventola = 0;
    return res;
}


int parmacChanged(struct PARAMETRI_MACCHINA *oldparmac, struct PARAMETRI_MACCHINA *curparmac)
{
    return memcmp(oldparmac, curparmac, sizeof(struct PARAMETRI_MACCHINA));
}