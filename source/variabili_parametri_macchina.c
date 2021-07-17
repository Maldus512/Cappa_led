/******************************************************************************/
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  modulo: variabili_parametri_macchina.c                                    */
/*                                                                            */
/*      ciclo macchina                                                        */
/*                                                                            */
/*  Autore: Massimo Zanna                                                     */
/*                                                                            */
/*  Data  : 30/04/2018      REV  : 00.0                                       */
/*                                                                            */
/*  U.mod.: 11/05/2018      REV  : 01.0                                       */
/*                                                                            */
/******************************************************************************/

#include <string.h>
#include "variabili_parametri_macchina.h"
#include "i2c_module2.h"
#include "gel/wearleveling/wearleveling.h"
#include "gel/data_structures/watcher.h"
#include "gel_conf.h"

 static wear_leveled_memory_t memory;
 static watcher_t watchlist[2] = {WATCHER_NULL};


unsigned int rampa_velocita_50hz[MAX_RAMPA] = {40, 51, 57, 65, 100}; // Velocita'
//int rampa_velocita_50hz[MAX_RAMPA] = {0, 20, 37, 52, 100};  // Temperatura


/* -------------------------------------------------------------------------- */
/*  parametri macchina                                                        */
/* -------------------------------------------------------------------------- */

struct PARAMETRI_MACCHINA parmac = {
    // BASE =========================================================== //
    // -------------------------------------------------------------------------------------------------------------------------------
    // UM      RANGE       TEST 0  PM 1    PM 2    PM 3    PM 4    PM 5    PM 6    RID
    .velocita_accensione = 5,
    .vel_ventola = 0,
    .timer_start = 15,
    .timer_stop  = 15,
};

static void speed_changed(void *new, void *data) {
    (void)data;
    unsigned char buffer = (unsigned char)(*(unsigned int*)new);
    wl_write(&memory, &buffer);
}


static int eeprom_read_block(size_t block_num, uint8_t * buffer){
    return sequentialRead_24XX16(MEM_16_B0, 0x01, block_num*WL_BLOCK_SIZE, buffer, WL_BLOCK_SIZE);
}


static int eeprom_write_block(size_t block_num, uint8_t * buffer){
    return sequentialWrite_24XX16(MEM_16_B0, 0x01, block_num*WL_BLOCK_SIZE, buffer, WL_BLOCK_SIZE);
}


void parmac_init(void) {
    wl_init(&memory, eeprom_write_block, eeprom_read_block, 16, 1);
}


void parmac_watchlist_init(struct PARAMETRI_MACCHINA *p) {
    watchlist[0] = WATCHER_DELAYED(&p->vel_ventola, speed_changed, NULL, 5000);
    watchlist[1] = WATCHER_NULL;
    watcher_list_init(watchlist);
}


void parmac_process_changes(unsigned long timestamp) {
    watcher_process_changes(watchlist, timestamp);
}


void parmac_save_speed(struct PARAMETRI_MACCHINA p) {
    unsigned char buffer = (unsigned char)(p.vel_ventola);
    wl_write(&memory, &buffer);
}


int saveParMac(struct PARAMETRI_MACCHINA p)
{
    unsigned char buffer[3] = {p.timer_start, p.timer_stop, p.velocita_accensione};
    return sequentialWrite_24XX16(MEM_16_B0, 0x00, 0x01, buffer, 3);
}

int loadParMac(struct PARAMETRI_MACCHINA *p)
{
    unsigned char buffer[3] = {15, 15, 5};
    
    int res = sequentialRead_24XX16(MEM_16_B0, 0x00, 0x01, buffer, 3);
    
    p->timer_start = buffer[0];
    p->timer_stop = buffer[1];
    p->velocita_accensione = buffer[2];
    
    if (p->timer_start > 15) {
        p->timer_start = 15;
    }
    if (p->timer_stop > 15) {
        p->timer_stop = 15;
    }
    if (p->velocita_accensione > 10) {
        p->velocita_accensione = 5;
    }
    
    if (wl_read(&memory, buffer) > 0) {
        p->vel_ventola = 0;
    } else {
        p->vel_ventola = buffer[0];
    }
    
    if (p->vel_ventola >= MAX_RAMPA)
        p->vel_ventola = 0;
    return res;
}


unsigned int parmac_get_speed(size_t level) {
    if (level == 0) {
        return rampa_velocita_50hz[0] + parmac.velocita_accensione;
    } else {
        return rampa_velocita_50hz[level];
    }
}