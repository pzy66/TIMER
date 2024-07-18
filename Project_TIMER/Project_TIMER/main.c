#include <reg52.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
#include "EEPROM.h"
 


unsigned long sec_count = 0; // 秒计数
unsigned int day_count = 1;  // 天计数，初始值为1
unsigned int year = 2024;    // 年份，初始值为2024
unsigned int days_in_year =0;
unsigned int month;
unsigned int day;
unsigned int sec;
unsigned int min;
unsigned int hour;
char buffer[26]; // 调整大小以适应格式化字符串

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
  if (count >= 574) {
    count = 0;
    if (sec_count < 86400) {
      sec_count++;
    }
    else {
      sec_count = 0;
      day_count++;
      days_in_year = 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 1 : 0);
      if (day_count > days_in_year) {
        day_count = 1;
        year++;
      }
    }
    
        month = ana_month(day_count);
        day = ana_day(day_count);
        sec = ana_sec(sec_count);
        min = ana_min(sec_count);
        hour = ana_hour(sec_count);

        buffer[0] = get(year, 4)+'0';
        buffer[1] = get (year, 3)+'0';
        buffer[2] = get (year, 2)+'0';
        buffer[3] = get (year, 1)+'0';
        buffer[4] = '-';
        buffer[5] = get (month, 2)+'0';
        buffer[6] = get (month, 1)+'0';
        buffer[7] = '-';
        buffer[8] = get (day, 2)+'0';
        buffer[9] = get (day, 1)+'0';
        buffer[10] = ' ';
        buffer[11] = get (hour, 2)+'0';
        buffer[12] = get (hour, 1)+'0';
        buffer[13] = ':';
        buffer[14] = get (min, 2)+'0';
        buffer[15] = get (min, 1)+'0';
        buffer[16] = ':';
        buffer[17] = get (sec, 2)+'0';
        buffer[18] = get (sec, 1)+'0';
        buffer[19] = ' ';
        buffer[20] = get_weekday(day_count)[0];
        buffer[21] = get_weekday(day_count)[1];
        buffer[22] = get_weekday(day_count)[2];
        buffer[23] = '\r';
        buffer[24] = '\n';
        buffer[25] = '\0'; // 以空字符结尾，标志字符串的结束

        UART_SendString(buffer); // 发送到UART
  }
}

//void uart_isr() interrupt 4 {
//    if (RI) {

//        RI = 0;                // 清除接收中断标志
//        }
//    }
//    if (TI) {
//        TI = 0;  // 清除发送中断标志
//    }
//}


// 主程序
void main() {
    Initdoor();  //中断初始化
    Timer0_Init(); //定时器1 100微妙
    InitUART();// 串口初始化函数
    while (1) {
        display_time(sec_count);
    }
}

