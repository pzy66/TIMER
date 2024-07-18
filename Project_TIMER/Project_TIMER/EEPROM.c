#include <reg52.h>
#include "EEPROM.h"

static void IAPTrigger();
static void IAPDisable();

static void IAPTrigger()
{
	ISP_TRIG = 0x46;          //对ISP-IAP命令触发寄存器写入触发命令0x46
	ISP_TRIG = 0xB9;          //对ISP-IAP命令触发寄存器写入触发命令0xB9
}

static void IAPDisable()
{
	ISP_CONTR = 0x00;          //禁用IAP读写EEPROM
	ISP_CMD = 0x00;          //无IAP操作
	ISP_TRIG = 0x00;          //关闭IAP功能
}

unsigned char IAPByteRead(unsigned int addr)
{
	unsigned char dat;        //定义数据缓存变量
	ISP_CONTR = 0x81;         //打开IAP功能，允许编程改变Flash，设置Flash操作等待时间
	ISP_CMD = 0x01;         //允许对"Data Flash/EEPROM区"进行字节读取

	ISP_ADDRL = addr;         //IAP操作地址寄存器低位
	ISP_ADDRH = addr >> 8;    //IAP操作地址寄存器高位

	IAPTrigger();             //触发IAP功能
	dat = ISP_DATA;           //将需要读出的数据放进缓存变量
	IAPDisable();             //禁用IAP功能
	return dat;               //将读取到的数据作为返回值
}

void IAPSectorErase(unsigned int addr)
{
	ISP_CONTR = 0x81;           //打开IAP功能，允许编程改变Flash，设置Flash操作等待时间
	ISP_CMD = 0x03;           //允许对"Data Flash/EEPROM区"进行扇区擦除

	ISP_ADDRL = addr;           //写入IAP操作地址寄存器低位
	ISP_ADDRH = addr >> 8;      //写入IAP操作地址寄存器高位

	IAPTrigger();               //触发IAP功能
	IAPDisable();               //禁用IAP功能
}

void IAPByteWrite(unsigned int addr, unsigned char dat)
{
	ISP_CONTR = 0x81;          //打开IAP功能，允许编程改变Flash，设置Flash操作等待时间
	ISP_CMD = 0x02;          //允许对"Data Flash/EEPROM区"进行字节写入

	ISP_ADDRL = addr;          //IAP操作地址寄存器低位
	ISP_ADDRH = addr >> 8;     //IAP操作地址寄存器高位
	ISP_DATA = dat;            //将需要写入的数据放进ISP_DATA

	IAPTrigger();              //触发IAP功能
	IAPDisable();              //禁用IAP功能
}

void store(int location, int a) {//记忆变量   注意！！存储区域起码要间隔1个，比如说location一个是0x2000，另一个起码是0x2002
	EA = 0; // 禁用全局中断(为了不让中断打断数据的存储）
	IAPSectorErase(location); // 先擦除EEPROM存储区域
	IAPByteWrite(location, a & 0xFF); // 写入低字节
	IAPByteWrite(location + 1, (a >> 8) & 0xFF); // 写入高字节
	EA = 1; // 使能全局中断
}

int read(int location) {		//读取变量 返回值是int类型的
	int a;
	EA = 0; // 禁用全局中断
	a = IAPByteRead(location) | (IAPByteRead(location + 1) << 8);
	EA = 1; // 使能全局中断
	return a;
}