#include "temp.h"


void Delay1ms(uint y)
{
	uint x;
	for(;y>0;y--)
	{
		for(x=110;x>0;x--);
	}
}

void delay642us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=71;b>0;b--)
        for(a=3;a>0;a--);
}

//��ʼ�� �¶ȴ����� 
uchar Ds18b20Init(){
	uchar i=0;
	DSPORT=0;
	delay642us();
	DSPORT=1;
	while(DSPORT)
	{
		i++;
		Delay1ms(1);
		if(i>5)
		{
			return 0;
		}
	}
	return 1;
}

//���͸��¶ȴ�����
void Ds18b20WriteByte(uchar dat)
{
	uchar i,j;
	for(j=0;j<9;j++)
	{
		DSPORT=0;
		i++;
		DSPORT=dat&0x01;
		i=6;
		while(i--);//68us
		DSPORT=1;
		dat>>=1;
	}
}


//��ȡ����
uchar Ds18b20ReadByte()
{
	uint i,j;
	uchar bi,byte;
	for(j=0;j<9;j++)
	{
		DSPORT=0;
		i++;
		DSPORT=1;
		i++;
		i++;
		bi=DSPORT;
		byte=(byte>>1)|(bi<<7);
		i=4;
		while(i--);
	}
	return byte;
}

//��ʼ��
void Ds18b20ChangeTemp()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0x44);
}

//�����¶ȶ�ȡ����
void Ds18b20ReadTempCom()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);
	Ds18b20WriteByte(0xbe);
}
//��ȡ�¶�
int Ds18b20ReadTemp()
{
	int temp=0;
	uchar tmh,tml;
	Ds18b20ChangeTemp();
	Ds18b20ReadTempCom();
	tml=Ds18b20ReadByte();//�ȶ����ֽ�
	tmh=Ds18b20ReadByte();
	temp=tmh;
	temp<<=8;//���16λ�ĸ߰�λ
	temp|=tml;
	return temp;
}
