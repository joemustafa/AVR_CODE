
#include <avr/io.h>
#include <util/delay.h>

#include "LTM022A69B.h"
#include "LCD_lib.h"
#include"touch.h"


unsigned char read_res ;

 typedef struct 
{
	unsigned int  x;//LCD×øcoordinates

	unsigned int  y;
	unsigned long x_ad_val; //ADC value
	unsigned long y_ad_val;						   	    
	unsigned char  pen_status;//The pen of the state
			  
}_touch_dot;

extern _touch_dot touch_dot;

void display_touch_debug()
{        //ADC results show
        lcd_display_string("READ SUCCESS:",BLACK,GREEN,1,3);
        lcd_display_number(14,3,read_res,6);

        lcd_display_string("X AD Val:",BLACK,GREEN,1,4);
        lcd_display_number(10,4,touch_dot.x_ad_val,6);

        lcd_display_string("Y AD Val:",BLACK,GREEN,1,5);
        lcd_display_number(10,5,touch_dot.y_ad_val,6);

        //Display coordinates
        lcd_display_string("X:",BLACK,GREEN,1,6);
        lcd_display_number(10,6,touch_dot.x,5);
        lcd_display_string("Y:",BLACK,GREEN,1,7);
        lcd_display_number(10,7,touch_dot.y,5);

}

int main(void)

{
	unsigned int i;
	DDRA=0XFF;
	PORTA=0X00;
//	DDRE |= (1<<PE4);

	DDRE &= ~(1<<PE4);
	PORTE &= ~(1<<PE4);	


	lcd_init();
    lcd_display_string( "experiment:Touch screen    ", BLACK, GREEN, 0, 0 );
    lcd_display_string( "CPU:ATMAGE128A-AU          ", BLACK, GREEN, 0, 1 );
    lcd_display_string( "www.WaveShare.net          ", BLACK, GREEN, 0, 2 );
//	_delay_ms(5000);
	while(1)
	{
		read_res=Read_Continue();
		lcd_draw_bigdot(BLACK,(touch_dot.x-20),(touch_dot.y-2));
//		for(i=0;i<100;i++)
//		{
//			lcd_draw_bigdot(BLACK,50,i);
//		}
//		lcd_draw_line(BLACK,0,0,20,20);
	
	}

}

 
