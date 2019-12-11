
#ifndef WDT_H
#define	WDT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "HardwareProfile.h"

#define     CHECK_NUM       3

#define     MAIN            0
#define     T1INT           1
#define     T2INT           2



void refresh_stamp_int(unsigned char x);
void disableWDT();
void enableWDT();

#ifdef	__cplusplus
}
#endif

#endif	/* WDT_H */
