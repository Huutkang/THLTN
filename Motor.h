#ifndef MOTOR_H
#define MOTOR_H

#include <mega328p.h>
#include "millis.h"

// Cac lenh dieu khien dong co
#define FORWARD 1
#define BACKWARD 2
#define RELEASE 0

// Cau truc du lieu de luu tru thong tin cua mot dong co
typedef struct {
    unsigned char in1Pin;  // Chan IN1
    unsigned char in2Pin;  // Chan IN2
    unsigned char enPin;   // Chan Enable (PWM)
    unsigned long previousMicros; // Thoi gian cap nhat truoc do (tinh bang micro giay)
    int currentCmd;    // Lenh hien tai cua dong co
} Motor;

// Khoi tao PWM (Pulse Width Modulation)
void pwm_init() {
    // Chon che do Fast PWM voi non-inverting mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    // Chon Prescaler la 64
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

// Ham khoi tao dong co
void motor_init(Motor *motor, unsigned char in1Pin, unsigned char in2Pin, unsigned char enPin) {
    motor->in1Pin = in1Pin;
    motor->in2Pin = in2Pin;
    motor->enPin = enPin;
    motor->previousMicros = 0;
    motor->currentCmd = RELEASE; // Khoi tao o trang thai dung

    // Dat cac chan la OUTPUT
    DDRB |= (1 << motor->in1Pin) | (1 << motor->in2Pin) | (1 << motor->enPin);

    // Dat dong co o trang thai dung
    PORTB &= ~((1 << motor->in1Pin) | (1 << motor->in2Pin));
    OCR0A = 0; // Dat PWM ve 0

    // Khoi tao PWM
    pwm_init();
}

// Ham dat toc do dong co (0-255)
void motor_setSpeed(int speed) {
    OCR0A = speed; // Su dung Timer0 cho PWM
}

// Ham dieu khien chieu quay cua dong co
void motor_run(Motor *motor, int cmd) {
    motor->currentCmd = cmd;
    motor->previousMicros = micros(); // Lay thoi gian hien tai

    switch (cmd) {
        case FORWARD:
            PORTB |= (1 << motor->in1Pin);
            PORTB &= ~(1 << motor->in2Pin);
            break;
        case BACKWARD:
            PORTB &= ~(1 << motor->in1Pin);
            PORTB |= (1 << motor->in2Pin);
            break;
        case RELEASE:
            PORTB &= ~((1 << motor->in1Pin) | (1 << motor->in2Pin));
            break;
    }
}

// Ham cap nhat trang thai dong co (nen duoc goi trong vong lap while(1))
void motor_update(Motor *motor) {
    unsigned long currentMicros = micros();
    // Kiem tra xem da du thoi gian de chuyen trang thai chua
    if (currentMicros - motor->previousMicros >= 10000) { // Chu ki cap nhat 10ms
        motor->previousMicros = currentMicros;
        motor_run(motor, motor->currentCmd); // Cap nhat lai trang thai dong co
    }
}

#endif
