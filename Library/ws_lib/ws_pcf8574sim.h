/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_pcf8574sim.h
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
#ifndef _WS_PCF8574SIM_H_
#define _WS_PCF8574SIM_H_
void writePcf8574(uint8_t tmp)
{
	iicStart();
	iicSendChar(0x40);
	iicSendChar(tmp);
	iicStop();
}

uint8_t readPcf8574(void)
{
	uint8_t tmp;
	iicStart();
	iicSendChar(0x41);
	tmp=iicGetChar(nACT);
	iicStop();		
	return(tmp);
}
		
#endif /*_WS_PCF8574SIM_H_*/
