#define _MILLIS_H_

unsigned long millis_value;

interrupt [TIM1_COMPA] void timer1_comp_isr(void)
{
    // Increment millisecond every 1ms
    millis_value++;  
}
void init_millis(unsigned long f_cpu){
     unsigned long ctc_match_overflow;
     ctc_match_overflow = ((f_cpu / 1000) / 8); //when timer0 is this value, 1ms has passed     
     // (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
     TCCR1B |= (1 << WGM12) | (1 << CS11);
     
     // high byte first, then low byte
     OCR1AH = (ctc_match_overflow >> 8);
     OCR1AL = ctc_match_overflow;
     
     // Enable the compare match interrupt
	 TIMSK1 |= (1 << OCIE1A);
#asm("sei")
}
unsigned long millis (void){
		 //Disable interrupts while we read millis_value or we might get an inconsistent value
		 unsigned long millis_return;
		 #asm("cli")
    	 millis_return = millis_value;
	     #asm("sei")
     	 return millis_return;         
}