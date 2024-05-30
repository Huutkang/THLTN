#ifndef Motor_h // Kiem tra xem Motor.h da duoc include chua
#define Motor_h // Danh dau Motor.h da duoc include

#include <mega328p.h> // Include file header cho chip ATmega328P

// Dinh nghia cac chan dieu khien dong co (thay doi theo mach cua ban)
#define IN1 8  // Chan IN1 cua driver dong co
#define IN2 9  // Chan IN2 cua driver dong co
#define EN  10 // Chan Enable (PWM) cua driver dong co

// Cac lenh dieu khien dong co
#define FORWARD 1  // Lenh quay thuan
#define BACKWARD 2 // Lenh quay nghich
#define RELEASE 0  // Lenh dung dong co

// Khai bao lop Motor
class Motor {
  public:
    Motor(int motor);             // Ham khoi tao (constructor)
    void setSpeed(int speed);      // Ham dat toc do dong co
    void run(int cmd);           // Ham yeu cau dong co thuc hien lenh
    void update();              // Ham cap nhat trang thai dong co

  private:
    int _motorPin;               // Chan dieu khien dong co
    unsigned long _previousMillis; // Thoi gian truoc do (luu lai de tinh toan thoi gian)
    int _interval;                // Khoang thoi gian giua cac lan chuyen trang thai
    int _currentCmd;              // Lenh hien tai dang duoc thuc hien
};

#endif
