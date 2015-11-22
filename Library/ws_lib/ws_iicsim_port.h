/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_iicsim_port.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313  (ICCAVR --> GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#ifndef _WS_IICSIM_PORT_H_
#define _WS_IICSIM_PORT_H_
#include <avr/io.h>
#include <ws_macro.h>
#include <util/delay.h>

/*Hardware Environment£ºDVK501 && M169+ EX*/
#if defined(_DVK501_M169_EX_)
#define DDR_IIC DDRE
#define PORT_IIC PORTE
#define PIN_IIC PINE
#define SDA_X 5
#define SCL_X 4
/*Hardware Environment£ºDVK501 && M162+ EX*/
#elif defined(_DVK501_M162_EX_)
#define DDR_IIC DDRD
#define PORT_IIC PORTD
#define PIN_IIC PIND
#define SDA_X 4
#define SCL_X 5
#else
  #warning "iic_sim interface undefined."
#endif

#define IIC_DELAY _delay_us(6)//asm("nop")

void SDA_IN()		{cbi(DDR_IIC,SDA_X);IIC_DELAY;}
void SDA_OUT()		{sbi(DDR_IIC,SDA_X);IIC_DELAY;}  
void SDA_SET()		{sbi(PORT_IIC,SDA_X);IIC_DELAY;}
void SDA_CLR()		{cbi(PORT_IIC,SDA_X);IIC_DELAY;}
#define SDA_PIN		(gbi(PIN_IIC,SDA_X))

void SCL_IN()		{cbi(DDR_IIC,SCL_X);IIC_DELAY;}
void SCL_OUT()		{sbi(DDR_IIC,SCL_X);IIC_DELAY;}  
void SCL_SET()		{sbi(PORT_IIC,SCL_X);IIC_DELAY;}
void SCL_CLR()		{cbi(PORT_IIC,SCL_X);IIC_DELAY;}
#define SCL_PIN		(gbi(PIN_IIC,SCL_X))

#include <ws_iicsim.h>
#endif /*_WS_IICSIM_PORT_H_*/
