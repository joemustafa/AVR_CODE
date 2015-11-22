/*
*========================================================================================================
*
* File                : ws_ps2_code.h
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

#ifndef _ws_ps2_code_c
#define _ws_ps2_code_c

#include <ws_ps2port.h>

const uint8_t keyboardToAscii[][2] = {
	{0x1C, 'a'},
	{0x32, 'b'},
	{0x21, 'c'},
	{0x23, 'd'},
	{0x24, 'e'},
	{0x2B, 'f'},
	{0x34, 'g'},
	{0x33, 'h'},
	{0x43, 'i'},
	{0x3B, 'j'},
	{0x42, 'k'},
	{0x4B, 'l'},
	{0x3A, 'm'},
	{0x31, 'n'},
	{0x44, 'o'},
	{0x4D, 'p'},
	{0x15, 'q'},
	{0x2D, 'r'},
	{0x1B, 's'},
	{0x2C, 't'},
	{0x3C, 'u'},
	{0x2A, 'v'},
	{0x1D, 'w'},
	{0x22, 'x'},
	{0x35, 'y'},
	{0x1A, 'z'},
	{0x45, '0'},
	{0x16, '1'},
	{0x1E, '2'},
	{0x26, '3'},
	{0x25, '4'},
	{0x2E, '5'},
	{0x36, '6'},
	{0x3D, '7'},
	{0x3E, '8'},
	{0x46, '9'},
	{0x0E, '`'},
	{0x4E, '-'},
	{0x55, '='},
	{0x5D, '\\'},
	{0x29, ' '},
	{0x54, '['},
	{0x5B, ']'},
	{0x4C, ';'},
	{0x52, '\''},
	{0x41, ','},
	{0x49, '.'},
	{0x4A, '/'},
	{0x71, '.'},
	{0x70, '0'},
	{0x69, '1'},
	{0x72, '2'},
	{0x7A, '3'},
	{0x6B, '4'},
	{0x73, '5'},
	{0x74, '6'},
	{0x6C, '7'},
	{0x75, '8'},
	{0x7D, '9'}
};

uint8_t	ps2GetChar(void)
{
	uint8_t	ps2char = 0x00;
	uint8_t ps2num = 0x00;

	ps2char = ps2GetCode();
	while(1)
	{
		if(ps2num > ((sizeof(keyboardToAscii)) >> 1)) 
			return(0);
		else if(keyboardToAscii[ps2num][0] == ps2char) 
			return(keyboardToAscii[ps2num][1]);
		ps2num++;
	}
}
#endif /*_ws_ps2_code_c*/
