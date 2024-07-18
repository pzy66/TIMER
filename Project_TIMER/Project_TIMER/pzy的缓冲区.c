#include <reg52.h>
#include "EEPROM.h"

sbit SegmentG1 = P2 ^ 3;
sbit SegmentG2 = P2 ^ 2;
sbit SegmentG3 = P2 ^ 1;
sbit SegmentG4 = P2 ^ 0;

sbit KEY1 = P3 ^ 2;
sbit KEY2 = P3 ^ 3;

#define EEPROM_ADDR 0x2800 // ����EEPROM�洢��ַ

static int num = 0;

void delay(int num) 
{
    while (num--) 
    {
        int i;
        for (i = 0; i < 123; i++);
    }
}

void External0_Handler() interrupt 0 // �ⲿ�ж�0�������
{
    num++;
    EA = 0; // ����ȫ���ж�
    IAPSectorErase(EEPROM_ADDR); // �Ȳ���EEPROM�洢����///////////11111111111111111111111111111111
    IAPByteWrite(EEPROM_ADDR, num & 0xFF); // д����ֽ�///////////11111111111111111111111111
    IAPByteWrite(EEPROM_ADDR + 1, (num >> 8) & 0xFF); // д����ֽ�/111111111111111111111111111111111
    EA = 1; // ʹ��ȫ���ж�
    while (KEY1 == 0);
}

void External1_Handler() interrupt 2 // �ⲿ�ж�1�������
{
    num--;
    EA = 0; // ����ȫ���ж�
    IAPSectorErase(EEPROM_ADDR); // �Ȳ���EEPROM�洢����
    IAPByteWrite(EEPROM_ADDR, num & 0xFF); // д����ֽ�
    IAPByteWrite(EEPROM_ADDR + 1, (num >> 8) & 0xFF); // д����ֽ�
    EA = 1; // ʹ��ȫ���ж�
    while (KEY2 == 0);
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

unsigned char leddata[] = 
{
    0x03,  //"0"
    0x9F,  //"1"
    0x25,  //"2"
    0x0D,  //"3"
    0x99,  //"4"
    0x49,  //"5"
    0x41,  //"6"
    0x1F,  //"7"
    0x01,  //"8"
    0x09,  //"9"
    0x11,  //"A"
    0xC1,  //"B"
    0x63,  //"C"
    0x85,  //"D"
    0x61,  //"E"
    0x71,  //"F"
    0x91,  //"H"
    0xE3,  //"L"
    0x13,  //"n"
    0x83,  //"u"
    0x31,  //"P"
    0xC5,  //"o"
    0xFD,  //"-"
    0xFF,  //Ϩ��
    0xFF   //�Զ���
};

void open(char a) 
{
    SegmentG1 = 1;
    SegmentG2 = 1;
    SegmentG3 = 1;
    SegmentG4 = 1;

    switch (a) 
    {
    case 0:
        SegmentG1 = 0;
        break;
    case 1:
        SegmentG2 = 0;
        break;
    case 2:
        SegmentG3 = 0;
        break;
    case 3:
        SegmentG4 = 0;
        break;
    default:
        break;
    }
}

void change(int num) 
{
    if (num < 0) 
    {
        P0 = leddata[22]; // ��ʾ "-"
        open(0); // �򿪵�һ����
        delay(2);
        num = -num; // ȡ��������
    }
    else 
    {
        P0 = leddata[23]; // Ϩ�����λ�õ������
        open(0); // �򿪵�һ����
        delay(2);
    }

    P0 = leddata[get(num, 1)];
    open(3); // �򿪵��ĸ���
    delay(2);

    P0 = leddata[get(num, 2)];
    open(2); // �򿪵�������
    delay(2);

    P0 = leddata[get(num, 3)];
    open(1); // �򿪵ڶ�����
    delay(2);

    if (num >= 1000) 
    {
        P0 = leddata[get(num, 4)];
        open(0); // �򿪵�һ����
        delay(2);
    }
}

void main() 
{
    // ��ȡEEPROM�е�numֵ
    EA = 0; // ����ȫ���ж�
    num = IAPByteRead(EEPROM_ADDR) | (IAPByteRead(EEPROM_ADDR + 1) << 8);//111111111111111111111111111111111
    EA = 1; // ʹ��ȫ���ж�

    // ����Ƿ�Ϊ��Чֵ
    if (num == 0xFFFF) {
        num = 0; // ��ʼ��Ϊ0
    }

    EX0 = 1; // ʹ���ⲿ�ж�0
    EX1 = 1; // ʹ���ⲿ�ж�1
    IT0 = 1; // �½��ش����ж�0
    IT1 = 1; // �½��ش����ж�1
    EA = 1;  // ʹ��ȫ���ж�

    while (1) 
    {
        change(num);
    }


}


#include <reg52.h>

unsigned long sec_count = 0; // �����
unsigned int day_count = 1;  // ���������ʼֵΪ1
unsigned int year = 2024;    // ��ݣ���ʼֵΪ2024

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

// �������ں��������ص�ǰ�·ݵĵڼ���
unsigned char ana_day(unsigned int day_count, unsigned int year) {
    unsigned char month = 1;
    while (day_count > days_in_month(month, year)) {
        day_count -= days_in_month(month, year);
        month++;
    }
    return day_count;
}

// �����·ݺ��������ص�ǰ���·�
unsigned char ana_month(unsigned int day_count, unsigned int year) {
    unsigned char month = 1;
    while (day_count > days_in_month(month, year)) {
        day_count -= days_in_month(month, year);
        month++;
    }
    return month;
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
