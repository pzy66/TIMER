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