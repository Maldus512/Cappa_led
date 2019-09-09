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
    OUT_TRIAC = 0,
            OUT_RELE1,
            OUT_RELE2,
            OUT_LED1P1,
            OUT_LED2P1,
            OUT_LED1P2,
            OUT_LED2P2,
            OUT_LED1,
            OUT_LED2,
            OUT_LED3,
            OUT_LED4,
            OUT_LED5,
            OUT_LEDP3,
            OUT_LEDP4,
            
            NUM_OUTPUT

} OUTPUT;


void init_Digout(void);



void set_digout(OUTPUT dig);

void update_digout(OUTPUT dig, unsigned char val);

void clear_digout(OUTPUT dig);

char get_digout(OUTPUT dig);

void clear_digout_all(void);

void set_digout_all(void);

#define toggle_digout(out)      update_digout(out, ~get_digout(out))

#endif	/* DIGOUT_H */
