#include <reg52.h>
#include"LED.h"

sbit KEY1 = P3 ^ 2;
sbit BEEP = P1 ^ 0;

void Timer2_Handdler() interrupt 6{
    static char i = 0;
    light_LED(i++);
    if (i == 3) {
        i = 0;
    }
}

static int ms = 0; // 初始化计数器为0

void delay(int num);


void Timer0_Handler() interrupt 1 {
    TH0 = 0xFC;  // 重新加载定时器初值高字节
    TL0 = 0x18;  // 重新加载定时器初值低字节
    ms++; // 每次中断时增加计数
}

void Key1_Handler() interrupt 0 {
    delay(10);
    if (KEY1 == 0) {
        ms = 0;  // 重置计数器
        TR0 = 1; // 启动定时器
        while (KEY1 == 0); // 等待按键释放
        TR0 = 0; // 启动定时器
    }
}

//int get(int num, char n) {
//    switch (n) {
//    case 1:
//        return num % 10; // 返回个位
//    case 2:
//        return (num / 10) % 10; // 返回十位
//    case 3:
//        return (num / 100) % 10; // 返回百位
//    case 4:
//        return (num / 1000) % 10; // 返回千位
//    default:
//        return 0; // 默认返回0
//    }
//}
//
//void delay(int num) {
//    while (num--) {
//        int i;
//        for (i = 0; i < 123; i++);
//    }
//}
//
//unsigned char leddata[] = {
//    0x03,  //"0"
//    0x9F,  //"1"
//    0x25,  //"2"
//    0x0D,  //"3"
//    0x99,  //"4"
//    0x49,  //"5"
//    0x41,  //"6"
//    0x1F,  //"7"
//    0x01,  //"8"
//    0x09,  //"9"
//    0x11,  //"A"
//    0xC1,  //"B"
//    0x63,  //"C"
//    0x85,  //"D"
//    0x61,  //"E"
//    0x71,  //"F"
//    0x91,  //"H"
//    0xE3,  //"L"
//    0x13,  //"n"
//    0x83,  //"u"
//    0x31,  //"P"
//    0xC5,  //"o"
//    0xFD,  //"-"
//    0xFF,  //熄灭
//};
//
//void open(char a) {
//    SegmentG1 = 1;
//    SegmentG2 = 1;
//    SegmentG3 = 1;
//    SegmentG4 = 1;
//
//    switch (a) {
//    case 0:
//        SegmentG1 = 0;
//        break;
//    case 1:
//        SegmentG2 = 0;
//        break;
//    case 2:
//        SegmentG3 = 0;
//        break;
//    case 3:
//        SegmentG4 = 0;
//        break;
//    default:
//        break;
//    }
//}
//
//void change(int num) {
//    P0 = leddata[get(num, 1)];
//    open(3); // 打开第四个灯
//    delay(1);
//
//    P0 = leddata[get(num, 2)];
//    open(2); // 打开第三个灯
//    delay(1);
//
//    P0 = leddata[get(num, 3)];
//    open(1); // 打开第二个灯
//    delay(1);
//
//    P0 = leddata[get(num, 4)];
//    open(0); // 打开第一个灯
//    delay(1);
//}


void main() {
    InitInterrupt();
    Init();
    while (1) {
        change(ms);
    }
}
