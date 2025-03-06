cmake_minimum_required(VERSION 3.10)
project(FireFighterCar)

# Set C standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED Ture)

# Add the executable
add_executable(car main.cpp I2C.cpp motor.cpp servo.cpp) 

# Link with i2c library if needed
target_link_libraries(car wiringPi)
