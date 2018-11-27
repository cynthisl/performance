#include <Arduino.h>
#define NUM_INT_TEST_RUNS 100000

unsigned long integer_add_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile int x = 5;
    volatile int y = 2;
    volatile int z = 0;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        z=x+y;
    }
    t2 = micros();

    return t2 - t1;
}

unsigned long integer_subtract_test() {
    // watch out for underflow
    unsigned long t1, t2;
    volatile int x = 32767;
    volatile int y = 2;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        x -= y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long integer_multiply_test() {
    // watch out for overflow
    // ints are 16 bit
    unsigned long t1, t2;
    volatile int x = 2;
    volatile int y = 2;

    unsigned long i;


    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        x *= y;
    }
    t2 = micros();

    return t2 - t1;
}
unsigned long integer_divide_test() {
    // watch out for overflow
    unsigned long t1, t2;
    volatile int x = 32766;
    volatile int y = 2;

    unsigned long i;

    t1 = micros();
    for(i=0; i<NUM_INT_TEST_RUNS; i++) {
        x /= y;
    }
    t2 = micros();

    return t2 - t1;
}

void integer_test() {

    unsigned long out;
    Serial.println("Integer tests");
    delay(1000);
    out = integer_add_test();
    Serial.print("Addition: ");
    Serial.println(out);

    delay(1000);
    out = integer_subtract_test();
    Serial.print("Sub: ");
    Serial.println(out);

    delay(1000);
    out = integer_multiply_test();
    Serial.print("Mult: ");
    Serial.println(out);

    delay(1000);
    out = integer_divide_test();
    Serial.print("Div: ");
    Serial.println(out);
}
