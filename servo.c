#include "servo.h"

static volatile uint8_t *servo_port; // Con tro toi port dieu khien servo
static uint8_t servo_pin; // Pin dieu khien servo
static volatile unsigned char target_angle;
static volatile unsigned long previous_millis;

void servo_init(volatile uint8_t *port, uint8_t pin)
{
    servo_port = port; // Luu lai port va pin
    servo_pin = pin;

    // Thiet lap chan dieu khien servo la OUTPUT
    *servo_port |= (1 << servo_pin);

    // Thiet lap Timer2 de tao tin hieu PWM
    TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20); // Fast PWM
    TCCR2B = (1 << CS21); // Prescaler 8
    OCR2A = 125; // Khoi tao gia tri ban dau (tuong ung goc 90 do)

    // Khoi tao bien thoi gian
    previous_millis = millis();
}

void servo_set_angle(unsigned char angle)
{
    target_angle = angle;
}

void servo_update(void)
{
    unsigned long current_millis = millis();

    if (current_millis - previous_millis >= 20)
    {
        unsigned int pulse_width = 1000 + (target_angle * 10);
        OCR2A = pulse_width / 8; // Chia cho 8 do prescaler la 8
        previous_millis = current_millis;
    }
}
