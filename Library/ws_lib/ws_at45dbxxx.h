/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_at45dbxxx.h
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
#ifndef _WS_AT45DBXXX_H_
#define _WS_AT45DBXXX_H_

#include <avr/io.h>

//==================================
void spi_transmit_byte(uint8_t Data)
{	
	SPDR=Data;								
    while(!(SPSR&0x80));
}
//============================================================
void write_buffer(uint16_t BufferOffset,uint8_t data)
{			
	CLR_SS_AT45DB();		
	spi_transmit_byte(0x84);//84			  						
	spi_transmit_byte(0xff);						
	spi_transmit_byte((uint8_t)(BufferOffset>>8));	
	spi_transmit_byte((uint8_t)BufferOffset);		
	spi_transmit_byte(data);		
	SET_SS_AT45DB();	
}
//================================================================
uint8_t read_buffer(uint16_t BufferOffset)
{		
    uint8_t temp;
	CLR_SS_AT45DB();
 	spi_transmit_byte(0xD4);//54
	spi_transmit_byte(0xff);
	spi_transmit_byte((uint8_t)(BufferOffset>>8));
	spi_transmit_byte((uint8_t)BufferOffset);
	spi_transmit_byte(0xff);
	spi_transmit_byte(0xff);
	temp=SPDR;	  
	SET_SS_AT45DB();
    return temp;								
}
#endif /*_WS_AT45DBXXX_H_*/
