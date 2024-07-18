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

