#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED=P2^0;
sbit k32=P3^2;
sbit k33=P3^3;
void delay(u16 i){
	while(i--);
}

void Init0Init(){
	IT0=1;//下降沿有效
	EX0=1;
	EA=1;
}

void Init1Init(){
	IT1=1;//下降沿有效
	EX1=1;
	EA=1;
}

void main()
{

	Init0Init();
	Init1Init();
	while(1){
	
	}
	
}

void Int0() interrupt 0
{
	delay(1000);
	
	if(k32==0){
		LED=~LED;
	}
}
void Int1() interrupt 2
{
	delay(1000);
	
	if(k33==0){
		LED=~LED;
	}
}