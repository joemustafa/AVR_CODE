/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_ps2port.h
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
#ifndef _WS_PS2PORT_H_
#define _WS_PS2PORT_H_

#include <ws_macro.h>

/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)	
#define SET_PS2_DA()	sbi(PORTD,3)
#define CLR_PS2_DA()	cbi(PORTD,3)
#define IN_PS2_DA()		cbi(DDRD,3)
#define OUT_PS2_DA()	sbi(DDRD,3)
#define GET_PS2_DA()	gbi(PIND,3)

#define SET_PS2_CL()	sbi(PORTD,2)
#define CLR_PS2_CL()	cbi(PORTD,2)
#define IN_PS2_CL()		cbi(DDRD,2)
#define OUT_PS2_CL()	sbi(DDRD,2)
#define GET_PS2_CL() 	gbi(PIND,2)

#define PS2_INT_VECTOR	INT2_vect

/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define SET_PS2_DA()	sbi(PORTD,3)
#define CLR_PS2_DA()	cbi(PORTD,3)
#define IN_PS2_DA()		cbi(DDRD,3)
#define OUT_PS2_DA()	sbi(DDRD,3)
#define GET_PS2_DA()  	gbi(PIND,3)

#define SET_PS2_CL()	sbi(PORTD,2)
#define CLR_PS2_CL()	cbi(PORTD,2)
#define IN_PS2_CL()		cbi(DDRD,2)
#define OUT_PS2_CL()	sbi(DDRD,2)
#define GET_PS2_CL()  	gbi(PIND,2)

#define PS2_INT_VECTOR	INT0_vect
void ps2IntInit(void)
{
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=0x40;
MCUCR=0x02;
MCUCSR=0x00;
GIFR=0x40;
}
/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define SET_PS2_DA()	sbi(PORTD,3)
#define CLR_PS2_DA()	cbi(PORTD,3)
#define IN_PS2_DA()		cbi(DDRD,3)
#define OUT_PS2_DA()	sbi(DDRD,3)
#define GET_PS2_DA()  	gbi(PIND,3)

#define SET_PS2_CL()	sbi(PORTD,2)
#define CLR_PS2_CL()	cbi(PORTD,2)
#define IN_PS2_CL()		cbi(DDRD,2)
#define OUT_PS2_CL()	sbi(DDRD,2)
#define GET_PS2_CL()  	gbi(PIND,2)

#define PS2_INT_VECTOR	INT0_vect
void ps2IntInit(void)
{
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x02;
EIMSK=0x01;
EIFR=0x01;
PCICR=0x00;
}

/*Hardware Environment£ºDVK501 && M69+ EX*/
#elif defined(_DVK501_M169_EX_)
#define SET_PS2_DA()	sbi(PORTD,0)
#define CLR_PS2_DA()	cbi(PORTD,0)
#define IN_PS2_DA()		cbi(DDRD,0)
#define OUT_PS2_DA()	sbi(DDRD,0)
#define GET_PS2_DA()  	gbi(PIND,0)

#define SET_PS2_CL()	sbi(PORTD,1)
#define CLR_PS2_CL()	cbi(PORTD,1)
#define IN_PS2_CL()		cbi(DDRD,1)
#define OUT_PS2_CL()	sbi(DDRD,1)
#define GET_PS2_CL()  	gbi(PIND,1)

#define PS2_INT_VECTOR	INT0_vect
void ps2IntInit(void)
{
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
EICRA=0x02;
EIMSK=0x01;
EIFR=0x01;
}

/*Hardware Environment£ºDVK501 && M62+ EX*/
#elif defined(_DVK501_M162_EX_)
#define SET_PS2_DA()	sbi(PORTD,3)
#define CLR_PS2_DA()	cbi(PORTD,3)
#define IN_PS2_DA()		cbi(DDRD,3)
#define OUT_PS2_DA()	sbi(DDRD,3)
#define GET_PS2_DA()  	gbi(PIND,3)

#define SET_PS2_CL()	sbi(PORTD,2)
#define CLR_PS2_CL()	cbi(PORTD,2)
#define IN_PS2_CL()		cbi(DDRD,2)
#define OUT_PS2_CL()	sbi(DDRD,2)
#define GET_PS2_CL()  	gbi(PIND,2)

#define PS2_INT_VECTOR	INT0_vect
void ps2IntInit(void)
{
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
GICR|=0x40;
MCUCR=0x02;
EMCUCR=0x00;
GIFR=0x40;
}
#else
  #warning "PS2 interface undefined."
#endif

#include <ws_ps2.h>

#endif /*_WS_PS2PORT_H_*/
