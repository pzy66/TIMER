#pragma once//1231241`23123

sbit LED1 = P2 ^ 4;          
sbit LED2 = P2 ^ 5;
sbit LED3 = P2 ^ 6;
sbit LED4 = P2 ^ 7;

void light_LED(void); 

static void delay(int nms);