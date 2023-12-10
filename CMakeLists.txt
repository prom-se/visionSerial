cmake_minimum_required(VERSION 3.5)
project(visionSerial)
set(CMAKE_CXX_STANDARD 11)
include_directories(.)
find_package(CSerialPort)
include_directories(${CSerialPort_INCLUDE_DIR})

add_executable(visionSerial
        src/demo.cpp
        src/serial.cpp
        include/serial.hpp
        include/packet.h)

target_link_libraries(visionSerial ${CSerialPort_LIBRARY} -pthread)
