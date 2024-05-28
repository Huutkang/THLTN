#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>



void setup_digital_input(uint8_t pin) {
    // Code đe setup digital input (su dung DDRx và PORTx)
    if (pin < 8) {
        DDRD &= ~(1 << pin); // Set DDRD pin thanh 0 (input)
        PORTD |= (1 << pin); // Kich hoạt pull-up resistor
        printf("Setup digital input cho chân D%d\n", pin);
    } else if (pin < 14) {
        pin -= 8;
        DDRB &= ~(1 << pin); // Set DDRB pin thành 0 (input)
        PORTB |= (1 << pin); // Kich hoạt pull-up resistor
        printf("Setup digital input cho chan D%d\n", pin + 8);
    } else {
        printf("Chan D%d khong hop le\n", pin);
    }
}

void setup_digital_output(uint8_t pin) {
    // Code đe setup digital output (su dụng DDRx)
    if (pin < 8) {
        DDRD |= (1 << pin); // Set DDRD pin thanh 1 (output)
        printf("Setup digital output cho chan D%d\n", pin);
    } else if (pin < 14) {
        pin -= 8;
        DDRB |= (1 << pin); // Set DDRB pin thanh 1 (output)
        printf("Setup digital output cho chan D%d\n", pin + 8);
    } else {
        printf("Chan D%d khong hop le\n", pin);
    }
}

void setup_analog_input(uint8_t pin) {
    // Code đe setup analog input (gia su chi su dung ADC cho cac chan A0 den A7)
    if (pin < 8) {
        printf("Setup analog input cho chan A%d\n", pin);
        // ADC setup code here (ADMUX, ADCSRA, etc.)
    } else {
        printf("Chan A%d khong hop le\n", pin);
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
            printf("Đoi so thu hai chi co the la 'I' hoac 'O'\n");
        }
    } else if (ten_chan[0] == 'A') {
        int chan = atoi(&ten_chan[1]);
        if (input_or_output == 'I') {
            setup_analog_input(chan);
        } else {
            printf("Chan analog khong the duoc setup la output\n");
        }
    } else {
        printf("Ten chan khong hop le\n");
    }
}

// int main() {
//     // Sử dụng hàm:
//     setup_1_chan("D2", 'I');
//     setup_1_chan("A3", 'I');
//     setup_1_chan("D9", 'O');
//     setup_1_chan("A4", 'O');  // A4 la mot cha analog, khong the setup là output
//     setup_1_chan("D10", 'X'); // X la mot gia tri khong hop le
//     setup_1_chan("B5", 'I');  // B5 la mot ten chan khong hop le

//     return 0;
// }