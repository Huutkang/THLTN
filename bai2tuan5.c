/*
 * bai1tuan5.c
 *
 * Created: 3/16/2024 11:10:10 AM
 * Author: HP
 */
#include <delay.h>
#include <mega328p.h>
volatile unsigned char rxdata;
void putchar(unsigned char data)
{
    while (!(UCSR0A & 0b00100000)); //Ch? thanh ghi d? li?u Empty
    UDR0 = data;
}
interrupt [USART_RXC] void usart_rx_isr(void) {
    rxdata = UDR0;
    putchar(rxdata);
}
void main(void)
{
    int n = 16000000/(16*9600) - 1;
    UBRR0H = n>>8; 
    UBRR0L = n;
    UCSR0C = 0b00000110; 
    UCSR0B = 0b10011000;
#asm("sei")
while (1)
    {
    // Please write your application code here    
    }
}
