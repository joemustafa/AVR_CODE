#ifndef	AT24CXX_H
#define	AT24CXX_H

#include "D:\ICC_H\CmmICC.H"
#include "D:\ICC_H\I2C.H"

#ifndef WR_DADR 
	#define WR_DADR		0xA0	//write device-address 
#endif
#ifndef RD_DADR 
	#define RD_DADR		0xA1	//read device-address
#endif

#define AT24CXX_ERR		0
#define AT24CXX_CRR		1

bool AT24CXX_Write(uint8 wordAdr,uint8 dat) 
{
	if( I2C_Write(WR_DADR, wordAdr, dat)==I2C_ERR )
		return AT24CXX_ERR;
	return AT24CXX_CRR;
}

bool AT24CXX_Read(uint8 wordAdr,uint8 *pRdDat) 
{
	if( I2C_Read(WR_DADR, wordAdr, RD_DADR, pRdDat)==I2C_ERR )
		return AT24CXX_ERR;
	return AT24CXX_CRR;
}

#endif
