#include <reg52.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
#include "EEPROM.h"
 


unsigned long sec_count = 0; // 秒计数
unsigned int day_count = 1;  // 天计数，初始值为1
unsigned int year = 2024;    // 年份，初始值为2024
 

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

void uart_isr() interrupt 4 {
    if (RI) {

        RI = 0;                // 清除接收中断标志
        }
    }
    if (TI) {
        TI = 0;  // 清除发送中断标志
    }
}


// 主程序
void main() {
    Initdoor();  //中断初始化
    Timer0_Init(); //定时器1 100微妙
    InitUART();// 串口初始化函数
    UART_SendString("Hello, world!\r\n");
    
    year=ana_year(day_count);
    month=ana_month(day_count);
    day=ana_day(day_count);
    sec = ana_sec(sec_count);
    min = ana_min(sec_count);
    hour = ana_hour(sec_count);

    while (1) {
        char buffer[] = {
        get_char(year, '4'), get_char(year, '3'), get_char(year, '2'), get_char(year, '1'), '-',
        get_char(month, '2'), get_char(month, '1'), '-',
        get_char(day, '2'), get_char(day, '1'), ' ',
        get_char(hour, '2'), get_char(hour, '1'), ':',
        get_char(minute, '2'), get_char(minute, '1'), ':',
        get_char(second, '2'), get_char(second, '1'), ' ',
        get_weekday(day_count)[0], get_weekday(day_count)[1], get_weekday(day_count)[2],
        '\0' // 以空字符结尾，标志字符串的结束
        };
        UART_SendString(buffer); // 发送到UART
    }
}

