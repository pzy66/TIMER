sfr ISP_DATA = 0XE2;    //定义ISP-IAP操作时的数据寄存器
sfr ISP_ADDRH = 0XE3;    //定义ISP-IAP操作地址寄存器低位
sfr ISP_ADDRL = 0XE4;    //定义ISP-IAP操作地址寄存器高位
sfr ISP_CMD = 0XE5;    //定义ISP-IAP命令寄存器
sfr ISP_TRIG = 0XE6;    //定义ISP-IAP命令触发寄存器
sfr ISP_CONTR = 0XE7;    //定义ISP-IAP命令寄存器

void store(int location, int a);
int read(int location);