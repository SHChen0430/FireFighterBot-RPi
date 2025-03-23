#include "ultrasonic.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono;

Ultrasonic::Ultrasonic(const std::string& chipname, int trig_line, int echo_line, double timeout)
    : trig_line_num(trig_line), echo_line_num(echo_line), timeout(timeout)
{
    chip = gpiod_chip_open_by_name(chipname.c_str());
    if (!chip) throw std::runtime_error("无法打开 GPIO 芯片");

    trig = gpiod_chip_get_line(chip, trig_line_num);
    echo = gpiod_chip_get_line(chip, echo_line_num);

    if (!trig || !echo) throw std::runtime_error("无法获取 GPIO 引脚");

    if (gpiod_line_request_output(trig, "ultrasonic-trig", 0) < 0)
        throw std::runtime_error("无法设置 TRIG 为输出");

    if (gpiod_line_request_input(echo, "ultrasonic-echo") < 0)
        throw std::runtime_error("无法设置 ECHO 为输入");

    gpiod_line_set_value(trig, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

Ultrasonic::~Ultrasonic() {
    if (trig) gpiod_line_release(trig);
    if (echo) gpiod_line_release(echo);
    if (chip) gpiod_chip_close(chip);
}

double Ultrasonic::_read() {
    gpiod_line_set_value(trig, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    gpiod_line_set_value(trig, 1);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    gpiod_line_set_value(trig, 0);

    auto timeout_start = steady_clock::now();

    // 等待 ECHO 为高
    while (gpiod_line_get_value(echo) == 0) {
        if (duration<double>(steady_clock::now() - timeout_start).count() > timeout)
            return -1;
    }
    auto pulse_start = steady_clock::now();

    // 等待 ECHO 为低
    while (gpiod_line_get_value(echo) == 1) {
        if (duration<double>(steady_clock::now() - timeout_start).count() > timeout)
            return -1;
    }
    auto pulse_end = steady_clock::now();

    double duration_s = duration<double>(pulse_end - pulse_start).count();
    return duration_s * SOUND_SPEED / 2.0 * 100.0;
}

double Ultrasonic::read(int times) {
    for (int i = 0; i < times; ++i) {
        double d = _read();
        if (d != -1)
            return d;
    }
    return -1;
}
