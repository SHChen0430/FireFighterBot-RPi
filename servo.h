#ifndef SERVO_H
#define SERVO_H

#include "I2C.h"

#define MIN_PW      500   // 0度对应的最小脉宽（微秒）
#define MAX_PW      2500  // 180度对应的最大脉宽（微秒）
#define PWM_PERIOD  20000 // 20ms周期对应50Hz频率

class Servo {
public:
    Servo(I2C& i2c, int ch);
    void setAngle(float angle);

private:
    I2C& i2c;
    int channel;

    void setFrequency(int freq);
    void setDutyCycle(int channel, float duty_cycle);
    float mapAngleToPulseWidth(float angle);
    float pulseWidthToDutyCycle(float pulse_width);
};

#endif // SERVO_H
