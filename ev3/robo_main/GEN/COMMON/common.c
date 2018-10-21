#include "common.h"

void COMMON_lcd_draw_string( const char* str, signed int siXpoint, signed int siYpoint )
{
#if	(__VC_DEBUG__)
	printf("%s\n", str );
#else	/* __VC_DEBUG__ */
	RSI_lcd_draw_string( str, siXpoint, siYpoint );
#endif	/* __VC_DEBUG__ */
	return;
}

void COMMON_lcd_draw_stringAndDec( const char* str, int iDecValue , signed int siXpoint, signed int siYpoint )
{
	char cBuff[256];
	
	memset( &cBuff, 0x00, sizeof(cBuff) );
	
	/* ï∂éöóÒåãçá */
	sprintf( cBuff, "%s%d", str , iDecValue );
	
#if	(__VC_DEBUG__)
	printf("%s\n", cBuff );
#else	/* __VC_DEBUG__ */
	RSI_lcd_draw_string( (const char*)(&cBuff), siXpoint, siYpoint );
#endif	/* __VC_DEBUG__ */
	return;
}

void COMMON_lcd_draw_stringAndHex( const char* str, int iHexValue , signed int siXpoint, signed int siYpoint )
{
	char cBuff[256];
	
	memset( &cBuff, 0x00, sizeof(cBuff) );
	
	/* ï∂éöóÒåãçá */
	sprintf( cBuff, "%s0x%08x", str , iHexValue );
	
#if	(__VC_DEBUG__)
	printf("%s\n", cBuff );
#else	/* __VC_DEBUG__ */
	RSI_lcd_draw_string( (const char*)(&cBuff), siXpoint, siYpoint );
#endif	/* __VC_DEBUG__ */
	return;
}

void COMMON_lcd_draw_stringAndPoint( const char* str, void* iPointValue, signed int siXpoint, signed int siYpoint )
{
	char cBuff[256];
	
	memset( &cBuff, 0x00, sizeof(cBuff) );
	
	/* ï∂éöóÒåãçá */
	sprintf( cBuff, "%s0x%p", str , iPointValue );
	
#if	(__VC_DEBUG__)
	printf("%s\n", cBuff );
#else	/* __VC_DEBUG__ */
	RSI_lcd_draw_string( (const char*)(&cBuff), siXpoint, siYpoint );
#endif	/* __VC_DEBUG__ */
	
	return;
}
