#include "servo.h"
#include <io.h>
#include <delay.h>
//tinh toan do rong xung tu goc
static unsigned short angle_to_pulse(char angle) {
    return (unsigned short)(SERVO_MIN_PULSE_WIDTH + ((SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) * angle) / 180);
}
//tinh toan goc tu do rong xung
static char pulse_to_angle(unsigned short pulse) {
    return (char)(((pulse - SERVO_MIN_PULSE_WIDTH) * 180) / (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH));
}
void attach(Servo* servo, char pin){
	servo->pin = pin;
    servo->min_pulse = SERVO_MIN_PULSE_WIDTH;
    servo->max_pulse = SERVO_MAX_PULSE_WIDTH;
    servo->current_pulse = DEFAULT_PULSE_WIDTH;
	
	
	// Thiet lap chan dieu khien servo la output
   	DDRB |= (1 << pin); // su dung chan PB3
	// cau hinh timer1 che do CTC, prescale 8
	TCCR2A = (1 << WGM21);
    TCCR2B |= (1 << CS21);

	// Thiet lap tan so PWM cho servo
    OCR2A = (F_CPU / 8 / SERVO_FREQUENCY) - 1;
    // bat ngat khi khi dat gia tri OCR2A
    TIMSK2 |= (1 << OCIE2A);
    #asm("sei");
}
// Thiet lap goc cho servo
void write(Servo* servo, unsigned short angle) {
    if (angle > 180) {
        angle = 180;
    }
    servo->current_pulse = angle_to_pulse(angle);
    servo_update_pwm(servo);
}
void write_us(Servo* servo, unsigned short pulse){
    if (pulse < servo->min_pulse) {
        pulse = servo->min_pulse;
    } else if (pulse > servo->max_pulse) {
        pulse = servo->max_pulse;
    }
    servo->current_pulse = pulse;
    servo_update_pwm(servo);
}
char servo_read(Servo* servo) {
    return pulse_to_angle(servo->current_pulse);
}
void servo_update_pwm(Servo* servo) {
    OCR2B = ((int)servo->current_pulse * (OCR2A + 1)) / 20000;
}
// thiet lap ngat
interrupt [TIM2_COMPA] void timer2_compa_isr(void) {
    // Thiet lap xung PWM cho servo tren chan PB3
    unsigned short delay_count = 0;
    if (OCR2B != 0) {
        PORTB |= (1 << PORTB3);
        while (delay_count < OCR2B) {
            delay_count++;
        }        
        PORTB &= ~(1 << PORTB3);
    }
}
