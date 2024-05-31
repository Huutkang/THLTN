#include <mega328p.h>
#include "millis.h" // Đảm bảo bạn đã thêm thư viện millis.h vào project
#include "motor.h"

// Khai báo 4 biến Motor
Motor motor1, motor2, motor3, motor4;

// Biến để lưu thời gian bắt đầu
unsigned long startTime;

// Hàm khởi tạo (chạy một lần khi bắt đầu)
void main(void) {
    // Khởi tạo các động cơ, điều chỉnh chân cho phù hợp với mạch của bạn:
    motor_init(&motor1, 8, 9, 10);  // IN1, IN2, EN cho motor1
    motor_init(&motor2, 11, 12, 13); // IN1, IN2, EN cho motor2
    motor_init(&motor3, 5, 6, 7);   // IN1, IN2, EN cho motor3
    motor_init(&motor4, 2, 3, 4);   // IN1, IN2, EN cho motor4

    while (1) {
        // Điều khiển động cơ theo ý muốn của bạn ở đây

        // Ví dụ: Cho 4 động cơ chạy tiến trong 2 giây, sau đó dừng lại
        motor_run(&motor1, FORWARD);
        motor_run(&motor2, FORWARD);
        motor_run(&motor3, FORWARD);
        motor_run(&motor4, FORWARD);
        motor_setSpeed(200); // Đặt tốc độ (0-255)

        // Lấy thời gian bắt đầu
        startTime = millis();

        // Chạy trong 2 giây (kiểm tra thời gian đã trôi qua)
        while (millis() - startTime < 2000) {
            // Cập nhật trạng thái động cơ trong khi chờ đợi
            motor_update(&motor1);
            motor_update(&motor2);
            motor_update(&motor3);
            motor_update(&motor4);
        }

        motor_run(&motor1, RELEASE);
        motor_run(&motor2, RELEASE);
        motor_run(&motor3, RELEASE);
        motor_run(&motor4, RELEASE);

        // Dừng trong 1 giây (kiểm tra thời gian đã trôi qua)
        startTime = millis();
        while (millis() - startTime < 1000) {
            // Cập nhật trạng thái động cơ trong khi chờ đợi
            motor_update(&motor1);
            motor_update(&motor2);
            motor_update(&motor3);
            motor_update(&motor4);
        }
    }
}
