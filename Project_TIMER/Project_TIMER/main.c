 #include <reg52.h>
#include <stdio.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
#include "EEPROM.h"
sbit BEEP=P1^0;
unsigned int sec_count = 0;
unsigned int day_count = 1;
unsigned int year = 2024;
unsigned int days_in_year = 0;
unsigned int month;
unsigned int day;
unsigned int sec;
unsigned int min;
unsigned int hour;
char* weekdays[] = {  "Mon", "Tue", "Wed", "Thu", "Fri","Sat", "Sun"};
char w = 0;
unsigned int alarm_hour=0;
unsigned int alarm_mintue=0;
char putchar(char ch) {
    SBUF = ch;
    while (TI == 0);
    TI = 0;
    return ch;
}
 void Exterrnal_Handler() interrupt 0
{
BEEP=1;
}
void Timer0_Handler() interrupt 1 {
   static unsigned int count = 0;
    TH0 = 0x3C;
    TL0 = 0xB0;
    count++;
    if (count >= 20) {
        count = 0;
        if (sec_count < 86400) {
            sec_count++;
        } else {
            sec_count = 0;
            day_count++;
            if (w < 6) {
                w++;
            } else {
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
        RI = 0;
    }
}

void main() {
    Initdoor();
    InitUART();
    Timer0_Init();
    while (1) {
     display_time(sec_count);
     light_LED();
  if(hour==alarm_hour&&min==alarm_mintue)
      {
        BEEP=0;
      }      
    }
}
