#include <mega328p.h>
#include "lib/millis.h"
#include "lib/gpio.h"
#include "lib/uart.h"
// #include "lib/Ultrasonic.h"
#include "lib/Motor.h"
#include <delay.h>


#define Echo 2
#define Trig 10


unsigned long current_time;
unsigned long time1=0;
// unsigned long time2=0;
// unsigned long time3=0;
// unsigned long time4=0;
// unsigned long time5=0;

int s = 0;
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
    // init_ultrasonic(Echo, Trig);
    pinMode(10, OUTPUT);
    motor_init();
    delay_ms(1000);
    while (1)
    {
        if (Timer(&time1,100)){
            control();
        }
    
    }
}




