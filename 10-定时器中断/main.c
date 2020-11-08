#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED=P2^0;

void delay(u16 i){
	while(i--);
}

void TimeroInit(){

	TMOD|=0x01;//��ʱ��0������ʽ1��GATA=0
	
	//  �������� 1/12/12=1us   1000*1=1ms ����1000����ʱ1ms  TH0 TL0��ʼֵ 65536-1000=FC18
	TH0=0xFC;//��ʱ1ms TH0��ʼֵ
	TL0=0x18;//��ʱ1ms TL0��ʼֵ
	
	ET0=1;
	EA=1;
	TR0=1;//tcon ���ƶ�ʱ���������
}


void main(){
	TimeroInit();
	while(1);
}
void Time0() interrupt 1
{
	static u16 i;
	TH0=0xFC;//��ʱ1ms TH0��ʼֵ
	TL0=0x18;//��ʱ1ms TL0��ʼֵ
	i++;
	if(i==1000){//�ж�1000�� 1��
		i=0;
		LED=~LED;
	}
}