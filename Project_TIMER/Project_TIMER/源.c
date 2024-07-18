#include <reg52.h>
#include "LED.h"

sbit KEY1 = P3 ^ 2;
sbit BEEP = P1 ^ 0;

void Timer2_Handdler() interrupt 6{
    static char i = 0;
    light_LED(i++);
    if (i == 3) {
        i = 0;
    }
}

static int ms = 0; // ��ʼ��������Ϊ0

void delay(int num);


void Timer0_Handler() interrupt 1 {
    TH0 = 0xFC;  // ���¼��ض�ʱ����ֵ���ֽ�
    TL0 = 0x18;  // ���¼��ض�ʱ����ֵ���ֽ�
    ms++; // ÿ���ж�ʱ���Ӽ���
}

void Key1_Handler() interrupt 0 {
    delay(10);
    if (KEY1 == 0) {
        ms = 0;  // ���ü�����
        TR0 = 1; // ������ʱ��
        while (KEY1 == 0); // �ȴ������ͷ�
        TR0 = 0; // ������ʱ��
    }
}

 

void main() {
    InitInterrupt();
    Init();
    while (1) {
        change(ms);
    }
}
