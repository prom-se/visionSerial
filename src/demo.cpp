#include "../include/serial.hpp"
#include <iostream>
visionSerial Serial("/dev/ttyUSB0",115200);
visionMsg msg1 = {1,1};
robotMsg msg2 = {1,false,0,0,20};

int main(){
    while(true){
        usleep(10000);
        Serial.visionUpdate(msg1);     // 更新自瞄数据
        Serial.robotUpdate(msg2);      // 获得机器人数据
    }
}
