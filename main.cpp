#include"I2C.h"
#include"motor.h"
#include"servo.h"
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <wiringPi.h>

int main() {
    i2c_init();
    wiringPiSetupGpio();
    
    Servo myServo(0);  // 创建通道 0 的舵机对象

    myServo.setAngle(0);   // 设置为 0°
    sleep(1);
    
    myServo.setAngle(-20); // 设置为 -20°
    sleep(1);
    
    myServo.setAngle(20);  // 设置为 20°
    sleep(1);

    return 0;

    /*
    car_forward();
    delay(1000);
    car_stop();
    delay(3000);
    car_back();
    delay(1000);
    car_stop();
    */

    return 0;
}