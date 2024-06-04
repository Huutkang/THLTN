#include <mega328p.h>
#include "millis.h"
#include "uart.h"
#include "Ultrasonic.h"
#include "Motor.h"
#include "servo.h"
#include <delay.h>


#define Echo 2
#define Trig 10
#define pinServo 9

// Nút bam
#define BUTTON1 2   // Nut chon che do tranh vat can (PD2)
#define BUTTON2 3  // Nut chon che do Bluetooth (PD3)
#define BUTTON3 4     // Nut chon che do giong nói (PD4)

#define mode_tranhvatcan 1  // Che do tranh vat can
#define mode_bluetooth 2 // Che do dieu khien Bluetooth
#define mode_voice 3     // Che do dieu khien bang giong noi
int mode = mode_tranhvatcan;   // Che do mac dinh là tranh vat can

unsigned long current_time;
unsigned long time1=0;
unsigned long time2=0;
unsigned long time3=0;
// unsigned long time4=0;
// unsigned long time5=0;

int distance = 0;
int Left, Right;
int dem;
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

void dung(){
    motor_run(DUNG,DUNG,DUNG,DUNG);
    putstring("dung\n");
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
int nhinphai() {
  servo_write(70);
  delay_ms(500);
  Left = ultrasonic(Echo, Trig);
  return Left;
}
int nhintrai() {
  servo_write(230);
  delay_ms(500);
  Right = ultrasonic(Echo, Trig);
  return Right;
}
// -- Che do dieu khien Bluetooth --
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
        //dung();
    }   
}
//Che do tranh vat can
void tranh_vat_can() {
    if (Timer(&time1, 200)) { // Kiem tra chuong ngai vat moi 200ms
        distance = ultrasonic(Echo, Trig); // Do khoang cach
        if (distance <= 12 && distance != 0) { // Neu co vat can gan hon 12cm
            dung(); // Dung xe

            // Lui lai mot chut
            lui();
            delay_ms(100); // Dung lai mot chut de on dinh
            dung();

            // Kiem tra khoang cach ben trai va ben phai
            Left = nhintrai();
            servo_write(150); // Tra servo ve vi tri giua
            delay_ms(300);      // Doi servo on dinh vi tri
            Right = nhinphai();
            servo_write(150);
            delay_ms(300);

            // Quyet dinh huong re dua tren khoang cach
            if (Left > Right) {
                quayphai(); // Re phai neu ben phai rong hon
                delay_ms(500);
            } else if (Left < Right) {
                quaytrai(); // Re trai neu ben trai rong hon
                delay_ms(500);
            } else {
                lui(); // Lui lai neu ca hai ben deu bi chan
                delay_ms(500); 
            }
            dung(); // Dung lai sau khi re
        } else {
            lui(); // Tiep tuc tien neu khong co vat can
        }
    }
}
// Che do dieu khien bang giong noi
void voice_control() {
    switch (rxdata) {
        case '^': tien(); break;        
        case '-': lui(); break;        
        case '<': quaytrai(); break;     
        case '>': quayphai(); break;     
        case 'L': tien_re_trai(); break;
        case 'R': tien_re_phai(); break;
        case 'S': dung(); break;       
        default: break;
    }
}
// Main
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
        // Nut bam doi che do
        if (digitalRead(BUTTON1) == LOW) {
            delay_ms(20);
            if (digitalRead(BUTTON1) == LOW) {
                mode = mode_tranhvatcan;
                while (digitalRead(BUTTON1) == LOW);
            }
        } else if (digitalRead(BUTTON2) == LOW) {
            delay_ms(20);
            if (digitalRead(BUTTON2) == LOW) {
                mode = mode_bluetooth;
                while (digitalRead(BUTTON2) == LOW);
            }
        } else if (digitalRead(BUTTON3) == LOW) {
            delay_ms(20);
            if (digitalRead(BUTTON3) == LOW) {
                mode = mode_voice;
                while (digitalRead(BUTTON3) == LOW);
            }
        }

        // Doi cac che do
        switch (mode) {
            case mode_tranhvatcan:
                tranh_vat_can(); // Che do tranh vat can
                break;
            case mode_bluetooth:
                control(); // Che do dieu khien Bluetooth
                break;
            case mode_voice:
                voice_control(); // Che do dieu khien bang giong noi
                break;
        }
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
