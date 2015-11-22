/********************************************************************************************************
*********************************************************************************************************
*
* File                : ws_adc_port.h
* Hardware Environment:
* Build Environment   : AVR Studio 4.16 + Winavr 20090313
* Version             : V1.0
* By                  : Wu Ze
*
*                                  (c) Copyright 2005-2009, WaveShare
*                                       http://www.waveShare.net
*                                          All Rights Reserved
*
*********************************************************************************************************
********************************************************************************************************/

#ifndef _WS_ADC_PORT_H_
#define _WS_ADC_PORT_H_
#include <avr/io.h>


/*Hardware Environment£ºDVK501 && M128+ EX*/
#if defined(_DVK501_M128_EX_)
#define ADC_MODE 1
#define ADC_BUFFER_SIZE 16
void adcInit(void)
{
#if (ADC_MODE==2)	
	ADMUX=(1<<REFS0); 
#else
	ADMUX=(1<<REFS0)|(1<<ADLAR); 
#endif
ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADFR)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); 
asm("SEI");
}

/*Hardware Environment£ºDVK501 && M16+ EX*/
#elif defined(_DVK501_M16_EX_)
#define ADC_MODE 1
#define ADC_BUFFER_SIZE 16
void adcInit(void)
{
#if (ADC_MODE==2)	
	ADMUX=(1<<REFS0); 
#else
	ADMUX=(1<<REFS0)|(1<<ADLAR); 
#endif
ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); 
asm("SEI");
}

/*Hardware Environment£ºDVK501 && M48+ EX*/
#elif defined(_DVK501_M48_EX_)
#define ADC_MODE 1
#define ADC_BUFFER_SIZE 16
void adcInit(void)
{
#if (ADC_MODE==2)	
	ADMUX=(1<<REFS0); 
#else
	ADMUX=(1<<REFS0)|(1<<ADLAR);
#endif
ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); 
asm("SEI");
}

/*Hardware Environment£ºDVK501 && M169+ EX*/
#elif defined(_DVK501_M169_EX_)
#define ADC_MODE 1
#define ADC_BUFFER_SIZE 16
void adcInit(void)
{
#if (ADC_MODE==2)	
	ADMUX=(1<<REFS0);
#else
	ADMUX=(1<<REFS0)|(1<<ADLAR);
#endif
ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); 
asm("SEI");
}

#else
  #warning "ADC interface undefined."
#endif

#include <ws_adc.h>

#endif /*_WS_ADC_PORT_H_*/
