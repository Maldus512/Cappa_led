/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: utility.h                                                         */
/*                                                                            */
/*      routine varie utili                                                   */
/*                                                                            */
/*  Autore: Massimo Zanna                                                     */
/*                                                                            */
/*  Data  : 24/03/2017      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef UTILITY_H
#define	UTILITY_H



// FUNZIONI PER GESTIRE ARRAY SALVATI NELLA SEZIONE EDS ===================== //
//
/* Legge una stringa normale e la scrive in una locazione eds */
void memwrite_eds(__eds__ unsigned char* str, unsigned char * msg, int len);

/* Legge una locazione eds e la copia in una stringa normale */
void memread_eds( unsigned char* str,__eds__ unsigned char * msg, int len);

/* Legge una locazione eds e la scrive in un'altra locazione eds */
void memswitch_eds(__eds__ unsigned char* str,__eds__ unsigned char * msg, int len);

void memcpy_psv(unsigned char* str, __psv__ void * msg, int len);

int mymemcmp(unsigned char* str, __psv__ void * msg, int len);

void rightshift(unsigned char* str, int start, int end);
void leftshift(unsigned char* str, int start, int end);
void wsfill(unsigned char *, int len);
void rstrip(unsigned char* str, int len);
void lstrip(unsigned char* str, int len, char c);
int centeralign(unsigned char* str, int len);
// void writeCenterString(int x, int y, int x2, int y2, char *str, GFONT *f);

int break_lines(char* text, int numLines, int lineLen, char lines[numLines][lineLen]);




// FUNZIONI CONVERSIONE DATI ================================================ //
//

/* converte un dato "long" in ASCII */
void l_to_asc(unsigned long, char *, unsigned char);

void signed_l_to_asc(long, char *, unsigned char);


/* reverse di servizio all "l_to_asc" */
void reverse(char *);

/* BCD to ASCII */
void BCD_to_ASCII(char BCD, char *string);

/* ASCII to BIN */
void ASCII_to_BCD(char *string, char BCD);

#define BCD2BIN(x) ((((x) >> 4) & 0xF) * 10 + ((x) & 0xF))
#define BIN2BCD(x) ((((x) / 10) << 4) | ((x) % 10))

void long_to_array(unsigned char bytes[4], unsigned long n);

// FUNZIONI CRC DATI ======================================================== //
//
/* Calcola il CRC a 32 bit di un buffer dati */
unsigned long int crc_32b(unsigned char *buffer, unsigned int length);
unsigned long int crc_32b_progressive(unsigned char *buffer, unsigned int length, unsigned long int crc);
unsigned long int crc_32b_progressive_eds(__eds__ unsigned char *buffer, unsigned int length, unsigned long int crc);

#endif	/* UTILITY_H */
