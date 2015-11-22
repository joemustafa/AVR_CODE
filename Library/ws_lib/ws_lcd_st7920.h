/*
*========================================================================================================
*
* File                : ws_lcd_st7920.h
* Hardware Environment:	
* Build Environment   : AVR Studio 4.16 + Winavr 20090313
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*========================================================================================================
*/

#ifndef _WS_LCD_ST7920_H
#define _WS_LCD_ST7920_H
#include <util/delay.h>
#include <string.h>
#include <stdarg.h>

#define LCD_DELAY() _delay_us(75)

void spiSendChar(uint8_t send_char)
{
	SPDR = send_char;
	while (!(SPSR & (1<<SPIF)));
}

void sendCodeST7920(uint8_t code)
{
	spiSendChar(0xF8);
	spiSendChar(code & 0xF0);
	spiSendChar((code<<4));
	LCD_DELAY();
}

void sendDataST7920(uint8_t data)
{
	spiSendChar(0xFA);
	spiSendChar(data & 0xF0);
	spiSendChar((data<<4));
	LCD_DELAY();
}

void refreshLCD(const uint8_t *lcd_stack)
{
	uint8_t addr;
	sendCodeST7920(0x02);	
	for(addr=0;addr < 16;addr++)
	{
		sendDataST7920(*(lcd_stack + addr));
	}
	for(addr=32;addr < 48;addr++)
	{
		sendDataST7920(*(lcd_stack + addr));
	}
	for(addr=16;addr < 32;addr++)
	{
		sendDataST7920(*(lcd_stack + addr));
	}
	
	for(addr=48;addr < 64;addr++)
	{
		sendDataST7920(*(lcd_stack + addr));
	}
}

void decToAscii(uint8_t* str,uint16_t dec,uint8_t width)
{
	while(width)
	{
		switch(width)
		{
			case 5:
			{
				*str = (dec/10000+'0');
				dec%=10000;
				break;
			}			
			case 4:
			{
				*str = (dec/1000+'0');
				dec%=1000;
				break;
			}
			case 3:
			{
				*str = (dec/100+'0');
				dec%=100;
				break;
			}
			case 2:
			{
				*str = (dec/10+'0');
				dec%=10;
				break;
			}
			case 1:
			{
				*str = (dec+'0');
				break;
			}
			default: *str = '0';
		}
		width--;
		str++;
	}
}

void hexToAscii(uint8_t* str,uint16_t hex,uint8_t width)
{
	uint16_t tmp;
	while(width)
	{
		switch(width)
		{		
			case 4:
			{
				tmp=(hex>>12);
				if(tmp>9) *str = tmp+('A'-10);
				else *str = tmp+'0';
				break;
			}
			case 3:
			{
				tmp=(hex>>8)&0x000F;
				if(tmp>9) *str = tmp+('A'-10);
				else *str = tmp+'0';
				break;
			}
			case 2:
			{
				tmp=(hex>>4)&0x000F;
				if(tmp>9) *str = tmp+('A'-10);
				else *str = tmp+'0';
				break;
			}
			case 1:
			{
				tmp=hex&0x000F;
				if(tmp>9) *str = tmp+('A'-10);
				else *str = tmp+'0';
				break;
			}
			default: *str = '0';
		}
		width--;
		str++;
	}
}

void showLine(const uint8_t x,const uint8_t y,uint8_t* lcd_stack,char * str,...)
{
	uint8_t coordinate = 16*y + x;
	va_list marker;
	va_start(marker,str); /* Initialize variable arguments. */ 
	while(*str!='\0')
	{
		if(coordinate>64) break;	

		if(*str == '\\')
		{
			str++;
			lcd_stack[coordinate] = *str;
		}
		else if(*str == '%')
		{
			str++;
			if (*str=='d'||*str=='D')
			{
				str++;
				decToAscii(&lcd_stack[coordinate],va_arg(marker,uint16_t),(*str-'0'));
				coordinate+=(*str-'0'-1);
			}
			else if(*str=='c'||*str=='C')
			{
				lcd_stack[coordinate] = va_arg(marker,uint16_t);
			}
			else if(*str=='x'||*str=='X')
			{
				str++;
				hexToAscii(&lcd_stack[coordinate],va_arg(marker,uint16_t),(*str-'0'));
				coordinate+=(*str-'0'-1);
			}
		}
		else
		{
			lcd_stack[coordinate] = *str;
		}
		str++;
		coordinate++;
	}
	va_end( marker ); /* Reset variable arguments. */ 
}

#endif /*_WS_LCD_ST7920_H*/
