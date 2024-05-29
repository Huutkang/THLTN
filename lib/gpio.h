#include <mega328p.h>
#include <avr/io.h>

// Ham chuyen chan so thanh cong va bit tuong ung
uint8_t digitalPinToPort(uint8_t pin);
uint8_t digitalPinToBitMask(uint8_t pin);

int digitalRead(uint8_t pin) {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);

    // Xac dinh cong va doc gia tri tu thanh ghi PIN cua cong do
    if (port == NOT_A_PIN) return LOW;

    // Doc gia tri tu cong tuong ung
    if (*portInputRegister(port) & bit) return HIGH;
    return LOW;
}

void digitalWrite(uint8_t pin, uint8_t value) {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;

    // Xac dinh cong va lay con tro toi thanh ghi PORT tuong ung
    if (port == NOT_A_PIN) return;
    out = portOutputRegister(port);

    // Dat hoac xoa bit tuong ung trong thanh ghi PORT
    if (value == LOW) {
        *out &= ~bit;
    } else {
        *out |= bit;
    }
}

// Ham chuyen chan so thanh cong
uint8_t digitalPinToPort(uint8_t pin) {
    if (pin >= 0 && pin <= 7) return PORT_D;
    if (pin >= 8 && pin <= 13) return PORT_B;
    if (pin >= 14 && pin <= 19) return PORT_C;
    return NOT_A_PIN;
}

// Ham chuyen chan so thanh bit mask
uint8_t digitalPinToBitMask(uint8_t pin) {
    if (pin >= 0 && pin <= 7) return (1 << pin);
    if (pin >= 8 && pin <= 13) return (1 << (pin - 8));
    if (pin >= 14 && pin <= 19) return (1 << (pin - 14));
    return 0;
}

// Ham tra ve con tro toi thanh ghi PIN cua cong
volatile uint8_t* portInputRegister(uint8_t port) {
    switch (port) {
        case PORT_B: return &PINB;
        case PORT_C: return &PINC;
        case PORT_D: return &PIND;
        default: return NULL;
    }
}

void main(void)
{
while (1)
    {
    // Please write your application code here

    }
}


