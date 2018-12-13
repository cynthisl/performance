#include <Arduino.h>
#include "helpers.h"
#define FP_TEST_NUM_RUNS 10000


unsigned long fp_add_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile float x = 14.9079;
    volatile float y = 23.0891;
    volatile float z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
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

unsigned long fp_subtract_test() {
    // watch out for underflow
    unsigned long t1, t2;
    volatile float x = 32.8709;
    volatile float y = 2.2890;
    volatile float z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
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
unsigned long fp_multiply_test() {
    // watch out for overflow
    // ints are 16 bit
    unsigned long t1, t2;
    volatile float x = 18.5492;
    volatile float y = 12.9078;
    volatile float z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
      z = x * y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long fp_divide_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile float x = 323.9078;
    volatile float y = 12.2343;
    volatile float z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
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

void print_fp_test_order() {
  Serial.print(F("fp_add,fp_sub,fp_mult,fp_div,"));
}

void fp_test() {
  unsigned long out;

  randomDelay();
  out = fp_add_test();
  printCSV(out,FP_TEST_NUM_RUNS);

  randomDelay();
  out = fp_subtract_test();
  printCSV(out,FP_TEST_NUM_RUNS);

  randomDelay();
  out = fp_multiply_test();
  printCSV(out,FP_TEST_NUM_RUNS);

  randomDelay();
  out = fp_divide_test();
  printCSV(out,FP_TEST_NUM_RUNS);
}

/*
void fp_test() {

    unsigned long out;
    Serial.println("Floating point tests");
    randomDelay();
    out = fp_add_test();
    Serial.print("Addition: ");
    Serial.println(out);
    randomDelay();
    out = fp_subtract_test();
    Serial.print("Sub: ");
    Serial.println(out);
    randomDelay();
    out = fp_multiply_test();
    Serial.print("Mult: ");
    Serial.println(out);
    randomDelay();
    out = fp_divide_test();
    Serial.print("Div: ");
    Serial.println(out);
}
*/
