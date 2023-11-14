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
#include <CSerialPort/SerialPort.h>
#include "include/packet.h"
using namespace itas109;
class serial {
private:
    CSerialPort ser;
    [[noreturn]] void send();
    [[noreturn]] void receive();
    visionArray visionArray_;
    carArray carArray_;
public:
    serial(const char* devName);
    inline void update(visionMsg *vision,carMsg *car){
        visionArray_.msg=*vision;
        *car=carArray_.msg;
    }

    void sendThread(){
        std::thread send_thread(&serial::send,std::ref(*this));
        send_thread.detach();
    }

    void reciveThread(){
        std::thread recive_thread(&serial::receive,std::ref(*this));
        recive_thread.detach();
    }
};


#endif //SERIAL_TEST_SERIAL_HPP
