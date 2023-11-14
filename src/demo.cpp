//
// Created by promise on 10/31/23.
//
#include "include/serial.hpp"
#include <iostream>
serial Serial("/dev/ttyUSB0");
visionMsg msg1 = {1,1};
carMsg msg2 = {1,false,0,0,20};

int main(){
    Serial.sendThread();
    Serial.reciveThread();
    while(true){
        Serial.update(&msg1,&msg2);
        std::cout << msg2.carPitch << "\n";
    }
}
