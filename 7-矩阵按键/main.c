#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

//38������������ ������ʾ�ڵ�һ������ܣ��൱��ʹ��һ�������
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


#define GPIO_KEY P1 // ���󰴼�����
#define GPIO_DIG P0 //���µڼ�������ʾ���µ�����

u8 KeyValue;//��Ŷ�ȡ�ļ�ֵ

u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void delay(u16 i){
	while(i--);
}

void KeyDown(){
	
	u8 a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f){//˵���а�������
	
		delay(1000);//����
		if(GPIO_KEY!=0x0f){
				GPIO_KEY=0x0f;
				
				switch(GPIO_KEY){
					case 0x07:KeyValue=0;break;//˵����һ���а�������	
					case 0x0b:KeyValue=1;break;//˵���ڶ����а�������	
					case 0x0d:KeyValue=2;break;//˵���������а�������	
					case 0x0e:KeyValue=3;break;//˵���������а�������	
				}
				GPIO_KEY=0xf0;
			
				switch(GPIO_KEY){
					case 0x70:KeyValue=KeyValue;break;//˵����һ���а�������	
					case 0xb0:KeyValue=KeyValue+4;break;//˵���ڶ����а�������	
					case 0xd0:KeyValue=KeyValue+8;break;//˵���������а�������	
					case 0xe0:KeyValue=KeyValue+12;break;//˵���������а�������	
				}
				while((a<50)&&(GPIO_KEY!=0xf0)){//���ⰴ��һֱ��
					delay(1000);
					a++;
				}
				
				
		}
	}
}

void main()
{

	//�������һ������ܼ���0�������
	LSA=0;
	LSB=0;
	LSC=1;
	
	//GPIO_DIG=smgduan[0];
	while(1){
		KeyDown();
		GPIO_DIG=smgduan[KeyValue];
		if(KeyValue>10){
			if(KeyValue>15){
				KeyValue=0;
			}
			LSD=0;
		}else{
			LSD=1;
		}
			
	}
	
}