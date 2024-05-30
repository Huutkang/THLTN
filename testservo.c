// test servo
#include "servo.h"

void main() {
    servo_init(PD5); // Khoi tao voi chan PD5

    while (1) {
        servo_write(90); // Quay servo den goc 90 do
        delay_ms(1000);
        servo_write(0); // Quay servo den goc 0 do
        delay_ms(1000);
    }
}
