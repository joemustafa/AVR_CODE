#ifndef LCD1602_H
#define LCD1602_H

#include "D:\ICC_H\CmmICC.H"

#define DELAY()		{NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();}

//uint8 bdata bdat;
//sbit bdat0=bdat^0;
//sbit bdat1=bdat^1;
//sbit bdat2=bdat^2;
//sbit bdat3=bdat^3;
//sbit bdat4=bdat^4;
//sbit bdat5=bdat^5;
//sbit bdat6=bdat^6;
//sbit bdat7=bdat^7;

uint8 bdat;
#define bdat0 (bdat&0x01)
#define bdat1 (bdat&0x02)
#define bdat2 (bdat&0x04)
#define bdat3 (bdat&0x08)
#define bdat4 (bdat&0x10)
#define bdat5 (bdat&0x20)
#define bdat6 (bdat&0x40)
#define bdat7 (bdat&0x80)

#define CGRAM0 0x00
#define CGRAM1 0x01
#define CGRAM2 0x02
#define CGRAM3 0x03
#define CGRAM4 0x04
#define CGRAM5 0x05
#define CGRAM6 0x06
#define CGRAM7 0x07

#define TRUE	1
#define FALSE	0
bool LCD1602Err = FALSE;

void busy(void)
{
	uint16 busyCounter=0;
	bool busySta;		
	IN_BF;
	SET_D4;
	SET_D5;
	SET_D6;
	SET_D7;
	DELAY();
	CLR_RS;
	DELAY();
	SET_RW;
	DELAY();

	do
	{
		SET_E;   
		DELAY();

		busySta=(bool)GET_BF;  
		CLR_E;
		DELAY(); 

		SET_D4;
		SET_D5;
		SET_D6;
		SET_D7;
		DELAY();
		SET_E;   
		DELAY();

		CLR_E;   
		DELAY();
		if(busyCounter==1000)
		{
			LCD1602Err=TRUE;	
			return ;		
		}
		busyCounter++;
	}
	while(busySta);

	LCD1602Err=FALSE;
	CLR_E;
	OUT_BF;
}

void write(bool flag,uint8 dat)	//flag=0:command,flag=1:data
{  
	bdat=dat;
	busy();
	if(flag)
		SET_RS;
	else
		CLR_RS;
	DELAY();
	CLR_RW;
	DELAY();
	if(bdat4)
		SET_D4;
	else
		CLR_D4;
	if(bdat5)
		SET_D5;
	else
		CLR_D5;
	if(bdat6)
		SET_D6;
	else
		CLR_D6;
	if(bdat7)
		SET_D7;
	else
		CLR_D7;
	DELAY();
	SET_E;	
	DELAY();
	CLR_E;
	DELAY(); 

	if(bdat0)
		SET_D4;
	else
		CLR_D4;
	if(bdat1)
		SET_D5;
	else
		CLR_D5;
	if(bdat2)
		SET_D6;
	else
		CLR_D6;
	if(bdat3)
		SET_D7;
	else
		CLR_D7;
	DELAY();
	SET_E;		
	DELAY();
	CLR_E;
	DELAY();
}

//void read(uint8 adr)
//{	
//}

void LCD1602_setCGRAM(uint8 adr,const uint8 buf[8])
{	
	uint8 i;
	write(0,0x40+adr*8);
	for(i=0;i<8;i++)
		write(1,buf[i]);

	//while(*buf)
		//write(1,*buf++);
}

//----	function  ------  1  --------  0  ----LcdWordPos--
//		dispEn		|   Enable	|  Disable	|	bit2
//		cursorEn	|   Enable	|  Disable	|	bit1
//		blinkEn		|   Enable	|  Disable	|	bit0
//------------------------------------------------------
//		isACinc		|	INC_AC  |  DEC_AC	|	bit1
//		shiftEn		|   Enable	|  Disable	|	bit0
//------------------------------------------------------
void LCD1602_setCmd(uint8  *str)
{
	static bool dispEn  =0;
	static bool cursorEn=0;
	static bool blinkEn =0;
	static bool shiftEn =0;
	static bool isACinc =0;
	
	if(!strcmp(str,"CLR_SCR"))			//clear screen
		write(0,0x01);

	else if(!strcmp(str,"GO_HOME"))		//set AC go home
		write(0,0x02);
/*--------------------------------------------------
isACinc & shiftEn 共用一个命令设置
--------------------------------------------------*/
	else if(!strcmp(str,"INC_AC"))		//set AC as inc mode
	{
		isACinc=1;
		if(shiftEn)
			write(0,0x07);
		else 
			write(0,0x06);
	}		
	else if(!strcmp(str,"DEC_AC"))		//set AC as dec mode
	{	
		isACinc=0;
		if(shiftEn)
			write(0,0x05);
		else
			write(0,0x04);
	}		
	else if(!strcmp(str,"EN_SHIFT"))	//enable shift
	{
		shiftEn=1;
		if(isACinc)
			write(0,0x07);
		else
			write(0,0x06);
	}
	else if(!strcmp(str,"DIS_SHIFT"))	//disable shift
	{
		shiftEn=0;
		if(isACinc)
			write(0,0x05);
		else
			write(0,0x04);
	}	

	else if(!strcmp(str,"OPEN_LCD"))	//opern lcd
	{
		dispEn=1;
		if(cursorEn)
			if(blinkEn)
				write(0,0x0F);
			else
				write(0,0x0E);
		else
			if(blinkEn)
				write(0,0x0D);
			else
				write(0,0x0C);
	}		
	else if(!strcmp(str,"CLOSE_LCD"))	//close lcd
	{
		dispEn=0;
		if(cursorEn)
			if(blinkEn)
				write(0,0x0B);
			else
				write(0,0x0A);
		else
			if(blinkEn)
				write(0,0x09);
			else
				write(0,0x08);
	}	
	else if(!strcmp(str,"OPEN_CURS"))	//open cursor	
	{
		cursorEn=1;
		if(dispEn)
			if(blinkEn)
				write(0,0x0F);
			else
				write(0,0x0E);
		else
			if(blinkEn)
				write(0,0x0B);
			else
				write(0,0x0A);
	}	
	else if(!strcmp(str,"CLOSE_CURS"))	//close cursor
	{
		cursorEn=0;
		if(dispEn)
			if(blinkEn)
				write(0,0x0D);
			else
				write(0,0x0C);
		else
			if(blinkEn)
				write(0,0x09);
			else
				write(0,0x08);
	}
	else if(!strcmp(str,"EN_BLINK"))	//enable blink cursor
	{
		blinkEn=1;
		if(dispEn)
			if(cursorEn)
				write(0,0x0F);
			else
				write(0,0x0D);
		else
			if(cursorEn)
				write(0,0x0B);
			else
				write(0,0x09);
	}
	else if(!strcmp(str,"DIS_BLINK"))	//disable blink cursor
	{
		blinkEn=0;
		if(dispEn)
			if(cursorEn)
				write(0,0x0E);
			else
				write(0,0x0C);
		else
			if(cursorEn)
				write(0,0x0A);
			else
				write(0,0x08);
	}

	else if(!strcmp(str,"RIGHT_SCR"))	//right shift screen
		write(0,0x1c);
	else if(!strcmp(str,"LEFT_SCR"))	//left shift screen
		write(0,0x18);
	else if(!strcmp(str,"RIGHT_CURS"))	//right shift cursor
		write(0,0x14);
	else if(!strcmp(str,"LEFT_CURS"))	//left shift cursor
		write(0,0x10);
}

void LCD1602_init(void)
{   
	OUT_RS;
	OUT_RW;
	OUT_E;
	OUT_D4;
	OUT_D5;
	OUT_D6;
	OUT_D7;
	delay50ms(1);

	CLR_D7;
	CLR_D6;
	SET_D5;
	SET_D4;
	DELAY();
	CLR_RS;
	DELAY();
	CLR_RW;         				

	SET_E;
	DELAY();
	CLR_E;
	delay50us(200);		
	SET_E;
	DELAY();
	CLR_E;
	delay50us(200);	
	SET_E;
	DELAY();
	CLR_E;
	delay50us(200);	
	
	CLR_D7;
	CLR_D6;
	SET_D5;
	CLR_D4;
	DELAY();
	SET_E;
	DELAY();
	CLR_E;		       			
	DELAY();
	LCD1602_setCmd("OPEN_LCD");
	LCD1602_setCmd("CLR_SCR");
	LCD1602_setCmd("INC_AC");
	//LCD1602_setCmd("OPEN_CURS");
	//LCD1602_setCmd("GO_HOME");
}

#define LCD1602_setAC(adr) write(0,adr)

void LCD1602_putc(uint8 adr,uint8 ch)
{
	write(0,adr);
	write(1,ch);
}

void LCD1602_puts(uint8 startAdr,uint8 *str)
{
	/*
	while(*str)
	{
		LCD1602_putc(addr++,*str++);
	}
	*/
	//LCD1602_setCmd("AC++");
	write(0,startAdr);
	while(*str)
		write(1,*str++);
}

//for example:dat=123,length=6,output 000123 
void LCD1602_putd0(uint8 endAdr,uint32 dat,uint8 length)
{
	sint8 i;
	speaData(dat,length);
	//LCD1602_setCmd("AC++");
	write(0,endAdr-length+1);
	for(i=length-1;i>=0;i--)
		write(1,dataElem[i]+0x30);
}

void LCD1602_putd(uint8 endAdr,uint32 dat,uint8 length)
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
	//LCD1602_setCmd("AC++");
	if(length>effectLen)
	{
		write(0,endAdr-length+1);
		for(i=length-effectLen-1;i>=0;i--)
			write(1,' ');
	}
	for(i=effectLen-1;i>=0;i--)
	{
		if(i==0||dataElem[i])
		{
			write(0,endAdr-i);
			for(;i>=0;i--)
				write(1,dataElem[i]+0x30);
		}
	}
}

//void LCD1602_sprintf(uint8 startAdr,uint32 dat,uint8 length)
//{
//	/* clear the display area first here! */
//	//LCD1602_puts(addr,"      ");
//	sprintf(t,"%luok",dat);
//	//LCD1602_setCmd("AC++");
//	LCD1602_puts(addr,t);
//}

#endif



