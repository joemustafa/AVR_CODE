/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_74hc164_port.h
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

#ifndef _WS_74HC164_PORT_H_
#define _WS_74HC164_PORT_H_
#include <avr/io.h>
#include <ws_macro.h>


/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)

#define HC164_OUT_DATA	sbi(DDRB,6)	   
#define HC164_SET_DATA	sbi(PORTB,6)
#define HC164_CLR_DATA	cbi(PORTB,6)

#define HC164_OUT_CLK  	sbi(DDRB,7)	   
#define HC164_SET_CLK 	sbi(PORTB,7)
#define HC164_CLR_CLK  	cbi(PORTB,7)

/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define HC164_OUT_DATA	sbi(DDRB,1)	  
#define HC164_SET_DATA	sbi(PORTB,1)
#define HC164_CLR_DATA	cbi(PORTB,1)

#define HC164_OUT_CLK  	sbi(DDRB,0)	 
#define HC164_SET_CLK 	sbi(PORTB,0)
#define HC164_CLR_CLK  	cbi(PORTB,0)

/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define HC164_OUT_DATA	sbi(DDRC,2)	  
#define HC164_SET_DATA	sbi(PORTC,2)
#define HC164_CLR_DATA	cbi(PORTC,2)

#define HC164_OUT_CLK  	sbi(DDRC,3)	   
#define HC164_SET_CLK 	sbi(PORTC,3)
#define HC164_CLR_CLK  	cbi(PORTC,3)

/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define HC164_OUT_DATA	sbi(DDRB,6)	   
#define HC164_SET_DATA	sbi(PORTB,6)
#define HC164_CLR_DATA	cbi(PORTB,6)

#define HC164_OUT_CLK  	sbi(DDRB,7)	   
#define HC164_SET_CLK 	sbi(PORTB,7)
#define HC164_CLR_CLK  	cbi(PORTB,7)

/*Hardware Environment£ºDVK501 && M162+ EX*/
#elif defined(_DVK501_M162_EX_)
#define HC164_OUT_DATA	sbi(DDRB,1)	   
#define HC164_SET_DATA	sbi(PORTB,1)
#define HC164_CLR_DATA	cbi(PORTB,1)

#define HC164_OUT_CLK  	sbi(DDRB,0)	   
#define HC164_SET_CLK 	sbi(PORTB,0)
#define HC164_CLR_CLK  	cbi(PORTB,0)

#else
  #warning "74HC164 interface undefined."
#endif

#include <ws_74hc164.h>

#endif /*_74HC164_PORT_H_*/
