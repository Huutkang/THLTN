#ifndef SERVO_H_
#define SERVO_H_

#include <mega328p.h>

// Cac ham dieu khien servo
void servo_init(volatile uint8_t *port, uint8_t pin); // Khoi tao voi port va pin
void servo_set_angle(unsigned char angle);
void servo_update(void);

#endif /* SERVO_H_ */
