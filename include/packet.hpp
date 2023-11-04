//
// Created by promise on 11/3/23.
//

#ifndef SERIAL_TEST_PACKET_HPP
#define SERIAL_TEST_PACKET_HPP

#include <cstdint>
#include <vector>
#include <algorithm>

struct aimMsg{
    float aimYaw=0.f;             // 目标Yaw轴偏移量
    float aimPitch=0.f;           // 目标Pitch轴偏移量
};
struct carMsg{
    uint8_t mode=0;               // 自瞄模式 0-装甲板 1-小符 2-大符
    uint8_t foeColor=0;           // 敌方颜色 0-blue 1-red
    float carYaw=0.f;            // 自身Yaw
    float carPitch=0.f;          // 自身Pitch
    float muzzleSpeed=30.f;       // 弹速
};

inline carMsg fromVector(const std::vector<uint8_t> & data){
    carMsg packet;
    std::copy(data.begin()+1, data.end()-1, reinterpret_cast<uint8_t *>(&packet));
    return packet;
}

inline std::vector<uint8_t> toVector(const aimMsg & data){
    std::vector<uint8_t> packet(sizeof(aimMsg));
    std::copy(
            reinterpret_cast<const uint8_t *>(&data),
            reinterpret_cast<const uint8_t *>(&data) + sizeof(aimMsg), packet.begin());
    packet.emplace(packet.begin(),0xA5);
    packet.emplace_back(0x5A);
    return packet;
}


#endif //SERIAL_TEST_PACKET_HPP
