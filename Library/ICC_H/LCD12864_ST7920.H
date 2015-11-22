/*--------------------------------------------------------------------
接口定义：

LCD12864_ST7920			ATmega16
1.GND		--------	GND
2.VCC		--------	VCC
3.V0		--------	V0
4.RS(CS)	--------	VCC
5.R/W(SID)	--------	MOSI/PB5
6.E(SCLK)	--------	SCK/PB7
7.D0		--------	NC
8.D1		--------	NC
9.D2		--------	NC
10.D3		--------	NC
11.D4		--------	NC
12.D5		--------	NC
13.D6		--------	NC
14.D7		--------	NC
15.PSB		--------	GND
16.NC		--------	NC
17.RST		--------	NC
18.NC		--------	NC
19.LED+		--------	VCC
20.LED-		--------	GND

--------------------------------------------------------------------*/

#ifndef LCD12864_ST7920_H
#define LCD12864_ST7920_H

#include "D:\ICC_H\CmmIcc.h"

void SPI_init()
{
	DDRB |= 0xB0;
	SPCR = 0x50;	//setup SPI
	SPSR = 0x01;	//setup SPI
	SEI();			
}

void lcd_wrByte(uint8 data)
{  
	SPDR = data;        
	while ((SPSR & 0x80) == 0);  
}

void lcd_wrCmd(uint8 HC,uint8 LC)
{
	lcd_wrByte(0xF8);
	lcd_wrByte(HC);	
	lcd_wrByte(LC);		
}

void lcd_wrDat(uint8 HD,uint8 LD)
{
	lcd_wrByte(0xFA);
	lcd_wrByte(HD);		
	lcd_wrByte(LD);		
} 

void lcd_set_xy(uint8 x,uint8 y) 
{
	uint8 adr;

	switch(x)
	{
	case 1: adr = 0x7F + y;
		break;		
	case 2: adr = 0x8F + y;
		break;		
	case 3: adr = 0x87 + y;
		break;		
	case 4: adr = 0x97 + y;
		break;		
	default:	;
	}
	lcd_wrCmd(adr&0xF0,(adr&0x0F)<<4);
}

void lcd_putc(uint8 x,uint8 y,uint8 ch)
{
	lcd_set_xy(x,y);
	delay50us(20); 
	lcd_wrDat(ch&0xF0,(ch&0x0F)<<4);
}

void lcd_putd0(uint8 x,uint8 y,uint32 dat,uint8 length)
{
	sint8 i;

	speaData(dat,length);
	lcd_set_xy(x,y);
	delay50us(40);
	for(i=length-1;i>=0;i--)
	{
		lcd_wrDat( (dataElem[i]+0x30)&0xF0 ,( (dataElem[i]+0x30)&0x0F )<<4 );
		delay50us(40); 
	}
}

void lcd_putd(uint8 x,uint8 y,uint32 dat,uint8 length)
{
	sint8 i;
	sint8 effectLen;

	if(dat>999999)
		effectLen=7;
	else if(dat>99999)
		effectLen=6;
	else if(dat>9999)
		effectLen=5;
	else if(dat>999)
		effectLen=4;
	else if(dat>99)
		effectLen=3;
	else if(dat>9)
		effectLen=2;
	else
		effectLen=1;
	speaData(dat,effectLen);

	lcd_set_xy(x,y);
	delay50us(40); 
	if(length>effectLen)
	{
		for(i=length-effectLen-1;i>=0;i--)
		{
			lcd_wrDat(' '&0xF0,(' '&0x0F)<<4);
			delay50us(40); 
		}
	}
	for(i=effectLen-1;i>=0;i--)
	{
		lcd_wrDat( (dataElem[i]+0x30)&0xF0 ,( (dataElem[i]+0x30)&0x0F )<<4 );
		delay50us(40);
	}
}

void lcd_puts(uint8 x,uint8 y,uint8 *str)
{ 
	lcd_set_xy(x,y);
	delay50us(20);   
	while(*str)
	{
		lcd_wrDat((*(str))&0xF0,((*(str))&0x0F)<<4);
		str++;
		delay50us(20);
	} 
}

void lcd_puts_(uint8 x,uint8 y,uint8 *str,uint8 dlyMs)
{ 
	lcd_set_xy(x,y);
	delay50us(20);   
	while(*str)
	{
		lcd_wrDat((*(str))&0xF0,((*(str))&0x0F)<<4);
		str++;
		delay50ms(dlyMs);
	} 
}

void lcd_clr()
{
	lcd_wrCmd(0x00,0x10);
	delay50us(200);
}

void lcd_init(void)
{
	SPI_init();	
	//OUT_LCD_CS;		
	//SET_LCD_CS;		
	delay50ms(1);
	lcd_wrCmd(0x30,0x30);	
	//lcd_wrCmd(0x00,0xF0);	
	lcd_wrCmd(0x00,0xC0);	
	lcd_wrCmd(0x00,0x10);	
	//lcd_wrCmd(0x10,0x00);	
	lcd_wrCmd(0x00,0x60);
	//lcd_wrCmd(0x00,0x70);	
	delay50ms(1);		
}

#endif