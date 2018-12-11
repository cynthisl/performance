#include <Arduino.h>
#include "helpers.h"
#define TRIG_TEST_NUM_RUNS 10000

unsigned long sin_test() {
  unsigned long t1, t2;
  volatile float angle = 23.8;
  volatile double sine;
  unsigned long i;

  t1 = micros();
  for(i=0; i<TRIG_TEST_NUM_RUNS; i++) {
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
    sine = sin(angle);
  }
  t2 = micros();

  return t2-t1;
}

unsigned long cos_test() {
  unsigned long t1, t2;
  volatile float angle = 23.8;
  volatile double cosine;
  unsigned long i;

  t1 = micros();
  for(i=0; i<TRIG_TEST_NUM_RUNS; i++) {
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
    cosine = cos(angle);
  }
  t2 = micros();

  return t2-t1;
}

unsigned long tan_test() {
  unsigned long t1, t2;
  volatile float angle = 23.8;
  volatile double tangent;
  unsigned long i;

  t1 = micros();
  for(i=0; i<TRIG_TEST_NUM_RUNS; i++) {
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
    tangent = tan(angle);
  }
  t2 = micros();

  return t2-t1;
}

void print_trig_test_order() {
  Serial.print(F("sin,cos,tan,"));
}

void trig_tests() {
  unsigned long t;

  delay(WAIT_BREAK);
  t = sin_test();
  printCSV(t,TRIG_TEST_NUM_RUNS);

  delay(WAIT_BREAK);
  t = cos_test();
  printCSV(t,TRIG_TEST_NUM_RUNS);

  delay(WAIT_BREAK);
  t = tan_test();
  printCSV(t,TRIG_TEST_NUM_RUNS);

}

/*
void trig_tests() {
  Serial.println("Trig tests");

  unsigned long t;

  delay(WAIT_BREAK);
  t = sin_test();
  Serial.print("Sin: ");
  Serial.println(t);


  delay(WAIT_BREAK);
  t = cos_test();
  Serial.print("Cos: ");
  Serial.println(t);

  delay(WAIT_BREAK);
  t = tan_test();
  Serial.print("Tan: ");
  Serial.println(t);

  delay(WAIT_BREAK);
}
*/
