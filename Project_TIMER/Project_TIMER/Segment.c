#include <reg52.h>
#include "Segment.h"
#include "Initial.h"
#include "analyze.h"

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

void open_segment(unsigned char seg) {
    SegmentG1 = 1;
    SegmentG2 = 1;
    SegmentG3 = 1;
    SegmentG4 = 1;

    switch (seg) {
    case 0: SegmentG1 = 0; break;
    case 1: SegmentG2 = 0; break;
    case 2: SegmentG3 = 0; break;
    case 3: SegmentG4 = 0; break;
    default: break;
    }
}

// 显示一个数码管的值
void display_digit(unsigned char position, unsigned char value) {
    P0 = leddata[value];
    open_segment(position);
    delay(1);
}

// 显示时间
void display_time(int sec_count) {
    unsigned char hour_high, hour_low, min_high, min_low;
    unsigned char ana_hour_val, ana_min_val;
  
    ana_hour_val = ana_hour(sec_count);
    ana_min_val = ana_min(sec_count);

    hour_high = get(ana_hour_val, 2);
    hour_low = get(ana_hour_val, 1);
    min_high = get(ana_min_val, 2);
    min_low = get(ana_min_val, 1);

    display_digit('3', hour_high);
    display_digit('2', hour_low);
    display_digit('1', min_high);
    display_digit('0', min_low);
}
