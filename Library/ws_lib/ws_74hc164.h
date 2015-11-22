/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_74hc164.h
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

#ifndef _WS_74HC164_H_
#define _WS_74HC164_H_
#include <stdint.h>

void hc164SetDat(uint8_t dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		HC164_CLR_CLK;
		if(dat&0x80)
			HC164_SET_DATA;
		else
			HC164_CLR_DATA;
		HC164_SET_CLK;
		dat = dat<<1;
	}
}

void hc164Init(void)
{
	HC164_OUT_DATA;
	HC164_OUT_CLK;
}
#endif /*_74HC164_H_*/
