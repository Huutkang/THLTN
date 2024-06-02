#include <mega328p.h>
#include "lib/millis.h"
#include "lib/uart.h"
#include "lib/Ultrasonic.h"
#include "lib/Motor.h"
#include "lib/servo.h"
#include <delay.h>


#define Echo 2
#define Trig 10
#define pinServo 9

unsigned long current_time;
unsigned long time1=0;
unsigned long time2=0;
// unsigned long time3=0;
// unsigned long time4=0;
// unsigned long time5=0;

int distance = 0;


int Timer(unsigned long *time, int wait){
    current_time = millis();
    if (current_time-*time>wait){
        *time = current_time;
        return 1;
    }
    else{
        return 0;
    }
}

// Len: U
// Xuong: D
// Trai: L 
// Phai: R 
// khong nhan gi: S 
// Len, Trai: T 
// Len, Phai: F 
// Xuong, Trai: H
// Xuong, Phai: G 
// nut 1 off->on: 1 
// nut 1 on->off: 2 
// nut 2 off->on: 3
// nut 2 on->off: 4

void control(){
    if (rxdata=='U'){
        motor_run(TIEN,TIEN,TIEN,TIEN);
        motor_setSpeed(1, 10);
        motor_setSpeed(2, 10);
        motor_setSpeed(3, 10);
        motor_setSpeed(4, 10);
    }
    else if (rxdata=='D'){
        motor_run(LUI,LUI,LUI,LUI);
        motor_setSpeed(1, 10);
        motor_setSpeed(2, 10);
        motor_setSpeed(3, 10);
        motor_setSpeed(4, 10);
    }
    else if (rxdata=='L'){
    }
    else if (rxdata=='R'){
    }
    else if (rxdata=='T'){
        motor_run(TIEN,TIEN,TIEN,TIEN);
        motor_setSpeed(2, 10);
        motor_setSpeed(3, 10);
        motor_setSpeed(1, 5);
        motor_setSpeed(4, 5);
        
    }else if (rxdata=='F'){
        motor_run(TIEN,TIEN,TIEN,TIEN);
        motor_setSpeed(2, 5);
        motor_setSpeed(3, 5);
        motor_setSpeed(1, 10);
        motor_setSpeed(4, 10);
    }else if (rxdata=='H'){
        motor_run(LUI,LUI,LUI,LUI);
        motor_setSpeed(2, 10);
        motor_setSpeed(3, 10);
        motor_setSpeed(1, 5);
        motor_setSpeed(4, 5);
    }else if (rxdata=='G'){
        motor_run(LUI,LUI,LUI,LUI);
        motor_setSpeed(2, 5);
        motor_setSpeed(3, 5);
        motor_setSpeed(1, 10);
        motor_setSpeed(4, 10);
    }
    else if (rxdata=='1'){
    }
    else if (rxdata=='2'){
    }
    else if (rxdata=='3'){
    }
    else if (rxdata=='4'){
    }
    else{
        motor_run(DUNG,DUNG,DUNG,DUNG);
    }
}

void main(void)
{   
    char buffer[20];
    init_millis(16000000);
    uart_init(9600);
    init_ultrasonic(Echo, Trig);
    motor_init();
    servo_init();
    servo_write(250);
    delay_ms(1000);
    servo_write(50);
    delay_ms(500);
    servo_write(150);
    while (1)
    {
        if (Timer(&time1,100)){
            control();
        }
        if (Timer(&time2, 500)){
            distance = ultrasonic(Echo , Trig);
            floatToString(distance, buffer, 1);
            putstring(buffer);
        }
        // if (Timer(&time3,100)){
        //     function();
        // }
    }
}




