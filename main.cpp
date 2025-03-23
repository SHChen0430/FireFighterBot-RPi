#include "I2C.h"
#include "motor.h"
#include "servo.h"
#include "FlameSensor.h"
#include "ultrasonic.h"
#include "buzzer.h"

#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>

int flag=0;

// Global flag set by background thread
std::atomic<bool> obstacleDetected(false);

// Monitor obstacle distance in the background
void monitorObstacle(Ultrasonic& ultrasonic) {
    while (true) {
        double dist = ultrasonic.read();
        if (dist != -1 && dist < 10) {
            obstacleDetected = true;
        }
        usleep(100000); // Check every 100ms
    }
}

// Slight obstacle avoidance behavior
void avoidObstacle(Buzzer& buzzer,Motor& motor, Servo& car) {
    std::cout << "🚧 遇到障碍物：开始规避" << std::endl;
    buzzer.on();
    // Stop and steer right slightly
    motor.stop();
    usleep(200000);
    buzzer.off();
    car.setAngle(35);         // Turn wheels to the right
    usleep(300000);
    buzzer.on();
    motor.backward();         // Move backward briefly
    sleep(1);
    motor.stop();
    buzzer.off();
    usleep(200000);
    car.setAngle(5);          // Recenter steering
    std::cout << "✅ 规避完成，继续搜索" << std::endl;
}

// Move forward with frequent obstacle check
void safeForward(Buzzer& buzzer,FlameSensor& sensor,Motor& motor, Servo& car, int durationMs) {
    int stepMs = 100;
    motor.forward();

    for (int elapsed = 0; elapsed < durationMs; elapsed += stepMs) {
        bool flame = sensor.detectFlame();
        if (obstacleDetected) {
            motor.stop();
            avoidObstacle(buzzer, motor, car);
            obstacleDetected = false;
            motor.forward();
        }else if(flame){
            std::cout << "🔥 检测到火焰!" << std::endl;

            motor.stop();
            usleep(500000);

            car.setAngle(5);
            usleep(500000);

            flag=1;
        }else if(!flame){
            flag=0;
            buzzer.off();
        }
        usleep(stepMs * 1000);
        

        if(flag==1){
            buzzer.on();
        }
    }

    motor.stop();
}

int main() {
    I2C i2c("/dev/i2c-1", 0x14);
    Motor motor(i2c, 0, 23, 24, 13, 12);
    FlameSensor sensor("gpiochip0", 4);
    Ultrasonic ultrasonic("gpiochip0", 27, 22);
    Buzzer buzzer;

    Servo Car(i2c, 2);
    Servo CameraH(i2c, 0);
    Servo CameraV(i2c, 1);


    // Start background thread for obstacle detection
    std::thread obstacleThread(monitorObstacle, std::ref(ultrasonic));

    buzzer.off();

    while (true) {
        
            std::cout << "🌀 未检测到火焰，继续搜索..." << std::endl;

            // Move forward with obstacle interrupt handling
            safeForward(buzzer, sensor, motor, Car, 3000);

            // Scan area a bit
            Car.setAngle(35);
            usleep(500000);
            motor.backward();
            sleep(1);
            motor.stop();
            Car.setAngle(5);
    }

    // Clean up thread
    if (obstacleThread.joinable()) {
        obstacleThread.detach(); // Let it run in background
    }

    return 0;
}
