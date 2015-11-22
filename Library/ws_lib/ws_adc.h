/*
*========================================================================================================
*
* File                : ws_adc.h
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

#ifndef _WS_ADC_H_
#define _WS_ADC_H_
#include <avr/interrupt.h>

#if (ADC_MODE==1)
	#define adc_uint_t uint8_t 	
#elif (ADC_MODE==2)
	#define adc_uint_t uint16_t 
#else 
	#define adc_uint_t uint8_t 
	#warning "ADC mode undefined.By default use 8bit mode."
	#warning "ADC_MODE==1: 8bit mode."
	#warning "ADC_MODE==2: 10bit mode."
#endif

volatile  adc_uint_t adc_buffer[ADC_BUFFER_SIZE];	

#ifndef ADC_BUFFER_SIZE
#define ADC_BUFFER_SIZE 16
warning "ADC_BUFFER_SIZE undefined.ADC_BUFFER_SIZE value defaults to 16"
#endif

#if (ADC_BUFFER_SIZE<255)
	volatile  uint8_t adc_wr_index=0,adc_rd_index=0,adc_counter=0;
#else 
	volatile  uint16_t adc_wr_index=0,adc_rd_index=0,adc_counter=0;
#endif

ISR(ADC_vect,ISR_BLOCK)
{
#if (ADC_MODE==1)
	adc_buffer[adc_wr_index]=ADCH;
#elif (ADC_MODE==2)
	adc_buffer[adc_wr_index]=ADC;
#endif

   if (++adc_wr_index == ADC_BUFFER_SIZE) adc_wr_index=0;
   if (++adc_counter == ADC_BUFFER_SIZE) adc_counter=0;
}

adc_uint_t getADC(void)
{
adc_uint_t data;
while(!adc_counter);
data=adc_buffer[adc_rd_index];	
if (++adc_rd_index == ADC_BUFFER_SIZE) adc_rd_index=0;	
cli();
--adc_counter;
sei();
return data;
}

#endif /*_WS_ADC_H_*/
