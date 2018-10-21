#include "lcd.h"

/*** font ***/

/********************************************************/
/* デフォルトのフォントを設定する						*/
/********************************************************/
int RSI_lcd_set_font( int iFont )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LCD],Font,%d\n", iFont );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_lcd_set_font( (lcdfont_t )iFont );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* フォントのサイズを取得する							*/
/********************************************************/
int RSI_lcd_font_get_size( int iFont, signed int* sipWidth, signed int* sipHeight )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LCD],Font,%d\n", iFont);
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_font_get_size( (lcdfont_t)iFont, (int32_t*)sipWidth, (int32_t*)sipHeight );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/*** image ***/

/********************************************************/
/* メモリファイルから画像をロードする					*/
/********************************************************/
int RSI_lcd_image_load( const S_RSI_MEMFILE* spMemfile, S_RSI_LCD_IMAGE* spImage )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_image_load( (const memfile_t*)spMemfile, (image_t*)spImage );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 画像のオブジェクトを解放する							*/
/********************************************************/
int RSI_lcd_image_free( S_RSI_LCD_IMAGE* spImage )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_image_free( (image_t*)spImage );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/*** lcd ***/

/********************************************************/
/* 指定位置で文字列を描く								*/
/********************************************************/
int RSI_lcd_draw_string( const char* str, signed int siXpoint, signed int siYpoint )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_lcd_draw_string( str, (int32_t)siXpoint, (int32_t)siYpoint );
#endif	/* __VC_DEBUG__ */
//	printf("[LCD],%s,[%d %d]\n",str, siXpoint, siYpoint );
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 指定座標で線を引く									*/
/********************************************************/
int RSI_lcd_draw_line( signed int siXsta, signed int siYsta, signed int siXend, signed int siYend )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LCD],[%d %d] [%d %d]\n", siXsta, siYsta, siXend, siYend );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_lcd_draw_line( (int32_t)siXsta, (int32_t)siYsta, (int32_t)siXend, (int32_t)siYend );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 矩形を描いて色を塗る									*/
/********************************************************/
int RSI_lcd_fill_rect( signed int siXpoint, signed int siYpoint, signed int siWidth, signed int siHeight, int iColor )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LCD],[%d %d] %d/%d Color is %d\n", siXpoint, siYpoint, siWidth, siHeight, iColor );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_lcd_fill_rect( (int32_t)siXpoint, (int32_t)siYpoint, (int32_t)siWidth, (int32_t)siHeight, (lcdcolor_t) iColor );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 指定座標で画像を表示する								*/
/********************************************************/
int RSI_lcd_draw_image( const S_RSI_LCD_IMAGE* spImage, signed int siXpoint, signed int siYpoint )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LCD],[%d %d]\n", siXpoint, siYpoint );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_lcd_draw_image( (const image_t*)spImage, (int32_t)siXpoint, (int32_t)siYpoint );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}
