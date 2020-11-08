#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;
void delay(u16 i){
	while(i--);
}

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

//ʱ����
u8 Hour,Minute,Second;

//�ⲿ�ж�
sbit k32=P3^2;//ѡ��ʱ��
sbit k33=P3^3;//��1

u8 IF_PRESS;//�Ƿ񰴹�����
u8 TIME_LOCATION;//�༭��һλ0 �༭ʱ��1�༭�֣�2������
u8 RESET_TIME_INIT=10,RESET_TIME=10;//��20����û�в�����ȡ����˸


//�ⲿ�ж�0��ʼ��
void Init0Init(){
	IT0=1;//�½�����Ч
	EX0=1;
	EA=1;
}
//�ⲿ�ж�2��ʼ��
void Init1Init(){
	IT1=1;//�½�����Ч
	EX1=1;
	EA=1;
}
//��ʱ����ʼ��
void TimeroInit(){
	TMOD|=0x01;//��ʱ��0������ʽ1��GATA=0
	
	//  �������� 1/12/12=1us   1000*1=1ms ����1000����ʱ1ms  TH0 TL0��ʼֵ 65536-1000=FC18
	TH0=0xFC;//��ʱ1ms TH0��ʼֵ
	TL0=0x18;//��ʱ1ms TL0��ʼֵ
	
	ET0=1;
	EA=1;
	TR0=1;//tcon ���ƶ�ʱ���������
}


void DidDispaly();//��̬ɨ���������ʾ����
void DispalyHourMinuteSecond(u8 i);//һ���滻��������ϵ�����

void main()
{

	Init0Init();
	Init1Init();
	TimeroInit();
	while(1){
		DidDispaly();
	}
	
}
void Int0() interrupt 0
{
	delay(1000);
	
	if(k32==0){
		if(IF_PRESS){//��һ�ΰ���Ĭ�ϱ༭ʱ
			TIME_LOCATION++;
		}
		IF_PRESS=1;
		if(TIME_LOCATION==3){
			TIME_LOCATION=0;
		}
		RESET_TIME=RESET_TIME_INIT;
	}
}
void Int1() interrupt 2
{
	delay(7000);
	
	if(k33==0){
		if(IF_PRESS==1){
			 switch(TIME_LOCATION){
				 case 0://�༭ʱ
					 Hour++;
					 if(Hour==24){
							Hour=0;
					 }
					 break; 
				 case 1://�༭��
					 Minute++;
					 if(Minute==60){
							Minute=0;
					 }
					 break;			 
				 case 2://�༭��
					 Second=0;
					 break;			 
			 
			 }
			 RESET_TIME=RESET_TIME_INIT;
		}
	}
}
void Time0() interrupt 1
{
	static u16 i;
	TH0=0xFC;//��ʱ1ms TH0��ʼֵ
	TL0=0x18;//��ʱ1ms TL0��ʼֵ
	i++;
	if(i==1000){//�ж�1000�� 1��
		i=0;
		Second++;
		RESET_TIME--;
		if(!RESET_TIME){
			IF_PRESS=0;
			TIME_LOCATION=0;
		}
		if(Second==60){
			Second=0;
			Minute++;
			if(Minute==60){
				Minute=0;
				Hour++;
				if(Hour==24){
					Hour=0;
				}
			}
		}
		
	}
}

void DidDispaly(){
	u8 i;
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
		DispalyHourMinuteSecond(i);//��ʾ��Ӧ������
		delay(100);
		smg = 0x00;
	}
}

void DispalyHourMinuteSecond(u8 i){
	switch(i){
			case 0://ʱ��ʮλ
				if(IF_PRESS&&TIME_LOCATION==0){
					if(Second%3!=0){
						smg = smgduan[Hour/10];
					}else{
						smg = 0x00;
					}
				}else{
					smg = smgduan[Hour/10];
				}
				
				break;		
			case 1://ʱ�ĸ�λ
				if(IF_PRESS&&TIME_LOCATION==0){
					if(Second%3!=0){
							smg = smgduan[Hour%10];
					}else{
						smg = 0x00;
					}
				}else{
						smg = smgduan[Hour%10];
				}
				break;		
			case 2://�����˸
				if(Second%2==1){
					smg = 0x40;
				}else{
					smg = 0x00;
				}
				break;		
			case 3://�ֵ�ʮλ
				if(IF_PRESS&&TIME_LOCATION==1){
					if(Second%3!=0){
							smg = smgduan[Minute/10];
					}else{
						smg = 0x00;
					}
				}else{
						smg = smgduan[Minute/10];
				}
				break;		
			case 4://�ֵĸ�λ
				if(IF_PRESS&&TIME_LOCATION==1){
					if(Second%3!=0){
							smg = smgduan[Minute%10];
					}else{
						smg = 0x00;
					}
				}else{
						smg = smgduan[Minute%10];
				}
				break;		
			case 5://����˸
				if(Second%2==1){
					smg = 0x40;
				}else{
					smg = 0x00;
				}
				break;
			case 6://���ʮλ
				if(IF_PRESS&&TIME_LOCATION==2){
					if(Second%2==1){
								smg = smgduan[Second/10];
					}else{
						smg = 0x00;
					}
				}else{
							smg = smgduan[Second/10];
				}
			
				break;
			case 7://��ĸ�λ
				if(IF_PRESS&&TIME_LOCATION==2){
					if(Second%2==1){
						smg = smgduan[Second%10];
					}else{
						smg = 0x00;
					}
				}else{
						smg = smgduan[Second%10];
				}
			
				break;
		}
}

