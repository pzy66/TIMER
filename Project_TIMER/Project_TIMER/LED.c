#include <reg52.h>
#include "LED.h"
#include "Initial.h"
 

void light_LED(void)
{
  unsigned char i;
  while (1)
  {
    P2 = 0xEF;

    for (i = 0; i < 4; i++)
    {
      delay(500);
      P2 = P2 << 1;
    }
  }
}