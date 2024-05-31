#include "millis.h"

volatile unsigned long timer0_micros = 0;

interrupt [TIM0_COMPA] void timer0_compa_isr(void) {
    timer0_micros++;
}

void init_millis(unsigned long f_cpu) {
    unsigned long ctc_match_overflow;
    ctc_match_overflow = ((f_cpu / 1000000) / 8);

    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS01);
    OCR0A = ctc_match_overflow;

    TIMSK0 |= (1 << OCIE0A);

    #asm("sei")
}

unsigned long millis() {
    return timer0_micros / 10;
}

unsigned long micros() {
    return timer0_micros * 100;
}
