//=================================================
/*#define FlashPageRead				0x52	// Main memory page read
#define FlashToBuf1Transfer 		0x53	// Main memory page to buffer 1 transfer
#define Buf1Read					0x54	// Buffer 1 read
#define FlashToBuf2Transfer 		0x55	// Main memory page to buffer 2 transfer
#define Buf2Read					0x56	// Buffer 2 read
#define StatusReg					0x57	// Status register
#define AutoPageReWrBuf1			0x58	// Auto page rewrite through buffer 1
#define AutoPageReWrBuf2			0x59	// Auto page rewrite through buffer 2
#define FlashToBuf1Compare    		0x60	// Main memory page to buffer 1 compare
#define FlashToBuf2Compare	    	0x61	// Main memory page to buffer 2 compare
#define ContArrayRead				0x68	// Continuous Array Read (Note : Only A/B-parts supported)
#define FlashProgBuf1				0x82	// Main memory page program through buffer 1
#define Buf1ToFlashWE   			0x83	// Buffer 1 to main memory page program with built-in erase
#define Buf1Write					0x84	// Buffer 1 write
#define FlashProgBuf2				0x85	// Main memory page program through buffer 2
#define Buf2ToFlashWE   			0x86	// Buffer 2 to main memory page program with built-in erase
#define Buf2Write					0x87	// Buffer 2 write
#define Buf1ToFlash     			0x88	// Buffer 1 to main memory page program without built-in erase
#define Buf2ToFlash		         	0x89	// Buffer 2 to main memory page program without built-in erase*/
//=========Read Commands============
#define ReadContArray 			0x68	
#define ReadFlashPage			0x52	
#define ReadBuffer1 			0x54	
#define ReadBuffer2 			0x56	
#define ReadStatusReg			0x57	
//====Program and Erase Command=====
#define WriteBuffer1			0x84	
#define WriteBuffer2			0x87	
#define Buf1ToFlashWithE   		0x83	
#define Buf2ToFlashWithE   		0x86	
#define Buf1ToFlashWithoutE    	0x88	
#define Buf2ToFlashWEthoutE     0x89	
#define PageErase		        0x81	
#define BlockErase		        0x50	
#define FlashProgBuffer1		0x82	
#define FlashProgBuffer2		0x85	
//========Additional Commands=======

#define FlashToBuffer1Tranfer	0x53	
#define FlashToBuffer2Tranfer	0x55	
#define FlashToBuffer1Compare	0x60	
#define FlashToBuffer2Compare	0x61	
#define AutoPageRewriteBuffer1	0x58	
#define AutoPageRewriteBuffer2	0x59	
//==============================================================
#define AT45DB_PORT		PORTE	 				
#define AT45DB_DDR		DDRE	   				
#define AT45DB_PIN		PINE      	
#define MOSI_1	 		AT45DB_PORT|= 1<<3	  	
#define MOSI_0	 	  	AT45DB_PORT&=~(1<<3)    
#define SCK_1	 		AT45DB_PORT|= 1<<4		
#define SCK_0			AT45DB_PORT&=~(1<<4)		
#define CS_1	 		AT45DB_PORT|= 1<<5		
#define CS_0			AT45DB_PORT&=~(1<<5)	
#define MISO	 		(PINE&(1<<2))	
#define BUSY	 		(PINE&(1<<6))		
//==================================================================
/*void Init_SPI()
{
	clk = 0;
	cs = 1;
	delay_ms(1);
	cs = 0;
	delay_ms(1);
}	*/

SPI_Transmit(int data)
{
	int temp, i;
	for(i = 0; i < 8; i++)
	{
		SCK_0; delay50us(2);
		temp = data;
		temp = temp & 0b10000000;
		if(temp == 0x80)
		{
			MOSI_1;
		}
		else
		{
			MOSI_0;
		}
		data = data << 1;	
		SCK_1;
		delay50us(2);		
	}
}

int SPI_read()
{
	int data, i;
	data = 0;	
	for(i = 0; i < 8; i++)
	{
		SCK_0;
		delay50us(2);
		data <<= 1;
		if(MISO)
			data |= 0x01;
		SCK_1;
		delay50us(2);
	}
	return data;
}

void Write_Buffer(uchar BufferNO,uint BufferOffset,uint NO,uchar *pc)
{							
	CS_0;					
	while(!BUSY);				
	if(BufferNO == 1)
	{	
		SPI_Transmit(WriteBuffer1);			
	}
	else
	if(BufferNO == 2)
	{	
		SPI_Transmit(WriteBuffer2);			
	}	
	else return;							
	SPI_Transmit(0x00);						
	SPI_Transmit((uchar)(BufferOffset>>8));	
	SPI_Transmit((uchar)BufferOffset);		
	do
	{
		SPI_Transmit(*pc);					
		pc++;				
	}
	while(--NO);
	CS_1;									
}
//=================================================================
void Read_Buffer(uchar BufferNO,uint BufferOffset,uint NO,uchar *pc)
{							
	CS_0;				
	while(!BUSY);					
	if(BufferNO == 1)
	{	
		SPI_Transmit(ReadBuffer1);			
	}
	else
	if(BufferNO == 2)
	{	
		SPI_Transmit(ReadBuffer2);			
	}	
	else return;							
	SPI_Transmit(0x00);						
	SPI_Transmit((uchar)(BufferOffset>>8));	
	SPI_Transmit((uchar)BufferOffset);		
	SPI_Transmit(0x00);						
	do
	{
		//SPI_Transmit(0x00);					
		*pc=SPI_read();							
		pc++;								
	}
	while(--NO);
	CS_1;									
}
	