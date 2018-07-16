/******************************************************************************/
/*                                                                            */
/*      H   H      SSSS     W   W                                             */
/*      H   H     S         W   W                                             */
/*      HHHHH      SSS      W   W                                             */
/*      H   H         S     W W W                                             */
/*      H   H  *  SSSS   *   W W   *  snc                                     */
/*                                                                            */
/*      *********************************                                     */
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  programma:  Scheda comando CAPPA                                          */
/*                                                                            */
/*  cliente:    Microelettronica - Valsamoggia Monteveglio (BO)               */
/*                                                                            */
/*  ver. 00:    25/03/2018  00.0 (base: H2Ox4 PIC v.01.0 del 03/04/20128)     */
/*                                                                            */
/*  ver. att.:  11/05/2018  00.3                                              */
/*                                                                            */
/*  BY:         Maldus (Mattia MALDINI) & Massimo ZANNA                       */
/*                                                                            */
/*  NNB:        SENSO DEGLI INGRESSI: INVERTITO                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  micro:      MicroChip PIC PIC24FJ256GA704 - 8   MHz - 44 Pin ????????     */
/*                                                                            */
/*  micro:      MicroChip PIC PIC24EP256GP204 - 60  MHz - 44 Pin ????????     */
/*              256K Flash - 32 Ram                                           */
/*              262.144 b ?  32.768 b ?                                       */
/*                                                                            */
/*============================================================================*/

// STRINGA "VERSIONE PROGRAMMA"            012345678901234567890
const unsigned char str_versione_prog[] = "[V:00.3 D:11/05/2018]\0";     // 21 CHR



// <editor-fold defaultstate="collapsed" desc=" ####    REVISIONI    #### ">

/*============================================================================*/
/*                                                                            */
/*  ver. 00.0: 28/04/2018 (base: H2Ox4 PIC v.01.0 del 03/04/2018)             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  ver. 00.1: 03/04/2018                                                     */
/*                                                                            */
/*      - PRIMA STESURA CON INIZIALIZZAZIONE RISORSE HW                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  ver. 00.2: 03/05/2018                                                     */
/*                                                                            */
/*      - PRIME PAGINATE E PROVA GT VELOCITA' MOTORE                          */
/*      - RISCONTRATE DIFFICOLTA' PRIORITY LEVEL INT E . NON SI PROGRAMMA !!! */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  ver. 00.3: 11/05/2018                                                     */
/*                                                                            */
/*      - CAMBIATO MICRO .... VA' MA .... PARE DIPENDENTE DALLA VEL clk !!??  */
/*      - CREATI 4 ANDAMENTI VEL                                              */
/*      - CREATA GT "TESTATA"                                                 */
/*                                                                            */
/******************************************************************************/

#include "HardwareProfile.h"
#include "system.h"
#include "timer.h"
#include "GPIO.h"
#include "ciclo.h"
#include "digin.h"
#include "peripherals.h"
#include "keyb.h"
#include "test_suite.h"
#include "MCP4018/rheostat.h"
#include "variabili_parametri_macchina.h"
#include "i2c_driver.h"
#include "digout.h"
#include "EEPROM/24XX16.h"
#include "dispfunz.h"



// ========================================================================== //
//  MAIN                                                                      //
// ========================================================================== //
int main(void)
{
    unsigned char tasto = 0;
    OUTPUT        led   = OUT_LED1P1;
    Configure_Oscillator();
    delay_ms(250);

    Init_GPIO();
    Init_I2C();

    // saveParMac(parmac);
    loadParMac(&parmac);


    Init_Timers();
    Init_Digin_Filter(&DI_P1, 0, 0, DEBOUNCE);
    Init_ZeroCrossing();



    setRheostatValue(parmac.potenziometro);

    delay_ms(500);
    // INIZIALIZZAZIONE TIPO USO "LED RUN ------------------------- //
    n_set_out_run =
        4;     // set var x test tempistiche con oscilloscopio # NNB: E' ANCHE WRITE PROTECT RAM M1, M2, M3 -!!!! ToDO

    // 0 = NO

    // 1 = TIMER 1 (1msec)
    // 20 = TIMER 2 (20msec)
    // 100 = TIMER 3 (100msec)

    // 4 = CICLO a 1sec

    // 30 = MAIN LOOP

    // 50 = INTERRUPT 50/60Hz


    Cambio_Pag(PAG_PRINCIPALE);

    // MAIN LOOP ============================================================ //
    // MAIN LOOP ============================================================ //
    // MAIN LOOP ============================================================ //
    set_digout(led);
    while (1)
    {
        if (pag_corrente != NULL && f_update)
        {
            tasto = KeyBoard();
            pag_corrente->k_processor(tasto);
            pag_corrente->d_processor();
            f_update = 0;
        }
    }
    return 0;
}
