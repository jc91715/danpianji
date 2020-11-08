#include <reg52.h>

sbit led = P0^0;

typedef unsigned int un16;

void delay(un16 i){
	while(i--);
}
void main()
{
	while(1){
		led=!led;
		delay(50000);
	}
}