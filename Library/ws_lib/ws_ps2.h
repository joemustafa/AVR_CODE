/*
*========================================================================================================
*
* File                : ws_ps2.h
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

#ifndef _WS_PS2_H_
#define _WS_PS2_H_

#include <avr/interrupt.h>

#define PS2_BUFFER_SIZE 8	
volatile  uint8_t ps2_buffer[PS2_BUFFER_SIZE];	

volatile  uint8_t ps2_status;	
volatile  uint8_t ps2_data;		
volatile  uint8_t ps2_parity;

volatile  uint8_t ps2_wr_index,ps2_rd_index,ps2_counter;

ISR(PS2_INT_VECTOR,ISR_BLOCK)
{
   ps2_status++;	
	if(ps2_status==1)
   { 
        if(GET_PS2_DA()) 
            ps2_status=0;		
   }
   else if(ps2_status<10 && ps2_status>0)
   {
      ps2_data=ps2_data>>1;
			if(GET_PS2_DA()) {ps2_data |= 0x80;ps2_parity++;}	
			else ps2_data &= 0x7F;
   }
   else if(ps2_status==10) 
   {
        if(GET_PS2_DA()) 	
            ps2_parity++;	
   }
   else if((ps2_status==11))
   {
        if((ps2_parity & 0x01))	
        {
        ps2_buffer[ps2_wr_index]=ps2_data;	
        if (++ps2_wr_index == PS2_BUFFER_SIZE) ps2_wr_index=0;	
        if (++ps2_counter == PS2_BUFFER_SIZE) ps2_counter=0;	
        ps2_status=0;
        ps2_parity=0;
        }
   }
   else
   {
        ps2_status=0;	
        ps2_parity=0;
   } 
}

uint8_t ps2GetCode(void)
{
uint8_t data;
while(!ps2_counter);
data=ps2_buffer[ps2_rd_index];
if (++ps2_rd_index == PS2_BUFFER_SIZE) ps2_rd_index=0;	
cli();
--ps2_counter;
sei();
return data;
}

void ps2Init(void)
{
ps2_status=0;
ps2_data=0;
ps2_parity=0;

ps2_wr_index=0;
ps2_rd_index=0;
ps2_counter=0; 

IN_PS2_CL();
SET_PS2_CL();
IN_PS2_DA();
SET_PS2_DA();
}

#endif /*_WS_PS2_H_*/
