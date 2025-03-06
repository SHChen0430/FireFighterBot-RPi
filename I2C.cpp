#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <wiringPi.h>

#define I2C_DEV "/dev/i2c-1"  // 树莓派 5 I2C 设备
#define I2C_ADDR 0x14  // AT32F413 I2C 地址

#define PWM_FREQ_REG  0x40  // PWM 频率
#define PWM_CH0_REG   0x20  // PWM 通道 0

int i2c_fd;  // I2C 设备文件描述符

// **初始化 I2C 设备**
void i2c_init() {
    if ((i2c_fd = open(I2C_DEV, O_RDWR)) < 0) {
        perror("❌ 无法打开 I2C 设备");
        exit(1);
    }
    if (ioctl(i2c_fd, I2C_SLAVE, I2C_ADDR) < 0) {
        perror("❌ 无法连接 I2C 设备");
        exit(1);
    }
    printf("✅ I2C 设备 %s 已连接\n", I2C_DEV);
}

// **I2C 写入 16-bit 数据**
void i2c_write(uint8_t reg, uint16_t value) {
    uint8_t buffer[3];
    buffer[0] = reg;                // 设备寄存器地址
    buffer[1] = (value >> 8) & 0xFF; // 高字节
    buffer[2] = value & 0xFF;        // 低字节

    if (write(i2c_fd, buffer, 3) != 3) {
        perror("❌ I2C 写入失败");
        exit(1);
    }
    printf("✅ I2C 写入：寄存器 0x%02X = 0x%04X\n", reg, value);
}

// **I2C 读取 16-bit 数据**
uint16_t i2c_read(uint8_t reg) {
    uint8_t buffer[2];

    // **设置要读取的寄存器**
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("❌ I2C 设置读取地址失败");
        exit(1);
    }

    // **读取 2 字节数据**
    if (read(i2c_fd, buffer, 2) != 2) {
        perror("❌ I2C 读取失败");
        exit(1);
    }

    uint16_t value = (buffer[0] << 8) | buffer[1];
    printf("✅ I2C 读取：寄存器 0x%02X = 0x%04X\n", reg, value);
    return value;
}

// **设置 PWM 频率**
void set_pwm_freq(uint16_t freq) {
    printf("📢 设置 PWM 频率: %d Hz\n", freq);
    i2c_write(PWM_FREQ_REG, freq);
}

// **设置 PWM 占空比**
void set_pwm_duty(uint8_t channel, uint16_t pulse_width) {
    printf("📢 设置 PWM 通道 %d: %d µs\n", channel, pulse_width);
    i2c_write(PWM_CH0_REG + channel, pulse_width);
}
