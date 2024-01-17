#ifndef __JPG_DECODER_H__
#define __JPG_DECODER_H__

#include "uiDisplay.h"

#define M_SOF0  0xc0
#define M_DHT   0xc4
#define M_EOI   0xd9
#define M_SOS   0xda
#define M_DQT   0xdb
#define M_DRI   0xdd
#define M_APP0  0xe0

static int Zig_Zag[8][8]={{0,1,5,6,14,15,27,28},
					  	  {2,4,7,13,16,26,29,42},
						  {3,8,12,17,25,30,41,43},
						  {9,11,18,24,37,40,44,53},
						  {10,19,23,32,39,45,52,54},
						  {20,22,33,38,46,51,55,60},
						  {21,34,37,47,50,56,59,61},
						  {35,36,48,49,57,58,62,63}
						 };

#define W1 2841 /* 2048*sqrt(2)*cos(1*pi/16) */
#define W2 2676 /* 2048*sqrt(2)*cos(2*pi/16) */
#define W3 2408 /* 2048*sqrt(2)*cos(3*pi/16) */
#define W5 1609 /* 2048*sqrt(2)*cos(5*pi/16) */
#define W6 1108 /* 2048*sqrt(2)*cos(6*pi/16) */
#define W7 565  /* 2048*sqrt(2)*cos(7*pi/16) */


//*************************************************************************************
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
					   
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;	  

typedef int HFILE;
typedef CHAR *LPSTR, *PSTR;

#define FALSE 0
#define TRUE 1  

/* constants for the biCompression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L    

typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
} RGBQUAD;
typedef RGBQUAD * LPRGBQUAD;


#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
	   
//宏定义					   
#define WIDTHBYTES(i)    ((i+31)/32*4)//??????????
//#define PI 3.1415926535
//函数返回值定义
#define FUNC_OK 0
#define FUNC_MEMORY_ERROR 1
#define FUNC_FILE_ERROR 2
#define FUNC_FORMAT_ERROR 3


//////////////////////////////////////////////////
//JPEG 解码函数
char showJPG (const unsigned char *JpegData, unsigned short left,unsigned short top);
void showerror(int funcret);
int  InitTag(void);
void InitTable(void);
int  Decode(unsigned short left,unsigned short top);
int  DecodeMCUBlock(void);
int  HufBlock(BYTE dchufindex,BYTE achufindex);
int  DecodeElement(void);
void IQtIZzMCUComponent(short flag);
void IQtIZzBlock(short  *s ,int * d,short flag);
void GetYUV(short flag);
void StoreBuffer(unsigned short left,unsigned short top);

BYTE ReadByte(void);
void Initialize_Fast_IDCT(void);
void Fast_IDCT(int * block);
void idctrow(int * blk);
void idctcol(int * blk);


#endif