
#include "test_suite.h"
#include "i2c_module2.h"

//__eds__ uint8_t test_array_eds[ARRAY_SIZE] __attribute__((eds));
uint8_t test_array_eds[ARRAY_SIZE];





void reset()
{
    uint16 i;

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        test_array_eds[i] = 0;
    }
}






uint8 eeprom24XX26_eds_test()
{
    uint16 i;
    uint8 x = 0;
    
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        COUNTBYTE(x);
        test_array_eds[i] = x;
    }
    sequentialWrite_24XX16(TEST_CONTROL_BYTE, TEST_ADDRESS, test_array_eds, ARRAY_SIZE);
    reset();
    sequentialRead_24XX16(TEST_CONTROL_BYTE, TEST_ADDRESS, test_array_eds, ARRAY_SIZE);
    
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        COUNTBYTE(x);
        
        if (test_array_eds[i] != x)
        {
            Nop();
            Nop();
            Nop();
            return 1;
        }
    }
    
    return 0;
}



