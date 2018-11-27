#include <Arduino.h>
#define FP_TEST_NUM_RUNS 100000


unsigned long fp_add_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile float x = 5.0;
    volatile float y = 2.0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
        x += y;
    }
    t2 = micros();

    return t2 - t1;
}

unsigned long fp_subtract_test() {
    // watch out for underflow
    unsigned long t1, t2;
    volatile float x = 32767.0;
    volatile float y = 2.0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
        x -= y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long fp_multiply_test() {
    // watch out for overflow
    // ints are 16 bit
    unsigned long t1, t2;
    volatile float x = 2.0;
    volatile float y = 2.0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
        x *= y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long fp_divide_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile float x = 32766.0;
    volatile float y = 2.0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<FP_TEST_NUM_RUNS; i++) {
        x /= y;
    }
    t2 = micros();

    return t2 - t1;
}

void fp_test() {

    unsigned long out;
    Serial.println("Floating point tests");
    delay(1000);
    out = fp_add_test();
    Serial.print("Addition: ");
    Serial.println(out);
    delay(1000);
    out = fp_subtract_test();
    Serial.print("Sub: ");
    Serial.println(out);
    delay(1000);
    out = fp_multiply_test();
    Serial.print("Mult: ");
    Serial.println(out);
    delay(1000);
    out = fp_divide_test();
    Serial.print("Div: ");
    Serial.println(out);
}
