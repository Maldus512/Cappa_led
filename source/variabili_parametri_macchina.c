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

const int step_rampe[] = {5, 6, 7, 8};

int rampa1[] = {30, 45, 60, 80, 99};
int rampa2[] = {30, 40, 45, 60, 80, 99};
int rampa3[] = {30, 40, 45, 50, 60, 80, 99};
int rampa4[] = {30, 40, 45, 50, 60, 70, 80, 99};


int *rampe_velocita_50hz[MAX_VELOCITA_4R] = {
    rampa1,
    rampa2, 
    rampa3,
    rampa4
};

/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA parmac =
{    
    // BASE =========================================================== //
    // -------------------------------------------------------------------------------------------------------------------------------  UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    .ver_pack_unpack_par_mac = 0,   // 000      ver.pack/unpack utilizzata per i PARAMETRI MACCHINA
                                                        //          da inserire in testa al pacchetto dati                              n.ro    0-255
    
    .lingua = 0,                    // 001                      lingua visualizzazione scritte (0=I,1=GB,2=F,3=E,4=D,5=GR, ...)     n.ro    0-9
    .logo_ditta_vis = 1,            // 002                      logo ditta da visulizzare (0=HSW, 1=ANO, 2=MSG, 3=ROT)              n.ro    0-250
    .rampa = 0,
    .vel_ventola = 0,
    .potenziometro = 0,
    .timer_start = 15,
    .timer_stop = 0,
    .tipo_motore = MOTORE_CUSTOM,
    .rampa_custom = {30, 40, 45, 50, 60, 70, 80, 99},
    .step_rampa_custom = MAX_RAMPA_CUSTOM,
};


int saveParMac(struct PARAMETRI_MACCHINA p) {
    return HDSequentialWriteI2C(MEM_16_B0, 0x00, 0x01, (unsigned char*)&p, sizeof(struct PARAMETRI_MACCHINA));
}

int loadParMac(struct PARAMETRI_MACCHINA* p) {
    return HDSequentialReadI2C(MEM_16_B0, 0x00, 0x01, (unsigned char*)p, sizeof(struct PARAMETRI_MACCHINA));
}
