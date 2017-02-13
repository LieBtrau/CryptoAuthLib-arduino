#include "atca_basic_tests.h"



ATCAIfaceCfg *gCfg = &cfg_sha204a_i2c_default;

void setup() {
  //Initialize Serial2 and wait for port to open:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  test_basic_init();
}

void loop() {
  Serial.print("0");
  delay(500);
}
