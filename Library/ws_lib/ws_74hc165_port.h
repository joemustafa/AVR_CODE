/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_74hc165_port.h
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


#ifndef _WS_74HC165_PORT_H_
#define _WS_74HC165_PORT_H_
#include <avr/io.h>
#include <ws_macro.h>

/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)
#define HC165_IN_RXD	cbi(DDRE,0)	   
#define HC165_GET_RXD	gbi(PINE,0)

#define HC165_OUT_TXD  	sbi(DDRE,1)	   
#define HC165_SET_TXD 	sbi(PORTE,1)
#define HC165_CLR_TXD  	cbi(PORTE,1)

#define HC165_OUT_PL	sbi(DDRD,1)	  
#define HC165_SET_PL	sbi(PORTD,1)
#define HC165_CLR_PL	cbi(PORTD,1)


/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define HC165_IN_RXD	cbi(DDRD,0)	   
#define HC165_GET_RXD	gbi(PIND,0)

#define HC165_OUT_TXD  	sbi(DDRD,1)	   
#define HC165_SET_TXD 	sbi(PORTD,1)
#define HC165_CLR_TXD  	cbi(PORTD,1)

#define HC165_OUT_PL	sbi(DDRC,1)	  
#define HC165_SET_PL	sbi(PORTC,1)
#define HC165_CLR_PL	cbi(PORTC,1)
/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define HC165_IN_RXD	cbi(DDRD,0)	   
#define HC165_GET_RXD	gbi(PIND,0)

#define HC165_OUT_TXD  	sbi(DDRD,1)	  
#define HC165_SET_TXD 	sbi(PORTD,1)
#define HC165_CLR_TXD  	cbi(PORTD,1)

#define HC165_OUT_PL	sbi(DDRC,4)	   
#define HC165_SET_PL	sbi(PORTC,4)
#define HC165_CLR_PL	cbi(PORTC,4)

/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define HC165_IN_RXD	cbi(DDRE,0)	   
#define HC165_GET_RXD	gbi(PINE,0)

#define HC165_OUT_TXD  	sbi(DDRE,1)	  
#define HC165_SET_TXD 	sbi(PORTE,1)
#define HC165_CLR_TXD  	cbi(PORTE,1)

#define HC165_OUT_PL	sbi(DDRE,5)	  
#define HC165_SET_PL	sbi(PORTE,5)
#define HC165_CLR_PL	cbi(PORTE,5)

/*Hardware Environment£ºDVK501 && M162+ EX*/
#elif defined(_DVK501_M162_EX_)
#define HC165_IN_RXD	cbi(DDRD,0)	  
#define HC165_GET_RXD	gbi(PIND,0)

#define HC165_OUT_TXD  	sbi(DDRD,1)	  
#define HC165_SET_TXD 	sbi(PORTD,1)
#define HC165_CLR_TXD  	cbi(PORTD,1)

#define HC165_OUT_PL	sbi(DDRD,4)	   
#define HC165_SET_PL	sbi(PORTD,4)
#define HC165_CLR_PL	cbi(PORTD,4)
#else
  #warning "74HC164 interface undefined."
#endif

#include <ws_74hc165.h>
#endif /*_WS_74HC165_PORT_H_*/
