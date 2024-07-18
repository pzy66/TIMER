#include "analyze.h"
// 计算秒数
char ana_sec(unsigned int sec_count) {
  return sec_count % 60;
}

// 计算分钟数
char ana_min(unsigned int sec_count) {
  return (sec_count / 60) % 60;
}

// 计算小时数
char ana_hour(unsigned int sec_count) {
  return (sec_count / 3600) % 24;
}

// 获取星期几的函数
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

// 帮助函数，确定每个月的天数
unsigned char days_in_month(unsigned char month, unsigned int year) {
  switch (month) {
  case 1: case 3: case 5: case 7: case 8: case 10: case 12:
    return 31;
  case 4: case 6: case 9: case 11:
    return 30;
  case 2:
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
      return 29; // 闰年
    else
      return 28; // 平年
  default:
    return 0;
  }
}