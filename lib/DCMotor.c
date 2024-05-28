#include "DCMotor.h"

DCMotor::DCMotor(uint8_t pinA, uint8_t pinB, uint8_t pinS) {
  this->pinA = pinA;
  this->pinB = pinB;
  this->pinS = pinS;

  pinMode(this->pinA, OUTPUT);
  pinMode(this->pinB, OUTPUT);
  pinMode(this->pinS, OUTPUT);
}


// Bật động cơ với tốc độ xác định.
void DCMotor::on(uint8_t speed) {
  this->off();

  // Đảm bảo tốc độ nằm trong phạm vi hợp lệ (0-255)
  speed = constrain(speed, -255, 255);
      
  // Đặt hướng động cơ dựa trên dấu hiệu tốc độ
  digitalWrite(this->pinA, speed >= 0 ? HIGH : LOW);
  digitalWrite(this->pinB, speed >= 0 ? LOW : HIGH);

  // Đặt tốc độ động cơ bằng cách sử dụng xung điều khiển PWM
  analogWrite(this->pinS, abs(speed));
}

// Bật động cơ với tốc độ xác định, trong một thời gian nhất định
void DCMotor::on(uint8_t speed, int millisec) {
  this->on(speed);
  delay(millisec);
  this->off();
}

// Tắt động cơ.
void DCMotor::off() {
  digitalWrite(this->pinA, LOW);
  digitalWrite(this->pinB, LOW);
  analogWrite(this->pinS, 0);
}
