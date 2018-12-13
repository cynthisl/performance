#include <Arduino.h>
#include "helpers.h"

#define MEM_TEST_NUM_RUNS 10000
#define MEM_TEST_ARRAY_SIZE 1024

unsigned long sram_test() {

  unsigned long t1, t2;

  volatile char arr[MEM_TEST_ARRAY_SIZE];
  int i, j;

  t1 = micros();
  for(i=0; i<MEM_TEST_NUM_RUNS; i++) {
    for(j=0; j<MEM_TEST_ARRAY_SIZE; j++) {
      arr[j] = (char)j;
    }
  }
  t2 = micros();

  return t2-t1;

}

void print_mem_test_order() {
  Serial.print(F("sram,"));
}

void mem_tests() {
  unsigned long out;

  randomDelay();
  out = sram_test();
  printCSV(out,MEM_TEST_NUM_RUNS);
}

/*
void mem_tests() {
  unsigned long out;
  randomDelay();
  out = sram_test();
  Serial.print("SRAM Test:");
  Serial.println(out);
}
*/
