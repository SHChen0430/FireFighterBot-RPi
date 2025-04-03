#include "buzzer.h"
#include <iostream>
#include <unistd.h>  // usleep

Buzzer::Buzzer(const std::string& chipname, unsigned int line_num) {
    chip = gpiod_chip_open_by_name(chipname.c_str());
    if (!chip) {
        std::cerr << "Failed to open GPIO chip\n";
        throw std::runtime_error("Failed to open GPIO chip");
    }

    line = gpiod_chip_get_line(chip, line_num);
    if (!line) {
        gpiod_chip_close(chip);
        std::cerr << "Failed to get GPIO line\n";
        throw std::runtime_error("Failed to get GPIO line");
    }

    if (gpiod_line_request_output(line, "buzzer", 0) < 0) {
        gpiod_chip_close(chip);
        std::cerr << "Failed to set line as output\n";
        throw std::runtime_error("Failed to request line as output");
    }
}

Buzzer::~Buzzer() {
    gpiod_line_release(line);
    gpiod_chip_close(chip);
}

void Buzzer::on() {
    gpiod_line_set_value(line, 1);
}

void Buzzer::off() {
    gpiod_line_set_value(line, 0);
}

void Buzzer::beep(int times, int duration_ms, int interval_ms, int freq_hz) {
    int period_us = 1000000 / freq_hz;         // 周期，例如 1000Hz = 1000us
    int half_period_us = period_us / 2;
    int cycles = (duration_ms * 1000) / period_us;

    for (int t = 0; t < times; ++t) {
        for (int i = 0; i < cycles; ++i) {
            gpiod_line_set_value(line, 1);
            usleep(half_period_us);
            gpiod_line_set_value(line, 0);
            usleep(half_period_us);
        }
        usleep(interval_ms * 1000);
    }
}
