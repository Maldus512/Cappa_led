/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: keyb.h                                                            */
/*                                                                            */
/*      gestione TASTIERA matrice 4x3 max - 3x3 usati                         */
/*                                                                            */
/*  Autore: Massimo ZANNA & Sabbiolino(Fabio BARALDI) & Maldus(Mattia MALDINI)*/
/*                                                                            */
/*  Data  : 08/11/2005      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/*  define                                                                    */
/*----------------------------------------------------------------------------*/

#define MS_REPEAT_LOW   300    // msec
#define MS_REPEAT_MID   100    // msec
#define MS_REPEAT_HIG   40     // msec




//  TASTI - WDS 2017 ------------------------------------ //

#define P_SX            0x01    // [S]
#define P_DX            0x02    // [D]
#define P_GIU           0x01    // [g]
#define P_SU            0x02    // [s]

#define P_PIU           0x03    // [+]
#define P_MENO          0x04    // [-]
#define P_PIU_MENO      0x05


extern unsigned char            OneShot;
extern unsigned int            Key_repeat_cnt;

/*----------------------------------------------------------------------------*/
/*  prototipi funzioni                                                        */
/*----------------------------------------------------------------------------*/

void Init_KeyBoard (void);

unsigned int InKey (void);
unsigned char KeyBoard (void);

typedef struct tagKEYB
{
    unsigned char   nKey;
    unsigned long   cKey;
    unsigned char   timer;
    unsigned char   index;
}KEYB;
