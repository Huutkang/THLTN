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
    servo_write(50); 
    delay_ms(100);
    return ultrasonic(Echo, Trig);
}
int nhintrai() {
    servo_write(150); 
    delay_ms(100);
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
        mode = 1;
    }else if (rxdata=='2'){
        mode = 1;
    }else if (rxdata=='3'){
        mode = 2;
    }else if (rxdata=='4'){
        mode = 2;
    }else{
        motor_run(DUNG,DUNG,DUNG,DUNG);
    }
}
void tranh_vat_can() {
    distance = ultrasonic(Echo, Trig);
    if (distance <= 10 && distance != 0) { 
        dung();
        lui();
        dung();
        Left = nhintrai();
        Right = nhinphai();
        servo_write(100);
        if (Left > Right) {
            quaytrai();
        } else if (Left < Right) {
            quayphai();
        } else {
            lui(); 
        }
        delay_ms(100);
        dung();
    } else {
        tien();
    }
}
// void tranh_vat_can() {
//     if (Timer(&time1, 200)) { // Kiem tra chuong ngai vat moi 200ms
//         distance = ultrasonic(Echo, Trig); // Do khoang cach
//         if (distance <= 10 && distance != 0) { // Neu co vat can gan hon 12cm
//             dung(); // Dung xe

//             // Lui lai mot chut
//             lui();
//             delay_ms(100); // Dung lai mot chut de on dinh
//             dung();

//             // Kiem tra khoang cach ben trai va ben phai
//             Left = nhintrai();
//             servo_write(150); // Tra servo ve vi tri giua
//             delay_ms(300);      // Doi servo on dinh vi tri
//             Right = nhinphai();
//             servo_write(150);
//             delay_ms(300);

//             // Quyet dinh huong re dua tren khoang cach
//             if (Left > Right + 2) {
//                 quayphai(); // Re phai neu ben phai rong hon 
//                 delay_ms(500);   
//                 servo_write(150);
//                 delay_ms(500);
//             } else if (Left +2 < Right) {
//                 quaytrai(); // Re trai neu ben trai rong hon
//                 delay_ms(500);
//                 servo_write(150);
//                 delay_ms(500);
//             } else {
//                 lui(); // Lui lai neu ca hai ben deu bi chan
//                 delay_ms(500); 
//             }
//             dung(); // Dung lai sau khi re
//         } else if (distance > 12)
//             tien(); // Tiep tuc tien neu khong co vat can
//     }
// }

void main(void)
{   
    int savemode=1;
    init_millis(16000000);
    uart_init(9600);
    init_ultrasonic(Echo, Trig);
    motor_init();
    servo_init();
    pinMode(PMODE, INPUT);
    delay_ms(3000);
    servo_write(50);
    delay_ms(3000);
    servo_write(150);
    delay_ms(3000);
    servo_write(100);
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
                if (Timer(&time2, 300)){
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
                        case '^': tien(); break;        
                        case '-': lui(); break;        
                        case '<': quaytrai(); break;     
                        case '>': quayphai(); break;     
                        case '(': tien_re_trai(); break;
                        case ')': tien_re_phai(); break;
                        case '[': lui_re_trai(); break;
                        case ']': lui_re_phai(); break;
                        case '.': dung(); break;
                    }
                    savemode = mode;
                }
        }
    }
}
