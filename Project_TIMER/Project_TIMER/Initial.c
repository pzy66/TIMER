#pragma once//123123
#include "Initial.h"
#include<reg52.h>
void Initdoor() {
    EA = 1;     // ʹ��ȫ���ж�
    EX0 = 1;    //�ж�0 KEY1  С��
    ET0 = 1;    //�ж�1 ��ʱ��0  С��
    EX1 = 1;    //�ж�2 KEY2  С��
    ET1 = 1;    //�ж�3 ��ʱ��1  С��
    ES = 1;     //�ж�4 �����ж�  С��
    ET2 = 1;    //�ж�5 ��ʱ��2  С��
}

void Init_Timer0() {
    TMOD = 0x01; // ���ö�ʱ��0Ϊģʽ1��16λ��ʱ��ģʽ��
    TH0 = 0xFC;  // ���ö�ʱ����ֵ���ֽ�
    TL0 = 0x18;  // ���ö�ʱ����ֵ���ֽ�
    TR0 = 0;     // ������ʱ��
}

void Init_Timer1()
{
}
