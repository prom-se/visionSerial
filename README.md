# NEXT-E_visionSerial
- NEXT-E 视觉串口通讯模块
## 串口库
- [CSerialPort](https://github.com/itas109/CSerialPort)
## 文件结构
```
visionSerial
├── include         头文件目录
│   ├── packet.h    结构体/联合体定义
│   └── serial.hpp  
└── src             源文件目录
    ├── demo.cpp    示例
    └── serial.cpp  
```
## 步兵数据包定义
定义可在[packet.h](include/packet.h)中修改
### 1.visionArray - TX
| Byte | Data |
| - | - |
| 0 | 0xA5 |
| 1-4 | aimYaw |
| 5-8 | aimPitch |
### 2.robotArray - RX
| Byte | Data |
| - | - |
| 0 | 0xA5 |
| 1 | Mode |
| 2 | foeColor |
| 3-4| Empty |
| 5-8 | robotYaw |
| 9-12 | robotPitch |
| 13-16 | muzzleSpeed |
## 使用方法
1. 实例化visionSerial对象时传入串口名称和波特率
2. 打开接收和发送线程
3. 更新数据

具体可参考
[demo.cpp](src/demo.cpp)