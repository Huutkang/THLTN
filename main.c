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
#define PMODE 13

unsigned long current_time;
unsigned long time1=0;
unsigned long time2=0;
unsigned long time3=0;
// unsigned long time4=0;
// unsigned long time5=0;

int distance = 0;
int mode = 1;
float Left;
float Right;

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

void dung(){
    motor_run(DUNG,DUNG,DUNG,DUNG);
}

int nhinphai() {
    servo_write(70);
    delay_ms(300);
    return ultrasonic(Echo, Trig);
}
int nhintrai() {
    servo_write(230);
    delay_ms(300);
    return ultrasonic(Echo, Trig);
}

void control(){
    if (rxdata=='U'){
        tien();
    }else if (rxdata=='D'){
        lui();
    }else if (rxdata=='L'){
        quaytrai();
    }else if (rxdata=='R'){
        quayphai();
    }else if (rxdata=='T'){
        tien_re_trai();
    }else if (rxdata=='F'){
        tien_re_phai();
    }else if (rxdata=='H'){
        lui_re_trai();
    }else if (rxdata=='G'){
        lui_re_phai();
    }else if (rxdata=='1'){
        mode = 2;
    }else if (rxdata=='2'){
        mode = 2;
    }else if (rxdata=='3'){
    }else if (rxdata=='4'){
    }else{
        motor_run(DUNG,DUNG,DUNG,DUNG);
    }
}

void tranh_vat_can() {
    distance = ultrasonic(Echo, Trig);
    if (distance <= 12 && distance != 0) { 
        dung();
        lui();
        delay_ms(100);
        dung();

        Left = nhintrai();
        servo_write(150);
        delay_ms(300);
        Right = nhinphai();
        servo_write(150);
        delay_ms(300);

        if (Left > Right) {
            quayphai();
            delay_ms(500);
        } else if (Left < Right) {
            quaytrai();
            delay_ms(500);
        } else {
            lui();
            delay_ms(500); 
        }
        dung();
    } else {
        lui();
        delay_ms(1000);
        dung();
    }
}


void main(void)
{   
    int savemode=1;
    char buffer[20];
    init_millis(16000000);
    uart_init(9600);
    init_ultrasonic(Echo, Trig);
    motor_init();
    servo_init();
    pinMode(PMODE, INPUT);
    delay_ms(3000);
    servo_write(100);
    delay_ms(1000);
    servo_write(200);
    delay_ms(1000);
    servo_write(150);
    while (1)
    {   
        if (Timer(&time1,500)){
            if (digitalRead(PMODE)==0){
                mode = 0;
            }else{
                mode = savemode;
            }
        }
        switch (mode){
            case 0:
                if (Timer(&time2, 200)){
                    tranh_vat_can(); 
                }
                break;
            case 1:
                if (Timer(&time2,200)){
                    control();
                }
                if (Timer(&time3,400)){
                    if (dem<1){
                        motor_run(DUNG,DUNG,DUNG,DUNG);
                        rxdata='S';
                    }
                    dem = 0;
                }
                break;
            case 2:
                if (Timer(&time2,200)){
                    switch (rxdata) {
                        case '1': mode = 1; break;
                        case '2': tien(); break;        
                        case '3': lui(); break;        
                        case '4': quaytrai(); break;     
                        case '5': quayphai(); break;     
                        case '6': tien_re_trai(); break;
                        case '7': tien_re_phai(); break;
                        case '8': dung(); break;       
                    }
                    savemode = mode;
                }
                
        }
    }
}


