/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_ds18b20.h
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

#include <ws_onewire_port.h>

void convertDs18b20(void) 
{ 
    resetOnewire(); 
    wOnewire(0xcc); 
    wOnewire(0x44); 
} 

uint8_t readTemp(void) 
{ 
	uint8_t temp1,temp2;
	convertDs18b20();
    resetOnewire(); 
    wOnewire(0xcc); 
    wOnewire(0xbe); 	
    temp1=rOnewire(); 
    temp2=rOnewire(); 
	temp2=temp2<<4;
	temp1=temp1>>4;
	temp2|=temp1;

	return (temp2&0x7F);
}
