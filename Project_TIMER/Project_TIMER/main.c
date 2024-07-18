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

// 主程序
void main() {
    Initdoor();  //中断初始化
    Timer0_Init(); //定时器1 100微妙
    InitUART();// 串口初始化函数
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // 主循环，可以为空，因为时间的更新在定时器中断处理函数中完成
    }
}

