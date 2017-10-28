#include "atca_basic_tests.h"

ATCAIfaceCfg *gCfg = &cfg_sha204a_i2c_default;
byte buffer[64];
HardwareSerial* debugPort;

void setup() {
  debugPort=&Serial1;
    debugPort->begin(9600);
    debugPort->println("Hello there!");
    //unitTests();
    if(getSerialNumber(buffer))
    {
        debugPort->print("Serial number: ");
        print(buffer, 9);
    }
    debugPort->println("Done reading serial number.");
    if(TRNG(buffer,64))
    {
        debugPort->print("Random number: ");
        print(buffer,64);
    }
}

void loop() {
    //debugPort->print("0");
    delay(500);
}

static int TRNG(byte *dest, unsigned size)
{
    byte randomnum[RANDOM_RSP_SIZE];

    if(atcab_init( gCfg ) != ATCA_SUCCESS)
    {
        return 0;
    }
    while(size)
    {
        if(atcab_random( randomnum ) != ATCA_SUCCESS)
        {
            return 0;
        }
        byte nrOfBytes = size > 32 ? 32 : size;
        memcpy(dest,randomnum, nrOfBytes);
        dest+=nrOfBytes;
        size-=nrOfBytes;
    }
    if(atcab_release() != ATCA_SUCCESS)
    {
        return 0;
    }
    return 1;
}

bool getSerialNumber(byte* buf)
{
  byte status;
    if(atcab_init( gCfg ) != ATCA_SUCCESS)
    {
        return false;
    }
    if(atcab_read_serial_number(buf) != ATCA_SUCCESS)
    {
        return false;
    }
    if((status=atcab_wakeup()) != ATCA_SUCCESS)
    {
      return false;
    }
    if((status=atcab_sleep()) != ATCA_SUCCESS)
    {
      return false;
    }
    if(atcab_release() != ATCA_SUCCESS)
    {
        return false;
    }
    return true;
}

void unitTests()
{
    test_basic_init();
    test_basic_doubleinit();
    test_basic_info();
    test_basic_random();
    test_basic_challenge();

    //The following tests can only be run while the config zone is still unlocked.
    test_basic_write_config_zone();
    test_basic_read_config_zone();
    test_basic_write_sha_config_zone();
    test_basic_read_sha_config_zone();

    //Locking the config zone of a device is an irreversible process.
    //test_basic_lock_config_zone(); //This test can only be done once on every unit.
}

void print(const byte* array, byte length)
{
    debugPort->print("Length = ");debugPort->println(length,DEC);
    char strA[3];
    for (byte i = 0; i < length; i++)
    {
        sprintf(strA,"%02X ",array[i]);
        debugPort->print(strA);
        if ((i + 1) % 16 == 0)
        {
            debugPort->println();
        }
    }
    debugPort->println();
}
