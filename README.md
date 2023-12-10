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
```
## 步兵数据包定义
定义可在[packet.h](include/packet.h)中修改

内存对齐为2
### 1.visionArray - TX
| Byte | Data |
| - | - |
| 0 | 0xA5 |
| 1 | 0x00 |
| 2-5 | aimYaw |
| 6-9 | aimPitch |

### 2.robotArray - RX
| Byte | Data |
| - | - |
| 0 | 0xA5 |
| 1 | 0x00 |
| 2 | Mode |
| 3 | foeColor |
| 4-7 | robotYaw |
| 8-11 | robotPitch |
| 12-15 | muzzleSpeed |
## 使用方法
1. 实例化visionSerial对象时传入串口名称和波特率
2. 更新数据

具体可参考
[demo.cpp](src/demo.cpp)