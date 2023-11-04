//
// Created by promise on 10/31/23.
//

#ifndef SERIAL_TEST_SERIAL_HPP
#define SERIAL_TEST_SERIAL_HPP
#include <libserialport.h>
#include <thread>
#include <string>
#include <cstring>
#include <vector>
#include "include/packet.hpp"

class serial {
private:
    sp_port *serialPort={};
    aimMsg *sendMsg   = new aimMsg;
    carMsg *receiveMsg = new carMsg;

    [[noreturn]] void send();
    [[noreturn]] void recive();

public:
    void open(const std::string &devName);
    inline void update(void *aim_msg,void *car_msg){
        memcpy(sendMsg,aim_msg,sizeof(aimMsg));
        memcpy(car_msg,receiveMsg,sizeof(carMsg));
    }
    void sendThread(){
        std::thread send_thread(&serial::send,std::ref(*this));
        send_thread.detach();
    }
    void reciveThread(){
        std::thread recive_thread(&serial::recive,std::ref(*this));
        recive_thread.detach();
    }
};


#endif //SERIAL_TEST_SERIAL_HPP
