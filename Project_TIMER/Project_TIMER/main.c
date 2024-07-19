#include <reg52.h>
#include <stdio.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
#include "EEPROM.h"
#include "output.h"

unsigned int sec_count = 0; // �����
unsigned int day_count = 1;  // ���������ʼֵΪ1
unsigned int year = 2024;    // ��ݣ���ʼֵΪ2024
unsigned int days_in_year =0;
unsigned int month;
unsigned int day;
unsigned int sec;
unsigned int min;
unsigned int hour;
char* weekdays[] = { "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri" };
char w=0;
char putchar(char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
    return ch;
}


// ��ʱ��0�жϷ������
void Timer0_Handler() interrupt 1 {
    static unsigned int count = 0; // ��ʱ���������
    count++;
    if (count >= 20) { // ÿ50ms���һ�Σ�20�������Լ1��
        count = 0;
        if (sec_count < 86400) { // һ����86400��
            sec_count++;
        }
        else {
            sec_count = 0;
            day_count++;
            if (w < 6) {
                w++;
            }
            else {
                w = 0;
            }
            days_in_year = 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 1 : 0);
            if (day_count > days_in_year) {
                day_count = 1;
                year++;
            }
        }
        month = ana_month(day_count, year);
        day = ana_day(day_count, year);
        sec = ana_sec(sec_count);
        min = ana_min(sec_count);
        hour = ana_hour(sec_count);
        printf("%d-%02d-%02d %02d:%02d:%02d ", year, month, day, hour, min, sec);
        printf("%s\n", weekdays[w]);
    }
}
   
void uart_isr() interrupt 4 {
    if (RI) {
        RI = 0;                // ��������жϱ�־
        }
    
}


// ������
void main() {
    Initdoor();  //�жϳ�ʼ��
    InitUART();// ���ڳ�ʼ������
   Timer0_Init(); //��ʱ��1 100΢��
    while (1) {
      
    }
}

