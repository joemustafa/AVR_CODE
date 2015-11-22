/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_pcf8591sim.h
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

#ifndef _WS_PCF8591SIM_H_
#define _WS_PCF8591SIM_H_

#define WR_DADR		0x90	//write device-address 
#define RD_DADR		0x91	//read device-address

#define MODE0 	0x00	//Channel0 = AIN0;
						//Channel1 = AIN1;
						//Channel2 = AIN2;
						//Channel3 = AIN3;
#define MODE1 	0x10	//Channel0 = AIN3-AIN0;
						//Channel1 = AIN3-AIN1
						//Channel2 = AIN3-AIN2;
#define MODE2 	0x20	//Channel0 = AIN0;
						//Channel1 = AIN1;
						//Channel2 = AIN3-AIN2;
#define MODE3 	0x30	//Channel0 = AIN1-AIN0;
						//Channel1 = AIN3-AIN2;
#define CHNL0 	0		//Using Channel0
#define CHNL1 	1		//Using Channel1
#define CHNL2 	2		//Using Channel2
#define CHNL3 	3		//Using Channel3

#define DAouputEn	0x40	//0x50 or 0x60 or 0x70 is also ok!

uint8_t pcf8591GetAD(uint8_t mode,uint8_t chan)
{
	uint8_t PCF8591_num;
	iicStart();
	iicSendChar(WR_DADR); 
	iicSendChar(mode|chan); 
	iicStart();
	iicSendChar(RD_DADR); 
	PCF8591_num=iicGetChar(nACT);	
	iicStop();
	return(PCF8591_num); 
	
	
}

void pcf8591SetDA(uint8_t val)
{
	iicWByte(WR_DADR,DAouputEn,val);
}

#endif /*_WS_PCF8591SIM_H_*/
