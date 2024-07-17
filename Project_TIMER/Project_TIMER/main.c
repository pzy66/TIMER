#include <reg52.h>
#include <stdio.h>

// ȫ�ֱ��������ڴ洢��ǰʱ�������
unsigned int year = 2024;
unsigned char month = 7;
unsigned char day = 17;
unsigned char hour = 12;
unsigned char minute = 30;
unsigned char second = 0;

// ��ȡ���ڼ��ĺ���
char* get_weekday(int day) {
    int d = (day + 1) % 7;
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
// ���ڷ����ַ�����
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
    TMOD = 0x20;    // ���ö�ʱ��1Ϊ������ʽ2 (16λ�Զ���װ)
    PCON = 0x80;    // �����ʼӱ�
    TH1 = TL1 = 0xF3;   // �趨��������װֵ����Ӧ������4800
    SCON = 0x50;    // ���ô��ڹ�����ʽΪģʽ1
    TR1 = 1;        // ������ʱ��1
    UART_SendString("UART Initialized\r\n");
}

// UART�жϷ�����
void UART_ISR() interrupt 4 {
    if (RI) {
        RI = 0;
        // ������յ������ݣ��������Ҫ�Ļ�
    }
    if (TI) {
        TI = 0;
        // ����������ɣ����Լ���������һ���ַ�
    }
}
// Helper function to determine the number of days in a month
unsigned char days_in_month(unsigned char month, unsigned int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29; // Leap year
        else
            return 28; // Non-leap year
    default:
        return 0;
    }
}

// Timer1 interrupt handler
void Timer1_Handler() interrupt 3 {
    static unsigned int s_iCnt1 = 0;   // 50ms counter variable (approx. 20 interrupts per second)
    char buffer[50];  // Buffer to store formatted string
    s_iCnt1++;

    if (s_iCnt1 >= 20) { // Every 20 interrupts is approximately 1 second
        s_iCnt1 = 0;    // Reset counter
        second++;
        if (second >= 60) {
            minute++;
            second = 0;
            if (minute >= 60) {
                hour++;
                minute = 0;
                if (hour >= 24) {
                    day++;
                    hour = 0;
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

        // Format current time and date for UART output
        sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d %s\r\n", year, month, day, hour, minute, second, get_weekday(day));
        UART_SendString(buffer); // Send to UART
    }
}


// ������

void main() {
    InitUART(); // ��ʼ������

    // ���Դ��ڷ���
    UART_SendString("Hello, world!\r\n");

    while (1) {
        // ��ѭ��������Ϊ�գ���Ϊʱ��ĸ����ڶ�ʱ���жϴ����������
    }
}
