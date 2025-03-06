#ifndef SERVO_H
#define SERVO_H

#include"I2C.h"

class Servo {
private:
    int channel;
    static constexpr float MIN_PW = 500.0f;  // 500us 对应 -90°
    static constexpr float MAX_PW = 2500.0f; // 2500us 对应  90°
    static constexpr float PWM_PERIOD = 20000.0f; // 50Hz -> 20ms (20000us)

    float mapAngleToPulseWidth(float angle);
    float pulseWidthToDutyCycle(float pulse_width);

public:
    Servo(int ch);
    void setAngle(float angle);

    void setFrequency(int freq);  // 设置 PWM 频率
    void setDutyCycle(int channel, float duty_cycle);  // 设置 PWM 占空比
};

#endif // SERVO_H
