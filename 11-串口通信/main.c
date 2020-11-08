#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED=P2^0;

void delay(u16 i){
	while(i--);
}

void UsartInit(){
	
	//T1��Ϊ�����ʷ�����
	TMOD=0x20;//��ʱ�������ڷ�ʽ2 TH1��TL1��� ��8Ϊ����
	TH1=0xF3;//��ʼֵ�������������
	TL1=0xF3;//
	
	PCON=0x80;//�����ʼӱ�
	TR1=1;//�򿪶�ʱ��
	
	SCON=0x50;
	ES=1;//���ж�
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
