#include <reg52.h>
#include<LED.h>

void light_LED(unsigned char led) {
    switch (led) {
    case 0: LED1 = 0; LED4 = 1; break;
    case 1: LED2 = 0; LED1 = 1; break;
    case 2: LED3 = 0; LED2 = 1; break;
    case 3: LED4 = 0; LED3 = 1; break;
    }
}