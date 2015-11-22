#ifndef IIC_sim_h
#define IIC_sim_h

#define DELAY_NOP asm("NOP\n")


void delay_10us(void)
{
 	 uchar delay_num;
	 for(delay_num=0;delay_num<=10;delay_num++){DELAY_NOP;}
}

void SDA_IN()		{I2C_DDR&=0xFE;delay_10us();}
void SDA_OUT()		{I2C_DDR|=0x01;delay_10us();}  
void SDA_SET()		{I2C_PORT|=0x01;delay_10us();}
void SDA_CLR()		{I2C_PORT&=0xFE;delay_10us();}
#define SDA_PIN			(I2C_PIN&0x01)

void SCL_IN()		{I2C_DDR&=0xFD;delay_10us();}
void SCL_OUT()		{I2C_DDR|=0x02;delay_10us();}  
void SCL_SET()		{I2C_PORT|=0x02;delay_10us();}
void SCL_CLR()		{I2C_PORT&=0xFD;delay_10us();}
#define SCL_PIN			((I2C_PIN>>1)&0x01)

#define READ 1
#define WRITE 0

#define ACT 1
#define nACT 0

/* I2C Config */
#define I2C_ERR			0
#define I2C_CRR			1

void I2C_Start()
{
	SCL_CLR();
	SDA_OUT();
	SDA_SET();
	SCL_OUT();
	SCL_SET();
	SDA_CLR();
	SCL_CLR();
}

void I2C_Stop()
{
	SCL_CLR();
	SDA_OUT();
	SDA_CLR();
	SCL_OUT();
	SCL_SET();
	SDA_SET();
	SCL_CLR();
}

void I2C_Send_DataAddr(uchar wrDAdr)	
{
	uchar I2C_n;
	SCL_CLR();
	SDA_OUT();
	SCL_OUT();
	for(I2C_n=0;I2C_n<=7;I2C_n++)
	{
		if((wrDAdr&0x80)==0x80) {SDA_SET();}
		else {SDA_CLR();}	
		SCL_SET();
		SCL_CLR();
		wrDAdr<<=1;
	}
	SDA_IN();
	SDA_SET();
	SCL_SET();
	while(SDA_PIN){};
	SCL_CLR();
	SDA_OUT();
}

uchar I2C_Read_DataAddr(uchar bAct)
{
	uchar n;
	uchar rdDAdr=0;
	SCL_CLR();
	SDA_IN();
	SCL_OUT();
	for(n=0;n<=7;n++)
	{
	 	rdDAdr<<=1;
		SCL_SET();
		DELAY_NOP;
		rdDAdr|=SDA_PIN;
		SCL_CLR();
		
	}
	SDA_OUT();
	if(bAct) {SDA_SET();}
	else {SDA_CLR();}
	SCL_SET();
	SCL_CLR();
	return(rdDAdr);
}

uchar I2C_ReadBusy(uchar wrDAdr)	
{
	uchar n;
	I2C_Start();
	SDA_OUT();
	SCL_OUT();
	for(n=0;n<=7;n++)
	{
		if((wrDAdr&0x80)==0x80) {SDA_SET();}
		else {SDA_CLR();}
		SCL_SET();
		SCL_CLR();
		wrDAdr<<=1;
	}
	SDA_IN();
	SDA_SET();
	SCL_SET();
	wrDAdr=SDA_PIN;
	SCL_CLR();	
	return(wrDAdr);

}

#endif