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

void Buzzer::beep(int times, int duration_ms, int interval_ms) {
    for (int i = 0; i < times; ++i) {
        on();
        usleep(duration_ms * 1000);
        off();
        usleep(interval_ms * 1000);
    }
}
