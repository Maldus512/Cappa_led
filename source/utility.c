/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: utility.c                                                         */
/*                                                                            */
/*      routine varie utili                                                   */
/*                                                                            */
/*  Autore: Mattia Maldini & Massimo Zanna                                    */
/*                                                                            */
/*  Data  : 24/03/2017      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/
#include <string.h>

#include "utility.h"

////#include "sgtypes.h"
////#include "gdispcfg.h"
////#include "gdisphw.h"
////#include "GDISP.h"
////#include "gi_fonts.h"



void long_to_array(unsigned char bytes[4], unsigned long n)
{
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
}



/*----------------------------------------------------------------------------*/
/*  Legge una stringa normale e la scrive in una locazione eds                */
/*----------------------------------------------------------------------------*/
void memwrite_eds(__eds__ unsigned char *str, unsigned char *msg, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        str[i] = msg[i];
    }
}

/*----------------------------------------------------------------------------*/
/*  Legge una locazione eds e la copia in una stringa normale                 */
/*----------------------------------------------------------------------------*/
void memread_eds(unsigned char *str, __eds__ unsigned char *msg, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        str[i] = msg[i];
    }
}

/*----------------------------------------------------------------------------*/
/*  Legge una locazione eds e la scrive in un'altra locazione eds             */
/*----------------------------------------------------------------------------*/
void memswitch_eds(__eds__ unsigned char *str, __eds__ unsigned char *msg, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        str[i] = msg[i];
    }
}


void memcpy_psv(unsigned char *str, __psv__ void *msg, int len)
{
    int i = 0;

    __psv__ char *tmp = (__psv__ char *)msg;

    for (i = 0; i < len; i++)
    {
        // str[i] = ((__psv__ LANGUAGE_STRUCT *) msg)->msg[i];
        // str[i] = ((__psv__  unsigned char *)msg)[i];
        str[i] = tmp[i];
    }
}

int mymemcmp(unsigned char *str, __psv__ void *msg, int len)
{
    int i = 0;

    for (i = 0; i < len; i++)
    {
        if (str[i] != ((__psv__ unsigned char *)msg)[i])
        {
            return 1;
        }
        // str[i] = ((__psv__  unsigned char *)msg)[i];
    }
    return 0;
}



int centeralign(unsigned char *str, int len)
{
    int ws = 0, i, size;
    rstrip(str, len);
    lstrip(str, len, ' ');
    size = strlen((char *)str);
    ws   = (len - size) / 2;
    if (ws % 2 != 0)
    {
        ws--;
    }

    if (ws == 0 || size == 0)
    {
        return 0;
    }

    for (i = size + ws - 1; i >= 0; i--)
    {
        if (i >= ws)
        {
            str[i] = str[i - ws];
        }
        else
        {
            str[i] = ' ';
        }
    }

    str[size + ws] = '\0';
    return ws;
}


void rstrip(unsigned char *str, int len)
{
    unsigned int i;
    for (i = len - 1; i > 0; i--)
    {
        if (str[i] != ' ' && str[i] != '\0')
        {
            str[i + 1] = '\0';
            return;
        }
    }
    if (i == 0 && str[0] == ' ')
    {
        str[0] = '\0';
    }
    else if (i == 0)
    {
        str[1] = '\0';
    }
}

void lstrip(unsigned char *str, int len, char c)
{
    int i, last = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] != c)
        {
            last = i;
            break;
        }
    }
    if (last != 0)
    {
        for (i = 0; i < len - last; i++)
        {
            str[i] = str[i + last];
        }
        str[len - last] = '\0';
    }
}




void wsfill(unsigned char *str, int len)
{
    int           i;
    unsigned char finished = 0;
    for (i = 0; i < len; i++)
    {
        if (!finished && str[i] != '\0')
        {
            continue;
        }
        else if (!finished && str[i] == '\0')
        {
            str[i]   = ' ';
            finished = 1;
        }
        else
        {
            str[i] = ' ';
        }
    }
    str[len] = '\0';
}




void rightshift(unsigned char *str, int start, int end)
{
    int i;
    for (i = end; i > start; i--)
    {
        str[i] = str[i - 1];
    }
}

void leftshift(unsigned char *str, int start, int end)
{
    int i;
    for (i = start; i < end; i++)
    {
        str[i] = str[i + 1];
    }
}





// -------------------------------------------------------------------------- //
//  void l_to_asc(unsigned long num,char *s_asc,unsigned char n_cifre)        //
//                                                                            //
//  conversione di una variabile long in stringa ascii                        //
// -------------------------------------------------------------------------- //
void l_to_asc(unsigned long num, char *s_asc, unsigned char n_cifre)
{
    unsigned char i = 0;

    do
    {
        // memorizza cifra significativa nell'array //
        s_asc[i++] = num % 10 + '0';
        num /= 10;
    } while (i < n_cifre);
    s_asc[i] = '\0';

    reverse(s_asc);
}

// -------------------------------------------------------------------------- //
//  void l_to_asc(unsigned long num,char *s_asc,unsigned char n_cifre)        //
//                                                                            //
//  conversione di una variabile long in stringa ascii                        //
// -------------------------------------------------------------------------- //
void signed_l_to_asc(long num, char *s_asc, unsigned char n_cifre)
{
    int i = 0;

    if (num < 0)
    {
        s_asc[n_cifre] = '-';
        num            = -num;
    }
    else
    {
        s_asc[n_cifre] = '+';
    }

    do
    {
        // memorizza cifra significativa nell'array //
        s_asc[i++] = num % 10 + '0';
        num /= 10;
    } while (i < n_cifre);
    s_asc[i + 1] = '\0';

    reverse(s_asc);
}




// -------------------------------------------------------------------------- //
//  void reverse(char * s)                                                    //
//                                                                            //
//  inverte la stringa s sul posto :                                          //
//  esegue un ciclo 'for'(per la lunghezza della stringa) e inverte ogni      //
//  elemento dell'array utilizzando due indici (i,j) che puntano              //
//  all'inizio e alla fine dell'array, con (i) che si incrementa e (j)        //
//  che si decrementa a ogni scambio di elementi                              //
// -------------------------------------------------------------------------- //
void reverse(char *s)
{
    int c;
    int i;
    int j;
    int size;

    size = strlen(s) - 1;

    for (i = 0, j = size; i < j; i++, j--)
    {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/*----------------------------------------------------------------------------*/
/* BCD_to_ASCII.                                                              */
/*----------------------------------------------------------------------------*/
void BCD_to_ASCII(char BCD, char *string)
{
    *string = (((unsigned int)BCD & 0xf0) >> 4) | 0x30;

    if (*string < '0' || *string > '9')
    {
        *string = '0';
    }
    string++;

    *string = ((BCD & 0x0f)) | 0x30;

    if (*string < '0' || *string > '9')
    {
        *string = '0';
    }
}

/*----------------------------------------------------------------------------*/
/* ASCII_to_BCD                                                               */
/*----------------------------------------------------------------------------*/
void ASCII_to_BCD(char *string, char BCD)
{
    BCD = 0;

    if (*string > '0' || *string < '9')
    {
        BCD = ((*string - 0x30) << 4);
    }
    string++;

    if (*string > '0' || *string < '9')
    {
        BCD |= (*string - 0x30);
    }
}





// ----------------------------- crc_32b ------------------------------------ //

/* This is the basic CRC-32 calculation with some optimization but no
table lookup. The the byte reversal is avoided by shifting the crc reg
right instead of left and by using a reversed 32-bit word to represent
the polynomial.
   When compiled to Cyclops with GCC, this function executes in 8 + 72n
instructions, where n is the number of bytes in the input message. It
should be doable in 4 + 61n instructions.
   If the inner loop is strung out (approx. 5*8 = 40 instructions),
it would take about 6 + 46n instructions.



 * Metodo: ISO 3309, ANSI X3.66, FIPS PUB 71, FED-STD-1003, ITU-T V.42, Ethernet,
           SATA, MPEG-2, Gzip, PKZIP, POSIX cksum, PNG, ZMODEM

 * Polinomio Generator Type: Reversed 0xEDB88320

 * Formato Uscita CRC: Little Endian (DCBA)



 */



unsigned long int crc_32b_progressive(unsigned char *buffer, unsigned int length, unsigned long int crc)
{
    int               i, j;
    unsigned long int byte, mask;

    i = 0;

    while (i < length)
    {
        byte = (unsigned long int)buffer[i];     // Get next byte.
        crc  = crc ^ byte;

        for (j = 7; j >= 0; j--)
        {     // Do eight times.
            mask = -(crc & 1);
            crc  = (crc >> 1) ^ (0xEDB88320 & mask);     // Polinomio
        }
        i = i + 1;
    }
    return ~crc;
}


unsigned long int crc_32b(unsigned char *buffer, unsigned int length)
{
    return crc_32b_progressive(buffer, length, 0xFFFFFFFF);
}


unsigned long int crc_32b_progressive_eds(__eds__ unsigned char *buffer, unsigned int length, unsigned long int crc)
{
    int               i, j;
    unsigned long int byte, mask;

    i = 0;
    // crc = 0xFFFFFFFF; // CRC Partenza

    while (i < length)
    {
        byte = (unsigned long int)buffer[i];     // Get next byte.
        crc  = crc ^ byte;

        for (j = 7; j >= 0; j--)
        {     // Do eight times.
            mask = -(crc & 1);
            crc  = (crc >> 1) ^ (0xEDB88320 & mask);     // Polinomio
        }
        i = i + 1;
    }
    return ~crc;
}



int break_lines(char *text, int numLines, int lineLen, char lines[numLines][lineLen])
{
    int len = strlen(text);
    int i, lbreak, lcount, base;
    int step;

    base = 0;

    for (lcount = 0; lcount < numLines; lcount++)
    {
        lines[lcount][0] = '\0';
    }

    for (lcount = 0; lcount < numLines; lcount++)
    {
        lbreak = lineLen - 1;
        step   = base + lineLen - 1;

        if (step > len)
        {
            step   = len;
            lbreak = step;
        }
        else
        {
            for (i = step; i > base; i--)
            {
                if (text[i] == ' ')
                {
                    lbreak = i;
                    break;
                }
            }
        }
        memcpy(lines[lcount], &text[base], lbreak - base);



        if (base + (lbreak - base) >= len)
        {
            lines[lcount][lbreak - base - 0] = '\0';
            break;
        }
        lines[lcount][lbreak - base] = '\0';
        base += lbreak - base;
    }


    //////    memcpy(lines[0], &text[0], 16);     // trucco
    //////    lines[0][16] = 0;
    //////    memcpy(lines[1], &text[16], 16);    // trucco
    //////    lines[1][16] = 0;


    return lcount;
}
