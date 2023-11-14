cmake_minimum_required(VERSION 3.16)
project(serial_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
find_package(CSerialPort)
include_directories(${CSerialPort_INCLUDE_DIR})
add_executable(serial_test
        src/demo.cpp
        src/serial.cpp
        include/serial.hpp
        include/packet.h)
target_link_libraries(serial_test ${CSerialPort_LIBRARY})
