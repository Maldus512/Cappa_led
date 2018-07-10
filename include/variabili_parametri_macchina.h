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

#ifndef VARIABILI_PARAMETRI_MACCHINA_H
#define	VARIABILI_PARAMETRI_MACCHINA_H


#define SIZE_PAR_MAC        5 // era 106


extern int old_livello_accesso;

#define MAX_VELOCITA_4R     4  // 8+8+8+8

#define MAX_RAMPA_CUSTOM    8

extern const int step_rampe[];

extern int *rampe_velocita_50hz[MAX_VELOCITA_4R];


typedef enum {
    MOTORE_CUSTOM,
    MOTORE_UNO,
    NUMERO_MOTORI
} TIPO_MOTORE;


/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA
{
// -------------------------------------------------------------------------------------------------------------------------------  UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    char   ver_pack_unpack_par_mac;// 000      ver.pack/unpack utilizzata per i PARAMETRI MACCHINA
                                            //          da inserire in testa al pacchetto dati                                  n.ro    0-255

    unsigned int     lingua;                 
    char    logo_ditta_vis;
    unsigned int     rampa;
    int     vel_ventola;
    char    potenziometro;
    unsigned int     timer_start;
    unsigned int     timer_stop;
    char    tipo_motore;
    int rampa_custom[MAX_RAMPA_CUSTOM];
    int step_rampa_custom;
};

extern struct PARAMETRI_MACCHINA parmac;


int saveParMac(struct PARAMETRI_MACCHINA p);
int loadParMac(struct PARAMETRI_MACCHINA* p);

#endif	/* VARIABILI_PARAMETRI_MACCHINA_H */
