/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_onewire_port.h
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

#ifndef WS_ONEWIRE_PORT_H
#define WS_ONEWIRE_PORT_H
#include <avr/io.h>
#include <ws_macro.h>

/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)	
#define SET_DQ() sbi(PORTB,5)
#define CLR_DQ() cbi(PORTB,5)
#define OUT_DQ() sbi(DDRB,5)
#define IN_DQ() cbi(DDRB,5)
#define GET_DQ() gbi(PINB,5)

/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define SET_DQ() sbi(PORTB,2)
#define CLR_DQ() cbi(PORTB,2)
#define OUT_DQ() sbi(DDRB,2)
#define IN_DQ() cbi(DDRB,2)
#define GET_DQ() gbi(PINB,2)

/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define SET_DQ() sbi(PORTB,0)
#define CLR_DQ() cbi(PORTB,0)
#define OUT_DQ() sbi(DDRB,0)
#define IN_DQ() cbi(DDRB,0)
#define GET_DQ() gbi(PINB,0)

/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define SET_DQ() sbi(PORTB,5)
#define CLR_DQ() cbi(PORTB,5)
#define OUT_DQ() sbi(DDRB,5)
#define IN_DQ() cbi(DDRB,5)
#define GET_DQ() gbi(PINB,5)

/*Hardware Environment£ºDVK501 && M162+ EX*/
#elif defined(_DVK501_M162_EX_)
#define SET_DQ() sbi(PORTB,2)
#define CLR_DQ() cbi(PORTB,2)
#define OUT_DQ() sbi(DDRB,2)
#define IN_DQ() cbi(DDRB,2)
#define GET_DQ() gbi(PINB,2)
#else
  #warning "Onewire interface undefined."
#endif

#include <ws_onewire.h>

#endif /*WS_ONEWIRE_PORT_H*/
