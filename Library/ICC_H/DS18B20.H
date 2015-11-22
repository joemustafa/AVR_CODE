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
#include "D:\ICC_H\onewirefords18b20.H"

void convert_ds18b20(void) 
{ 
    reset_onewire(); 
    ack_onewire(); 
    delay50us(200); 
    write_onewire(0xcc); 
    write_onewire(0x44); 
} 

unsigned char read_temperature(void) 
{ 
	unsigned char temp1,temp2;
	convert_ds18b20();
    reset_onewire(); 
    ack_onewire(); 
    delay50us(200); 
    write_onewire(0xcc); 
    write_onewire(0xbe); 	
    temp1=read_onewire(); 
    temp2=read_onewire(); 
	temp2=temp2<<4;
	temp1=temp1>>4;
	temp2|=temp1;

	return temp2;
	     
}
