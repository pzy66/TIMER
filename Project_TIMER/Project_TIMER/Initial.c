#include "Initial.h"
#include<reg52.h>

void Init_time() {

}

void Initdoor() {
    EA = 1;     // 使能全局中断
    EX0 = 1;    //中断0 KEY1  小门
    IT0=1;
    ET0 = 1;    //中断1 定时器0  小门
    EX1 = 1;    //中断2 KEY2  小门
    ET1 = 1;    //中断3 定时器1  小门
    ES = 1;     //中断4 串口中断  小门
    ET2 = 1;    //中断5 定时器2  小门
}


void Timer0_Init() {
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TH0 = 0x3C;
    TL0 = 0xB0;
    TR0 = 1;
    TF0 = 0;
}
 


// 串口初始化函数
void InitUART() {
  TMOD = 0x20;    // 设置定时器1为模式2（8位自动重装）
  PCON = 0x80;    // 波特率加倍
  TH1 = 0xF3;     // 设定波特率重装值，对应波特率4800
  TL1 = 0xF3;
  SCON = 0x50;    // 设置串口工作方式为模式1
  TR1 = 1;        // 启动定时器1
}

void delay(int nms)
{
    unsigned int i, j;
    for (i = 0; i < nms; i++)
    {
        for (j = 0; j < 123; j++)
        {

        }
    }
}

int get(int num, char n) 
{
    switch (n) 
    {
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

 