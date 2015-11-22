#ifndef PCF8574_sim_H
#define PCF8574_sim_H

void PCF8574_wByte(uchar dat)
{
	I2C_Start(); 
	I2C_Send_DataAddr(0x40); 
	I2C_Send_DataAddr(dat); 
	I2C_Stop();
}

uchar PCF8574_rByte()
{
	uchar PCF8574_dat;
	I2C_Start();
	I2C_Send_DataAddr(0x40); 
	I2C_Start();
	I2C_Send_DataAddr(0x41); 
	PCF8574_dat=I2C_Read_DataAddr(nACT);	
	I2C_Stop();
	return(PCF8574_dat);
}
#endif