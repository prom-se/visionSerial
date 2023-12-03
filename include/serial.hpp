//
// Created by promise on 10/31/23.
//

#ifndef SERIAL_TEST_SERIAL_HPP
#define SERIAL_TEST_SERIAL_HPP
#include <thread>
#include <vector>
#include <unistd.h>
#include <CSerialPort/SerialPort.h>
#include "../include/packet.h"
using namespace itas109;
class visionSerial {
private:
    CSerialPort ser;
    [[noreturn]] void send();
    [[noreturn]] void receive();
    visionArray visionArray_;
    robotArray robotArray_;
public:
    visionSerial(const char* devName,const int baudRate);
    inline void visionUpdate(visionMsg *vision){
        visionArray_.msg=*vision;
    }
    inline void robotUpdate(robotMsg *robot){
        *robot=robotArray_.msg;
    }

    void sendThread(){
        std::thread send_thread(&visionSerial::send,std::ref(*this));
        send_thread.detach();
    }

    void reciveThread(){
        std::thread recive_thread(&visionSerial::receive,std::ref(*this));
        recive_thread.detach();
    }
};


#endif //SERIAL_TEST_SERIAL_HPP
