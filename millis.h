#ifndef _MILLIS_H_
#define _MILLIS_H_

#include <mega328p.h>

// Bien toan cuc de theo doi thoi gian (tinh bang don vi 100 micro giay)
extern volatile unsigned long timer0_micros;

// Khai bao nguyen mau ham khoi tao
void init_millis(unsigned long f_cpu);

// Khai bao nguyen mau ham lay thoi gian da troi qua (tinh bang mili giay)
unsigned long millis(void);

// Khai bao nguyen mau ham lay thoi gian da troi qua (tinh bang micro giay)
unsigned long micros(void);

#endif /* _MILLIS_H_ */
