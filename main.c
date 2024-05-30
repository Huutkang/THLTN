#include <mega328p.h>
#include "lib/millis.h"
#include "lib/gpio.h"
#include "lib/uart.h"
// #include "lib/Ultrasonic.h"
// #include "lib/DCMotor.h"

#include <delay.h>

unsigned long current_time;
unsigned long time1=0;
unsigned long time2=0;
unsigned long time3=0;
unsigned long time4=0;
unsigned long time5=0;

int s = 0;

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

void led(){
    if (s==0){
        s=1;
        digitalWrite(13, HIGH);
    }else{
        s=0;
        digitalWrite(13, LOW);
    }
}

void main(void)
{   
    init_millis(16000000);
    uart_init(9600);
    pinMode(13, OUTPUT);
    while (1)
    {
        if (Timer(&time1, 500)){
            led();
            putstring("Hello, world!\n");
        }
    
    }
}


