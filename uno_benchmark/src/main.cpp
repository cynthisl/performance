#include <Arduino.h>
#include "tests.h"

void setup()
{
  Serial.begin(9600);

 integer_test();

 delay(1000);

 fp_test();

 delay(1000);

 trig_tests();
}

void loop()
{
  // nop
}
