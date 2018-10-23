/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: HardwareProfile.h                                                 */
/*                                                                            */
/*      definizione di tutti i BIT utilizzati nell' HW                        */
/*                                                                            */
/*  Autore: Sabbiolino(Fabio BARALDI) & Madus(Mattia MALDINI) & Massimo ZANNA */
/*                                                                            */
/*  Data  : 01/05/2016      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 03/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#ifndef HARDWAREPROFILE_H
#define	HARDWAREPROFILE_H

#include <xc.h>

#define OUT                     0
#define IN                      1
#define OUTPUT_PIN              OUT
#define INPUT_PIN               IN

#define DEBOUNCE                5   // 5msec



#define LED_RUN_TRIS            TRISBbits.TRISB8
#define LED_RUN                 LATBbits.LATB8


// TODO: READ_WRITE dovrebbe essere RB2
#define DISP_READ_WRITE_TRIS    TRISBbits.TRISB3




//  KEYBOARD ================================================================ //
//
#define KEY_1                   !PORTBbits.RB1
#define KEY_1_TRIS              TRISBbits.TRISB1
#define KEY_2                   !PORTBbits.RB4
#define KEY_2_TRIS              TRISBbits.TRISB4
#define KEY_3                   !PORTCbits.RC6
#define KEY_3_TRIS              TRISCbits.TRISC6
#define KEY_4                   !PORTCbits.RC7
#define KEY_4_TRIS              TRISCbits.TRISC7



//  INPUT ===========+++===================================================== //
//
#define IN_01                   KEY_1
#define IN_02                   KEY_2
#define IN_03                   KEY_3
#define IN_04                   KEY_4

#define IN_05                   PORTBbits.RB7
#define ZERO_XING_TRIS          TRISBbits.TRISB7
#define ZERO_XING               IN_05



//  GENERIC OUTPUTS ========================================================= //
//
#define OUT_01                  LATCbits.LATC8
#define OUT_01_TRIS             TRISCbits.TRISC8
#define OUT_02                  LATBbits.LATB9
#define OUT_02_TRIS             TRISBbits.TRISB9
#define OUT_03                  LATCbits.LATC9
#define OUT_03_TRIS             TRISCbits.TRISC9


// LEDs
#define OUT_04                  LATBbits.LATB0
#define OUT_04_TRIS             TRISBbits.TRISB0
#define OUT_05                  LATBbits.LATB2
#define OUT_05_TRIS             TRISBbits.TRISB2
#define OUT_06                  LATBbits.LATB3
#define OUT_06_TRIS             TRISBbits.TRISB3
#define OUT_07                  LATCbits.LATC0
#define OUT_07_TRIS             TRISCbits.TRISC0
#define OUT_08                  LATCbits.LATC1
#define OUT_08_TRIS             TRISCbits.TRISC1
#define OUT_09                  LATCbits.LATC2
#define OUT_09_TRIS             TRISCbits.TRISC2
#define OUT_10                  LATCbits.LATC3
#define OUT_10_TRIS             TRISCbits.TRISC3
#define OUT_11                  LATCbits.LATC5
#define OUT_11_TRIS             TRISCbits.TRISC5
#define OUT_12                  LATCbits.LATC4
#define OUT_12_TRIS             TRISCbits.TRISC4


#define TRIAC                   OUT_01
#define RELE1                   OUT_02
#define RELE2                   OUT_03



//  I2C ===================================================================== //
//
#define I2C_CLK                 LATAbits.LATA1
#define I2C_CLK_TRIS            TRISAbits.TRISA1
#define I2C_DATA_OUT            LATAbits.LATA0      //PORTBbits.RB11    
#define I2C_DATA_IN             PORTAbits.RA0
#define I2C_DATA_TRIS           TRISAbits.TRISA0
//#define WRITE_PROTECT           LATBbits.LATB7      //PORTBbits.RB7
//#define WRITE_PROTECT_TRIS      TRISBbits.TRISB7


#define I2C_MODULE              0
#define I2C_BITBANG             1
#define I2C_MODE                I2C_BITBANG
#define MEM_24XX16              0
#define RAM_TYPE                MEM_24XX16

//  I2C memory parameters ------------------------------- //
#define HIGH_ADD_LIMIT  0x07
#define RAM_TYPE        MEM_24XX16
#define HIGH_ADDRESS    FALSE

#define MEM_16_B0       0xA0

#define BLOCK_SIZE      0x100
#define PAGE_SIZE       0x10
#define MEM_SIZE        0x800   // 2 Kbyte




// PIN Inutilizzati ========================================================= //

#define UNUSED0_TRIS            TRISAbits.TRISA2
#define UNUSED1_TRIS            TRISAbits.TRISA7
#define UNUSED2_TRIS            TRISAbits.TRISA10

#define UNUSED4_TRIS            TRISBbits.TRISB12
#define UNUSED5_TRIS            TRISBbits.TRISB13
#define UNUSED6_TRIS            TRISBbits.TRISB14
#define UNUSED7_TRIS            TRISBbits.TRISB15




#define UNUSED0                 LATAbits.LATA2
#define UNUSED1                 LATAbits.LATA7
#define UNUSED2                 LATAbits.LATA10

#define UNUSED4                 LATBbits.LATB12
#define UNUSED5                 LATBbits.LATB13
#define UNUSED6                 LATBbits.LATB14
#define UNUSED7                 LATBbits.LATB15


#endif	/* HARDWAREPROFILE_H */
