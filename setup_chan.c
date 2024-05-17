#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

// Giả sử có các hàm để setup các chân
void setup_digital_input(uint8_t pin) {
    // Code để setup digital input (sử dụng DDRx và PORTx)
    if (pin < 8) {
        DDRD &= ~(1 << pin); // Set DDRD pin thành 0 (input)
        PORTD |= (1 << pin); // Kích hoạt pull-up resistor
        printf("Setup digital input cho chân D%d\n", pin);
    } else if (pin < 14) {
        pin -= 8;
        DDRB &= ~(1 << pin); // Set DDRB pin thành 0 (input)
        PORTB |= (1 << pin); // Kích hoạt pull-up resistor
        printf("Setup digital input cho chân D%d\n", pin + 8);
    } else {
        printf("Chân D%d không hợp lệ\n", pin);
    }
}

void setup_digital_output(uint8_t pin) {
    // Code để setup digital output (sử dụng DDRx)
    if (pin < 8) {
        DDRD |= (1 << pin); // Set DDRD pin thành 1 (output)
        printf("Setup digital output cho chân D%d\n", pin);
    } else if (pin < 14) {
        pin -= 8;
        DDRB |= (1 << pin); // Set DDRB pin thành 1 (output)
        printf("Setup digital output cho chân D%d\n", pin + 8);
    } else {
        printf("Chân D%d không hợp lệ\n", pin);
    }
}

void setup_analog_input(uint8_t pin) {
    // Code để setup analog input (giả sử chỉ sử dụng ADC cho các chân A0 đến A7)
    if (pin < 8) {
        printf("Setup analog input cho chân A%d\n", pin);
        // ADC setup code here (ADMUX, ADCSRA, etc.)
    } else {
        printf("Chân A%d không hợp lệ\n", pin);
    }
}

void setup_1_chan(const char* ten_chan, char input_or_output) {
    if (ten_chan[0] == 'D') {
        int chan = atoi(&ten_chan[1]);
        if (input_or_output == 'I') {
            setup_digital_input(chan);
        } else if (input_or_output == 'O') {
            setup_digital_output(chan);
        } else {
            printf("Đối số thứ hai chỉ có thể là 'I' hoặc 'O'\n");
        }
    } else if (ten_chan[0] == 'A') {
        int chan = atoi(&ten_chan[1]);
        if (input_or_output == 'I') {
            setup_analog_input(chan);
        } else {
            printf("Chân analog không thể được setup là output\n");
        }
    } else {
        printf("Tên chân không hợp lệ\n");
    }
}

int main() {
    // Sử dụng hàm:
    setup_1_chan("D2", 'I');
    setup_1_chan("A3", 'I');
    setup_1_chan("D9", 'O');
    setup_1_chan("A4", 'O');  // A4 là một chân analog, không thể setup là output
    setup_1_chan("D10", 'X'); // X là một giá trị không hợp lệ
    setup_1_chan("B5", 'I');  // B5 là một tên chân không hợp lệ

    return 0;
}
