#include <Arduino.h>
#include "helpers.h"
#include "tests.h"

#define NUM_BENCHMARK_RUNS 10

void setup() {
  Serial.begin(9600);
  int i;

 Serial.println(F("Uno Benchmarking Test"));
 Serial.println(F("----------------------"));

  print_integer_test_order();
  print_fp_test_order();
  print_trig_test_order();
  print_digitalio_test_order();
  print_analogio_test_order();
  print_mem_test_order();
  Serial.println();

  for(i=0; i<NUM_BENCHMARK_RUNS; i++) {
   delay(WAIT_BREAK);
   integer_test();

   delay(WAIT_BREAK);
   fp_test();

   delay(WAIT_BREAK);
   trig_tests();

   delay(WAIT_BREAK);
   digital_io_tests();

   delay(WAIT_BREAK);
   analog_io_tests();

   delay(WAIT_BREAK);
   mem_tests();

   Serial.println();
  }
}

void loop()
{
  // nop
}
