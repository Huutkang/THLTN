#include <mega328p.h>
#include <delay.h>

#define Echo 0 // A0 corresponds to PC0
#define Trig 1 // A1 corresponds to PC1

long pulseIn(int pin, int value) {
    long width = 0;
    // Wait for any previous pulse to end
    while ((PINC & (1 << pin)) == value);

    // Wait for the pulse to start
    while ((PINC & (1 << pin)) != value);

    // Measure the width of the pulse
    while ((PINC & (1 << pin)) == value) {
        width++;
        delay_us(1);
    }

    return width;
}

int ultrasonic() {
    PORTC &= ~(1 << Trig);  // digitalWrite(Trig, LOW);
    delay_us(4);            // delayMicroseconds(4);
    PORTC |= (1 << Trig);   // digitalWrite(Trig, HIGH);
    delay_us(10);           // delayMicroseconds(10);
    PORTC &= ~(1 << Trig);  // digitalWrite(Trig, LOW);

    long t = pulseIn(Echo, 1);
    long cm = t / 29 / 2;   // time convert distance
    return cm;
}

void main() {
    DDRC |= (1 << Trig);   // Set Trig pin as output
    DDRC &= ~(1 << Echo);  // Set Echo pin as input

    while (1) {
        int distance = ultrasonic();
        // Use the distance as needed
        delay_ms(100); // Example delay
    }
}
