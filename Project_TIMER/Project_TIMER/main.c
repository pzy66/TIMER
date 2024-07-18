#include <reg52.h>
#include <stdio.h>

// ȫ�ֱ��������ڴ洢��ǰʱ�������
static unsigned int year = 2024;
static unsigned char month = 1;
static unsigned char day = 1;
static unsigned char hour = 0;
static unsigned char minute = 0;
static unsigned char second = 0;
static unsigned int  day_count = 1;

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

// ���ڳ�ʼ������
void InitUART() {
    TMOD = 0x20;    // ���ö�ʱ��1Ϊģʽ2��8λ�Զ���װ��
    PCON = 0x80;    // �����ʼӱ�
    TH1 = 0xF3;     // �趨��������װֵ����Ӧ������4800
    TL1 = 0xF3;
    SCON = 0x50;    // ���ô��ڹ�����ʽΪģʽ1
    TR1 = 1;        // ������ʱ��1
    UART_SendString("UART Initialized\r\n");
}

// ��ʱ��0��ʼ������
void Timer0_Init() {
    TMOD &= 0xF0;  // �����ʱ��0ģʽλ
    TMOD |= 0x02;  // ���ö�ʱ��0Ϊģʽ2��8λ�Զ���װ��
    TH0 = 0xB8;    // �趨��װֵ��ʹ��ʱ��0ÿ250�λ����������һ��
    TL0 = 0xB8;
    ET0 = 1;       // ������ʱ��0�ж�
    EA = 1;        // ȫ���ж�ʹ��
    TR0 = 1;       // ������ʱ��0
}

// ��ʱ��0�жϷ������
void Timer0_Handler() interrupt 1 {
    static unsigned int count = 0; // ��ʱ���������
    char buffer[50];

    count++;

    if (count >= 12000) { // ÿ4000�������Լ1��
        count = 0;
        // ����ʱ��
        second++;
        if (second >= 60) {
            second = 0;
            minute++;
            if (minute >= 60) {
                minute = 0;
                hour++;
                if (hour >= 24) {
                    hour = 0;
                    day++;
                    day_count++;
                    if (day > days_in_month(month, year)) {
                        day = 1;
                        month++;
                        if (month > 12) {
                            month = 1;
                            year++;
                        }
                    }
                }
            }
        }

        // ��ʽ����ǰʱ�䲢���������
        sprintf(buffer, "%4d-%2d-%2d %2d:%2d:%2d %s\r\n", year, month, day, hour, minute, second, get_weekday(day));
        UART_SendString(buffer); // ���͵�UART
    }
}

// ������
void main() {
    InitUART(); // ��ʼ������
    Timer0_Init();  // ��ʼ����ʱ��0
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // ��ѭ��������Ϊ�գ���Ϊʱ��ĸ����ڶ�ʱ���жϴ����������
    }
}

