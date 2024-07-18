#include <reg52.h>
#include "LED.h"
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"
 

unsigned long sec_count = 0; // �����
unsigned int day_count = 1;  // ���������ʼֵΪ1
unsigned int year = 2024;    // ��ݣ���ʼֵΪ2024
 
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

// ������
void main() {
    Initdoor();  //�жϳ�ʼ��
    Timer0_Init(); //��ʱ��1 100΢��
    InitUART();// ���ڳ�ʼ������
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // ��ѭ��������Ϊ�գ���Ϊʱ��ĸ����ڶ�ʱ���жϴ����������
    }
}

