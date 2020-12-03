#include "i2c.h"

void Delay10us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}

//��ʼ�ź�
void I2cStart()
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();
	SDA=0;
	Delay10us();
	SCL=0;
	Delay10us();
}

//��ֹ�ź�
void I2cStop()
{
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();
	SDA=1;
	Delay10us();

}

unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;
	
	for(a=0;a<8;a++)
	{
		SDA=dat>>7;//�������λ
		dat=dat<<1; 
		//���ϸı�ʱ���źţ����ܷ�������
		Delay10us();
		SCL=1;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	
	//����8λ���ݣ����߿��г����ȴ�Ӧ��SDAΪ0�����Զ�Ϊ0��Ӧ��ɹ�������1
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();
	
	while(SDA){//һ��ʱ���ûӦ��ɹ�����ΪӦ��ʧ��
		b++;
		if(b>200){
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
	return 1;
}

unsigned char I2cReadByte()
{
		unsigned char a=0,dat=0;
	
		for(a=0;a<8;a++)
		{
			SCL=1;//�����ȶ�
			Delay10us();
			dat<<=1;
			dat|=SDA;//�Ƚ������λ
			Delay10us();
			SCL=0;
			Delay10us();
		}
		return dat;
}