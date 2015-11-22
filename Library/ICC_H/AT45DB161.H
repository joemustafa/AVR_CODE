//==================================   				
void spi_init(void)
{
	SPCR=0x5C;    
}
//==================================
void spi_transmit_byte(uchar Data)
{	
	SPDR=Data;								
    while(!(SPSR&0x80));
}
//============================================================
void write_buffer(uint BufferOffset,uchar data)
{					
	spi_transmit_byte(0x84);			  						
	spi_transmit_byte(0xff);						
	spi_transmit_byte(BufferOffset>>8);	
	spi_transmit_byte(BufferOffset);		
	spi_transmit_byte(data);			
}
//================================================================
uchar read_buffer(uint BufferOffset)
{		
    uchar temp;	 	
 	spi_transmit_byte(0xD4);			
	spi_transmit_byte(0xff);						
	spi_transmit_byte(BufferOffset>>8);	
	spi_transmit_byte(BufferOffset);		
	spi_transmit_byte(0xff);						
	spi_transmit_byte(0xff);					
	temp=SPDR;	  
    return temp;								
} 