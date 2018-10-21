#include "common.h"

void COMMON_lcd_draw_string( const char* str, signed int siXpoint, signed int siYpoint )
{
	RSI_lcd_draw_string( str, siXpoint, siYpoint );
	
	return;
}

void COMMON_lcd_draw_stringAndDec( const char* str, int iDecValue , signed int siXpoint, signed int siYpoint )
{
	char cBuff[256];
	
	memset( &cBuff, 0x00, sizeof(cBuff) );
	
	/* ï∂éöóÒåãçá */
	sprintf( cBuff, "%s%d", str , iDecValue );
	
	RSI_lcd_draw_string( (const char*)(&cBuff), siXpoint, siYpoint );
	
	return;
}

void COMMON_lcd_draw_stringAndHex( const char* str, int iHexValue , signed int siXpoint, signed int siYpoint )
{
	char cBuff[256];
	
	memset( &cBuff, 0x00, sizeof(cBuff) );
	
	/* ï∂éöóÒåãçá */
	sprintf( cBuff, "%s0x%08x", str , iHexValue );
	
	RSI_lcd_draw_string( (const char*)(&cBuff), siXpoint, siYpoint );
	
	return;
}

