/*
 * gpio.c
 *
 * Created: 19/05/2024 10:02:10 CH
 * Author: HP
 */

#include <mega328p.h>
#include <avr/io.h>

// H�m chuy?n ch�n s? th�nh c?ng v� bit tuong ?ng
uint8_t digitalPinToPort(uint8_t pin);
uint8_t digitalPinToBitMask(uint8_t pin);

int digitalRead(uint8_t pin) {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);

    // X�c d?nh c?ng v� d?c gi� tr? t? thanh ghi PIN c?a c?ng d�
    if (port == NOT_A_PIN) return LOW;

    // �?c gi� tr? t? c?ng tuong ?ng
    if (*portInputRegister(port) & bit) return HIGH;
    return LOW;
}

void digitalWrite(uint8_t pin, uint8_t value) {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;

    // X�c d?nh c?ng v� l?y con tr? t?i thanh ghi PORT tuong ?ng
    if (port == NOT_A_PIN) return;
    out = portOutputRegister(port);

    // �?t ho?c x�a bit tuong ?ng trong thanh ghi PORT
    if (value == LOW) {
        *out &= ~bit;
    } else {
        *out |= bit;
    }
}


// H�m chuy?n ch�n s? th�nh c?ng
uint8_t digitalPinToPort(uint8_t pin) {
    if (pin >= 0 && pin <= 7) return PORT_D;
    if (pin >= 8 && pin <= 13) return PORT_B;
    if (pin >= 14 && pin <= 19) return PORT_C;
    return NOT_A_PIN;
}

// H�m chuy?n ch�n s? th�nh bit mask
uint8_t digitalPinToBitMask(uint8_t pin) {
    if (pin >= 0 && pin <= 7) return (1 << pin);
    if (pin >= 8 && pin <= 13) return (1 << (pin - 8));
    if (pin >= 14 && pin <= 19) return (1 << (pin - 14));
    return 0;
}

// H�m tr? v? con tr? t?i thanh ghi PIN c?a c?ng
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
