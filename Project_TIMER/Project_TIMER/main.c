#include <reg52.h>
#include <stdio.h>
#include <LED.h>
#include <Segment.h>
#include <Initial.h>


// ȫ�ֱ��������ڴ洢��ǰʱ�������
static unsigned int  day_count = 1;
static unsigned int  sec_count = 0;

static unsigned int year = 2024;
static unsigned char month = 1;
static unsigned char day = 1;
static unsigned char hour = 0;
static unsigned char minute = 0;
static unsigned char second = 0;

// ��ȡ���ڼ��ĺ���
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

// ����������ȷ��ÿ���µ�����
unsigned char days_in_month(unsigned char month, unsigned int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29; // ����
        else
            return 28; // ƽ��
    default:
        return 0;
    }
}

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
      }
      else {
        sec_count = 0;
        day_count++;
      }
    }   
}

void UART() interrupt 4
{
//  static unsigned char s_iBuffer;   //������ʱ�������
//  s_iBuffer = SBUF;                 //�����ݴӴ������ݻ���Ĵ�����ȡ��
//  RI = 0;                           //��������жϱ�־λ

//  SBUF = s_iBuffer;                 //�����ݷ��봮�����ݻ���Ĵ���
//  while(!TI)                        //�ȴ������������
//  {
//    
//  }
//  TI = 0;                           //���������ɱ�־λ
//  unsigned char arrString[]="Hello";
//  unsigned char i;
//  for(i=0;i<12;i++)
//  {
//    SBUF=arrString[i];
//    while(!TI)
//    {
//      
//    }
//    TI=0;
//  }

}
