#include <reg52.h>
#include <stdio.h>

// 全局变量，用于存储当前时间和日期
static unsigned int year = 2024;
static unsigned char month = 1;
static unsigned char day = 1;
static unsigned char hour = 0;
static unsigned char minute = 0;
static unsigned char second = 0;
static unsigned int  day_count = 1;

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

// 串口初始化函数
void InitUART() {
    TMOD = 0x20;    // 设置定时器1为模式2（8位自动重装）
    PCON = 0x80;    // 波特率加倍
    TH1 = 0xF3;     // 设定波特率重装值，对应波特率4800
    TL1 = 0xF3;
    SCON = 0x50;    // 设置串口工作方式为模式1
    TR1 = 1;        // 启动定时器1
    UART_SendString("UART Initialized\r\n");
}

// 定时器0初始化函数
void Timer0_Init() {
    TMOD &= 0xF0;  // 清除定时器0模式位
    TMOD |= 0x02;  // 设置定时器0为模式2（8位自动重装）
    TH0 = 0xB8;    // 设定重装值，使定时器0每250次机器周期溢出一次
    TL0 = 0xB8;
    ET0 = 1;       // 开启定时器0中断
    EA = 1;        // 全局中断使能
    TR0 = 1;       // 启动定时器0
}

// 定时器0中断服务程序
void Timer0_Handler() interrupt 1 {
    static unsigned int count = 0; // 定时器溢出计数
    char buffer[50];

    count++;

    if (count >= 12000) { // 每4000次溢出大约1秒
        count = 0;
        // 更新时间
        second++;
        if (second >= 60) {
            second = 0;
            minute++;
            if (minute >= 60) {
                minute = 0;
                hour++;
                if (hour >= 24) {
                    hour = 0;
                    day++;
                    day_count++;
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

        // 格式化当前时间并输出到串口
        sprintf(buffer, "%4d-%2d-%2d %2d:%2d:%2d %s\r\n", year, month, day, hour, minute, second, get_weekday(day));
        UART_SendString(buffer); // 发送到UART
    }
}

// 主程序
void main() {
    InitUART(); // 初始化串口
    Timer0_Init();  // 初始化定时器0
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // 主循环，可以为空，因为时间的更新在定时器中断处理函数中完成
    }
}

