// 定时器0中断服务程序
void Timer0_Handler() interrupt 1 {
  static unsigned int count = 0; // 定时器溢出计数
  char buffer[50];

  count++;

  if (count >= 12000) { // 每4000次溢出大约1秒
    count = 0;
    // 更新时间
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

    // 格式化当前时间并输出到串口
    sprintf(buffer, "%4d-%2d-%2d %2d:%2d:%2d %s\r\n", year, month, day, hour, minute, second, get_weekday(day));
    UART_SendString(buffer); // 发送到UART
  }
}