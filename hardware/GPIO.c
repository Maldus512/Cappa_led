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

    ANSA = 0;
    ANSB = 0;

    
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
    OUT_04_TRIS                     = OUT;
    OUT_05_TRIS                     = OUT;
    OUT_06_TRIS                     = OUT;
    OUT_07_TRIS                     = OUT;
    OUT_08_TRIS                     = OUT;
    OUT_09_TRIS                     = OUT;
    OUT_10_TRIS                     = OUT;
    OUT_11_TRIS                     = OUT;
    OUT_12_TRIS                     = OUT;

    OUT_01                          = 0;
    OUT_02                          = 0;
    OUT_03                          = 0;
    OUT_04                          = 0;
    OUT_05                          = 0;
    OUT_06                          = 0;
    OUT_07                          = 0;
    OUT_08                          = 0;
    OUT_09                          = 0;
    OUT_10                          = 0;
    OUT_11                          = 0;
    OUT_12                          = 0;
    
    LED_RUN_TRIS = OUT;
    
    LED_RUN = 0;
    
    /* Tiro a massa tutti i pin del micro che non utilizziamo */
    UNUSED0_TRIS = OUT;
    UNUSED1_TRIS = OUT;
    UNUSED2_TRIS = OUT;

    UNUSED4_TRIS = OUT;
    UNUSED5_TRIS = OUT;
    UNUSED6_TRIS = OUT;
    UNUSED7_TRIS = OUT;
    
   
    
    
    UNUSED0 = 0;
    UNUSED1 = 0;
    UNUSED2 = 0;
    
    UNUSED4 = 0;
    UNUSED5 = 0;
    UNUSED6 = 0;
    UNUSED7 = 0;
    
}
