#ifndef MOTOR_H
#define MOTOR_H

#include "I2C.h"
#include <gpiod.h>

class Motor {
private:
    I2C& i2c;
    gpiod_chip* chip;
    gpiod_line* pin1;
    gpiod_line* pin2;
    uint8_t pwmChannel1, pwmChannel2, pwmChannel3;

public:
    Motor(I2C& i2c_device, int gpio_chip, int p1, int p2, uint8_t ch1, uint8_t ch2, uint8_t ch3);
    ~Motor();
   
    void forward();
    void backward();
    void stop();
    void leftspin();
    void fan();
};

#endif