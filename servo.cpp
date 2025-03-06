#include "servo.h"
#include <iostream>

// 构造函数
Servo::Servo(int ch) : channel(ch) {
    setFrequency(50); // 舵机通常使用 50Hz 频率
}

// 角度映射到脉宽
float Servo::mapAngleToPulseWidth(float angle) {
    if (angle < -90) angle = -90;
    if (angle > 90) angle = 90;
    return (angle + 90) * (MAX_PW - MIN_PW) / 180.0f + MIN_PW;
}

// 脉宽映射到占空比
float Servo::pulseWidthToDutyCycle(float pulse_width) {
    return pulse_width / PWM_PERIOD; // 计算占空比
}

// 设置舵机角度
void Servo::setAngle(float angle) {
    float pulse_width = mapAngleToPulseWidth(angle);
    float duty_cycle = pulseWidthToDutyCycle(pulse_width);
    
    // 调用 I2C 控制的 PWM 代码
    setDutyCycle(channel, duty_cycle);
    
    // 打印调试信息
    std::cout << "✅ Servo 通道 " << channel
              << " 设置角度: " << angle
              << "°, 脉宽: " << pulse_width
              << "us, 占空比: " << duty_cycle * 100 << "%" << std::endl;
}

void Servo::setFrequency(int freq) {
    std::cout << "📢 设置 PWM 频率: " << freq << " Hz" << std::endl;
    set_pwm_freq(freq);  // 调用 I2C 函数设置 PWM 频率
}

void Servo::setDutyCycle(int channel, float duty_cycle) {
    uint16_t pulse_width = static_cast<uint16_t>(duty_cycle * 20000); // 50Hz -> 20ms
    std::cout << "📢 设置通道 " << channel << " 占空比: " << duty_cycle * 100 << "% (" << pulse_width << "us)" << std::endl;
    set_pwm_duty(channel, pulse_width);  // 调用 I2C 发送数据
}
