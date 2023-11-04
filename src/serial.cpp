//
// Created by promise on 10/31/23.
//

#include "include/serial.hpp"

void serial::open(const std::string &devName) {
    sp_return portStatus;
    do{ sp_get_port_by_name(devName.c_str(), &serialPort);
        sp_open(serialPort, SP_MODE_READ_WRITE);
        sp_set_parity(serialPort, SP_PARITY_NONE);
        sp_set_baudrate(serialPort, 115200);
        sp_set_stopbits(serialPort, 1);
        sp_set_flowcontrol(serialPort,SP_FLOWCONTROL_NONE);
        portStatus = sp_set_bits(serialPort, 8);
    }while(portStatus!=SP_OK);
}


[[noreturn]] void serial::send() {
    while (true) {
        std::vector<uint8_t> sendVec = toVector(*sendMsg);
        sp_blocking_write(serialPort,sendVec.data(),sendVec.size(),50);
    }
}

#include <iostream>

[[noreturn]] void serial::recive() {
    while(true){
        std::vector<uint8_t> receiveVec;
        uint8_t head;
        receiveVec.resize(sizeof(carMsg)+1);
        sp_blocking_read(serialPort,&head,1,10);
        if(head==0xA5){
            sp_blocking_read(serialPort,receiveVec.data(),sizeof(carMsg)+1,10);
            if(receiveVec[16]==0x5A){
                receiveVec.resize(sizeof(carMsg)+2);
                receiveVec.emplace(receiveVec.begin(),head);
                *receiveMsg = fromVector(receiveVec);
            }
        }
    }
}
