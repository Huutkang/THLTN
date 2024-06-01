#ifndef Servo_h
#define Servo_h
#include <mega328p.h>
#include <io.h>

#define F_CPU 16000000
#define DEFAULT_PULSE_WIDTH  	1500     // do rong xung mac dinh
#define SERVO_MIN_PULSE_WIDTH 500		// do rong xung nho nhat
#define SERVO_MAX_PULSE_WIDTH 2500	// do rong xung lon nhat
#define SERVO_FREQUENCY 50

typedef struct {
    char pin;           // Chan dieu khien servo
    unsigned short min_pulse;    // Do rong xung nho nhat
    unsigned short max_pulse;    // Ðo rong xung lon nhat
    unsigned short current_pulse; // Ðo rong xung hien tai
} Servo;

void attach(Servo* servo, char pin);		// khoi tao servo
void write(Servo* servo, unsigned short angle);	// Thiet lap goc cho servo
void write_us(Servo* servo, unsigned short pulse);	// Thiet lap do rong xung cho servo
void servo_update_pwm(Servo* servo);	// cap nhat	tin hieu PWM cho servo
unsigned short read(Servo* servo);	// doc gia tri goc hien tai cua servo

#endif
