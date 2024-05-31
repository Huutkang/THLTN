#ifndef _MILLIS_H_
#define _MILLIS_H_

#include <mega328p.h>

// Bien toan cuc de theo doi thoi gian da troi qua
// Tinh bang don vi 100 micro giay (0.1 mili giay)
volatile unsigned long timer0_micros = 0;

// Ham ngat duoc goi khi bo dem Timer0 tran
interrupt [TIM0_COMPA] void timer0_compa_isr(void) {
    timer0_micros++; // Tang bien dem thoi gian len 1 don vi
}

// Ham khoi tao bo dem millis va micros
// f_cpu la tan so hoat dong cua vi dieu khien (VD: 16000000 cho 16MHz)
void init_millis(unsigned long f_cpu) {
    unsigned long ctc_match_overflow;

    // Tinh toan gia tri so sanh de tao tran sau moi 1 micro giay
    ctc_match_overflow = ((f_cpu / 1000000) / 8); // Chia 8 do su dung prescaler 8

    // Thiet lap Timer0 o che do CTC (Clear Timer on Compare Match)
    TCCR0A |= (1 << WGM01);

    // Chon prescaler la 8
    TCCR0B |= (1 << CS01);

    // Cai dat gia tri so sanh de tao tran sau moi 1 micro giay
    OCR0A = ctc_match_overflow;

    // Cho phep ngat khi bo dem trung khop gia tri so sanh
    TIMSK0 |= (1 << OCIE0A);

    // Bat ngat toan cuc
    #asm("sei")
}

// Ham tra ve thoi gian da troi qua tinh bang mili giay
unsigned long millis() {
    return timer0_micros / 10; // Chuyen doi tu don vi 100 micro giay sang mili giay
}

// Ham tra ve thoi gian da troi qua tinh bang micro giay
unsigned long micros() {
    return timer0_micros * 100; // Chuyen doi tu don vi 100 micro giay sang micro giay
}

#endif /* _MILLIS_H_ */
