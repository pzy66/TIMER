sfr ISP_DATA = 0XE2;    //����ISP-IAP����ʱ�����ݼĴ���
sfr ISP_ADDRH = 0XE3;    //����ISP-IAP������ַ�Ĵ�����λ
sfr ISP_ADDRL = 0XE4;    //����ISP-IAP������ַ�Ĵ�����λ
sfr ISP_CMD = 0XE5;    //����ISP-IAP����Ĵ���
sfr ISP_TRIG = 0XE6;    //����ISP-IAP������Ĵ���
sfr ISP_CONTR = 0XE7;    //����ISP-IAP����Ĵ���

void store(int location, int a);
int read(int location);