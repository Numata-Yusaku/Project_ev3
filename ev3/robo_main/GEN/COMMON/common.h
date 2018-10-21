#ifndef	__COMMON_H__
#define	__COMMON_H__

/***** �C���N���[�h *****/
/* �W�����C�u���� */
#if	(__VC_DEBUG__)
#include <Windows.h>
#include <process.h>
#else	/* __VC_DEBUG__ */
#endif	/* __VC_DEBUG__ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* RSI */
#include "fs.h"
#include "hw.h"
#include "lcd.h"
#include "motor.h"
#include "sensor.h"

/* TOPPERS */


/* ���C�� */

/***** �萔 *****/

/***** �\���� *****/

/***** �֐��v���g�^�C�v *****/
void COMMON_lcd_draw_string( const char* str, signed int siXpoint, signed int siYpoint );
void COMMON_lcd_draw_stringAndDec( const char* str, int iDecValue, signed int siXpoint, signed int siYpoint );
void COMMON_lcd_draw_stringAndHex( const char* str, int iHexValue, signed int siXpoint, signed int siYpoint );

/***** �e�[�u�� *****/


#endif	/* __COMMON_H__ */
