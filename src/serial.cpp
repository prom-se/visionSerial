//
// Created by promise on 10/31/23.
//

#include "include/serial.hpp"

serial::serial(const char* devName){
    ser.init(devName,115200);
    ser.open();
}

[[noreturn]] void serial::send(){
    uint8_t head=0xA5;
    while(true){
        ser.writeData(&head,1);
        ser.writeData(visionArray_.array,sizeof(visionArray));
    }
}

[[noreturn]] void serial::receive(){
    uint8_t head;
    while(true){
        head=0x00;
        ser.readData(&head,1);
        if(head==0xA5) ser.readData(carArray_.array,sizeof(carArray));
    }
}