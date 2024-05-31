#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <mega328p.h>
#include <delay.h>
#include "gpio.h"

long pulseIn(int pin, int value) {
    long width = 0;
    while ((digitalRead(pin)) == value);
    while ((digitalRead(pin)) != value);
    while ((digitalRead(pin)) == value) {
        width++;
        delay_us(1);
    }
    return width;
}

void init_ultrasonic(int Echo, int Trig){
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
}

float ultrasonic(int Echo, int Trig) {
    long t;
    float cm;
    digitalWrite(Trig, LOW);
    delay_us(4);
    digitalWrite(Trig, HIGH);
    delay_us(10);
    digitalWrite(Trig, LOW);
    t = pulseIn(Echo, 1);
    cm = (t/2.9)/2;   // time convert distance
    return cm;
}

#endif 

