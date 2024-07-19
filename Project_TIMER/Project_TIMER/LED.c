#include <reg52.h>
#include "LED.h"
#include "Initial.h"
 

void light_LED(void)
{
  LED1 = 0;       //打开LED1
  delay(500);  //延迟500ms
  LED1 = 1; 

  LED2 = 0;       //打开LED2
  delay(500);  //延迟500ms
  LED2 = 1;

  LED3 = 0;       //打开LED3
  delay(500);  //延迟500ms
  LED3 = 1;

  LED4 = 0;       //打开LED4
  delay(500);  //延迟500ms
  LED4 = 1;
}