#include <reg52.h>
#include <intrins.h>
#include "i2c.h"
typedef unsigned char u8;
typedef unsigned int u16;


sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;
sbit k4=P3^3;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
u8 num=0,num0=0,disp[4],disp0[4];
void delay(u16 i){
	while(i--);
}

void Keypros()
{
		if(k1==0)
		{
			delay(1000);
			if(k1==0)
			{
				At24c02Write(1,num);
			}
			while(!k1);
		}
		if(k2==0)
		{
			delay(1000);
			if(k2==0)
			{
				num0=At24c02Read(1);
			}
			while(!k2);
		}
		if(k3==0)
		{
			delay(1000);
			if(k3==0)
			{
				num++;
				if(num>255){
					num=0;
				}
			}
			while(!k3);
		}
		if(k4==0)
		{
			delay(1000);
			if(k4==0)
			{
				num=0;
			}
			while(!k4);
		}
}
void datapros()
{
	disp[0]=smgduan[num/1000];
	disp[1]=smgduan[num%1000/100];
	disp[2]=smgduan[num%1000%100/10];
	disp[3]=smgduan[num%1000%100%10];
}
void datapros0()
{
	disp0[0]=smgduan[num0/1000];
	disp0[1]=smgduan[num0%1000/100];
	disp0[2]=smgduan[num0%1000%100/10];
	disp0[3]=smgduan[num0%1000%100%10];
}
void DigDispaly(){
	u8 i;
	for(i=0;i<7;i++){
		switch(i){
			case 0:
				LSA=0;LSB=0;LSC=0;
				break;
			
			case 1:
				LSA=0;LSB=0;LSC=1;
				break;
			
			case 2:
				LSA=0;LSB=1;LSC=0;
				break;
			
			case 3:
				LSA=0;LSB=1;LSC=1;
				break;
				case 4:
				LSA=1;LSB=0;LSC=0;
				break;
			
			case 5:
				LSA=1;LSB=0;LSC=1;
				break;
			case 6:
				LSA=1;LSB=1;LSC=0;
				break;
			case 7:
				LSA=1;LSB=1;LSC=1;
				break;
			
		}
		if(i>3){
			P0=disp0[7-i];
		}else{
			P0=disp[3-i];
		}
	
		delay(100);
		P0 = 0x00;
	}
}
void main(){

	while(1){
		Keypros();
		datapros();
		datapros0();
		DigDispaly();
	
	}
}

