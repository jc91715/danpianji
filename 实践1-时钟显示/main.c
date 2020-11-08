#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;
void delay(u16 i){
	while(i--);
}

//74HC573锁存器
//OE=1 开始工作--1脚
//vcc--20脚 
//GND--10脚
//LE=1 正常--11脚
//LE=0 锁存--11脚

#define smg P0 //使用P0口对74HC573进行控制

//38译码器的输入
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

//时分秒
u8 Hour,Minute,Second;

//外部中断
sbit k32=P3^2;//选择时分
sbit k33=P3^3;//加1

u8 IF_PRESS;//是否按过按键
u8 TIME_LOCATION;//编辑哪一位0 编辑时，1编辑分，2重置秒
u8 RESET_TIME_INIT=10,RESET_TIME=10;//在20秒内没有操作，取消闪烁


//外部中断0初始化
void Init0Init(){
	IT0=1;//下降沿有效
	EX0=1;
	EA=1;
}
//外部中断2初始化
void Init1Init(){
	IT1=1;//下降沿有效
	EX1=1;
	EA=1;
}
//定时器初始化
void TimeroInit(){
	TMOD|=0x01;//定时器0工作方式1。GATA=0
	
	//  机器周期 1/12/12=1us   1000*1=1ms 计数1000次用时1ms  TH0 TL0初始值 65536-1000=FC18
	TH0=0xFC;//定时1ms TH0初始值
	TL0=0x18;//定时1ms TL0初始值
	
	ET0=1;
	EA=1;
	TR0=1;//tcon 控制定时或计数开启
}


void DidDispaly();//动态扫描数码管显示数字
void DispalyHourMinuteSecond(u8 i);//一秒替换掉数码管上的数字

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
		if(IF_PRESS){//第一次按键默认编辑时
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
				 case 0://编辑时
					 Hour++;
					 if(Hour==24){
							Hour=0;
					 }
					 break; 
				 case 1://编辑分
					 Minute++;
					 if(Minute==60){
							Minute=0;
					 }
					 break;			 
				 case 2://编辑秒
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
	TH0=0xFC;//定时1ms TH0初始值
	TL0=0x18;//定时1ms TL0初始值
	i++;
	if(i==1000){//中断1000次 1秒
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
		DispalyHourMinuteSecond(i);//显示对应的数字
		delay(100);
		smg = 0x00;
	}
}

void DispalyHourMinuteSecond(u8 i){
	switch(i){
			case 0://时的十位
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
			case 1://时的个位
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
			case 2://点的闪烁
				if(Second%2==1){
					smg = 0x40;
				}else{
					smg = 0x00;
				}
				break;		
			case 3://分的十位
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
			case 4://分的个位
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
			case 5://点闪烁
				if(Second%2==1){
					smg = 0x40;
				}else{
					smg = 0x00;
				}
				break;
			case 6://秒的十位
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
			case 7://秒的个位
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

