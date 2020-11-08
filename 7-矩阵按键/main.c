#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int u16;

//38译码器的输入 控制显示在第一个数码管，相当于使用一个数码管
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


#define GPIO_KEY P1 // 矩阵按键控制
#define GPIO_DIG P0 //按下第几个键显示按下的数字

u8 KeyValue;//存放读取的键值

u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void delay(u16 i){
	while(i--);
}

void KeyDown(){
	
	u8 a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f){//说明有按键按下
	
		delay(1000);//消抖
		if(GPIO_KEY!=0x0f){
				GPIO_KEY=0x0f;
				
				switch(GPIO_KEY){
					case 0x07:KeyValue=0;break;//说明第一列有按键按下	
					case 0x0b:KeyValue=1;break;//说明第二列有按键按下	
					case 0x0d:KeyValue=2;break;//说明第三列有按键按下	
					case 0x0e:KeyValue=3;break;//说明第四列有按键按下	
				}
				GPIO_KEY=0xf0;
			
				switch(GPIO_KEY){
					case 0x70:KeyValue=KeyValue;break;//说明第一行有按键按下	
					case 0xb0:KeyValue=KeyValue+4;break;//说明第二行有按键按下	
					case 0xd0:KeyValue=KeyValue+8;break;//说明第三行有按键按下	
					case 0xe0:KeyValue=KeyValue+12;break;//说明第四行有按键按下	
				}
				while((a<50)&&(GPIO_KEY!=0xf0)){//避免按键一直按
					delay(1000);
					a++;
				}
				
				
		}
	}
}

void main()
{

	//点亮最后一个数码管即第0个数码管
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