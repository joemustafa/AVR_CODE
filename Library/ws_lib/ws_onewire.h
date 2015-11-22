/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_onewire.h
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

#ifndef _WS_ONEWIRE_H_
#define _WS_ONEWIRE_H_
#include <util/delay.h>

void resetOnewire(void) 
{
	OUT_DQ();
    CLR_DQ();
    _delay_us(750);
    SET_DQ();
	IN_DQ(); 
	while(GET_DQ());
	while(!(GET_DQ()));
	OUT_DQ();
}

uint8_t rOnewire(void)
{
    uint8_t data=0,i=0;
    for(i=0;i<8;i++)
    {
		data=data>>1;
		OUT_DQ();
        CLR_DQ();
        _delay_us(5);
		SET_DQ();
		_delay_us(15);
		IN_DQ();
        if(GET_DQ()) data|=0x80;
        else while(!(GET_DQ()));
		_delay_us(60);
		SET_DQ();
	}
	return(data);
}

void wOnewire(uint8_t data)
{
    uint8_t i=0;
	OUT_DQ();
    for(i=0;i<8;i++)
    {
        if(data&0x01)
		{
            CLR_DQ();
            _delay_us(5);
            SET_DQ();
            _delay_us(85); //65
		}
   	 	else
   	 	{
       		CLR_DQ(); 
        	_delay_us(90);  //65
        	SET_DQ();
        	_delay_us(5);
    	}
    	data=data>>1;
    }
}
#endif /*_WS_ONEWIRE_H_*/
