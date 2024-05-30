#include "Motor.h"

// Bien luu tru trang thai cua dong co
static unsigned long previousMillis = 0; 
static int interval = 1000; // Khoang thoi gian mac dinh giua cac trang thai la 1 giay
static int currentCmd = RELEASE; // Khoi tao dong co o trang thai dung

// Ham khoi tao dong co
void motor_init(void) {
  DDRB |= (1 << IN1) | (1 << IN2) | (1 << EN); // Dat cac chan IN1, IN2, EN la OUTPUT
}

// Ham dat toc do dong co (0-255)
void motor_setSpeed(int speed) {
  // Thuc hien PWM tai day (ban can tu viet code PWM cho ATmega328P)
  // Vi du su dung Timer0:
  OCR0A = speed; // Dat gia tri PWM
  TCCR0A |= (1 << COM0A1); // Che do PWM khong dao xung
  TCCR0A |= (1 << WGM00) | (1 << WGM01); // Che do Fast PWM
  TCCR0B |= (1 << CS01); // Prescaler 8
}

// Ham dieu khien chieu quay cua dong co
void motor_run(int cmd) {
  currentCmd = cmd; // Luu lai lenh moi
  previousMillis = millis(); // Cap nhat thoi gian bat dau thuc hien lenh
}

// Ham cap nhat trang thai dong co (nen duoc goi trong vong lap loop())
void motor_update(void) {
  unsigned long currentMillis = millis(); // Lay thoi gian hien tai

  // Kiem tra xem da du thoi gian de chuyen trang thai chua
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Cap nhat lai thoi gian truoc do

    switch (currentCmd) { // Thuc hien lenh dieu khien dong co
      case FORWARD:
        PORTB |= (1 << IN1);
        PORTB &= ~(1 << IN2);
        break;
      case BACKWARD:
        PORTB &= ~(1 << IN1);
        PORTB |= (1 << IN2);
        break;
      case RELEASE:
        PORTB &= ~(1 << IN1);
        PORTB &= ~(1 << IN2);
        break;
    }
  }
}
