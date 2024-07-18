#include "Initial.h"
#include<reg52.h>

void Init_time() {

}

void Initdoor() {
    EA = 1;     // ʹ��ȫ���ж�
    EX0 = 1;    //�ж�0 KEY1  С��
    ET0 = 1;    //�ж�1 ��ʱ��0  С��
    EX1 = 1;    //�ж�2 KEY2  С��
    ET1 = 1;    //�ж�3 ��ʱ��1  С��
    ES = 1;     //�ж�4 �����ж�  С��
    ET2 = 1;    //�ж�5 ��ʱ��2  С��
}

void Timer0_Init() {
  TMOD &= 0xF0;  // �����ʱ��0ģʽλ
  TMOD = 0x02; // ��ʱ��0����ģʽ2��8λ�Զ���װ��
  TH0 = 0x9C;  // ������װֵΪ0x9C��100΢�붨ʱ��
  TL0 = 0x9C;  // ���ó�ʼֵΪ0x9C
  TR0 = 1;     // ������ʱ��0
}




// ���ڳ�ʼ������
void InitUART() {
  TMOD = 0x20;    // ���ö�ʱ��1Ϊģʽ2��8λ�Զ���װ��
  PCON = 0x80;    // �����ʼӱ�
  TH1 = 0xF3;     // �趨��������װֵ����Ӧ������4800
  TL1 = 0xF3;
  SCON = 0x50;    // ���ô��ڹ�����ʽΪģʽ1
  TR1 = 1;        // ������ʱ��1
}

void delay(int nms)
{
    unsigned int i, j;
    for (i = 0; i < nms; i++)
    {
        for (j = 0; j < 123; j++)
        {

        }
    }
}

char get(int num, char n)
{
    switch (n)
    {
    case '1':
        return '0' + (num % 10); // ���ظ�λ
    case '2':
        return '0' + ((num / 10) % 10); // ����ʮλ
    case '3':
        return '0' + ((num / 100) % 10); // ���ذ�λ
    case '4':
        return '0' + ((num / 1000) % 10); // ����ǧλ
    default:
        return '0'; // Ĭ�Ϸ���'0'
    }
}