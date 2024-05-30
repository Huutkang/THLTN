#include "servo.h"

// Cac bien toan cuc de luu cau hinh
uint8_t servo_pin;        // Chan dieu khien servo (VD: PD5)

void servo_init(uint8_t pin) {
    servo_pin = pin;

    // Cau hinh Timer1
    DDRD |= (1 << servo_pin);      // Dat chan servo la OUTPUT
    TCCR1A |= (1 << COM1A1);      // Che do PWM khong dao pha (non-inverting)
    TCCR1B |= (1 << CS11);       // Prescaler 8

    // Gia tri mac dinh cho tan so va do rong xung
    ICR1 = 20000; // Tan so PWM 50Hz (20ms)
}

void servo_write(uint8_t angle) {
    // Tinh toan do rong xung PWM dua tren goc quay
    uint16_t pulse_width = 500 + (angle * 10); // 500us (0 do) - 2500us (180 do)

    // Dat thanh ghi OCR1A
    OCR1A = pulse_width;
}

// (Ham servo_read() khong thay doi)
