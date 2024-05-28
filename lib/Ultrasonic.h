#include <mega328p.h>
#include <delay.h>

#define Echo 0 // A0 - PC0
#define Trig 1 // A1 - PC1

long pulseIn(int pin, int value) {
    long width = 0;
    // Doi xung truoc do ket thuc
    while ((PINC & (1 << pin)) == value);

    // Cho cho xung bat dau
    while ((PINC & (1 << pin)) != value);

    // Do do rong cua xung
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

// void main() {
//     DDRC |= (1 << Trig);   // Set Trig pin as output
//     DDRC &= ~(1 << Echo);  // Set Echo pin as input

//     while (1) {
//         int distance = ultrasonic();
//         // xu dung khoang cach khi can thiet
//         delay_ms(100); // Example delay
//     }
// }