#ifndef __TEST_SUITE_H__
#define __TEST_SUITE_H__

#define ARRAY_SIZE  512

#define uint8   uint8_t
#define uint16  uint16_t

#define COUNTBYTE(x)        x = (x == 0xFF) ? 0 : x+1


#define TEST_CONTROL_BYTE   0xA0
#define TEST_ADDRESS        0x00, 0x00



unsigned char eeprom24XX26_eds_test();
unsigned char eeprom24XX26_extern_eds_test();
unsigned char events_test();

#endif