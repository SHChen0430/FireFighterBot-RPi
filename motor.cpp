#include"I2C.h"

void car_forward(){
    pinMode(23,OUTPUT);//
    pinMode(24,OUTPUT);//

    digitalWrite(23,LOW);
    delay(100);
    digitalWrite(24,HIGH);

    set_pwm_freq(50);  // **设置 PWM 频率 50Hz**
    set_pwm_duty(13, 1500);  // **设置通道 0 占空比 1500µs**
    set_pwm_duty(12, 1500);  // **设置通道 1 占空比 1500µs**
}

void car_back(){
    pinMode(23,OUTPUT);//
    pinMode(24,OUTPUT);//

    digitalWrite(23,HIGH);
    delay(100);
    digitalWrite(24,LOW);

    set_pwm_freq(50);  // **设置 PWM 频率 50Hz**
    set_pwm_duty(13, 1500);  // **设置通道 0 占空比 1500µs**
    set_pwm_duty(12, 1500);  // **设置通道 1 占空比 1500µs**
}

void car_stop(){
    pinMode(23,OUTPUT);//
    pinMode(24,OUTPUT);//

    digitalWrite(23,LOW);
    delay(100);
    digitalWrite(24,HIGH);

    set_pwm_freq(50);  // **设置 PWM 频率 50Hz**
    set_pwm_duty(13, 0);  // **设置通道 0 占空比 1500µs**
    set_pwm_duty(12, 0);  // **设置通道 1 占空比 1500µs**
}