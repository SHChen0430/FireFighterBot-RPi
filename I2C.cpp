#include "I2C.h"

I2C::I2C(const char* dev, uint8_t addr) : device(dev), address(addr) {
    if ((i2c_fd = open(device, O_RDWR)) < 0) {
        perror("❌ 无法打开 I2C 设备");
        exit(1);
    }
    if (ioctl(i2c_fd, I2C_SLAVE, address) < 0) {
        perror("❌ 无法连接 I2C 设备");
        exit(1);
    }
    printf("✅ I2C 设备 %s 已连接\n", device);
}

I2C::~I2C() {
    close(i2c_fd);
}

void I2C::writeRegister(uint8_t reg, uint16_t value) {
    uint8_t buffer[3] = { reg, static_cast<uint8_t>(value >> 8), static_cast<uint8_t>(value & 0xFF) };

    if (write(i2c_fd, buffer, 3) != 3) {
        perror("❌ I2C 写入失败");
        exit(1);
    }
    //printf("✅ I2C 写入：寄存器 0x%02X = 0x%04X\n", reg, value);
}

uint16_t I2C::readRegister(uint8_t reg) {
    uint8_t buffer[2];

    if (write(i2c_fd, &reg, 1) != 1) {
        perror("❌ I2C 设置读取地址失败");
        exit(1);
    }

    if (read(i2c_fd, buffer, 2) != 2) {
        perror("❌ I2C 读取失败");
        exit(1);
    }

    uint16_t value = (buffer[0] << 8) | buffer[1];
    printf("✅ I2C 读取：寄存器 0x%02X = 0x%04X\n", reg, value);
    return value;
}

void set_pwm_freq(I2C& i2c, uint16_t freq){
    //printf("设置PWM频率: %d Hz\n", freq);
    i2c.writeRegister(PWM_FREQ_REG, freq);
}

void set_pwm_duty(I2C& i2c, uint8_t channel, uint16_t pulse_width){
    //printf("设置PWM通道 %d: %dus\n", channel, pulse_width);
    i2c.writeRegister(PWM_CH0_REG + channel, pulse_width);
}
