#ifndef _onewire_H_
#define _onewire_H_

void reset_onewire(void) 
{ 
	set_onewire_dq_ddr();
    clr_onewire_dq(); 
    delayus(500);
    set_onewire_dq(); 
    delayus(60);
	clr_onewire_dq_ddr();
} 

void ack_onewire(void) 
{ 	
    while(in_onewire_dq());
    while(!(in_onewire_dq())); 
    delayus(38);
	set_onewire_dq_ddr();
} 

unsigned char read_onewire(void) 
{ 
    unsigned char data=0,i=0; 
    for(i=0;i<8;i++) 
    { 
		set_onewire_dq_ddr();

        data=data>>1; 
        clr_onewire_dq(); 
        delayus(1);
        set_onewire_dq(); 
        delayus(2);

		clr_onewire_dq_ddr();
        if(in_onewire_dq()) data|=0x80; 
        delayus(118);
	} 
	return(data); 
} 

void write_onewire(unsigned char data) 
{ 
    unsigned char i=0; 
	set_onewire_dq_ddr();
    for(i=0;i<8;i++) 
    { 
        if(data&0x01)
		{ 
            clr_onewire_dq(); 
            delayus(14);
            set_onewire_dq(); 
            delayus(108);
		}	 
   	 	else 
   	 	{ 
       		 clr_onewire_dq(); 
        	delayus(108);
        	set_onewire_dq(); 
        	delayus(14);
    	} 
    	data=data>>1; 
    } 
} 
#endif
