#include <Arduino.h>
#define TRIG_TEST_NUM_RUNS 100000

unsigned long sin_test() {
  unsigned long t1, t2;
  volatile float angle = 23.8;
  volatile double sine;
  unsigned long i;

  t1 = micros();
  for(i=0; i<TRIG_TEST_NUM_RUNS; i++) {
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
  }
  t2 = micros();

  return t2-t1;
}
void trig_tests() {
  Serial.println("Trig tests");

  unsigned long t;

  delay(1000);
  t = sin_test();
  Serial.print("Sin: ");
  Serial.println(t);


  delay(1000);
  t = cos_test();
  Serial.print("Cos: ");
  Serial.println(t);

  delay(1000);
  t = tan_test();
  Serial.print("Tan: ");
  Serial.println(t);

  delay(1000);
}
