#ifndef Motor_h
#define Motor_h

#include <mega328p.h>
#include <millis.h>

// Dinh nghia cac chan dieu khien dong co (thay doi theo mach cua ban)
#define IN1 8  
#define IN2 9  
#define EN  10 

// Cac lenh dieu khien dong co
#define FORWARD 1  
#define BACKWARD 2 
#define RELEASE 0  

// Khai bao cac ham dieu khien dong co
void motor_init(void);
void motor_setSpeed(int speed);
void motor_run(int cmd);

#endif