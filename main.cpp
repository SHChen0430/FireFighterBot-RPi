#include"I2C.h"
#include"motor.h"
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
    
    car_forward();
    delay(1000);
    car_stop();
    delay(3000);
    car_back();
    delay(1000);
    car_stop();

    return 0;
}