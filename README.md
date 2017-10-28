# CryptoAuthLib-arduino
Arduino port of CryptoAuthLib

The original Atmel library has been changed as little as possible to make it compile under Arduino.  Most of the files are only moved to another folder to satisfy the Arduino build system.  Maybe this could be avoided using symbolic links.

The library supports ATSHA204A, ATECC108A and ATECC508A.  It has only been tested with ATSHA204A.  

The library has been tested with bitbang I²C on pins 3 & 4 of the Arduino.  Change "i2c_bitbang_at88ck9000.cpp" if you want to use other pins.  The Arduino Wire library can't be used because its internal buffers are too small.

Up to now this library has only been used to generate "high quality" (dixit Atmel) random numbers.  Using the existing Atmel library compared to starting from scratch has the benefit of saving a lot of time and offers the option of easily adding extra features later on.

## Low power remark

I found out that during sleep, the ATSHA204A sinks about 60µA.  This sink current goes through SDA & SCL which are pulled up through 3V3.  So if you really want low power, you will have to disable the pull-ups and enable pull down on the I²C lines.
