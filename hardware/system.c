/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: system.c                                                          */
/*                                                                            */
/*      configurazione OSCILLATORE SYS e CLK periferiche                      */
/*                                                                            */
/*  Autore: Maldus(Mattia MALDINI) & Massimo ZANNA                            */
/*                                                                            */
/*  Data  : 04/05/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include "HardwareProfile.h"
#include "system.h"

/* FSEC */
#pragma config BWRP    = OFF      /* Boot Segment Write-Protect bit (Boot Segment may be written) */
#pragma config BSS     = DISABLED /* Boot Segment Code-Protect Level bits (No Protection (other than BWRP)) */
#pragma config BSEN    = OFF      /* Boot Segment Control bit (No Boot Segment) */
#pragma config GWRP    = OFF      /* General Segment Write-Protect bit (General Segment may be written) */
#pragma config GSS     = DISABLED /* General Segment Code-Protect Level bits (No Protection (other than GWRP)) */
#pragma config CWRP    = OFF      /* Configuration Segment Write-Protect bit (Configuration Segment may be written) */
#pragma config CSS     = DISABLED /* Configuration Segment Code-Protect Level bits (No Protection (other than CWRP)) */
#pragma config AIVTDIS = OFF      /* Alternate Interrupt Vector Table bit (Disabled AIVT) */

/* FBSLIM */
#pragma config BSLIM = 0x1FFF /* Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)   \
                                 */

/* FSIGN */

/* FOSCSEL */
#pragma config FNOSC   = FRCPLL     // OSCFDIV              /* Oscillator Source Selection (Internal Fast RC (FRC)) */
#pragma config PLLMODE = 0b0001     // DISABLED       /* PLL Mode Selection (No PLL used; PLLEN bit is not available) */
#pragma config IESO    = OFF /* Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source) \
                                */

/* FOSC */
#pragma config POSCMD   = NONE /* Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode) */
#pragma config OSCIOFCN = ON   /* OSC2 Pin Function bit (OSC2 is a General Purpose IO) */
#pragma config SOSCSEL  = OFF  /* Digital mode */
#pragma config PLLSS =                                                                                                 \
    PLL_FRC /* PLL Secondary Selection Configuration bit (PLL is fed by the on-chip Fast RC (FRC) oscillator) */
#pragma config IOL1WAY = OFF /* Peripheral pin select configuration bit (Allow multiple reconfigurations) */
#pragma config FCKSM =                                                                                                 \
    CSECMD /* Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled) */

/* FWDT */
#pragma config WDTPS  = PS64 /* Watchdog Timer Postscaler bits (1:32,768) */
#pragma config FWPSA  = PR32   /* Watchdog Timer Prescaler bit (1:128) */
#pragma config FWDTEN = ON_SWDTEN     /* Watchdog Timer Enable bits (WDT and SWDTEN disabled) */
#pragma config WINDIS = OFF     /* Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode) */
#pragma config WDTWIN = WIN25   /* Watchdog Timer Window Select bits (WDT Window is 25% of WDT period) */
#pragma config WDTCMX =                                                                                                \
    WDTCLK /* WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits) */
#pragma config WDTCLK = LPRC /* WDT Clock Source Select bits (WDT uses LPRC) */

/* FPOR */
#pragma config BOREN = ON  /* Brown Out Enable bit (Brown Out Enable Bit) */
#pragma config LPCFG = OFF /* Low power regulator control (No Retention Sleep) */
#pragma config DNVPEN =                                                                                                \
    ENABLE /* Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive) */

/* FICD */
#pragma config ICS    = PGD3 /* ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1) */
#pragma config JTAGEN = OFF  /* JTAG Enable bit (JTAG is disabled) */

/* FDEVOPT1 */
#pragma config ALTCMPI =                                                                                               \
    DISABLE /* Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations) */
#pragma config TMPRPIN = OFF /* Tamper Pin Enable bit (TMPRN pin function is disabled) */
#pragma config SOSCHP =                                                                                                \
    ON /* SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC high power mode (default)) */
#pragma config ALTI2C1 = ALTI2CDIS /* Alternate I2C pin Location (SDA1 and SCL1 on RB9 and RB8) */





void Configure_Oscillator()
{
    OSCDIVbits.DIV = 0;          /* 8 MHz diviso 1 = 8 MHz */
                                 //    CLKDIVbits.RCDIV = 0;   /* Fast Internal RC Oscillator come source (8 MHz) */
                                 //    CLKDIVbits.CPDIV = 0B01;    // 16mhz
    CLKDIVbits.CPDIV = 0B00;     // 32mhz
    //    OSCTUNbits.TUN = 0x019 /*0b011001*/;
}



//
//
//#include <p24EP256GP204.h>
//
//#include "HardwareProfile.h"
//#include "system.h"
//
////FAS
////////#pragma config AWRP = OFF
////////#pragma config APL = OFF
////////#pragma config APLK = OFF
//
//// FGS
//#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
//#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)
////////#pragma config GSS = OFF
////////#pragma config GSSK = OFF
//
//// FOSCSEL
//#pragma config FNOSC = FRCPLL          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with
//postscaler)
//#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected
//oscillator source)
//
//// FOSC
//#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
//#pragma config OSCIOFNC = ON           // OSC2 Pin Function bit (OSC2 is clock output)
//#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
//#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor
//are disabled)
//
//// FWDT
//#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
//#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
//#pragma config PLLKEN = ON             // PLL Lock Enable bit (Clock switch will not wait for the PLL lock signal.)
//#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user
//software)
//
//// FPOR
//#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
//#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
////#pragma config WDTWIN = WIN75           // Watchdog Window Select bits (WDT Window is 75% of WDT period)
////#pragma config BOREN = ON
////#pragma config FPWRT = PWR128
//
//// FICD
//#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGEC2 and PGED2)
////#pragma config RSTPRI = PF
//#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
//
//
//
// void Configure_Oscillator()
//{
//    /* Frequenza settata: 60 MHz */
//    CLKDIVbits.FRCDIV = 0;
//    // abilito il PLL e attendo che si stabilizzi
//    CLKDIVbits.PLLPRE = 0;  //N1 = PLLPRE + 2
//    CLKDIVbits.PLLPOST = 0; //N2 = 2*(PLLPOST + 1)
//
//    PLLFBDbits.PLLDIV = 28; //M = PLLDIV + 2
//
//    //Fpllo = Fin + (M/(N1*N2))
//    //Fin = 8MHz
//    //Fplli = Fin/N1
//    //Fvco = Fosc desiderato
//    //Fvco = M * Fplli ==> M = Fvco/Fplli
//    // PLLDIV = 28
//    __builtin_write_OSCCONH(0x01);
//    __builtin_write_OSCCONL(OSCCON | 0x01);
////    while (OSCCONbits.COSC != OSCCONbits.NOSC);
//    while (OSCCONbits.COSC != 1);
//    while (OSCCONbits.LOCK != 1);
//
//    RCONbits.SWDTEN = 0;
//}
