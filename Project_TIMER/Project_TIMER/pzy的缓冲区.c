#include <reg52.h>
#include "EEPROM.h"

sbit SegmentG1 = P2 ^ 3;
sbit SegmentG2 = P2 ^ 2;
sbit SegmentG3 = P2 ^ 1;
sbit SegmentG4 = P2 ^ 0;
sbit KEY1 = P3 ^ 2;
sbit KEY2 = P3 ^ 3;

#define EEPROM_ADDR 0x2800 // 定义EEPROM存储地址

static int num = 0;

void delay(int num) {
    while (num--) {
        int i;
        for (i = 0; i < 123; i++);
    }
}

void External0_Handler() interrupt 0 // 外部中断0处理程序
{
    num++;
    EA = 0; // 禁用全局中断
    IAPSectorErase(EEPROM_ADDR); // 先擦除EEPROM存储区域
    IAPByteWrite(EEPROM_ADDR, num & 0xFF); // 写入低字节
    IAPByteWrite(EEPROM_ADDR + 1, (num >> 8) & 0xFF); // 写入高字节
    EA = 1; // 使能全局中断
    while (KEY1 == 0);
}

void External1_Handler() interrupt 2 // 外部中断1处理程序
{
    num--;
    EA = 0; // 禁用全局中断
    IAPSectorErase(EEPROM_ADDR); // 先擦除EEPROM存储区域
    IAPByteWrite(EEPROM_ADDR, num & 0xFF); // 写入低字节
    IAPByteWrite(EEPROM_ADDR + 1, (num >> 8) & 0xFF); // 写入高字节
    EA = 1; // 使能全局中断
    while (KEY2 == 0);
}

int get(int num, char n) {
    switch (n) {
    case 1:
        return num % 10; // 返回个位
    case 2:
        return (num / 10) % 10; // 返回十位
    case 3:
        return (num / 100) % 10; // 返回百位
    case 4:
        return (num / 1000) % 10; // 返回千位
    default:
        return 0; // 默认返回0
    }
}

unsigned char leddata[] = {
    0x03,  //"0"
    0x9F,  //"1"
    0x25,  //"2"
    0x0D,  //"3"
    0x99,  //"4"
    0x49,  //"5"
    0x41,  //"6"
    0x1F,  //"7"
    0x01,  //"8"
    0x09,  //"9"
    0x11,  //"A"
    0xC1,  //"B"
    0x63,  //"C"
    0x85,  //"D"
    0x61,  //"E"
    0x71,  //"F"
    0x91,  //"H"
    0xE3,  //"L"
    0x13,  //"n"
    0x83,  //"u"
    0x31,  //"P"
    0xC5,  //"o"
    0xFD,  //"-"
    0xFF,  //熄灭
    0xFF   //自定义
};

void open(char a) {
    SegmentG1 = 1;
    SegmentG2 = 1;
    SegmentG3 = 1;
    SegmentG4 = 1;

    switch (a) {
    case 0:
        SegmentG1 = 0;
        break;
    case 1:
        SegmentG2 = 0;
        break;
    case 2:
        SegmentG3 = 0;
        break;
    case 3:
        SegmentG4 = 0;
        break;
    default:
        break;
    }
}

void change(int num) {
    if (num < 0) {
        P0 = leddata[22]; // 显示 "-"
        open(0); // 打开第一个灯
        delay(2);
        num = -num; // 取正数处理
    }
    else {
        P0 = leddata[23]; // 熄灭符号位置的数码管
        open(0); // 打开第一个灯
        delay(2);
    }

    P0 = leddata[get(num, 1)];
    open(3); // 打开第四个灯
    delay(2);

    P0 = leddata[get(num, 2)];
    open(2); // 打开第三个灯
    delay(2);

    P0 = leddata[get(num, 3)];
    open(1); // 打开第二个灯
    delay(2);

    if (num >= 1000) {
        P0 = leddata[get(num, 4)];
        open(0); // 打开第一个灯
        delay(2);
    }
}

void main() {
    // 读取EEPROM中的num值
    EA = 0; // 禁用全局中断
    num = IAPByteRead(EEPROM_ADDR) | (IAPByteRead(EEPROM_ADDR + 1) << 8);
    EA = 1; // 使能全局中断

    // 检查是否为无效值
    if (num == 0xFFFF) {
        num = 0; // 初始化为0
    }

    EX0 = 1; // 使能外部中断0
    EX1 = 1; // 使能外部中断1
    IT0 = 1; // 下降沿触发中断0
    IT1 = 1; // 下降沿触发中断1
    EA = 1;  // 使能全局中断

    while (1) {
        change(num);
    }


}
