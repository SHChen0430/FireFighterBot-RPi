#ifndef I2C_H
#define I2C_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <wiringPi.h>

void i2c_init();
void i2c_write(uint8_t, uint16_t value);
uint16_t i2c_read(uint8_t reg);
void set_pwm_freq(uint16_t freq);
void set_pwm_duty(uint8_t channel, uint16_t pulse_width);


#endif