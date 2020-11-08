#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED=P2^0;

void delay(u16 i){
	while(i--);
}

void UsartInit(){
	
	//T1作为波特率发生器
	TMOD=0x20;//定时器工作在方式2 TH1和TL1相等 用8为计数
	TH1=0xF3;//初始值根据软件来计算
	TL1=0xF3;//
	
	PCON=0x80;//波特率加倍
	TR1=1;//打开定时器
	
	SCON=0x50;
	ES=1;//开中断
	EA=1;//
	
}

void main(){
	UsartInit();
	while(1);
}

void Usart() interrupt 4
{
	u8 receiveData;
	receiveData = SBUF;
	RI=0;
	SBUF=receiveData;
	while(!TI);
	TI=0;
	
}
