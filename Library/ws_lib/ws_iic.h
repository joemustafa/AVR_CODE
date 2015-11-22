/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_iic.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313  (ICCAVR --> GCCAVR)
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#ifndef _WS_IIC_H_
#define _WS_IIC_H_

/* TWSR values (not bits) */
/* Master */
#define I2C_START			0x08
#define I2C_RESTART			0x10

/* Master Transmitter */
#define I2C_MT_SLA_ACK		0x18
#define I2C_MT_SLA_NACK		0x20
#define I2C_MT_DATA_ACK		0x28
#define I2C_MT_DATA_NACK	0x30
#define I2C_MT_ARB_LOST		0x38

/* Master Receiver */
#define I2C_MR_ARB_LOST		0x38
#define I2C_MR_SLA_ACK		0x40
#define I2C_MR_SLA_NACK		0x48
#define I2C_MR_DATA_ACK		0x50
#define I2C_MR_DATA_NACK	0x58

/* Slave Transmitter */
#define I2C_ST_SLA_ACK			0xA8
#define I2C_ST_ARB_LOST_SLA_ACK 0xB0
#define I2C_ST_DATA_ACK			0xB8
#define I2C_ST_DATA_NACK		0xC0
#define I2C_ST_LAST_DATA		0xC8

/* Slave Receiver */
#define I2C_SR_SLA_ACK				0x60
#define I2C_SR_ARB_LOST_SLA_ACK		0x68
#define I2C_SR_GCALL_ACK			0x70
#define I2C_SR_ARB_LOST_GCALL_ACK	0x78
#define I2C_SR_DATA_ACK				0x80
#define I2C_SR_DATA_NACK			0x88
#define I2C_SR_GCALL_DATA_ACK		0x90
#define I2C_SR_GCALL_DATA_NACK		0x98
#define I2C_SR_STOP					0xA0

/* Misc */
#define I2C_NO_INFO			0xF8
#define I2C_BUS_ERROR		0x00

/*
 * The lower 3 bits of TWSR are reserved on the ATmega163.
 * The 2 LSB carry the prescaler bits on the newer ATmegas.
 */
#define I2C_STATUS_MASK	(_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|_BV(TWS3))
#define I2C_STATUS		(TWSR & I2C_STATUS_MASK)

/*
 * R/~W bit in SLA+R/W address field.
 */
#define I2C_READ		1
#define I2C_WRITE		0

#define I2CStart()    	(TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN))
#define I2CStop()     	(TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN))
#define I2CWaitAck()	{while(!(TWCR&(1<<TWINT)));}
#define I2CChkAck() 	(TWSR&0xf8)					//check ack
#define I2CSendAck()	(TWCR|=(1<<TWEA))
#define I2CSendNoAck()	(TWCR&=~(1<<TWEA))
#define I2CSendByte(x)	{TWDR=(x);TWCR=(1<<TWINT)|(1<<TWEN);} 
#define I2CRcvNckByte()	(TWCR=(1<<TWINT)|(1<<TWEN))
#define I2CRcvAckByte()	(TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA))

/* For Program */
#define I2C_Stop()		I2CStop()
#define I2C_SendAck()	I2CSendAck()
#define I2C_SendNoAck() I2CSendNoAck()
#define I2C_WaitAck()	I2CWaitAck()

/* I2C Config */
#define I2C_ERR			0
#define I2C_CRR			1

uint8_t I2C_Start()					
{
	I2CStart();						
	I2CWaitAck();
	if( I2CChkAck()!=I2C_START ) 
		return I2C_ERR;
	return I2C_CRR;
}

uint8_t I2C_Restart()					
{
	I2CStart();						
	I2CWaitAck();
	if( I2CChkAck()!=I2C_RESTART ) 
		return I2C_ERR;
	return I2C_CRR;
}

uint8_t I2C_SendWrDAdr(uint8_t wrDAdr)	
{
	I2CSendByte(wrDAdr);			
	I2CWaitAck();
	if( I2CChkAck()!=I2C_MT_SLA_ACK )
		return I2C_ERR;
	return I2C_CRR;
}

uint8_t I2C_SendWrDAdr_(uint16_t wrDAdr)	
{
	if( (wrDAdr&0xF000) == 0xF000 )	
		if( I2C_SendWrDAdr( (uint8_t)wrDAdr>>8 )==I2C_ERR )	
			return I2C_ERR;
	if( I2C_SendWrDAdr( (uint8_t)wrDAdr )==I2C_ERR )	
		return I2C_ERR;
	return I2C_CRR;
}

uint8_t I2C_SendRdDAdr(uint8_t rdDAdr)	
{
	I2CSendByte(rdDAdr);			
	I2CWaitAck();
	if( I2CChkAck()!=I2C_MR_SLA_ACK )  
		return I2C_ERR;
	return I2C_CRR;	
}

uint8_t I2C_SendRdDAdr_(uint8_t rdDAdr)	
{
	if( (rdDAdr&0xF000) == 0xF000)	
		if( I2C_SendWrDAdr( (uint8_t)rdDAdr>>8 )==I2C_ERR )	
			return I2C_ERR;
	if( I2C_SendWrDAdr( (uint8_t)rdDAdr )==I2C_ERR )	
		return I2C_ERR;
	return I2C_CRR;
}

uint8_t I2C_SendDat(uint8_t configDat)	
{
	I2CSendByte(configDat);			
	I2CWaitAck();
	if( I2CChkAck()!=I2C_MT_DATA_ACK ) 
		return I2C_ERR;
	return I2C_CRR;	
}

uint8_t I2C_RcvNAckDat(uint8_t *pRdDat)	
{
	I2CRcvNckByte();
	I2CWaitAck();
	if( I2CChkAck()!=I2C_MR_DATA_NACK )
		return I2C_ERR;
	*pRdDat=TWDR;
	return I2C_CRR;
}

uint8_t I2C_RcvAckDat(uint8_t *pRdDat)	
{
	I2CRcvAckByte();					
	I2CWaitAck();
	if( I2CChkAck()!=I2C_MR_DATA_ACK )
		return I2C_ERR;
	*pRdDat=TWDR;
	return I2C_CRR;
}

uint8_t I2C_Write(uint16_t wrDAdr,uint8_t wordAdr,uint8_t dat)
{
	if( I2C_Start()==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendDat(wordAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendDat(dat)==I2C_ERR )
		return I2C_ERR;

	I2C_Stop();

	return I2C_CRR;
}

//uint8_t I2C_Write_(uint16 wrDAdr,uint8 wordAdr,
//				  uint8 *pWrDat,uint8 num)
//{
//
//} 

uint8_t I2C_Read(uint16_t wrDAdr,uint8_t wordAdr,
			  uint8_t rdDAdr,uint8_t *pRdDat)
{
	if( I2C_Start()==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendDat(wordAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_Restart()==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_RcvNAckDat(pRdDat)==I2C_ERR )
		return I2C_ERR;

	I2C_Stop();

	return I2C_CRR;
}

uint8_t I2C_Read_(uint16_t wrDAdr,uint8_t wordAdr,
			   uint8_t rdDAdr,uint8_t *pRdDat,uint8_t num)
{
 	uint8_t i;
	
	if( I2C_Start()==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendDat(wordAdr)==I2C_ERR )
		return I2C_ERR;

	if( I2C_Restart()==I2C_ERR )
		return I2C_ERR;

	if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
		return I2C_ERR;

	for(i=0;i<num-1;i++)
		if( I2C_RcvAckDat(pRdDat+i)==I2C_ERR )
			return I2C_ERR;
	
	if( I2C_RcvNAckDat(pRdDat+i)==I2C_ERR )
			return I2C_ERR;

	I2C_Stop();
	
	return I2C_CRR;
}

#endif /*_WS_IIC_H_*/
