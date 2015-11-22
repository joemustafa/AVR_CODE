#include"avr/io.h"
#include"SPI0.h"

//#define uint unsigned int
//#define uchar unsigned char


void SPI0_Init(void);
uchar SPI0_communication(uchar send_char);


//****************************************** 
//SPI��ʼ�� 
//****************************************** 

void SPI0_Init(void)
{

	SPCR=0x59;          //ʹ��SPI �� ����SPIΪ��ģʽ������ʱCLIΪ1����һ�������زɼ����ݣ�ʱ��    FOSC/16
	SPSR=0x00;			//setup SPI
	DDRB=0x07;
//	PORB=0X00;
//	SPI_RxHead = 0; 
//	SPI_TxHead = 0; 
	
}

//****************************************** 
//�������� 
//****************************************** 

uchar SPI0_communication(uchar send_char)
{
	SPDR = send_char;               //�������ݴ���
	while (!(SPSR & (1<<SPIF)));    //�ȴ��������
	return SPDR;
}


























