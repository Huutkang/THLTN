#define DCMotor_H

#include <mega328p.h>

class DCMotor {
  private:
    uint8_t pinA;
    uint8_t pinB;
    uint8_t pinS;
  
  public:
    // Constructor
    DCMotor(uint8_t pinA, uint8_t pinB, uint8_t pinS);

    // Bat dong co voi toc do xac dinh.
    void on(uint8_t speed);

    // Bat dong co voi toc do xac dinh, trong mot thoi gian nhat dinh.
    void on(uint8_t speed, int millisec);

    // Turn the motor off.
    void off();
};

