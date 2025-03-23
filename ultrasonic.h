#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <gpiod.h>
#include <string>

class Ultrasonic {
public:
    Ultrasonic(const std::string& chipname, int trig_line, int echo_line, double timeout = 0.02);
    ~Ultrasonic();
    double read(int times = 10);

private:
    double _read();

    gpiod_chip* chip;
    gpiod_line* trig;
    gpiod_line* echo;

    int trig_line_num;
    int echo_line_num;
    double timeout; // 秒
    const double SOUND_SPEED = 343.3; // m/s
};

#endif
