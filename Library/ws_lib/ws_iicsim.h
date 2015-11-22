/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_iicsim.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313  (ICCAVR --> GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#ifndef _WS_IICSIM_H_
#define _WS_IICSIM_H_

//读写定义
#define READ 1
#define WRITE 0

//有无act
#define ACT 1
#define nACT 0

/* I2C Config */
#define I2C_ERR			0
#define I2C_CRR			1

void iicStart()
{
	SCL_OUT();
	SCL_CLR();
	SDA_OUT();
	SDA_SET();
	SCL_SET();
	SDA_CLR();
	SCL_CLR();
}

void iicStop()
{
	SCL_OUT();
	SCL_CLR();
	SDA_OUT();
	SDA_CLR();
	SCL_SET();
	SDA_SET();
	SCL_CLR();
}

void iicSendChar(uint8_t wrDAdr)	
{
	uint8_t I2C_n;
	SDA_OUT();
	for(I2C_n=0;I2C_n<=7;I2C_n++)
	{
		if(wrDAdr&0x80) {SDA_SET();}
		else {SDA_CLR();}	
		SCL_SET();
		SCL_CLR();
		wrDAdr<<=1;
	}
	SDA_IN();
	SDA_SET();
	SCL_SET();
	while(SDA_PIN){};
	SCL_CLR();
}

uint8_t iicGetChar(uint8_t bAct)
{
	uint8_t n;
	uint8_t rdDAdr=0;
	SDA_IN();
	SDA_SET();
	for(n=0;n<=7;n++)
	{
	 	rdDAdr<<=1;
		SCL_SET();
		if(SDA_PIN)	rdDAdr|=0x01;
		SCL_CLR();
		
	}
	SDA_OUT();
	if(bAct) {SDA_CLR();}
	else {SDA_SET();}
	SCL_SET();
	SCL_CLR();
	return(rdDAdr);
}

uint8_t iicReadBusy(uint8_t wrDAdr)	
{
	uint8_t n;
	iicStart();
	for(n=0;n<=7;n++)
	{
		if(wrDAdr&0x80) {SDA_SET();}
		else {SDA_CLR();}
		SCL_SET();
		SCL_CLR();
		wrDAdr<<=1;
	}
	SDA_IN();
	SDA_SET();
	SCL_SET();
	if(SDA_PIN)wrDAdr=1;
	else wrDAdr=0;
	SCL_CLR();	
	return(wrDAdr);
}

void iicWByte(uint8_t wrDAdr,uint8_t wordAdr,uint8_t dat)
{
	iicStart(); 
	iicSendChar(wrDAdr); 
	iicSendChar(wordAdr); 
	iicSendChar(dat); 
	iicStop();
}

void iicWPage(uint8_t wrDAdr,uint8_t wordAdr,uint8_t *pWrDat)
{
	uint8_t n;
	iicStart();
	iicSendChar(wrDAdr);
	iicSendChar(wordAdr); 
	for(n=0;n<=15;n++) 
		iicSendChar(*(pWrDat+n));
	iicStop();
}

uint8_t iicRByte(uint8_t wrDAdr,uint8_t wordAdr)
{
	iicStart();
	iicSendChar(wrDAdr); 
	iicSendChar(wordAdr); 
	wrDAdr|=0x01; 
	iicStart();
	iicSendChar(wrDAdr);
	wrDAdr=iicGetChar(ACT);	
	iicStop();
	return(wrDAdr); 
}

void iicRPage(uint8_t wrDAdr,uint8_t wordAdr,uint8_t *pRdDat,uint8_t num)
{
	uint8_t stack_num=0;
	iicStart();
	iicSendChar(wrDAdr); 
	iicSendChar(wordAdr); 
	wrDAdr|=0x01; 
	iicStart();
	iicSendChar(wrDAdr); 
	while(--num)
	{
		*(pRdDat+stack_num)=iicGetChar(ACT);
		stack_num++;
	}
	*(pRdDat+stack_num)=iicGetChar(nACT);
	iicStop();
}

#endif /*_WS_IICSIM_H_*/
