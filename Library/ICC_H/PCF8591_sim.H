#ifndef PCF8591_sim_H
#define PCF8591_sim_H

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

uchar PCF8591_getAD(uchar wordAdr)
{
	uchar PCF8591_num;
	I2C_Start();
	I2C_Send_DataAddr(WR_DADR);
	I2C_Send_DataAddr(wordAdr); 
	I2C_Start();
	I2C_Send_DataAddr(RD_DADR);
	PCF8591_num=I2C_Read_DataAddr(ACT);	
	I2C_Stop();
	return(PCF8591_num); 
}

void PCF8591_setDA(uchar val)
{
	I2C_Start(); 
	I2C_Send_DataAddr(WR_DADR); 
	I2C_Send_DataAddr(DAouputEn); 
	I2C_Send_DataAddr(val);
	I2C_Stop();
}

#endif