#ifndef AT24CXX_sim_h
#define AT24CXX_sim_h

#define uchar unsigned char
#define uint unsigned int

void AT24C_wByte(uchar AT24C_wrDAdr,uchar wordAdr,uchar dat)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0); 
	I2C_Start(); 
	I2C_Send_DataAddr(AT24C_wrDAdr);
	I2C_Send_DataAddr(wordAdr);
	I2C_Send_DataAddr(dat); 
	I2C_Stop();
}

void AT24C_wPage(uchar AT24C_wrDAdr,uchar wordAdr,uchar *pWrDat)
{
	uchar AT24C_n;
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0); 
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr);
	I2C_Send_DataAddr(wordAdr); 
	for(AT24C_n=0;AT24C_n<=15;AT24C_n++) 
		I2C_Send_DataAddr(*(pWrDat+AT24C_n));
	I2C_Stop();
}

uchar AT24C_rByte(uchar AT24C_wrDAdr,uchar wordAdr)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0);
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	I2C_Send_DataAddr(wordAdr); 
	AT24C_wrDAdr|=0x01; 
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	AT24C_wrDAdr=I2C_Read_DataAddr(nACT);	
	I2C_Stop();
	return(AT24C_wrDAdr);
}

void AT24C_rPage(uchar AT24C_wrDAdr,uchar wordAdr,uchar *pRdDat,uchar num)
{
	AT24C_wrDAdr=(((AT24C_wrDAdr<<1)&0x0E)|0xA0); 
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	I2C_Send_DataAddr(wordAdr); 
	AT24C_wrDAdr|=0x01;
	I2C_Start();
	I2C_Send_DataAddr(AT24C_wrDAdr); 
	for(num--;num>0;num--) 
	{
		*pRdDat=I2C_Read_DataAddr(ACT);
		pRdDat++;
	}
	*pRdDat=I2C_Read_DataAddr(nACT);
	I2C_Stop();
}

#endif