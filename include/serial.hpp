#ifndef VISION_SERIAL_HPP
#define VISION_SERIAL_HPP

#include <thread>
#include <vector>
#include <memory>
#include <unistd.h>
#include <CSerialPort/SerialPort.h>
#include "../include/packet.h"
#include <string.h>

using namespace itas109;

/*
@brief 视觉串口通信类,实例化后使用visionUpdate传入自瞄信息;使用robotUpdate接收机器人信息。
*/
class visionSerial {
public:
    /*
    @brief 构造函数，设置串口设备名称和波特率
    @param devName_ 串口设备名称
    @param baudRate_ 波特率
    */
    explicit visionSerial(const char* devName_, const int baudRate_)
    :isOk{false},devName{devName_},baudRate{baudRate_},ser{new CSerialPort(devName_)}
    {
        watchDogThred=std::thread(&visionSerial::watchDogThredFun,std::ref(*this));
        // ser.setReadIntervalTimeout(5);
        sendThread=std::thread(&visionSerial::sendThreadFun,std::ref(*this));
        reciveThread=std::thread(&visionSerial::receiveThreadFun,std::ref(*this));
    };

    /*
    @brief 析构函数,用来结束线程和关闭串口。
    */
    ~visionSerial(){
        reciveThread.detach();
        sendThread.detach();
        watchDogThred.detach();
        isOk=false;
        if(ser->isOpen()){
            ser->close();
        }
    };

    /*
    @brief 更新发送的视觉信息
    @param vision 视觉信息结构体
    */
    inline void visionUpdate(visionMsg &vision){
        vision.head=0xa5;
        visionArray_.msg=vision;
    };

    /*
    @brief 获得接收的机器人信息
    @param robot 机器人信息结构体
    */
    inline void robotUpdate(robotMsg &robot){
        robot=robotArray_.msg;
    };

    bool isOk;
private:

    /*
    @brief 发送线程函数
    */
    void sendThreadFun(){
        while(true){
            // usleep(5000);
            ser->writeData(visionArray_.array,sizeof(visionArray));
            isOk=ser->isOpen();
        }
    };

    /*
    @brief 接收线程函数
    */
    void receiveThreadFun(){
        while(true){
            // usleep(5000);
            std::vector<uint8_t> head(2);
            std::vector<uint8_t> array(sizeof(robotArray)-2);
            ser->readData(head.data(),2);
            if(head[0]==0xa5 && head[1]==0x00){
                ser->readData(array.data(),sizeof(robotArray)-2);
                array.reserve(sizeof(robotArray));
                array.insert(array.begin(),head[1]);array.insert(array.begin(),head[0]);
                std::memcpy(robotArray_.array,array.data(),sizeof(robotArray));
            }
            isOk=ser->isOpen();
        }
    };

    /*
    @brief 看门狗线程函数
    */
    void watchDogThredFun(){
        while(true){
            if(isOk){
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            else{
                ser->init(devName,baudRate);
                isOk=ser->open();
            }
        }
    };

    const char* devName;
    const int baudRate;
    std::unique_ptr<CSerialPort> ser;
    std::thread sendThread;
    std::thread reciveThread;
    std::thread watchDogThred;
    visionArray visionArray_;
    robotArray robotArray_;
};

#endif //VISION_SERIAL_HPP
