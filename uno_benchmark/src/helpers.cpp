#include <Arduino.h>

void printCSV(unsigned long val, unsigned long num_times) {
  Serial.print(val);
  //Serial.print((float)val/num_times, 6);
  Serial.print(",");
}
