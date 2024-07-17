#pragma once

sbit SegmentG1 = P2 ^ 3;    //¾§Ìå¹Ü
sbit SegmentG2 = P2 ^ 2;
sbit SegmentG3 = P2 ^ 1;
sbit SegmentG4 = P2 ^ 0;

void change(int num);