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
  unsigned char arrString[] = "Hello World��";
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
//  static unsigned char s_iBuffer;   //������ʱ�������
//  s_iBuffer = SBUF;                 //�����ݴӴ������ݻ���Ĵ�����ȡ��
//  RI = 0;                           //��������жϱ�־λ

//  SBUF = s_iBuffer;                 //�����ݷ��봮�����ݻ���Ĵ���
//  while(!TI)                        //�ȴ������������
//  {
//    
//  }
//  TI = 0;                           //���������ɱ�־λ
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
