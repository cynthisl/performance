#include <Arduino.h>
#include "tests.h"

void setup()
{
  Serial.begin(9600);

 Serial.println("Uno Benchmarking Test");
 Serial.println("----------------------");

 delay(1000);
 integer_test();

 delay(1000);
 fp_test();

 delay(1000);
 trig_tests();

 delay(1000);
 digital_io_tests();

 delay(1000);
 analog_io_tests();

 delay(1000);
 mem_tests();
}

void loop()
{
  // nop
}
