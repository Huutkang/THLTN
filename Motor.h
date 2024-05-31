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
    unsigned char in1Pin;    // Chan IN1
    unsigned char in2Pin;    // Chan IN2
    unsigned char enPin;     // Chan Enable (PWM)
    unsigned long previousMicros; // Thoi gian cap nhat truoc do (tinh bang micro giay)
    int currentCmd;       // Lenh hien tai cua dong co
} Motor;

// Khai bao cac ham dieu khien dong co
void motor_init(Motor *motor, unsigned char in1Pin, unsigned char in2Pin, unsigned char enPin);
void motor_setSpeed(int speed); // Dieu chinh dong co chi can toc do, khong can thong tin dong co
void motor_run(Motor *motor, int cmd);
void motor_update(Motor *motor);

#endif
