#include<reg52.h>

void Timer0_Handdler() interrupt 1{
   
}

void Timer2_Handdler() interrupt 6{
    static char i = 0;
    light_LED(i++);
    if (i == 3) {
        i = 0;
    }
}