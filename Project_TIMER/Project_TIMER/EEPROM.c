#include <reg52.h>
#include "EEPROM.h"

static void IAPTrigger();
static void IAPDisable();

static void IAPTrigger()
{
	ISP_TRIG = 0x46;          //��ISP-IAP������Ĵ���д�봥������0x46
	ISP_TRIG = 0xB9;          //��ISP-IAP������Ĵ���д�봥������0xB9
}

static void IAPDisable()
{
	ISP_CONTR = 0x00;          //����IAP��дEEPROM
	ISP_CMD = 0x00;          //��IAP����
	ISP_TRIG = 0x00;          //�ر�IAP����
}

unsigned char IAPByteRead(unsigned int addr)
{
	unsigned char dat;        //�������ݻ������
	ISP_CONTR = 0x81;         //��IAP���ܣ������̸ı�Flash������Flash�����ȴ�ʱ��
	ISP_CMD = 0x01;         //�����"Data Flash/EEPROM��"�����ֽڶ�ȡ

	ISP_ADDRL = addr;         //IAP������ַ�Ĵ�����λ
	ISP_ADDRH = addr >> 8;    //IAP������ַ�Ĵ�����λ

	IAPTrigger();             //����IAP����
	dat = ISP_DATA;           //����Ҫ���������ݷŽ��������
	IAPDisable();             //����IAP����
	return dat;               //����ȡ����������Ϊ����ֵ
}

void IAPSectorErase(unsigned int addr)
{
	ISP_CONTR = 0x81;           //��IAP���ܣ������̸ı�Flash������Flash�����ȴ�ʱ��
	ISP_CMD = 0x03;           //�����"Data Flash/EEPROM��"������������

	ISP_ADDRL = addr;           //д��IAP������ַ�Ĵ�����λ
	ISP_ADDRH = addr >> 8;      //д��IAP������ַ�Ĵ�����λ

	IAPTrigger();               //����IAP����
	IAPDisable();               //����IAP����
}

void IAPByteWrite(unsigned int addr, unsigned char dat)
{
	ISP_CONTR = 0x81;          //��IAP���ܣ������̸ı�Flash������Flash�����ȴ�ʱ��
	ISP_CMD = 0x02;          //�����"Data Flash/EEPROM��"�����ֽ�д��

	ISP_ADDRL = addr;          //IAP������ַ�Ĵ�����λ
	ISP_ADDRH = addr >> 8;     //IAP������ַ�Ĵ�����λ
	ISP_DATA = dat;            //����Ҫд������ݷŽ�ISP_DATA

	IAPTrigger();              //����IAP����
	IAPDisable();              //����IAP����
}

void store(int location, int a) {//�������   ע�⣡���洢��������Ҫ���1��������˵locationһ����0x2000����һ��������0x2002
	EA = 0; // ����ȫ���ж�(Ϊ�˲����жϴ�����ݵĴ洢��
	IAPSectorErase(location); // �Ȳ���EEPROM�洢����
	IAPByteWrite(location, a & 0xFF); // д����ֽ�
	IAPByteWrite(location + 1, (a >> 8) & 0xFF); // д����ֽ�
	EA = 1; // ʹ��ȫ���ж�
}

int read(int location) {		//��ȡ���� ����ֵ��int���͵�
	int a;
	EA = 0; // ����ȫ���ж�
	a = IAPByteRead(location) | (IAPByteRead(location + 1) << 8);
	EA = 1; // ʹ��ȫ���ж�
	return a;
}