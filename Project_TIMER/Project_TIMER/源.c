#include <reg52.h>
#include "LED.h"

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

 

void main() {
    InitInterrupt();
    Init();
    while (1) {
        change(ms);
    }
}
