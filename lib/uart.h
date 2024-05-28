#include <mega328p.h>



#define fosc    16000000

volatile unsigned char rxdata;



void uart_init(unsigned int BAUDRATE)
{
  // Cau hinh toc do BAUD
    unsigned int n = fosc/BAUDRATE/16 - 1;
    UBRR0H = n>>8;
    UBRR0L = n;
//Config mode and data frame 
//Che đo khong đong bo, 8 bit du lieu, 1 bit dung, khong co tinh chan le
    UCSR0C = 0b00000110;
//Enable transmiter and receiver, RX interupt
    UCSR0B = 0b10011000;  
    #asm ("sei")
}
void putchar(unsigned char data)
{
	while (!(UCSR0A & 0b00100000)); // cho cho thanh ghi du lieu trong
	UDR0 = data;
}
void putstring(char *str)
{
   while (*str)
   {
        putchar(*str); 
        if (*str == '\n')
        putchar('\r');
        str++;
   }
}

void floatToString(float num, char* buffer, int decimalPlaces) {
    // Chuyen doi phan nguyên thành string
    int intPart = (int)num;
    int index = 0;
    int i, j;
    char temp;
    int digit;
    float decimalPart = num - (int)num;
    do {
        buffer[index++] = intPart % 10 + '0';
        intPart /= 10;
    } while (intPart != 0);

    // Ðao nguoc chuoi phan nguyên
    
    for (i = 0, j = index - 1; i < j; i++, j--) {
        temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Thêm dau cham
    buffer[index++] = '.';

    // Chuyen doi phan thap phan thanh string
    for ( i = 0; i < decimalPlaces; i++) {
        decimalPart *= 10;
        digit = (int)decimalPart;
        buffer[index++] = '0' + digit;
        decimalPart -= digit;
    }

    // Ket thuc string
    buffer[index] = '\n';
}

// Hàm nhan mot ký tu tu UART
interrupt [USART_RXC] void usart_rx_isr(void) {
    rxdata = UDR0;
    putchar(rxdata);
}

// void main(){
//     uart_init(9600);     
//     while(1){
//         float temp = 12.3432534;
//         char buffer[20]; 
//         floatToString(temp, buffer, 6);  
//         putstring(buffer);
//         delay_ms(500);
//     }
// }


