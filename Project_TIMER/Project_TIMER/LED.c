#include <reg52.h>
#include "LED.h"
#include "Initial.h"
 

void light_LED(void)
{
  LED1 = 0;       //��LED1
  delay(500);  //�ӳ�500ms
  LED1 = 1; 

  LED2 = 0;       //��LED2
  delay(500);  //�ӳ�500ms
  LED2 = 1;

  LED3 = 0;       //��LED3
  delay(500);  //�ӳ�500ms
  LED3 = 1;

  LED4 = 0;       //��LED4
  delay(500);  //�ӳ�500ms
  LED4 = 1;
}