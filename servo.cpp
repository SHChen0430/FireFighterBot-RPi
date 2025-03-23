#include "servo.h"
#include <iostream>

Servo::Servo(I2C& i2c, int ch) : i2c(i2c), channel(ch) {
    setFrequency(50); // 舵机频率通常为 50Hz
}

void Servo::setAngle(float angle) {
    float pulse_width = mapAngleToPulseWidth(angle);
    float duty_cycle = pulseWidthToDutyCycle(pulse_width);

    setDutyCycle(channel, duty_cycle);

    //std::cout << "✅ Servo 通道 " << channel
    //          << " 设置角度: " << angle
    //          << "°, 脉宽: " << pulse_width
    //          << "us, 占空比: " << duty_cycle * 100 << "%" << std::endl;
}

void Servo::setFrequency(int freq) {
    //std::cout << "📢 设置 PWM 频率: " << freq << " Hz" << std::endl;
    set_pwm_freq(i2c, freq);
}

void Servo::setDutyCycle(int channel, float duty_cycle) {
    uint16_t pulse_width = static_cast<uint16_t>(duty_cycle * PWM_PERIOD);
    //std::cout << "📢 设置通道 " << channel << " 占空比: " << duty_cycle * 100 << "% (" << pulse_width << "us)" << std::endl;
    set_pwm_duty(i2c, channel, pulse_width);
}

float Servo::mapAngleToPulseWidth(float angle) {
    if (angle < -90) angle = -90;
    if (angle > 90)  angle = 90;
    return (angle + 90) * (MAX_PW - MIN_PW) / 180.0f + MIN_PW;
}

float Servo::pulseWidthToDutyCycle(float pulse_width) {
    return pulse_width / PWM_PERIOD;
}
