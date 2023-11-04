//
// Created by promise on 10/31/23.
//
#include "include/serial.hpp"
serial Serial;
aimMsg msg1 = {1,1};
carMsg msg2 = {1,false,0,0,20};

int main(){
    Serial.open("/dev/ttyUSB0");
    Serial.sendThread();
    Serial.reciveThread();
    while(true){
        Serial.update(&msg1,&msg2);
    }
}
