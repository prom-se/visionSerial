//
// Created by promise on 10/31/23.
//

#include "../include/serial.hpp"
#include <string.h>

visionSerial::visionSerial(const char* devName, const int baudRate){
    ser.init(devName,baudRate);
    ser.open();
    // ser.setReadIntervalTimeout(5);
}

[[noreturn]] void visionSerial::send(){
    while(true){
        // usleep(5000);
        ser.writeData(visionArray_.array,sizeof(visionArray));
    }
}

[[noreturn]] void visionSerial::receive(){
    while(true){
        // usleep(5000);
        uint8_t array[sizeof(robotArray)];
        ser.readData(array,sizeof(robotArray));
        if(array[0]==0xa5 && array[1]==0x00){
            memcpy(robotArray_.array,array,sizeof(robotArray));
        }
    }
}