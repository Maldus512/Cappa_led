/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: digout.h                                                          */
/*                                                                            */
/*      gestione OUTPUT                                                       */
/*                                                                            */
/*  Autore: Massimo ZANNA & Sabbiolino (Fabio BARALDI)                        */
/*                                                                            */
/*  Data  : 13/01/2012      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 26/04/2017      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef DIGOUT_H
#define	DIGOUT_H



#define OUT_OBLO_OPEN           9       // OUT associato al chiavistello oblo' (usare COMANDO relativo)
#define OUT_OBLO_CLOSE          10      // OUT associato al chiavistello oblo' (usare COMANDO relativo)

#define NRO_OUT_MAX             16      // limita in TEST n.ro max OUT testabili

#define T_AUTO_OFF_TEST_OUT     4       // tempo AUTO OFF OUTPUT nel TEST OUT in sec


typedef enum {
    OUT_TRIAC = 1,
            OUT_RELE1,
            OUT_RELE2
} OUTPUT;


void init_Digout(void);

void Read_stato_out(void);

void agg_out_mom(void);

void set_digout(OUTPUT dig);

void update_digout(OUTPUT dig, unsigned char val);

void clear_digout(OUTPUT dig);

char get_digout(OUTPUT dig);

void clear_digout_all(void);

void set_digout_all(void);


#endif	/* DIGOUT_H */
