#ifndef SERVO_H_
#define SERVO_H_

#include <mega328p.h>

void servo_init(uint8_t pin);
void servo_write(uint8_t angle);
uint8_t servo_read();

#endif
