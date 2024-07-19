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
    TMOD &= 0xF0; // �����ʱ��0ģʽλ
    TMOD |= 0x01; // ���ö�ʱ��0Ϊ16λģʽ

    // �����ʼֵ
    // ��ʱ������ֵ = 65536 - (��ʱʱ�� / ��������)
    // �����������Ϊ1΢�룬��ʱʱ��Ϊ50000΢��
    // �������ڿ���ͨ��ʱ��Ƶ�ʣ�ͨ��Ϊ12 MHz��������
    TH0 = 0x8A;
    TL0 = 0xD0;        // ���õ�8λ

    TR0 = 1; // ������ʱ��0
    TF0 = 0; // ��������־
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

int get(int num, char n) 
{
    switch (n) 
    {
    case 1:
        return num % 10; // ���ظ�λ
    case 2:
        return (num / 10) % 10; // ����ʮλ
    case 3:
        return (num / 100) % 10; // ���ذ�λ
    case 4:
        return (num / 1000) % 10; // ����ǧλ
    default:
        return 0; // Ĭ�Ϸ���0
    }
}

 