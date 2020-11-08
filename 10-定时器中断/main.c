#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED=P2^0;

void delay(u16 i){
	while(i--);
}

void TimeroInit(){

	TMOD|=0x01;//定时器0工作方式1。GATA=0
	
	//  机器周期 1/12/12=1us   1000*1=1ms 计数1000次用时1ms  TH0 TL0初始值 65536-1000=FC18
	TH0=0xFC;//定时1ms TH0初始值
	TL0=0x18;//定时1ms TL0初始值
	
	ET0=1;
	EA=1;
	TR0=1;//tcon 控制定时或计数开启
}


void main(){
	TimeroInit();
	while(1);
}
void Time0() interrupt 1
{
	static u16 i;
	TH0=0xFC;//定时1ms TH0初始值
	TL0=0x18;//定时1ms TL0初始值
	i++;
	if(i==1000){//中断1000次 1秒
		i=0;
		LED=~LED;
	}
}