/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_at45dbxxx_port.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313 (ICCAVR --> GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/
#ifndef _WS_AT45DBXXX_PORT_H_
#define _WS_AT45DBXXX_PORT_H_
#include <avr/io.h>
#include <ws_macro.h>

/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)
#define CLR_SS_AT45DB() cbi(PORTB,0)
#define SET_SS_AT45DB() sbi(PORTB,0)
void spiInitAt45db(void)
{
	DDRB|=0x07;
	PORTB&=0xF8;
	SPCR=0x50;
	SPSR=0x01;
}

/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define CLR_SS_AT45DB() cbi(PORTB,4)
#define SET_SS_AT45DB() sbi(PORTB,4)
void spiInitAt45db(void)
{
	DDRB|=0xF0;
	SPCR=0x50;
	SPSR=0x01;
}
/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define CLR_SS_AT45DB() cbi(PORTB,2)
#define SET_SS_AT45DB() sbi(PORTB,2)
void spiInitAt45db(void)
{
	DDRB|=0x3C;
	SPCR=0x50;
	SPSR=0x01;
}
/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define CLR_SS_AT45DB() cbi(PORTB,0)
#define SET_SS_AT45DB() sbi(PORTB,0)
void spiInitAt45db(void)
{
	DDRB|=0x0F;
	SPCR=0x50;
	SPSR=0x01;
}

/*Hardware Environment£ºDVK501 && M162+ EX*/
#elif defined(_DVK501_M162_EX_)
#define CLR_SS_AT45DB() cbi(PORTB,4)
#define SET_SS_AT45DB() sbi(PORTB,4)
void spiInitAt45db(void)
{
	DDRB|=0xF0;
	SPCR=0x50;
	SPSR=0x01;
}

#else
  #warning "AT45DBXXX interface undefined."
#endif

#include <ws_at45dbxxx.h>

#endif /*_WS_AT45DBXXX_PORT_H_*/
