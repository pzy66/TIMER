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