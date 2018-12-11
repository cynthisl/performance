#include <Arduino.h>
#include "helpers.h"
#define ANALOG_READ_PIN A0
#define ANALOG_WRITE_PIN A1
#define ANALOG_TEST_NUM_RUNS 10000


unsigned long analog_read_test() {
  unsigned long t1, t2;
  volatile int read_val;
  unsigned long i;

  t1 = micros();
  for(i=0; i<ANALOG_TEST_NUM_RUNS; i++) {
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
    read_val = analogRead(ANALOG_READ_PIN);
  }
  t2 = micros();

  return t2-t1;
}

unsigned long analog_write_test() {
  pinMode(ANALOG_WRITE_PIN, OUTPUT);

  unsigned long t1, t2;
  unsigned long i;

  t1 = micros();
  for(i=0; i<ANALOG_TEST_NUM_RUNS; i++) {
    analogWrite(ANALOG_WRITE_PIN, 0);
    analogWrite(ANALOG_WRITE_PIN, 15);
    analogWrite(ANALOG_WRITE_PIN, 30);
    analogWrite(ANALOG_WRITE_PIN, 45);
    analogWrite(ANALOG_WRITE_PIN, 60);
    analogWrite(ANALOG_WRITE_PIN, 75);
    analogWrite(ANALOG_WRITE_PIN, 90);
    analogWrite(ANALOG_WRITE_PIN, 105);
    analogWrite(ANALOG_WRITE_PIN, 120);
    analogWrite(ANALOG_WRITE_PIN, 135);
    analogWrite(ANALOG_WRITE_PIN, 150);
    analogWrite(ANALOG_WRITE_PIN, 165);
    analogWrite(ANALOG_WRITE_PIN, 180);
    analogWrite(ANALOG_WRITE_PIN, 195);
    analogWrite(ANALOG_WRITE_PIN, 210);
    analogWrite(ANALOG_WRITE_PIN, 225);
    analogWrite(ANALOG_WRITE_PIN, 240);
    analogWrite(ANALOG_WRITE_PIN, 255);
  }
  t2 = micros();

  return t2-t1;
}

void print_analogio_test_order() {
  Serial.print(F("analog_read,analog_write,"));
}

void analog_io_tests() {
  unsigned long out;

  delay(WAIT_BREAK);
  out = analog_read_test();
  printCSV(out, ANALOG_TEST_NUM_RUNS);

  delay(WAIT_BREAK);
  out = analog_write_test();
printCSV(out,ANALOG_TEST_NUM_RUNS);

}

/*
void analog_io_tests() {
  Serial.println("Analog IO tests");
  unsigned long out;

  delay(WAIT_BREAK);
  out = analog_read_test();
  Serial.print("Read: ");
  Serial.println(out);

  delay(WAIT_BREAK);
  out = analog_write_test();
  Serial.print("Write: ");
  Serial.println(out);

}
*/
