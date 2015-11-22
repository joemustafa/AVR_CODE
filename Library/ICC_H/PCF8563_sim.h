#ifndef PCF8563_sim_H
#define PCF8563_sim_H


#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )
#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )

//#ifndef WR_DADR 
	#define WR_DADR		0x01	//write device-address 
//#endif
//#ifndef RD_DADR 
	#define RD_DADR		0x01	//read device-address
//#endif

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

void PCF8563_wByte(uchar AT24C_wrDAdr,uchar wordAdr,uchar dat)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0);
	I2C_Start(); 
	I2C_Send_DataAddr(AT24C_wrDAdr);
	I2C_Send_DataAddr(wordAdr); 
	I2C_Send_DataAddr(dat);
	I2C_Stop();
}

uchar PCF8563_rByte(uchar AT24C_wrDAdr,uchar wordAdr)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0); 
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr);
	I2C_Send_DataAddr(wordAdr);
	AT24C_wrDAdr|=0x01; 
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	AT24C_wrDAdr=I2C_Read_DataAddr(ACT);
	I2C_Stop();
	return(AT24C_wrDAdr); 
}

void PCF8563_rPage(uchar AT24C_wrDAdr,uchar wordAdr,uchar *pRdDat,uchar num)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0);
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	I2C_Send_DataAddr(wordAdr); 
	AT24C_wrDAdr|=0x01;
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr);
	for(;num>0;num--) 
	{
		*pRdDat=I2C_Read_DataAddr(ACT);
		pRdDat++;
	}
	*pRdDat=I2C_Read_DataAddr(nACT); 
	I2C_Stop();
}

void PCF8563_getTime(uchar *buf)
{
	do
	{
		PCF8563_rPage(WR_DADR,SECOND_DATA_BUF,buf,3);
		buf[0]=buf[0]&0x7f;		//get second data
	}while(!buf[0]);				//if "second==0"£¬read again for avoid mistake
	
	buf[1]=buf[1]&0x7f;		//get minute data
	buf[2]=buf[2]&0x3f;		//get hour data

	buf[0]=changeHexToInt(buf[0]);
	buf[1]=changeHexToInt(buf[1]);
	buf[2]=changeHexToInt(buf[2]);
}

void PCF8563_setTime(uchar hour,uchar minute,uchar second)
{
	
	hour=changeIntToHex(hour);		
	minute=changeIntToHex(minute);
	second=changeIntToHex(second);

	PCF8563_wByte(WR_DADR,HOUR_DATA_BUF,hour);
	PCF8563_wByte(WR_DADR,MINUTE_DATA_BUF,minute);
	PCF8563_wByte(WR_DADR,SECOND_DATA_BUF,second);
}

void PCF8563_init()
{
	PCF8563_wByte(WR_DADR,CTRL_BUF1,0x00);			//basic setting
	PCF8563_wByte(WR_DADR,CTRL_BUF2,0x12);			//alarm enable
	//WriteAByte(HOUR_AE_BUF,0x09);		//set alarm hour at 9:00
	//WriteAByte(CLK_FRQ_BUF,0xf0);		//set clkout frequency
}

#endif

