#include "analyze.h"
// ��������
char ana_sec(unsigned int sec_count) {
  return sec_count % 60;
}

// ���������
char ana_min(unsigned int sec_count) {
  return (sec_count / 60) % 60;
}

// ����Сʱ��
char ana_hour(unsigned int sec_count) {
  return (sec_count / 3600) % 24;
}