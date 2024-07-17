#pragma once//123123
#include "Initial.h"
#include<reg52.h>
void Initdoor() {
    EA = 1;     // 使能全局中断
    EX0 = 1;    //中断0 KEY1  小门
    ET0 = 1;    //中断1 定时器0  小门
    EX1 = 1;    //中断2 KEY2  小门
    ET1 = 1;    //中断3 定时器1  小门
    ES = 1;     //中断4 串口中断  小门
    ET2 = 1;    //中断5 定时器2  小门
}

void Init_Timer0() {
    TMOD = 0x01; // 设置定时器0为模式1（16位定时器模式）
    TH0 = 0xFC;  // 设置定时器初值高字节
    TL0 = 0x18;  // 设置定时器初值低字节
    TR0 = 0;     // 启动定时器
}

void Init_Timer1()
{
}
