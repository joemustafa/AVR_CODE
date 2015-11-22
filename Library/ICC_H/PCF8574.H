#ifndef PCF8574_H
#define PCF8574_H
#include "D:\ICC_H\CmmICC.H"
#include "D:\ICC_H\I2C.H"

void Write_PCF8574(unsigned char data)
{
	if( I2C_Start()==0 )
		return ;	
	if( I2C_SendWrDAdr_(0x40)==0 )
		return ;
	if( I2C_SendDat(data)==0 )
		return ;
	I2C_Stop();
	delay50ms(1);					
}

unsigned char Read_PCF8574(void)
{
	if( I2C_Start()==0 )
		return 0;	
	if( I2C_SendWrDAdr_(0x40)==0 )
		return 0;
	if( I2C_Restart()==I2C_ERR )
		return I2C_ERR;
	if( I2C_SendRdDAdr(0x41)==I2C_ERR )
		return I2C_ERR;
	I2CRcvNckByte();I2CWaitAck();
	if( I2CChkAck()!=I2C_MR_DATA_NACK )
		return I2C_ERR;
	I2C_Stop();
	return TWDR;
}
#endif