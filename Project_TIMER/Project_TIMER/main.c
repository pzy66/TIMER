#include <reg52.h>

sbit KEY1 = P3^2;

static void InitInterrupt(void);
static void InitUART(void);

static void InitInterrupt()
{
  IT0 = 1;
  EX0 = 1;
  ES = 1;
  EA = 1;
}

static void InitUART()
{
  SCON = 0X50;
  TMOD = 0X20;
  PCON = 0X80;
  
  TL1 = 0XF3;
  TH1 = TL1;
  TR1 = 1;
}

void main()
{
  InitInterrupt();
  InitUART();
  while(1)
  {
    
  }
}

void External0() interrupt 0
{
  unsigned char arrString[] = "Hello World！";
  unsigned char i;
  
  for(i=0;i<12;i++)
  {
    SBUF = arrString[i];
    while(!TI)
    {
      
    }
    
    TI = 0;
  }
}

void UART() interrupt 4
{
//  static unsigned char s_iBuffer;   //定义临时缓冲变量
//  s_iBuffer = SBUF;                 //将数据从串口数据缓冲寄存器中取出
//  RI = 0;                           //清除接收中断标志位

//  SBUF = s_iBuffer;                 //将数据放入串口数据缓冲寄存器
//  while(!TI)                        //等待发送数据完成
//  {
//    
//  }
//  TI = 0;                           //清除发送完成标志位
//  unsigned char arrString[]="Hello";
//  unsigned char i;
//  for(i=0;i<12;i++)
//  {
//    SBUF=arrString[i];
//    while(!TI)
//    {
//      
//    }
//    TI=0;
//  }

}
