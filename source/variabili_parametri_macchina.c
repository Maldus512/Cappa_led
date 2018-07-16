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

#include "variabili_parametri_macchina.h"
#include "i2c_module2.h"

int old_livello_accesso = 0;

int rampa1[] = {20, 35, 50, 60, 100};
int rampa2[] = {20, 35, 50, 65, 100};
int rampa3[] = {20, 35, 50, 70, 100};
int rampa4[] = {20, 35, 50, 70, 100};


int *rampe_velocita_50hz[NUM_RAMPE] = {rampa1, rampa2, rampa3, rampa4};

/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA parmac = {
    // BASE =========================================================== //
    // -------------------------------------------------------------------------------------------------------------------------------
    // UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    .ver_pack_unpack_par_mac = 0,     // 000      ver.pack/unpack utilizzata per i PARAMETRI MACCHINA
    //          da inserire in testa al pacchetto dati                              n.ro    0-255

    .rampa         = 0,
    .vel_ventola   = 0,
    .potenziometro = 0,
    .timer_start   = 15,
    .timer_stop    = 15,
};


int saveParMac(struct PARAMETRI_MACCHINA p)
{
    return sequentialWrite_24XX16(MEM_16_B0, 0x00, 0x01, (unsigned char *)&p, sizeof(struct PARAMETRI_MACCHINA));
}

int loadParMac(struct PARAMETRI_MACCHINA *p)
{
    return sequentialRead_24XX16(MEM_16_B0, 0x00, 0x01, (unsigned char *)p, sizeof(struct PARAMETRI_MACCHINA));
}
