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
void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();//开始信号
	I2cSendByte(0xa0);//器件地址  1010 000 0发送000器件地址 0 发送
	I2cSendByte(addr);//首地址
	I2cSendByte(dat);//数据
	I2cStop();
}

//先去找要读的地址，再去读数据
unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();//
	I2cSendByte(0xa0);//
	I2cSendByte(addr);
	I2cStart();//
	I2cSendByte(0xa1);//
	num = I2cReadByte();
	I2cStop();
	
	return  num;
}
	


