# 🚒FireFighterBot-RPi
![image](https://github.com/user-attachments/assets/f6bdd30b-2a96-474b-b4fc-489d554d57f5)
## 📌Project Description

This project is an intelligent vehicle used for autonomous inspection, automatically identifying fire sources and sounding alarms. This car uses a Raspberry PI and a flame sensor, and combines obstacle detection and basic alarm mechanisms. The automatic operation of this system can be applied to daily automated inspection tasks.

As a long-term safety challenge facing humanity, the early detection of fire is of irreplaceable significance in industrial, commercial and household Settings.
Traditional fire prevention and control measures such as fire alarms and manual patrols have obvious lags and limitations. Once the source of fire is not detected in the first instance, it is very likely to cause a large-scale fire or even a major safety accident. We have explored a set of intelligent cars that feature "active perception, autonomous judgment and rapid response"

## 💡Project innovation points

1. Use intelligent small vehicles to inspect flames: It reduces human resource consumption to a greater extent and can identify small flames more quickly than traditional flame alarm systems, effectively preventing fires from the source

2. Intelligent path inspection mechanism: By simulating the manual inspection actions through the process of moving forward - turning - reversing - moving forward again, the vehicle can autonomously cover a large area, effectively reducing the dead corner rate

3. Clear priority of control logic: The obstacle avoidance logic has the highest priority to ensure operational safety. Flame detection is only effective when moving forward, saving computing resources

### ✅Software structure module

The system adopts a modular C++ design, and the main functional units are as follows:

1. Flame recognition module: Uses a flame sensor to identify flames;

2. Control logic module: The main logic loop judges the current state and schedules behaviors such as obstacle avoidance and flame detection.

3. Drive module: Based on the GPIO interface, it drives various types of motors, buzzers and other actuating devices;

4. Status management module: Maintain the consistency of system status, including whether it is in forward, obstacle avoidance, fire extinguishing, alarm and other states.

### ✅ Hardware Requirements

#### ultrasonic sensor
![image](https://github.com/user-attachments/assets/72946f33-ee36-4dc1-a404-242dea7bbdf2)
#### CSI camera
![image](https://github.com/user-attachments/assets/37656e9f-9959-49ba-bf83-bb83c6dc51ac)
#### Flame Sensor
![image](https://github.com/user-attachments/assets/262eff8a-5ad0-4b81-ae05-9705f50d4488)
#### Buzzer
![image](https://github.com/user-attachments/assets/6aa6dfd4-c236-4a21-8518-3eddd9596395)

Besides, we connected them together with two TT motors, three servo motors, a battery pack, and a bunch of "beautiful messy" wires!

### ✅ How is works

1. The car is in the default forward state

2. If an obstacle (ultrasonic) is detected → immediately enter the obstacle avoidance process:
Control the turning Angle → reverse → Move forward again, and resume the main process (main function)

3. If a flame is detected (only valid in the forward state) :
Stop moving → Activate the buzzer → The camera takes real-time photos of the scene → Upload the images to the cloud (can be connected to other systems) → Get remote alerts through the photos to avoid false alarms

4. If there is no flame after moving forward for a while:
Active inspection that follows the preset logic to turn + reverse → continue moving forward → form a fan-shaped or spiral area

Obstacle avoidance logic has the highest priority and is only triggered in the forward state, followed by flame detection, and finally regular inspection

## 📂 Project Structure

FireFighterBot-RPi

```bash
├── .vscode/              # VSCode workspace settings
├── build/                # Compiled binaries and build outputs (v1.00)
├── CMakeLists.txt        # CMake build configuration file
├── FlameSensor.cpp       # Logic to read and process flame sensor data
├── FlameSensor.h         # Flame sensor function declarations
├── I2C.cpp               # Implementation for I2C communication
├── I2C.h                 # I2C interface header
├── buzzer.cpp            # Controls the buzzer (for alerts)
├── buzzer.h              # Buzzer control function declarations
├── main.cpp              # Main patrol logic and system control (v1.01)
├── motor.cpp             # DC motor control logic
├── motor.h               # Motor driver header
├── servo.cpp             # Servo motor steering control logic
├── servo.h               # Servo control declarations
├── ultrasonic.cpp        # Ultrasonic sensor handling
├── ultrasonic.h          # Header for ultrasonic distance logic
```

## ▶️ Run

This project uses CMake for building. Please follow the steps below:

Step 1: Go into the build directory 
```bash
cd build 
```
Step 2: Run CMake to generate Makefiles 
```bash
cmake .. 
```
Step 3: Compile the project 
```bash
make 
```
Step 4: Run the executable (requires sudo for GPIO access) 
```bash
sudo ./car 
```
## 🧩 Social Media

Here is our youtubu link and bilibili link, where we documented the process of completing the entire project.
```bash
Youtubu：https://youtu.be/xD0HRMBRjAI

Bilibili：https://www.bilibili.com/video/BV1Do58zdEHr/share_source=copy_web&vd_source=3f262d99275a4ff1f67faab678661e16
```
## 📝 License

MIT License © 2025 FireFighterBot-RPi Project Contributors. See LICENSE for details.

All sensors and actuating devices are universal models for e-commerce platforms, avoiding supply challenges.
Developers are welcome to Fork this project and add custom recognition models, flame level discrimination, or multi-vehicle collaboration logic, etc.
