#include <reg52.h>
#include <intrins.h>

#define led P2

typedef unsigned char u8;
typedef unsigned int un16;
void delay(un16 i){
	while(i--);
}
void main()
{
	u8 i=0;
	led = 0xfe;
	delay(50000);
	while(1){
		for(i=0;i<7;i++){//Ñ­»·×óÒÆ
			led=_crol_(led,1);
			delay(50000);
		}
		for(i=0;i<7;i++){//Ñ­»·ÓÒÒÆ
			led=_cror_(led,1);
			delay(50000);
		}

	}
}