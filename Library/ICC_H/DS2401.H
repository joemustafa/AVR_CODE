#ifndef _STK48
#define ds18b20_dq PC7
#else 
#define ds18b20_dq PC5
#endif
#define set_onewire_dq_ddr() DDRC|=1<<ds18b20_dq
#define set_onewire_dq() PORTC|=1<<ds18b20_dq
#define clr_onewire_dq() PORTC&=~(1<<ds18b20_dq) 
#define clr_onewire_dq_ddr() DDRC&=~(1<<ds18b20_dq)
#define in_onewire_dq() PINC&(1<<ds18b20_dq)
#include "D:\ICC_H\onewirefor2401.H"
void get_number(unsigned char *n)
{	
	unsigned char T;
	reset_onewire();		 		
	write_onewire(0x33);				
	for(T=8;T>0;T--)
	{
		*n=read_onewire();n++;
	}
}
   