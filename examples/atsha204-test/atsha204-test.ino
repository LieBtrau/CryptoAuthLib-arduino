#include "atca_basic_tests.h"

ATCAIfaceCfg *gCfg = NULL;

void setup() {
  //Initialize Serial2 and wait for port to open:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  atca_basic_tests(ATSHA204A);
}

void loop() {
  Serial.print("0");
  delay(500);
}
