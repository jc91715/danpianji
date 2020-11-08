#include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int un16;



sbit led=P2^0;
sbit k1=P3^1;


void delay(un16 i){
	while(i--);
}

void keypros(){
	if(k1==0){//按下的时候k1是低电平
		delay(1000);
		if(k1==0){
			 led=~led;
		}
		while(!k1);
	}
}

void main()
{
	while(1){
		keypros();
	}
	
}