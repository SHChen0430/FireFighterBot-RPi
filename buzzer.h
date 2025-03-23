#ifndef BUZZER_H
#define BUZZER_H

#include <gpiod.h>
#include <string>

class Buzzer {
public:
    Buzzer(const std::string& chipname = "gpiochip0", unsigned int line_num = 17);
    ~Buzzer();

    void on();      // 打开蜂鸣器
    void off();     // 关闭蜂鸣器
    void beep(int times = 1, int duration_ms = 200, int interval_ms = 200); // 响若干次

private:
    struct gpiod_chip* chip;
    struct gpiod_line* line;
};

#endif // BUZZER_H
