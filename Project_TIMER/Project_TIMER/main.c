#include <reg52.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
#include "EEPROM.h"
 


unsigned long sec_count = 0; // �����
unsigned int day_count = 1;  // ���������ʼֵΪ1
unsigned int year = 2024;    // ��ݣ���ʼֵΪ2024
unsigned int days_in_year =0;
unsigned int month;
unsigned int day;
unsigned int sec;
unsigned int min;
unsigned int hour;
char buffer[26]; // ������С����Ӧ��ʽ���ַ���
// ���ڷ����ַ�������
void UART_SendString(unsigned char* str) {
    while (*str != '\0') {
        SBUF = *str;    // ���͵�ǰ�ַ�
        while (!TI);    // �ȴ��������
        TI = 0;         // ���������ɱ�־
        str++;          // ָ����һ���ַ�
    }
}

 

// ��ʱ��0�жϷ������
void Timer0_Handler() interrupt 1 {
  static unsigned int count = 0; // ��ʱ���������
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
        buffer[25] = '\0'; // �Կ��ַ���β����־�ַ����Ľ���

        UART_SendString(buffer); // ���͵�UART
  }
}

void uart_isr() interrupt 4 {
    if (RI) {

        RI = 0;                // ��������жϱ�־
        }
    }
    if (TI) {
        TI = 0;  // ��������жϱ�־
    }
}


// ������
void main() {
    Initdoor();  //�жϳ�ʼ��
    Timer0_Init(); //��ʱ��1 100΢��
    InitUART();// ���ڳ�ʼ������
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
        '\0' // �Կ��ַ���β����־�ַ����Ľ���
        };
        UART_SendString(buffer); // ���͵�UART
    }
}

