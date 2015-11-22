/******************************************************************************

* File Name          : LTM022A69B.c
* Author             : Librae
* Last Modified Date : 08/12/2010
* Description        : This file provides the 
						LTM022A69B LCD related functions' declaration.

******************************************************************************/
#include <avr/io.h>
#include <util/delay.h>

//#include "SPI0.h"
#include "LTM022A69B.h"
#include "LCD_lib.h"


#define uint unsigned int 
#define uchar unsigned char

void lcd_ctrl_port_init(void);      //nRS,nCS ... initialization

//=============================================================================
//							LCD Basic Functions
//=============================================================================
/******************************************************************************
* Function Name  : LCD_WRITE_REG
* Description    : write LCD register
* Input          : index
* Output         : None
* Return         : None
******************************************************************************/

void SPI0_Init(void)
{

	DDRB=0xff;
	PORTB=0X00;

	SPCR=0x50;          //使能SPI ， 设置SPI为主模式，空闲时CLI为1，第一个上升沿采集数据，时钟    FOSC/16
	SPSR=0x00;			//setup SPI

//	SPI_RxHead = 0; 
//	SPI_TxHead = 0; 
	
}

//****************************************** 
//发送数据 
//****************************************** 

unsigned char SPI0_communication(unsigned char send_char)
{
	SPDR = send_char;               //启动数据传输
	while (!(SPSR & (1<<SPIF)));    //等待传输结束
	return SPDR;
}




void LCD_WRITE_REG(unsigned int index)
{
	uint value_index;
	LCD_RS_L();
	LCD_CS_L();
	value_index=index;
	value_index =value_index>>8;
    SPI0_communication((unsigned char)(value_index));    //00000000 000000000

	value_index=index;
	value_index &=0x00ff;
    SPI0_communication((unsigned char)(index));
	LCD_CS_H();
	LCD_RS_H();
}


/******************************************************************************
* Function Name  : LCD_SEND_COMMAND
* Description    : send command to LCD
* Input          : index, data
* Output         : None
* Return         : None
******************************************************************************/
void LCD_SEND_COMMAND(unsigned int index,unsigned int data)
{
	//select command register
	LCD_RS_L();
	LCD_CS_L();
    SPI0_communication((unsigned char)(index>>8));    //00000000 000000000
    SPI0_communication((unsigned char)(index));
	LCD_CS_H();
	//send data
	LCD_RS_H();
	LCD_CS_L();
    SPI0_communication((unsigned char)(data>>8));    //00000000 000000000
    SPI0_communication((unsigned char)(data));
	LCD_CS_H();
}


/******************************************************************************
* Function Name  : LCD_WRITE_COMMAND
* Description    : send command to LCD
* Input          : index, data
* Output         : None
* Return         : None
******************************************************************************/
void LCD_WRITE_COMMAND(unsigned int index,unsigned int data)
{
	//select command register
	LCD_RS_L();
	LCD_CS_L();
    SPI0_communication((unsigned char)(index>>8));    //00000000 000000000
    SPI0_communication((unsigned char)(index));
	LCD_CS_H();
	//send data
	LCD_RS_H();

	LCD_CS_L();
    SPI0_communication((unsigned char)(data>>8));    //00000000 000000000
    SPI0_communication((unsigned char)(data));
	LCD_CS_H();
}

/*******************************************************************************
* Function Name  : LCD_WRITE_DATA
* Description    : write data to LCD
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WRITE_DATA(unsigned int data)
{
    SPI0_communication((unsigned char)(data>>8));    //00000000 000000000
    SPI0_communication((unsigned char)(data));
}
/********************************************************************************
* Function Name  : lcd_ctrl_port_init
* Description    : nRS,nCS ... initialization  for LPC1114 PIN
* Input          : None
* Output         : None
* Return         : None
********************************************************************************/
void lcd_ctrl_port_init()
{
	DDRD=0XFF;
//	PORTD=0X40;
    
}
/******************************************************************************
* Function Name  : lcd_init
* Description    : LCD initialization
* Input          : None
* Output         : None
* Return         : None
******************************************************************************/
void lcd_init(void)
{
     lcd_ctrl_port_init();
    SPI0_Init();
//  reser LCD
	PORTB &= ~(1<<PB6);
	_delay_us(5);
	PORTB |= (1<<PB6);
	_delay_us(5);


	LCD_WRITE_COMMAND( 0x000, 0x0001 ); /* oschilliation start */
	_delay_us( 10 );
	/* Power settings */  	
	LCD_WRITE_COMMAND( 0x100, 0x0000 ); /*power supply setup*/	
	LCD_WRITE_COMMAND( 0x101, 0x0000 ); 
	LCD_WRITE_COMMAND( 0x102, 0x3110 ); 
	LCD_WRITE_COMMAND( 0x103, 0xe200 ); 
	LCD_WRITE_COMMAND( 0x110, 0x009d ); 
	LCD_WRITE_COMMAND( 0x111, 0x0022 ); 
	LCD_WRITE_COMMAND( 0x100, 0x0120 ); 
	_delay_us( 20 );

	LCD_WRITE_COMMAND( 0x100, 0x3120 );
	_delay_us( 80 );
	/* Display control */   
	LCD_WRITE_COMMAND( 0x001, 0x0100 );
	LCD_WRITE_COMMAND( 0x002, 0x0000 );
	LCD_WRITE_COMMAND( 0x003, 0x1230 );
	LCD_WRITE_COMMAND( 0x006, 0x0000 );
	LCD_WRITE_COMMAND( 0x007, 0x0101 );
	LCD_WRITE_COMMAND( 0x008, 0x0808 );
	LCD_WRITE_COMMAND( 0x009, 0x0000 );
	LCD_WRITE_COMMAND( 0x00b, 0x0000 );
	LCD_WRITE_COMMAND( 0x00c, 0x0000 );
	LCD_WRITE_COMMAND( 0x00d, 0x0018 );
	/* LTPS control settings */   
	LCD_WRITE_COMMAND( 0x012, 0x0000 );
	LCD_WRITE_COMMAND( 0x013, 0x0000 );
	LCD_WRITE_COMMAND( 0x018, 0x0000 );
	LCD_WRITE_COMMAND( 0x019, 0x0000 );

	LCD_WRITE_COMMAND( 0x203, 0x0000 );
	LCD_WRITE_COMMAND( 0x204, 0x0000 );

	LCD_WRITE_COMMAND( 0x210, 0x0000 );
	LCD_WRITE_COMMAND( 0x211, 0x00ef );
	LCD_WRITE_COMMAND( 0x212, 0x0000 );
	LCD_WRITE_COMMAND( 0x213, 0x013f );
	LCD_WRITE_COMMAND( 0x214, 0x0000 );
	LCD_WRITE_COMMAND( 0x215, 0x0000 );
	LCD_WRITE_COMMAND( 0x216, 0x0000 );
	LCD_WRITE_COMMAND( 0x217, 0x0000 );

	// Gray scale settings
	LCD_WRITE_COMMAND( 0x300, 0x5343);
	LCD_WRITE_COMMAND( 0x301, 0x1021);
	LCD_WRITE_COMMAND( 0x302, 0x0003);
	LCD_WRITE_COMMAND( 0x303, 0x0011);
	LCD_WRITE_COMMAND( 0x304, 0x050a);
	LCD_WRITE_COMMAND( 0x305, 0x4342);
	LCD_WRITE_COMMAND( 0x306, 0x1100);
	LCD_WRITE_COMMAND( 0x307, 0x0003);
	LCD_WRITE_COMMAND( 0x308, 0x1201);
	LCD_WRITE_COMMAND( 0x309, 0x050a);

	/* RAM access settings */ 
	LCD_WRITE_COMMAND( 0x400, 0x4027 );
	LCD_WRITE_COMMAND( 0x401, 0x0000 );
	LCD_WRITE_COMMAND( 0x402, 0x0000 );	/* First screen drive position (1) */   	
	LCD_WRITE_COMMAND( 0x403, 0x013f );	/* First screen drive position (2) */   	
	LCD_WRITE_COMMAND( 0x404, 0x0000 );

	LCD_WRITE_COMMAND( 0x200, 0x0000 );
	LCD_WRITE_COMMAND( 0x201, 0x0000 );
	
	LCD_WRITE_COMMAND( 0x100, 0x7120 );
	LCD_WRITE_COMMAND( 0x007, 0x0103 );
	_delay_us( 10 );
	LCD_WRITE_COMMAND( 0x007, 0x0113 );


	_delay_us(20);
	
	lcd_clear_screen(GREEN);
}


/******************************************************************************
* Function Name  : lcd_clear_screen
* Description    : clear screen
* Input          : color_background: refresh background color
* Output         : None
* Return         : None
******************************************************************************/

void lcd_clear_screen(unsigned int color_background)
{
	unsigned int i,j;

	LCD_WRITE_COMMAND(0x210,0x00);
	LCD_WRITE_COMMAND(0x212,0x0000);
	LCD_WRITE_COMMAND(0x211,0xEF);
	LCD_WRITE_COMMAND(0x213,0x013F);

	
	LCD_WRITE_COMMAND(0x200,0x0000);
	LCD_WRITE_COMMAND(0x201,0x0000);

	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();

	for(i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
		{
		  LCD_WRITE_DATA( color_background );
		}
	}
	LCD_RS_L();
	LCD_CS_H();
}

/******************************************************************************
* Function Name  : lcd_clear_area
* Description    : clear area,fill
* Input          : color_front:draw a rectangle, fill with color_front
                   x:
                   y:
                   width: rectangle width
                   height:rectangle height
* Output         : None
* Return         : None
******************************************************************************/
void lcd_clear_area(unsigned int color_front, 
                    unsigned char x, 
                    unsigned int y, 
                    unsigned int width, 
                    unsigned height)
{
	unsigned int i, j;

	LCD_WRITE_COMMAND( 0x210, x ); 	//x start point
	LCD_WRITE_COMMAND( 0x212, y ); 	//y start point
	LCD_WRITE_COMMAND( 0x211, x + width - 1 );	//x end point
	LCD_WRITE_COMMAND( 0x213, y + height - 1 );	//y end point
		
	LCD_WRITE_COMMAND( 0x200, x );
	LCD_WRITE_COMMAND( 0x201, y );

	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();

	for( i = 0; i < height; i++ )
	{
		for( j = 0; j < width; j++ )
		{
			LCD_WRITE_DATA( color_front );

		}
	}
	LCD_CS_H();
}

/******************************************************************************
* Function Name  : lcd_set_cursor
* Description    : Set cursor
* Input          : x, y
* Output         : None
* Return         : None
******************************************************************************/
void lcd_set_cursor(unsigned char x, unsigned int y)
{
  	if( (x > 320) || (y > 240) )
	{
		return;
	}
	LCD_WRITE_COMMAND( 0x200, x );
	LCD_WRITE_COMMAND( 0x201, y );
}

/******************************************************************************
* Function Name  : lcd_display_char
* Description    : ch_asc: ascii code of data. position_x, position_y.
					color_front, color_background.
* Input          : None
* Output         : None
* Return         : None
******************************************************************************/
void lcd_display_char(  unsigned char ch_asc, 
                        unsigned int color_front,
                        unsigned int color_background, 
                        unsigned char postion_x, 
                        unsigned char postion_y)
{
	unsigned char i, j, b;
	const unsigned char *p = 0;
	
	LCD_WRITE_COMMAND(0x210,postion_x*8); 	//x start point
	LCD_WRITE_COMMAND(0x212,postion_y*16); 	//y start point
	LCD_WRITE_COMMAND(0x211,postion_x*8+7);	//x end point
	LCD_WRITE_COMMAND(0x213,postion_y*16+15);	//y end point

	LCD_WRITE_COMMAND(0x200,postion_x*8);	
	LCD_WRITE_COMMAND(0x201,postion_y*16);
	
		
	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();

	p = ascii;
	p += ch_asc*16;
	for(j=0;j<16;j++)
	{
		b=*(p+j);
		for(i=0;i<8;i++)
		{
			if( b & 0x80 )
			{
				LCD_WRITE_DATA(color_front);
			}
			else
			{
				LCD_WRITE_DATA(color_background);
			}
			b=b<<1;			
		}	
	}

	LCD_CS_H();
}

/******************************************************************************
* Function Name  : lcd_display_string
* Description    : *str: address of string data. 
					x: the xth row(0~30).
					y: the yth column(0~20).
					color_front, color_background.
* Input          : None
* Output         : None
* Return         : None
******************************************************************************/
void lcd_display_string(unsigned char *str, 
						unsigned int color_front, 
						unsigned int color_background, 
						unsigned char x, 
						unsigned char y )
{
	while (*str) 
	{ 
		lcd_display_char( *str, color_front, color_background, x, y);
		if(++x>=30)
		{
			x=0;
			if(++y>=20)
			{
				y=0;
			}
		}
		str ++;
    }
}

/******************************************************************************
* Function Name  : 汉字显示
* Description    : 16x16点阵的汉字显示函数
* Input          : gb:汉字对应字模中的位置，x:显示位置第几列，y:显示位置第几行
					color_front, color_background.  
* Output         : None
* Return         : None
******************************************************************************/
/*显示方法（年月日）
for( i = 2; i < 8; i++ )
{
	lcd_display_GB2312( i-2, (i-1)*2, 0 );
}
*/
void lcd_display_GB2312( unsigned char gb, 
						unsigned int color_front, 
						unsigned int color_background, 
						unsigned char postion_x, 
						unsigned char postion_y )
{
	unsigned char i,j,b;
	unsigned char *p;
	
	LCD_WRITE_COMMAND(0x210,postion_x*8); 	//x start point
	LCD_WRITE_COMMAND(0x212,postion_y*16); 	//y start point
	LCD_WRITE_COMMAND(0x211,postion_x*8+7);	//x end point
	LCD_WRITE_COMMAND(0x213,postion_y*16+15);	//y end point

	LCD_WRITE_COMMAND(0x200,postion_x*8);	
	LCD_WRITE_COMMAND(0x201,postion_y*16);

	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();

	p = (unsigned char *)GB2312;
	p += gb*32;
	for(j=0;j<32;j++)
	{
		b=*(p+j);
		for(i=0;i<8;i++)
		{
			if(b&0x80)
			{
				LCD_WRITE_DATA(color_front);
			}
			else
			{
				LCD_WRITE_DATA(color_background);
			}
			b=b<<1;
			
		}	
	}
	LCD_CS_H();
}

/******************************************************************************
* Function Name  : lcd_display_image
* Description    : Draw image
* Input          : x, y: image start at x, y. width, length, *img.
* Output         : None
* Return         : None
******************************************************************************/
void lcd_display_image( const unsigned char *img, 
					unsigned char x, 
					unsigned int y, 
					unsigned int width, 
					unsigned height )
{
	unsigned int i, j;
	unsigned int data16;


	LCD_WRITE_COMMAND( 0x210, x ); 	//x start point
	LCD_WRITE_COMMAND( 0x212, y ); 	//y start point
	LCD_WRITE_COMMAND( 0x211, x + width - 1 );	//x end point
	LCD_WRITE_COMMAND( 0x213, y + height - 1 );	//y end point
		
	LCD_WRITE_COMMAND( 0x200, x );
	LCD_WRITE_COMMAND( 0x201, y );

	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();


	for( i = 0; i < height; i++ )
	{
		for( j = 0; j < width; j++ )
		{
			//Be carful of MCU type, big endian or little endian
			//little endian
			data16 = ( *(img + 1) << 8 ) | (*img);
			LCD_WRITE_DATA( data16 );
			img += 2;
		}
	}
	LCD_CS_H();
}

//=============================================================================
//							Application Functions
//=============================================================================

/******************************************************************************
* Function Name  : lcd_display_test
* Description    : test
* Input          : None
* Output         : None
* Return         : None
******************************************************************************/
const unsigned int color[] =
{
	// 0 ~ 262143, 0x00000 ~ 0x3FFFF
	0xf800,	//red
	0x07e0,	//green
	0x001f,	//blue
	0xffe0,	//yellow
	0x0000,	//black
	0xffff,	//white
	0x07ff,	//light blue
	0xf81f	//purple
};

void lcd_display_test(void)
{
	unsigned int temp, num;
	unsigned int i;
	unsigned char n;

	lcd_clear_screen(RED);
    _delay_us(600);
	
	LCD_WRITE_COMMAND(0x210,0x00);
	LCD_WRITE_COMMAND(0x212,0x0000);
	LCD_WRITE_COMMAND(0x211,0xEF);
	LCD_WRITE_COMMAND(0x213,0x013F);
	
	LCD_WRITE_COMMAND(0x200,0x0000);
	LCD_WRITE_COMMAND(0x201,0x0000);

	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();
	//dispaly color bar
	for(n=0;n<8;n++)
	{
		LCD_CS_L();
		LCD_RS_H();
		temp=color[n];
		for(num=40*240;num>0;num--)
		{
			LCD_WRITE_DATA(temp);
		}
	}

//	_delay_us(600);

	//display pure color
	for(n=0;n<8;n++)
	{


	    temp=color[n];
		for(i=0;i<240;i++)
		{
			for(num=0;num<320;num++)
			{
		  		LCD_WRITE_DATA(temp);
			}
		}
	_delay_us(600);
	}
	lcd_clear_screen(GREEN);
	LCD_CS_H();	
	LCD_RS_H();

}

void Swap(unsigned int *a , unsigned int *b)	//for BresenhamLine
{
	unsigned int tmp;
	tmp = *a ;
	*a = *b ;
	*b = tmp ;
} 

/******************************************************************************
* Function Name  : lcd_draw_dot
* Description    : draw dot
* Input          : color, x, y
* Output         : None
* Return         : None
******************************************************************************/
void lcd_draw_dot(unsigned int color_front,
                  unsigned char x,
                  unsigned int y)
{

	LCD_SEND_COMMAND(0x210,x);
	LCD_SEND_COMMAND(0x212,y);
	LCD_SEND_COMMAND(0x211,x+1);
	LCD_SEND_COMMAND(0x213,y+1);
	
	
	LCD_RS_L();
	LCD_WRITE_REG(0x202);	//RAM Write index
	LCD_CS_L();
	LCD_WRITE_DATA(color_front);


}


/******************************************************************************
* Function Name  : lcd_draw_bigdot
* Description    : draw big dot,9 pix.
* Input          : color_frong, x, y
* Output         : None
* Return         : None
******************************************************************************/
void lcd_draw_bigdot(unsigned int   color_front,
                     unsigned int    x,
                     unsigned int    y )
{
    lcd_draw_dot(color_front,x,y);
    lcd_draw_dot(color_front,x,y+1);
    lcd_draw_dot(color_front,x,y-1);

    lcd_draw_dot(color_front,x+1,y);
    lcd_draw_dot(color_front,x+1,y+1);
    lcd_draw_dot(color_front,x+1,y-1);
    
    lcd_draw_dot(color_front,x-1,y);    
    lcd_draw_dot(color_front,x-1,y+1);
    lcd_draw_dot(color_front,x-1,y-1);
    
}

/******************************************************************************
* Function Name  : lcd_draw_line
* Description    : BresenhamLine
* Input          : c, x1, y1, x2, y2
* Output         : None
* Return         : None
******************************************************************************/
unsigned char lcd_draw_line(  
						unsigned int line_color,
                        unsigned int x1,
                        unsigned int y1,
                        unsigned int x2,
                        unsigned int y2 )
{
	unsigned int dx , dy;
	unsigned int tx , ty;
	unsigned int inc1 , inc2;
	unsigned int d , iTag;
	unsigned int x , y;
	lcd_draw_dot( line_color , x1 , y1 );
	if( x1 == x2 && y1 == y2 )	/*如果两点重合，结束后面的动作*/
	{
		return 1;
	}
	iTag = 0;
	dx = ( x2 - x1 );
	dy = ( y2 - y1 );
	if( dx < dy )	/*如果dy为计长方向，则交换纵横坐标*/
	{
		iTag = 1 ;
		Swap ( &x1, &y1 );
		Swap ( &x2, &y2 );
		Swap ( &dx, &dy );
	}
	tx = ( x2 - x1 ) > 0 ? 1 : -1;	   /*确定是增1还是减1*/
	ty = ( y2 - y1 ) > 0 ? 1 : -1;
	x = x1;
	y = y1;
	inc1 = 2 * dy;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while( x != x2 )	 /*循环画点*/
	{
		if( d < 0 )
		{
			d += inc1 ;
		}
		else
		{
			y += ty ;
			d += inc2 ;
		}
		if( iTag )
		{
			lcd_draw_dot ( line_color, y, x ) ;
		}
		else
		{
			lcd_draw_dot ( line_color, x, y ) ;
		}
		x += tx ;
	}
	return 0;
}

/**********************************************/
/* 函数功能；求m的n次方                       */
/**********************************************/
unsigned long mypow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}
/**********************************************/
/* 函数功能：显示数字                         */
/* 入口参数：x,y :起点坐标	 	              */
/*           num_len :数字的位数				  */
/*           num:数值(0~4294967295);	   	  */
/**********************************************/
void lcd_display_number(unsigned int x,
                        unsigned int y,
                        unsigned long num,
                        unsigned char num_len )
{         	
	unsigned char t,temp;
	unsigned char enshow=0;		 // 此变量用来去掉最高位的0	
				   
	for(t=0;t<num_len;t++)
	{
		temp=(num/mypow(10,num_len-t-1))%10;
		if(enshow==0&&t<(num_len-1))
		{
			if(temp==0)
			{
				//lcd_display_char(' ',BLACK,WHITE,x+8*t,y);
                lcd_display_char(' ',BLACK,WHITE,x+t,y);
				continue;
			}else enshow=1; 
		 	 
		}
	 	//lcd_display_char(temp+'0',BLACK,WHITE,x+8*t,y); 
        lcd_display_char(temp+'0',BLACK,WHITE,x+t,y); 
	}
} 
/********************************end of file**************************************/


