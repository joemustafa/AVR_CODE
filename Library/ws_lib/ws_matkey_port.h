/*
*========================================================================================================
*
* File                : ws_matkey_port.h
* Hardware Environment:	
* Build Environment   : AVR Studio 4.16 + Winavr 20090313
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*========================================================================================================
*/
#ifndef _WS_MATKEY_PORT_H_
#define _WS_MATKEY_PORT_H_

#include <avr/io.h>

/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)
#define MATKEY_PORT PORTA
#define MATKEY_PIN PINA
#define MATKEY_DDR DDRA


/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define MATKEY_PORT PORTA
#define MATKEY_PIN PINA
#define MATKEY_DDR DDRA

/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define MATKEY_PORT PORTD
#define MATKEY_PIN PIND
#define MATKEY_DDR DDRD
/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define MATKEY_PORT PORTA
#define MATKEY_PIN PINA
#define MATKEY_DDR DDRA

/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M162_EX_)
#define MATKEY_PORT PORTA
#define MATKEY_PIN PINA
#define MATKEY_DDR DDRA
#else
  #warning "matkey interface undefined."
#endif

#include <ws_matkey.h>

#endif /*_WS_MATKEY_PORT_H_*/
