#include <reg52.h>
#include <stdio.h>
#include <LED.h>
#include <Segment.h>
#include <Initial.h>


// 全局变量，用于存储当前时间和日期
static unsigned int  day_count = 1;
static unsigned int  sec_count = 0;

static unsigned int year = 2024;
static unsigned char month = 1;
static unsigned char day = 1;
static unsigned char hour = 0;
static unsigned char minute = 0;
static unsigned char second = 0;

// 获取星期几的函数
char* get_weekday(int  day_count) {
    int d = (day_count + 1) % 7;
    switch (d) {
    case 0: return "Sat";
    case 1: return "Sun";
    case 2: return "Mon";
    case 3: return "Tue";
    case 4: return "Wed";
    case 5: return "Thu";
    case 6: return "Fri";
    default: return "Unknown";
    }
}

// 帮助函数，确定每个月的天数
unsigned char days_in_month(unsigned char month, unsigned int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29; // 闰年
        else
            return 28; // 平年
    default:
        return 0;
    }
}

// 串口发送字符串函数
void UART_SendString(unsigned char* str) {
    while (*str != '\0') {
        SBUF = *str;    // 发送当前字符
        while (!TI);    // 等待发送完成
        TI = 0;         // 清除发送完成标志
        str++;          // 指向下一个字符
    }
}


// 定时器0中断服务程序
void Timer0_Handler() interrupt 1 {
    static unsigned int count = 0; // 定时器溢出计数
    count++;
    if (count >= 10000) {
      count = 0;
      if (sec_count < 86400) {
        sec_count++;
      }
      else {
        sec_count = 0;
        day_count++;
      }
    }   
}

void UART() interrupt 4
{
//  static unsigned char s_iBuffer;   //定义临时缓冲变量
//  s_iBuffer = SBUF;                 //将数据从串口数据缓冲寄存器中取出
//  RI = 0;                           //清除接收中断标志位

//  SBUF = s_iBuffer;                 //将数据放入串口数据缓冲寄存器
//  while(!TI)                        //等待发送数据完成
//  {
//    
//  }
//  TI = 0;                           //清除发送完成标志位
//  unsigned char arrString[]="Hello";
//  unsigned char i;
//  for(i=0;i<12;i++)
//  {
//    SBUF=arrString[i];
//    while(!TI)
//    {
//      
//    }
//    TI=0;
//  }

}
