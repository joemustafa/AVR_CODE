#ifndef PCF8591_H
#define PCF8591_H

#include "D:\ICC_H\CmmICC.H"
//sbit I2C_SCL=P3^1;
//sbit I2C_SDA=P3^0;
#include "D:\ICC_H\I2C.H"

#ifndef WR_DADR 
	#define WR_DADR		0x90	//write device-address 
#endif
#ifndef RD_DADR 
	#define RD_DADR		0x91	//read device-address
#endif

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

void PCF8591_getAD(uint8 mode,uint8 chan,uint8 *pRdDat)
{
	I2C_Read(WR_DADR,mode|chan,RD_DADR,pRdDat);
}

void PCF8591_setDA(uint8 val)
{
	I2C_Write(WR_DADR,DAouputEn,val);
}

#endif
