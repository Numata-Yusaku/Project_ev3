#ifndef	__LCD_H__
#define	__LCD_H__

/***** �C���N���[�h *****/
#include <stdio.h>
#include "rsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */

/*** GEN ***/

/*** APL ***/

/***** �萔 *****/
#define	D_RSI_LCD_WIDTH			(178)	/* LCD��ʂ̕� */
#define	D_RSI_LCD_HEIGHT		(128)	/* LCD��ʂ̍��� */


enum EN_RSI_LCD_FONT
{
	E_RSI_LCD_FONT_SMALL = 0,		/* �������T�C�Y�̃t�H���g */
	E_RSI_LCD_FONT_MEDIUM,			/* ���ʃT�C�Y�̃t�H���g */
};

enum EN_RSI_LCD_COLOR
{
	E_RSI_LCD_COLOR_WHITE = 0,		/* �� */
	E_RSI_LCD_COLOR_BLACK,			/* �� */
};

/***** �\���� *****/
typedef struct
{
	signed int	width;
	signed int	height;
	void*		vpData;
}S_RSI_LCD_IMAGE;

/***** �֐��v���g�^�C�v *****/
/* font */
int RSI_lcd_set_font( int iFont );
int RSI_lcd_font_get_size( int iFont, signed int* sipWidth, signed int* sipHeight );

/* image */
int RSI_lcd_image_load( const S_RSI_MEMFILE* spMemfile, S_RSI_LCD_IMAGE* spImage );
int RSI_lcd_image_free( S_RSI_LCD_IMAGE* spImage );

/* lcd */
int RSI_lcd_draw_string( const char* str, signed int siXpoint, signed int siYpoint );
int RSI_lcd_draw_line( signed int siXsta, signed int siYsta, signed int siXend, signed int siYend );
int RSI_lcd_fill_rect( signed int siXpoint, signed int siYpoint, signed int siWidth, signed int siHeight, int iColor );
int RSI_lcd_draw_image( const S_RSI_LCD_IMAGE* spImage, signed int siXpoint, signed int siYpoint );

/***** �e�[�u�� *****/


#endif	/* __LCD_H__ */
