/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_pcf8563sim.h
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

#ifndef _WS_PCF8563SIM_H_
#define _WS_PCF8563SIM_H_

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define converseIntToHex(dec)	( ( ((dec)>>4) *10 ) + ((dec)%16) )
#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )
#define converseHexToInt(hex)	( ( ((hex)/10) <<4 ) + ((hex)%10) )


#define WR_DADR		0xA2	//write device-address
#define RD_DADR		0xA3	//read device-address

#define CTRL_BUF1		0x00
#define CTRL_BUF2		0x01

#define SECOND_DATA_BUF	0x02
#define MINUTE_DATA_BUF	0x03
#define HOUR_DATA_BUF	0x04

#define DAY_DATA_BUF	0x05
#define WEEK_DATA_BUF	0x06
#define MONTH_DATA_BUF	0x07
#define YEAR_DATA_BUF	0x08

#define MINUTE_AE_BUF	0x09
#define HOUR_AE_BUF		0x0A
#define DAY_AE_BUF		0x0B
#define WEEK_AE_BUF		0x0C

#define CLK_FRQ_BUF		0x0D
#define TIMER_CTRL_BUF	0x0E
#define COUNT_VAL_BUF	0x0F

#define PCF8563_ERR		0
#define PCF8563_CRR		1


void PCF8563_getTime(uint8_t *buf)
{
	iicRPage(WR_DADR,SECOND_DATA_BUF,buf,3);
	buf[0]=buf[0]&0x7f;		//get second data
	buf[1]=buf[1]&0x7f;		//get minute data
	buf[2]=buf[2]&0x3f;		//get hour data

	buf[0]=changeHexToInt(buf[0]);
	buf[1]=changeHexToInt(buf[1]);
	buf[2]=changeHexToInt(buf[2]);
}

void PCF8563_setTime(uint8_t hour,uint8_t minute,uint8_t second)
{
	hour=changeIntToHex(hour);		
	minute=changeIntToHex(minute);
	second=changeIntToHex(second);

	iicWByte(WR_DADR,HOUR_DATA_BUF,hour);
	iicWByte(WR_DADR,MINUTE_DATA_BUF,minute);
	iicWByte(WR_DADR,SECOND_DATA_BUF,second);
}

void PCF8563_init()
{
	iicWByte(WR_DADR,CTRL_BUF1,0x00);			//basic setting
	iicWByte(WR_DADR,CTRL_BUF2,0x12);			//alarm enable
}

#endif /*_WS_PCF8563SIM_H_*/
