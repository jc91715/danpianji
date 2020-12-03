#include "i2c.h"

void Delay10us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}

//开始信号
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

//阻止信号
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
		SDA=dat>>7;//发送最高位
		dat=dat<<1; 
		//不断改变时钟信号，才能发送数据
		Delay10us();
		SCL=1;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	
	//发送8位数据，总线空闲出来等待应答，SDA为0（会自动为0）应答成功，返回1
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();
	
	while(SDA){//一段时间后还没应答成功，视为应答失败
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
			SCL=1;//数据稳定
			Delay10us();
			dat<<=1;
			dat|=SDA;//先接受最高位
			Delay10us();
			SCL=0;
			Delay10us();
		}
		return dat;
}