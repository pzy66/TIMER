#include <reg52.h>
#include "LED.h"
#include "Initial.h"
 

void light_LED(void)
{
  LED1 = 0;       //打开LED1
  DelayNms(50);  //延迟500ms


  LED2 = 0;       //打开LED2
  DelayNms(50);  //延迟500ms


  LED3 = 0;       //打开LED3
  DelayNms(50);  //延迟500ms


  LED4 = 0;       //打开LED4
  DelayNms(50);  //延迟500ms
}