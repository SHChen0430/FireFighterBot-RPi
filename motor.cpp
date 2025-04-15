#include "motor.h"
#include <iostream>
#include <unistd.h>  // for usleep

Motor::Motor(I2C& i2c_device, int gpio_chip, int p1, int p2, uint8_t ch1, uint8_t ch2, uint8_t ch3)
    : i2c(i2c_device), pwmChannel1(ch1), pwmChannel2(ch2), pwmChannel3(ch3) {
   
    chip = gpiod_chip_open_by_number(gpio_chip);
    if (!chip) {
        perror("❌ 无法打开 GPIO 芯片");
        exit(1);
    }

    pin1 = gpiod_chip_get_line(chip, p1);
    pin2 = gpiod_chip_get_line(chip, p2);

    if (!pin1 || !pin2) {
        perror("❌ 无法获取 GPIO 线路");
        exit(1);
    }

    if (gpiod_line_request_output(pin1, "motor_control", 0) < 0 ||
        gpiod_line_request_output(pin2, "motor_control", 0) < 0) {
        perror("❌ 无法请求 GPIO 线路");
        exit(1);
    }
}

Motor::~Motor() {
    gpiod_line_release(pin1);
    gpiod_line_release(pin2);
    gpiod_chip_close(chip);
}

void Motor::forward() {
    gpiod_line_set_value(pin1, 0);
    usleep(100000);  // 100ms
    gpiod_line_set_value(pin2, 1);

    i2c.writeRegister(0x40, 50);  // 设置 PWM 频率 50Hz
    i2c.writeRegister(0x20 + pwmChannel1, 600);
    i2c.writeRegister(0x20 + pwmChannel2, 600);
}

void Motor::backward() {
    gpiod_line_set_value(pin1, 1);
    usleep(100000);
    gpiod_line_set_value(pin2, 0);

    i2c.writeRegister(0x40, 50);
    i2c.writeRegister(0x20 + pwmChannel1, 800);
    i2c.writeRegister(0x20 + pwmChannel2, 800);
}

void Motor::stop() {
    gpiod_line_set_value(pin1, 0);
    usleep(100000);
    gpiod_line_set_value(pin2, 1);

    i2c.writeRegister(0x40, 50);
    i2c.writeRegister(0x20 + pwmChannel1, 0);
    i2c.writeRegister(0x20 + pwmChannel2, 0);
}

void Motor::leftspin() {
    gpiod_line_set_value(pin1, 1);
    usleep(100000);
    gpiod_line_set_value(pin2, 1);

    i2c.writeRegister(0x40, 50);
    i2c.writeRegister(0x20 + pwmChannel1, 1500);
    i2c.writeRegister(0x20 + pwmChannel2, 1500);
}

void Motor::fan() {
    i2c.writeRegister(0x40, 1000);
    i2c.writeRegister(0x20 + pwmChannel3, 1500);
}