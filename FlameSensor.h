#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include <gpiod.h>
#include <string>

class FlameSensor {
public:
    // 构造函数，初始化火焰传感器引脚
    FlameSensor(const std::string& chipName, unsigned int lineOffset);

    // 析构函数，释放资源
    ~FlameSensor();

    // 读取传感器状态，返回true表示检测到火焰
    bool detectFlame();

private:
    gpiod_chip* chip;       // GPIO芯片
    gpiod_line* line;       // GPIO引脚
};

#endif // FLAME_SENSOR_H
