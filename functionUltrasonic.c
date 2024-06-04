#include <mega328p.h>
#include <delay.h>

#define Echo 0 // A0 corresponds to PC0
#define Trig 1 // A1 corresponds to PC1

// Hàm giả lập millis() để trả về thời gian hiện tại tính bằng milisecond
unsigned long millis() {
    // Implement the millis function here, which returns the current time in milliseconds.
    // You may need to use a timer and interrupt to keep track of the elapsed time.
    // This is a placeholder implementation.
    static unsigned long currentTime = 0;
    return currentTime++;
}

long pulseIn(int pin, int value) {
    long width = 0;
    unsigned long startTime = millis();

    // Wait for any previous pulse to end
    while ((PINC & (1 << pin)) == value) {
        if (millis() - startTime > 10) {  // Timeout after 10ms
            return 0; // Return 0 to indicate timeout
        }
    }

    // Wait for the pulse to start
    startTime = millis();  // Reset start time
    while ((PINC & (1 << pin)) != value) {
        if (millis() - startTime > 10) {  // Timeout after 10ms
            return 0; // Return 0 to indicate timeout
        }
    }

    // Measure the width of the pulse
    startTime = millis();  // Reset start time
    while ((PINC & (1 << pin)) == value) {
        if (millis() - startTime > 10) {  // Timeout after 10ms
            return 0; // Return 0 to indicate timeout
        }
        width++;
        delay_us(1);
    }

    return width;
}

int ultrasonic() {
    long t;
    long cm;
    PORTC &= ~(1 << Trig);  // digitalWrite(Trig, LOW);
    delay_us(4);            // delayMicroseconds(4);
    PORTC |= (1 << Trig);   // digitalWrite(Trig, HIGH);
    delay_us(10);           // delayMicroseconds(10);
    PORTC &= ~(1 << Trig);  // digitalWrite(Trig, LOW);
    t = pulseIn(Echo, 1);
    cm = t / 29 / 2;   // time convert distance
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
