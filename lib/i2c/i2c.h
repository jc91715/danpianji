#ifndef _I2C_H
#define _I2C_H
#include <reg52.h>

sbit SDA=P2^0;
sbit SCL=P2^1;

void I2cStart();
void I2cStop();
unsigned char I2cSendByte(unsigned char dat);
unsigned char I2cReadByte();
#endif