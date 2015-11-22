/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_pcf8574.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313 (ICCAVR-->GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#ifndef _WS_PCF8574_H_
#define _WS_PCF8574_H_

void Write_PCF8574(uint8_t data)
{
	if( I2C_Start()==0 )
		return ;	
	if( I2C_SendWrDAdr_(0x40)==0 )
		return ;
	if( I2C_SendDat(data)==0 )
		return ;
	I2C_Stop();

}

uint8_t Read_PCF8574(void)
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
#endif /*_WS_PCF8574_H_*/
