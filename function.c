#define fosc    16000000
void uart_init(unsigned int BAUDRATE)
{
  //Config BAUD Rate
    unsigned int n = fosc/BAUDRATE/16 - 1;
    UBRR0H = n>>8;
    UBRR0L = n;
//Config mode and data frame 
//Asynchronous mode, 8 data bit, 1 stop bit, no Parity
    UCSR0C = 0b00000110;
//Enable transmiter and receiver, RX interupt
    UCSR0B = 0b10011000;  
    #asm ("sei")
}
void putchar(unsigned char data)
{
	while (!(UCSR0A & 0b00100000)); //wait for data register empty
	UDR0 = data;
}
void putstring(char *str)
{
   while (*str)
   {
        putchar(*str); 
        //if see the line feed, add carriage return
        if (*str == '\n')
        putchar('\r');
        str++;
   }
}
void floatToString(float num, char* buffer, int decimalPlaces) {
    // Chuy?n d?i ph?n nguyên thành string
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

    // Ð?o ngu?c chu?i ph?n nguyên
    
    for (i = 0, j = index - 1; i < j; i++, j--) {
        temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Thêm d?u ch?m
    buffer[index++] = '.';

    // Chuy?n d?i ph?n th?p phân thành string
    for ( i = 0; i < decimalPlaces; i++) {
        decimalPart *= 10;
        digit = (int)decimalPart;
        buffer[index++] = '0' + digit;
        decimalPart -= digit;
    }

    // K?t thúc string
    buffer[index] = '\n';
}

// Hàm nhận một ký tự từ UART
unsigned char USART_Receive(void) {
    // Chờ cho đến khi dữ liệu nhận sẵn sàng
    while (!(UCSRA & (1<<RXC)));
    // Trả về dữ liệu đã nhận
    return UDR;
}

// Hàm nhận một chuỗi từ UART
void USART_ReceiveString(char* buffer, int max_length) {
    int i = 0;
    char received_char;
    // Nhận lần lượt từng ký tự cho đến khi gặp ký tự kết thúc '\0'
    do {
        received_char = USART_Receive();
        buffer[i] = received_char;
        i++;
    } while (received_char != '\0' && i < max_length - 1); // Tránh việc tràn bộ nhớ và lưu lại ký tự kết thúc
    // Kết thúc chuỗi với ký tự '\0'
    buffer[i] = '\0';
}

int main(void) {
    // Khởi tạo UART với tốc độ baud là 9600
    uart_init(9600);

    // Khai báo một buffer để lưu chuỗi nhận được
    char received_string[100];

    // Vòng lặp chính
    while (1) {
        // Nhận chuỗi từ UART
        USART_ReceiveString(received_string, 100);
        
        // In ra chuỗi đã nhận được
        putstring("Received string: ");
        putstring(received_string);
    }

    return 0;
}
