 #include <reg52.h>
#include <intrins.h>

typedef unsigned char u8;
typedef unsigned int un16;

sbit beep=P1^5;

void delay(un16 i){
	while(i--);
}
void main()
{
	
	while(1){
			beep = ~beep;
			delay(100);//改变延时时间可该改变声音大小
	}
}