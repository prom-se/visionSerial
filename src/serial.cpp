//
// Created by promise on 10/31/23.
//

#include "../include/serial.hpp"
visionSerial::visionSerial(const char* devName, const int baudRate){
    ser.init(devName,baudRate);
    ser.open();
    // ser.setReadIntervalTimeout(5);
}

[[noreturn]] void visionSerial::send(){
    uint8_t head=0xA5;
    while(true){
        // usleep(5000);
        ser.writeData(&head,1);
        ser.writeData(visionArray_.array,sizeof(visionArray));
    }
}

[[noreturn]] void visionSerial::receive(){
    uint8_t head;
    while(true){
        // usleep(5000);
        head=0x00;
        ser.readData(&head,1);
        if(head==0xA5) ser.readData(robotArray_.array,sizeof(robotArray));
    }
}