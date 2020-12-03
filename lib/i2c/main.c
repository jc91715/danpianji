#include <reg52.h>
#include "i2c.h"

typedef unsigned char u8;
typedef unsigned int u16;
sbit k1=P3^0;
sbit k2=P3^1;
u8 num=0,k2Toggle=0;
u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};


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
	u8 num0;
	I2cStart();//
	I2cSendByte(0xa0);//
	I2cSendByte(addr);
	I2cStart();//
	I2cSendByte(0xa1);//
	num0 = I2cReadByte();
	I2cStop();
	
	return  num0;
}
void delay(u16 i){
	while(i--);
}



void main(){

	while(1){
		
		//eeprom
		At24c02Write(1,num);
		delay(100);
		num=At24c02Read(1);
		
		P0=smgduan[num];
		
		delay(100000);
		num++;
		if(num>=9){
			num=0;
		}
	}
}
