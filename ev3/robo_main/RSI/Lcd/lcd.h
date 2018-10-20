#ifndef	__LCD_H__
#define	__LCD_H__

/***** インクルード *****/
#include <stdio.h>
#include "rsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */

/*** GEN ***/

/*** APL ***/

/***** 定数 *****/
#define	D_RSI_LCD_WIDTH			(178)	/* LCD画面の幅 */
#define	D_RSI_LCD_HEIGHT		(128)	/* LCD画面の高さ */


enum EN_RSI_LCD_FONT
{
	E_RSI_LCD_FONT_SMALL = 0,		/* 小さいサイズのフォント */
	E_RSI_LCD_FONT_MEDIUM,			/* 普通サイズのフォント */
};

enum EN_RSI_LCD_COLOR
{
	E_RSI_LCD_COLOR_WHITE = 0,		/* 白 */
	E_RSI_LCD_COLOR_BLACK,			/* 黒 */
};

/***** 構造体 *****/
typedef struct
{
	signed int	width;
	signed int	height;
	void*		vpData;
}S_RSI_LCD_IMAGE;

/***** 関数プロトタイプ *****/
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

/***** テーブル *****/


#endif	/* __LCD_H__ */
