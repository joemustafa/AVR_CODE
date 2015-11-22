/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_74hc165.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/


#ifndef _WS_74HC165_H_
#define _WS_74HC165_H_
#include <stdint.h>

uint8_t hc165GetDat()
{
	uint8_t i,dat=0;
	HC165_CLR_PL;
	HC165_SET_PL;
	for(i=0;i<8;i++)
	{
		HC165_CLR_TXD;
		dat = dat<<1;
		if(HC165_GET_RXD)
			dat |= 0x01;
		HC165_SET_TXD;
	}
	return dat;
}

void hc165Init(void)
{
	HC165_OUT_PL;
	HC165_OUT_TXD;
	HC165_IN_RXD;
}
#endif /*_WS_74HC165_H_*/
