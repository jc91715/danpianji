#include <reg52.h>
#include "temp.h"

typedef unsigned char u8;
typedef unsigned int u16;



sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
u8 num=0,num0=0,DisplayData[8];
void delay(u16 i){
	while(i--);
}


void datapros(int temp)
{
	float tp;
	if(temp<0){
		DisplayData[0]=0x40;
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;
	}else{
		DisplayData[0]=0x00;
	}
	
	DisplayData[1]=smgduan[temp/10000];
	DisplayData[2]=smgduan[temp%10000/1000];
	DisplayData[3]=smgduan[temp%10000%1000/100]|0x80;
	DisplayData[4]=smgduan[temp%100/10];
	DisplayData[4]=smgduan[temp%100%10];
}

void DigDispaly(){
	u8 i;
	for(i=0;i<6;i++){
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
		P0=DisplayData[5-i];
	
		delay(100);
		P0 = 0x00;
	}
}
void main(){
	int temp;
	while(1){
		temp = Ds18b20ReadTemp();
		datapros(temp);
		DigDispaly();
	
	}
}

