#ifndef Software_H
#define Software_H

#include <math.h>
#include <string.h>

typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned long	ulong;
typedef signed char		schar;
typedef signed int		sint;
typedef signed long		slong;

typedef unsigned char	bool;
typedef unsigned char	uint8;
typedef unsigned int	uint16;
typedef unsigned long   uint32;
typedef signed  char	sint8;
typedef signed	int		sint16;
typedef signed	long	sint32;
typedef signed  char	int8;
typedef signed  int		int16;
typedef signed  long	int32;

//typedef unsigned char ubyte;
//typedef unsigned int	uword;
//typedef unsigned long udword;
//typedef signed   char	sbyte;
//typedef signed   int	sword;
//typedef signed   long	sdword;

//#define NULL			0
//#define EOF			-1
//#define TRUE   		1
//#define FALSE  		0
//#define YES   		1
//#define NO  			0
//#define ON			1
//#define OFF			0
//#define ENABLE   		1
//#define DISABLE		0
//#define CRR			1
//#define ERR			0
//#define RIGHT			1
//#define WRONG			0
//#define SUCCESS		1
//#define FAILURE		0
//#define PI			3.1415926	//3.1415926535897932

//#define _CALLOC(a)		( (a *)calloc(n,sizeof(a)) )
//#define _MALLOC(a)		( (a *)malloc(sizeof(a)) )
//#define _MIN(a,b)			( (a) < (b) ? (a) : (b) )
//#define _MAX(a,b)			( (a) > (b) ? (a) : (b) )
//#define _EXCHANGE(a,b)	{ int t; t=a; a=b; b=t; }
//#define _TOLOWER(c)		( (c)+32 )
//#define _TOUPPER(c)		( (c)-32 )

//#ifndef BIT
//#define BIT(x)	( 1<<(x) )
//#endif

uint8 dataElem[6];
void speaData(uint32 dat,sint8 len)
{
    uint8 i;
    uint32 j,y;
    for(i=0,j=1;i<len;i++)
    {
        y=dat/j;
        dataElem[i]=y%10;
        j*=10;
    }
}

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )

#define converseIntToHex(dec)	( ( ((dec)>>4) *10 ) + ((dec)%16) )

#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )

#define converseHexToInt(hex)	( ( ((hex)/10) <<4 ) + ((hex)%10) )

#endif
