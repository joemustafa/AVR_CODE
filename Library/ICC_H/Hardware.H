#ifndef Hardware_H
#define Hardware_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <macros.h>
#include <eeprom.h>
//#include <wdt.h>

/* TWI configs */
#if NO_INCLUDE_I2C_H
;
#else
#include "D:\ICC_H\I2C.H"	
#endif

/* hard configs */
#ifndef flash
	#define flash	const
#endif

#ifndef code
	#define code	const
#endif

#ifndef NOP
	#define NOP()	asm("nop")
#endif

/* io configs */
#define sbi(io,bit)		(  io |=  (1<<bit) )	//example: sbi(PORTA,0);sbi(DDRA,0);
#define cbi(io,bit)		(  io &= ~(1<<bit) )	//example: cbi(PORTA,0);cbi(DDRA,0);
#define gbi(pin ,bit)	( pin &   (1<<bit) )	//example: gbi(PINA,0);

/* interrupt configs */
#define DIS_INT  asm("sei")
#define EN_INT   asm("cli")

/* wdt configs */
#define WDT()    asm("wdr")

/* bit operation */
//#ifndef BIT
//#define BIT(x)	( 1<<(x) )
//#endif

/* USART configs for 4 Mhz crystal */
//#define BAUD9600			25
//#define BAUD19000			12
//#define UART_TRAN_ON()	UCR |=  0x08
//#define UART_TRAN_OFF()	UCR &= ~0x08
//#define UART_RCV_ON()		UCR |=  0x10
//#define UART_RCV_OFF()	UCR &= ~0x10

void delay50us(sint16 t)
{
    uint8 j;		
    for(;t>0;t--)			
        for(j=0;j<70;j++)	
            ;
}

void delay50ms(sint16 t)
{
	uint16 i; 
	for(;t>0;t--)
		for(i=0;i<52642;i++)
			; 
}


void delayus(uint16 t)
{
	uint16 i;
	for(i=0;i<t;i++)
		{
			//asm("NOP\n");
			//asm("NOP\n");
		}
}

#endif