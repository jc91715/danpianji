#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int un16;

//74HC573������
//OE=1 ��ʼ����--1��
//vcc--20�� 
//GND--10��
//LE=1 ����--11��
//LE=0 ����--11��

#define smg P0 //ʹ��P0�ڶ�74HC573���п���

//38������������
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};


void delay(un16 i){
	while(i--);
}
void DidDispaly(){
	u8 i;
	u8 j;
	for(i=0;i<8;i++){
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
		smg = smgduan[i];//8���������ʾ01234567
		delay(100);
		smg = 0x00;
//		for(j=0;j<16;i++){//ÿ��������ʾ0-15
//			smg=smgduan[i];
//			delay(3125);
//		}
	
	}
}

void main()
{

	

	while(1){
		DidDispaly();
	}
	
}