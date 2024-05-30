#include "Motor.h"

// Khai báo 4 d?i tu?ng Motor, m?i d?i tu?ng d?i di?n cho 1 d?ng co
Motor motor1(1); 
Motor motor2(2);
Motor motor3(3);
Motor motor4(4);

void main() {
  motor_init(); // Kh?i t?o các chân di?u khi?n cho c? 4 d?ng co

  while (1) {
    // Test quay thu?n t?t c? các d?ng co
    motor1.setSpeed(200); // Ð?t t?c d? cho d?ng co 1 là 200
    motor2.setSpeed(200); // Ð?t t?c d? cho d?ng co 2 là 200
    motor3.setSpeed(200); // Ð?t t?c d? cho d?ng co 3 là 200
    motor4.setSpeed(200); // Ð?t t?c d? cho d?ng co 4 là 200

    motor1.run(FORWARD);  // Yêu c?u d?ng co 1 quay thu?n
    motor2.run(FORWARD);  // Yêu c?u d?ng co 2 quay thu?n
    motor3.run(FORWARD);  // Yêu c?u d?ng co 3 quay thu?n
    motor4.run(FORWARD);  // Yêu c?u d?ng co 4 quay thu?n

    motor1.update(); // C?p nh?t tr?ng thái d?ng co 1
    motor2.update(); // C?p nh?t tr?ng thái d?ng co 2
    motor3.update(); // C?p nh?t tr?ng thái d?ng co 3
    motor4.update(); // C?p nh?t tr?ng thái d?ng co 4

    delay_ms(2000); // Ch? 2 giây d? quan sát

    // Test quay ngh?ch t?t c? các d?ng co
    motor1.run(BACKWARD); // Yêu c?u d?ng co 1 quay ngh?ch
    motor2.run(BACKWARD); // Yêu c?u d?ng co 2 quay ngh?ch
    motor3.run(BACKWARD); // Yêu c?u d?ng co 3 quay ngh?ch
    motor4.run(BACKWARD); // Yêu c?u d?ng co 4 quay ngh?ch

    motor1.update(); // C?p nh?t tr?ng thái d?ng co 1
    motor2.update(); // C?p nh?t tr?ng thái d?ng co 2
    motor3.update(); // C?p nh?t tr?ng thái d?ng co 3
    motor4.update(); // C?p nh?t tr?ng thái d?ng co 4

    delay_ms(2000); // Ch? 2 giây d? quan sát

    // D?ng t?t c? các d?ng co trong 1 giây
    motor1.run(RELEASE); // Yêu c?u d?ng co 1 d?ng
    motor2.run(RELEASE); // Yêu c?u d?ng co 2 d?ng
    motor3.run(RELEASE); // Yêu c?u d?ng co 3 d?ng
    motor4.run(RELEASE); // Yêu c?u d?ng co 4 d?ng

    motor1.update(); // C?p nh?t tr?ng thái d?ng co 1
    motor2.update(); // C?p nh?t tr?ng thái d?ng co 2
    motor3.update(); // C?p nh?t tr?ng thái d?ng co 3
    motor4.update(); // C?p nh?t tr?ng thái d?ng co 4

    delay_ms(1000); // Ch? 1 giây
  }
}
