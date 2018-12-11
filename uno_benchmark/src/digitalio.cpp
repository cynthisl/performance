#include <Arduino.h>
#include "helpers.h"
#define DIGITAL_READ_PIN 2
#define DIGITAL_WRITE_PIN 3
#define DIGITAL_TEST_NUM_RUNS 10000


unsigned long digital_read_test() {
  // Use internal pullup so we don't need an extra resistor
  pinMode(DIGITAL_READ_PIN, INPUT_PULLUP);
  unsigned long t1, t2;
  volatile int read_val;
  unsigned long i;

  t1 = micros();
  for(i=0; i<DIGITAL_TEST_NUM_RUNS; i++) {
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
    read_val = digitalRead(DIGITAL_READ_PIN);
  }
  t2 = micros();

  return t2-t1;
}

unsigned long digital_write_test() {
  pinMode(DIGITAL_WRITE_PIN, OUTPUT);

  unsigned long t1, t2;
  unsigned long i;

  t1 = micros();
  for(i=0; i<DIGITAL_TEST_NUM_RUNS; i++) {
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
    digitalWrite(DIGITAL_WRITE_PIN, LOW);
  }
  t2 = micros();

  return t2-t1;
}

void print_digitalio_test_order() {
  Serial.print(F("digital_read,digital_write,"));
}

void digital_io_tests() {
  unsigned long out;

  delay(WAIT_BREAK);
  out = digital_read_test();
  printCSV(out,DIGITAL_TEST_NUM_RUNS);

  delay(WAIT_BREAK);
  out = digital_write_test();
  printCSV(out,DIGITAL_TEST_NUM_RUNS);
}

/*
void digital_io_tests() {
  Serial.println("Digital IO tests");
  unsigned long out;

  delay(WAIT_BREAK);
  out = digital_read_test();
  Serial.print("Read: ");
  Serial.println(out);

  delay(WAIT_BREAK);
  out = digital_write_test();
  Serial.print("Write: ");
  Serial.println(out);

}
*/
