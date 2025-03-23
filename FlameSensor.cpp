#include "FlameSensor.h"
#include <iostream>

// 构造函数：打开 GPIO 芯片并请求引脚作为输入
FlameSensor::FlameSensor(const std::string& chipName, unsigned int lineOffset) {
    chip = gpiod_chip_open_by_name(chipName.c_str());
    if (!chip) {
        std::cerr << "Failed to open GPIO chip: " << chipName << std::endl;
        std::exit(EXIT_FAILURE);
    }

    line = gpiod_chip_get_line(chip, lineOffset);
    if (!line) {
        std::cerr << "Failed to get GPIO line: " << lineOffset << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (gpiod_line_request_input(line, "flame-sensor") < 0) {
        std::cerr << "Failed to request GPIO line as input." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// 析构函数：释放 GPIO 资源
FlameSensor::~FlameSensor() {
    if (line) {
        gpiod_line_release(line);
    }
    if (chip) {
        gpiod_chip_close(chip);
    }
}

// 读取传感器状态（低电平表示检测到火焰）
bool FlameSensor::detectFlame() {
    int value = gpiod_line_get_value(line);
    if (value < 0) {
        std::cerr << "Failed to read GPIO value." << std::endl;
        return false;
    }
    return value == 0; // LOW = flame detected
}