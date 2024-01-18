#ifndef _COLOR_H_
#define _COLOR_H_

#define WHITE               	0xFFFF
#define BLACK              	 	0x0000
#define RED                	 	0xF800
#define BLUE                	0x001F
#define GREEN               	0x07E0

//��ɫ��ʽ
#define STYLE_DEFAULT

//Ĭ����ɫ��ʽ
#ifdef STYLE_DEFAULT

	#define BG_COLOR			0x33d6 	
	#define TXT_COLOR			0xFFFF
	#define ACTIVE_COLOR		0x2b12

#endif

//��ɫ��ʽ
#ifdef STYLE_GREEN

	#define BG_COLOR			0x5dcb 	
	#define TXT_COLOR			0xFFFF
	#define ACTIVE_COLOR		0x44e8

#endif

//��ɫ��ʽ
#ifdef STYLE_YELLOW

	#define BG_COLOR			0xf569 	
	#define TXT_COLOR			0xFFFF
	#define ACTIVE_COLOR		0xeca3

#endif

//��ɫ��ʽ
#ifdef STYLE_RED

	#define BG_COLOR			0xda89 	
	#define TXT_COLOR			0xFFFF
	#define ACTIVE_COLOR		0xc985

#endif

#endif
