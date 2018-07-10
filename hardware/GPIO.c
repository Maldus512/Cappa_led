/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: GPIO.c                                                            */
/*                                                                            */
/*      SetUp STATO di tutti i BIT utilizzati nell' HW                        */
/*                                                                            */
/*  Autore: Sabbiolino (Fabio BARALDI) & Massimo ZANNA                        */
/*                                                                            */
/*  Data  : 01/05/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include "HardwareProfile.h"





void Init_GPIO(void)
{    
    // DISABILITO AD NEI BIT CHE USO COME INPUT (tutti)
    AD1CON1bits.ADON = 0;
    ANSAbits.ANSA0 = 0;
    ANSAbits.ANSA1 = 0;
    ANSAbits.ANSA2 = 0;
    ANSAbits.ANSA3 = 0;

//    ANSELA = 0;

    // Init Directions & Preset pin DATA & CONTROL LCD ====================== //
    DISP_DATA_TRIS = DISP_DATA_TRIS & ~DISP_DATA_MASK;
    DISP_EN_TRIS                    = OUT;
    DISP_RESET_TRIS                 = OUT;
    DISP_READ_WRITE_TRIS            = OUT;
    DISP_RS_TRIS                    = OUT;
    DISP_CS_TRIS                    = OUT;
    
    // ---------------------------------
    DISP_DATA_OUT = DISP_DATA_OUT & ~DISP_DATA_MASK;
    DISP_EN                         = 1;
    DISP_RESET                      = 1;
    DISP_READ_WRITE                 = 1;
    DISP_CS                         = 1;
    DISP_RS                         = 1;
    
    /* Keyboard */
    KEY_1_TRIS                      = IN;
    KEY_2_TRIS                      = IN;
    KEY_3_TRIS                      = IN;
    KEY_4_TRIS                      = IN;
    
    ZERO_XING_TRIS                  = IN;
    
    /* OUTPUT */
    OUT_01_TRIS                     = OUT;
    OUT_02_TRIS                     = OUT;
    OUT_03_TRIS                     = OUT;

    OUT_01                          = 0;
    OUT_02                          = 0;
    OUT_03                          = 0;
    
    LED_RUN_TRIS = OUT;
    
    LED_RUN = 0;
    
    /* Tiro a massa tutti i pin del micro che non utilizziamo */
    UNUSED0_TRIS = OUT;
    UNUSED1_TRIS = OUT;
    UNUSED2_TRIS = OUT;

    UNUSED3_TRIS = OUT;
    UNUSED4_TRIS = OUT;
    UNUSED5_TRIS = OUT;
    UNUSED6_TRIS = OUT;
    UNUSED7_TRIS = OUT;
    
    UNUSED8_TRIS = OUT;
   
    
    
    UNUSED0 = 0;
    UNUSED1 = 0;
    UNUSED2 = 0;
    
    UNUSED3 = 0;
    UNUSED4 = 0;
    UNUSED5 = 0;
    UNUSED6 = 0;
    UNUSED7 = 0;
    
    UNUSED8 = 0;
}
