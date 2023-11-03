cmake_minimum_required(VERSION 3.16)
project(serial_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(serial_test
        src/main.cpp
        src/serial.cpp
        include/serial.hpp
        include/packet.hpp)
target_link_libraries(serial_test -lserialport)
