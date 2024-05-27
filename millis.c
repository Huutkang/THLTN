#include <mega328p.h>
#include "millis.h"

void main(void){
	 DDRB = (1 << DDB5); //setting PORTB5 to an output
  	 PORTB ^= (1 << PORTB5);

  	 init_millis(16000000UL); //frequency the atmega328p is running at
  	 unsigned long prev_millis; //the last time the led was toggled
  	 prev_millis = millis();
  	 while(1){
     		 if (millis() - prev_millis > 1000){
      		 	PORTB ^= (1 << PORTB5); //Turn on / Turn off the LED
      			prev_millis = millis();
    }
  }
}
}
