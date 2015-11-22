/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_ds2401.h
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
#ifndef _WS_DS2401_H_
#define _WS_DS2401_H_
#include <ws_onewire_port.h>

void getDs2401Number(uint8_t* tmp)
{
	uint8_t t1;
	resetOnewire();	
	wOnewire(0x33);	
	for(t1=0;t1<8;t1++)
	{
		*(tmp+t1)=rOnewire();
	}
}

#endif /*_WS_DS2401_H_*/
