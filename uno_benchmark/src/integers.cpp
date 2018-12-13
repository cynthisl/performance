#include <Arduino.h>
#include "helpers.h"
#define NUM_INT_TEST_RUNS 10000

unsigned long integer_add_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile int x = 15907;
    volatile int y = 14873;
    volatile int z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
        z = x + y;
    }
    t2 = micros();

    return t2 - t1;
}

unsigned long integer_subtract_test() {
    // watch out for underflow
    unsigned long t1, t2;
    volatile int x = 32767;
    volatile int y = 16390;
    volatile int z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
      z = x - y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long integer_multiply_test() {
    // watch out for overflow
    // ints are 16 bit
    unsigned long t1, t2;
    volatile int x = 15907;
    volatile int y = 2;
    volatile int z = 0;

    unsigned long i;


    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
        z = x*y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long integer_divide_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile int x = 32766;
    volatile int y = 2;
    volatile int z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
        z = x/y;
    }
    t2 = micros();

    return t2 - t1;
}

/*
void integer_test() {

    unsigned long out;
    Serial.println("Integer tests");
    randomDelay();
    out = integer_add_test();
    Serial.print("Addition: ");
    Serial.println(out);

    randomDelay();
    out = integer_subtract_test();
    Serial.print("Sub: ");
    Serial.println(out);

    randomDelay();
    out = integer_multiply_test();
    Serial.print("Mult: ");
    Serial.println(out);

    randomDelay();
    out = integer_divide_test();
    Serial.print("Div: ");
    Serial.println(out);
}
*/
void print_integer_test_order() {
  Serial.print(F("int_add,int_sub,int_mult,int_div,"));
}
void integer_test() {
  unsigned long out;

  randomDelay();
  out = integer_add_test();
  printCSV(out,NUM_INT_TEST_RUNS);

  randomDelay();
  out = integer_subtract_test();
  printCSV(out,NUM_INT_TEST_RUNS);

  randomDelay();
  out = integer_multiply_test();
  printCSV(out,NUM_INT_TEST_RUNS);

  randomDelay();
  out = integer_divide_test();
  printCSV(out,NUM_INT_TEST_RUNS);

}
