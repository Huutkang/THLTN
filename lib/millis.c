#include <mega328p.h>
#include "millis.h"

void main(void){
	 DDRB = (1 << DDB5); // cài đặt PORTB5 thành đầu ra
  	 PORTB ^= (1 << PORTB5);

  	 init_millis(16000000UL); // tần số atmega328p đang chạy ở
  	 unsigned long prev_millis; // lần cuối cùng đèn led được bật
  	 prev_millis = millis();
  	 while(1){
     		 if (millis() - prev_millis > 1000){
      		 	PORTB ^= (1 << PORTB5); //Turn on / Turn off the LED
      			prev_millis = millis();
    }
  }
}
