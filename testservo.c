#include "servo.h"
#include <delay.h>

void main(void)
{
    // Khởi tạo servo trên chân PD5
    servo_init(&PORTD, 5); 

    while (1)
    {
        // Di chuyển servo qua lại giữa 0 và 180 độ
        for (unsigned char angle = 0; angle <= 180; angle++)
        {
            servo_set_angle(angle);
            servo_update();
            delay_ms(15); // Điều chỉnh độ trễ để thay đổi tốc độ quay
        }

        for (unsigned char angle = 180; angle > 0; angle--)
        {
            servo_set_angle(angle);
            servo_update();
            delay_ms(15);
        }
    }
}
