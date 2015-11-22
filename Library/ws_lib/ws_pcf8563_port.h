/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_pcf8563_port.h
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

#ifndef _WS_PCF8563_PORT_H_
#define _WS_PCF8563_PORT_H_

#include <avr/io.h>

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define converseIntToHex(dec)	( ( ((dec)>>4) *10 ) + ((dec)%16) )
#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )
#define converseHexToInt(hex)	( ( ((hex)/10) <<4 ) + ((hex)%10) )


#define WR_DADR		0xA2	//write device-address
#define RD_DADR		0xA3	//read device-address



#include <ws_pcf8563.h>

#endif /*_WS_PCF8563_PORT_H_*/
