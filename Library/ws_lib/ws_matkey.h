/*
*========================================================================================================
*
* File                : ws_matkey.h
* Hardware Environment:	
* Build Environment   : AVR Studio 4.16 + Winavr 20090313
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*========================================================================================================
*/
#ifndef _WS_MATKEY_H_
#define _WS_MATKEY_H_
#include <stdint.h>
const uint8_t setSta_[4]={0xfe,0xfd,0xfb,0xf7};       
const uint8_t getSta_[4]={0x70,0xb0,0xd0,0xe0};  

uint8_t getKeyVal()
{
    uint8_t i,j,getSta,keyVal;
	MATKEY_PORT=0xFF;
    MATKEY_DDR=0x0F;
    for(i=0;i<4;i++)              
    {               			
        MATKEY_PORT = setSta_[i];
        if(MATKEY_PIN!=setSta_[i])
        {
            getSta=MATKEY_PIN&0xf0;
            for(j=0;j<4;j++)    
                if(getSta==getSta_[j])                                 
            	{
                    keyVal=j+i*4;
                    return keyVal;
            	}
        }
    }
    return 0xFF;
}

#endif /*_WS_MATKEY_H_*/
