#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int un16;

//74HC573锁存器
//OE=1 开始工作--1脚
//vcc--20脚 
//GND--10脚
//LE=1 正常--11脚
//LE=0 锁存--11脚

#define smg P0 //使用P0口对74HC573进行控制



u8 code smgduan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void delay(un16 i){
	while(i--);
}

void main()
{

	u8 i=0;

	while(1){
		for(i=0;i<16;i++){
			smg=smgduan[i];//显示在8各中的最后一个数码管，单独的那个要smg=~smgduan[i]
			delay(50000);
		}
	}
	
}