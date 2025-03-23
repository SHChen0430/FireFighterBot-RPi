#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <cstdio>
#include <cstdlib>

class I2C {
public:
    I2C(const char* dev, uint8_t addr);
    ~I2C();

    void writeRegister(uint8_t reg, uint16_t value);
    uint16_t readRegister(uint8_t reg);

private:
    const char* device;
    uint8_t address;
    int i2c_fd;
};

// Constants for PWM control
#define PWM_FREQ_REG 0x40
#define PWM_CH0_REG  0x20

// Helper functions
void set_pwm_freq(I2C& i2c, uint16_t freq);
void set_pwm_duty(I2C& i2c, uint8_t channel, uint16_t pulse_width);

#endif // I2C_H
