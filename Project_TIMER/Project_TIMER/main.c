#include <reg52.h>
#include <stdio.h>

// 全局变量，用于存储当前时间和日期
unsigned int year = 2024;
unsigned char month = 7;
unsigned char day = 17;
unsigned char hour = 12;
unsigned char minute = 30;
unsigned char second = 0;

// 获取星期几的函数
char* get_weekday(int day) {
    int d = (day + 1) % 7;
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
// 串口发送字符函数
void UART_SendString(unsigned char* str) {
    while (*str != '\0') {
        SBUF = *str;    // 发送当前字符
        while (!TI);    // 等待发送完成
        TI = 0;         // 清除发送完成标志
        str++;          // 指向下一个字符
    }
}
// 串口初始化函数
void InitUART() {
    TMOD = 0x20;    // 设置定时器1为工作方式2 (16位自动重装)
    PCON = 0x80;    // 波特率加倍
    TH1 = TL1 = 0xF3;   // 设定波特率重装值，对应波特率4800
    SCON = 0x50;    // 设置串口工作方式为模式1
    TR1 = 1;        // 启动定时器1
    UART_SendString("UART Initialized\r\n");
}

// UART中断服务函数
void UART_ISR() interrupt 4 {
    if (RI) {
        RI = 0;
        // 处理接收到的数据，如果有需要的话
    }
    if (TI) {
        TI = 0;
        // 发送数据完成，可以继续发送下一个字符
    }
}
// Helper function to determine the number of days in a month
unsigned char days_in_month(unsigned char month, unsigned int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29; // Leap year
        else
            return 28; // Non-leap year
    default:
        return 0;
    }
}

// Timer1 interrupt handler
void Timer1_Handler() interrupt 3 {
    static unsigned int s_iCnt1 = 0;   // 50ms counter variable (approx. 20 interrupts per second)
    char buffer[50];  // Buffer to store formatted string
    s_iCnt1++;

    if (s_iCnt1 >= 20) { // Every 20 interrupts is approximately 1 second
        s_iCnt1 = 0;    // Reset counter
        second++;
        if (second >= 60) {
            minute++;
            second = 0;
            if (minute >= 60) {
                hour++;
                minute = 0;
                if (hour >= 24) {
                    day++;
                    hour = 0;
                    if (day > days_in_month(month, year)) {
                        day = 1;
                        month++;
                        if (month > 12) {
                            month = 1;
                            year++;
                        }
                    }
                }
            }
        }

        // Format current time and date for UART output
        sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d %s\r\n", year, month, day, hour, minute, second, get_weekday(day));
        UART_SendString(buffer); // Send to UART
    }
}


// 主程序

void main() {
    InitUART(); // 初始化串口

    // 测试串口发送
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // 主循环，可以为空，因为时间的更新在定时器中断处理函数中完成
    }
}
