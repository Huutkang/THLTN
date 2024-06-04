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
unsigned long time3=0;
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

void tien(){
    motor_run(TIEN,TIEN,TIEN,TIEN);
    motor_setSpeed(1, 10);
    motor_setSpeed(2, 10);
    motor_setSpeed(3, 10);
    motor_setSpeed(4, 10);
    putstring("len\n");
}

void lui(){
    motor_run(LUI,LUI,LUI,LUI);
    motor_setSpeed(1, 10);
    motor_setSpeed(2, 10);
    motor_setSpeed(3, 10);
    motor_setSpeed(4, 10);
    putstring("xuong\n");
}

void quaytrai(){
    motor_run(LUI,TIEN,TIEN,LUI);
    motor_setSpeed(2, 7);
    motor_setSpeed(3, 7);
    motor_setSpeed(1, 7);
    motor_setSpeed(4, 7);
    putstring("trai\n");
}

void quayphai(){
    motor_run(TIEN,LUI,LUI,TIEN);
    motor_setSpeed(2, 7);
    motor_setSpeed(3, 7);
    motor_setSpeed(1, 7);
    motor_setSpeed(4, 7);
    putstring("phai\n");
}

void tien_re_trai(){
    motor_run(TIEN,TIEN,TIEN,TIEN);
    motor_setSpeed(2, 10);
    motor_setSpeed(3, 10);
    motor_setSpeed(1, 5);
    motor_setSpeed(4, 5);
}

void tien_re_phai(){
    motor_run(TIEN,TIEN,TIEN,TIEN);
    motor_setSpeed(2, 5);
    motor_setSpeed(3, 5);
    motor_setSpeed(1, 10);
    motor_setSpeed(4, 10);
}

void lui_re_trai(){
    motor_run(LUI,LUI,LUI,LUI);
    motor_setSpeed(2, 10);
    motor_setSpeed(3, 10);
    motor_setSpeed(1, 5);
    motor_setSpeed(4, 5);
}

void lui_re_phai(){
    motor_run(LUI,LUI,LUI,LUI);
    motor_setSpeed(2, 5);
    motor_setSpeed(3, 5);
    motor_setSpeed(1, 10);
    motor_setSpeed(4, 10);
}
void control(){
    if (rxdata=='U'){
        tien();
    }
    else if (rxdata=='D'){
        lui();
    }
    else if (rxdata=='L'){
        quaytrai();
    }
    else if (rxdata=='R'){
        quayphai();
    }
    else if (rxdata=='T'){
        tien_re_trai();

    }else if (rxdata=='F'){
        tien_re_phai();
    }else if (rxdata=='H'){
        lui_re_trai();
    }else if (rxdata=='G'){
        lui_re_phai();
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
    delay_ms(3000);
    servo_write(100);
    delay_ms(1000);
    servo_write(200);
    delay_ms(1000);
    servo_write(150);
    while (1)
    {
        if (Timer(&time1,200)){
            control();
        }
        if (Timer(&time2, 300)){
            distance = ultrasonic(Echo , Trig);
            floatToString(distance, buffer, 1);
            putstring(buffer);
        }
        if (Timer(&time3,400)){
            if (dem<1){
                motor_run(DUNG,DUNG,DUNG,DUNG);
                rxdata='S';
            }
            dem = 0;
        }
    }
}




