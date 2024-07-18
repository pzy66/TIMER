#include <reg52.h>
#include "Segment.h"
#include "Initial.h"

unsigned char leddata[] = 
{
    0x03,  //"0"
    0x9F,  //"1"
    0x25,  //"2"
    0x0D,  //"3"
    0x99,  //"4"
    0x49,  //"5"
    0x41,  //"6"
    0x1F,  //"7"
    0x01,  //"8"
    0x09,  //"9"
    0x11,  //"A"
    0xC1,  //"B"
    0x63,  //"C"
    0x85,  //"D"
    0x61,  //"E"
    0x71,  //"F"
    0x91,  //"H"
    0xE3,  //"L"
    0x13,  //"n"
    0x83,  //"u"
    0x31,  //"P"
    0xC5,  //"o"
    0xFD,  //"-"
    0xFF,  //熄灭
};

void open(char a) 
{
    SegmentG1 = 1;
    SegmentG2 = 1;
    SegmentG3 = 1;
    SegmentG4 = 1;

    switch (a) 
    {
    case 0:
        SegmentG1 = 0;
        break;
    case 1:
        SegmentG2 = 0;
        break;
    case 2:
        SegmentG3 = 0;
        break;
    case 3:
        SegmentG4 = 0;
        break;
    default:
        break;
    }
}

void change(int num) 
{
    P0 = leddata[get(num, 1)];
    open(3); // 打开第四个灯
    delay(1);

    P0 = leddata[get(num, 2)];
    open(2); // 打开第三个灯
    delay(1);

    P0 = leddata[get(num, 3)];
    open(1); // 打开第二个灯
    delay(1);

    P0 = leddata[get(num, 4)];
    open(0); // 打开第一个灯
    delay(1);
}
