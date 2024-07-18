#include <reg52.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
 

unsigned long sec_count = 0; // 秒计数
unsigned int day_count = 1;  // 天计数，初始值为1
unsigned int year = 2024;    // 年份，初始值为2024
 
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
    },
    else {
      sec_count = 0;
      day_count++;
      unsigned int days_in_year = 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 1 : 0);
      if (day_count > days_in_year) {
        day_count = 1;
        year++;
      }
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

