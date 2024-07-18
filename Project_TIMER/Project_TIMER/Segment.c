#include<reg52.h>
#include<Segment.h>
int get(int num, char n) 
{
    switch (n) {
    case 1:
        return num % 10; // 返回个位
    case 2:
        return (num / 10) % 10; // 返回十位
    case 3:
        return (num / 100) % 10; // 返回百位
    case 4:
        return (num / 1000) % 10; // 返回千位
    default:
        return 0; // 默认返回0
    }
}

void delay(int num) {
    while (num--) {
        int i;
        for (i = 0; i < 123; i++);
    }
}

unsigned char leddata[] = {
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

void open(char a) {
    SegmentG1 = 1;
    SegmentG2 = 1;
    SegmentG3 = 1;
    SegmentG4 = 1;

    switch (a) {
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

void change(int num) {
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
