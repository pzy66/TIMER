#include <reg52.h>
#include <LED.h>
 
static void delay(int nms)
{
  unsigned int i, j;
  for (i = 0; i < nms; i++)
  {
    for (j = 0; j < 123; j++)
    {

    }
  }
}

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