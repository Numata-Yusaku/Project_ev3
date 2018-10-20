#ifndef	__HW_H__
#define	__HW_H__

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
#define	D_RSI_HW_SOUND_MANUAL_STOP		(-1)		/* 音声の再生を手動で停止するためのフラグ */
#define	D_RSI_HW_NOTE_C4				(unsigned short)(261.63)	/* ノートC4の周波数 */
#define	D_RSI_HW_NOTE_CS4				(unsigned short)(277.18)	/* ノートC#4の周波数 */
#define	D_RSI_HW_NOTE_D4				(unsigned short)(293.66)	/* ノートD4の周波数 */
#define	D_RSI_HW_NOTE_DS4				(unsigned short)(311.13)	/* ノートD#4の周波数 */
#define	D_RSI_HW_NOTE_E4				(unsigned short)(329.63)	/* ノートE4の周波数 */
#define	D_RSI_HW_NOTE_F4				(unsigned short)(349.23)	/* ノートF4の周波数 */
#define	D_RSI_HW_NOTE_FS4				(unsigned short)(369.99)	/* ノートF#4の周波数 */
#define	D_RSI_HW_NOTE_G4				(unsigned short)(392.00)	/* ノートG4の周波数 */
#define	D_RSI_HW_NOTE_GS4				(unsigned short)(415.30)	/* ノートG#4の周波数 */
#define	D_RSI_HW_NOTE_A4				(unsigned short)(440.00)	/* ノートA4の周波数 */
#define	D_RSI_HW_NOTE_AS4				(unsigned short)(466.16)	/* ノートA#4の周波数 */
#define	D_RSI_HW_NOTE_B4				(unsigned short)(493.88)	/* ノートB4の周波数 */
#define	D_RSI_HW_NOTE_C5				(unsigned short)(523.25)	/* ノートC5の周波数 */
#define	D_RSI_HW_NOTE_CS5				(unsigned short)(554.37)	/* ノートC#5の周波数 */
#define	D_RSI_HW_NOTE_D5				(unsigned short)(587.33)	/* ノートD5の周波数 */
#define	D_RSI_HW_NOTE_DS5				(unsigned short)(622.25)	/* ノートD#5の周波数 */
#define	D_RSI_HW_NOTE_E5				(unsigned short)(659.25)	/* ノートE5の周波数 */
#define	D_RSI_HW_NOTE_F5				(unsigned short)(698.46)	/* ノートF5の周波数 */
#define	D_RSI_HW_NOTE_FS5				(unsigned short)(739.99)	/* ノートF#5の周波数 */
#define	D_RSI_HW_NOTE_G5				(unsigned short)(783.99)	/* ノートG5の周波数 */
#define	D_RSI_HW_NOTE_GS5				(unsigned short)(830.61)	/* ノートG#5の周波数 */
#define	D_RSI_HW_NOTE_A5				(unsigned short)(880.00)	/* ノートA5の周波数 */
#define	D_RSI_HW_NOTE_AS5				(unsigned short)(932.33)	/* ノートA#5の周波数 */
#define	D_RSI_HW_NOTE_B5				(unsigned short)(987.77)	/* ノートB5の周波数 */
#define	D_RSI_HW_NOTE_C6				(unsigned short)(1046.50)	/* ノートC6の周波数 */
#define	D_RSI_HW_NOTE_CS6				(unsigned short)(1108.73)	/* ノートC#6の周波数 */
#define	D_RSI_HW_NOTE_D6				(unsigned short)(1174.66)	/* ノートD6の周波数 */
#define	D_RSI_HW_NOTE_DS6				(unsigned short)(1244.51)	/* ノートD#6の周波数 */
#define	D_RSI_HW_NOTE_E6				(unsigned short)(1318.51)	/* ノートE6の周波数 */
#define	D_RSI_HW_NOTE_F6				(unsigned short)(1396.91)	/* ノートF6の周波数 */
#define	D_RSI_HW_NOTE_FS6				(unsigned short)(1479.98)	/* ノートF#6の周波数 */
#define	D_RSI_HW_NOTE_G6				(unsigned short)(1567.98)	/* ノートG6の周波数 */
#define	D_RSI_HW_NOTE_GS6				(unsigned short)(1661.22)	/* ノートG#6の周波数 */
#define	D_RSI_HW_NOTE_A6				(unsigned short)(1760.00)	/* ノートA6の周波数 */
#define	D_RSI_HW_NOTE_AS6				(unsigned short)(1864.66)	/* ノートA#6の周波数 */
#define	D_RSI_HW_NOTE_B6				(unsigned short)(1975.53)	/* ノートB6の周波数 */

enum EN_RSI_HW_BUTTON
{
	E_RSI_HW_BUTTON_LEFT = 0,	/* 左ボタン */
	E_RSI_HW_BUTTON_RIGHT,		/* 右ボタン */
	E_RSI_HW_BUTTON_UP,			/* 上ボタン */
	E_RSI_HW_BUTTON_DOWN,		/* 下ボタン */
	E_RSI_HW_BUTTON_ENTER,		/* 中央ボタン */
	E_RSI_HW_BUTTON_BACK,		/* 戻るボタン */

	/* ここより上に定義すること */
	E_RSI_HW_BUTTON_TNUM,		/* ボタンの数 */
};

enum EN_RSI_HW_LEDCOLOR
{
	E_RSI_HW_LEDCOLOR_OFF = 0,								/* オフ */
	E_RSI_HW_LEDCOLOR_RED = 1 << 0,							/* 赤 */
	E_RSI_HW_LEDCOLOR_GREEN = 1 << 1,						/* 緑 */
	E_RSI_HW_LEDCOLOR_ORANGE								/* オレンジ */
		= E_RSI_HW_LEDCOLOR_RED | E_RSI_HW_LEDCOLOR_GREEN,
};
/***** 構造体 *****/

/***** 関数プロトタイプ *****/
/* battery */
int RSI_hw_battery_current_mA( void );
int RSI_hw_battery_voltage_mV( void );

/* button */
int RSI_hw_button_is_pressed( int iButton );
int RSI_hw_button_set_on_clicked( int iButton, void* vpHandler, intptr_t exinf );

/* led */
int RSI_hw_led_set_color( int iColor );

/* speaker */
int RSI_hw_speaker_set_volume( unsigned char ucVolume );
int RSI_hw_speaker_play_tone( unsigned short usFrequency, signed int siDuration );
int RSI_hw_speaker_play_file( const S_RSI_FILEINFO* spMemfile, signed int siDuration );
int RSI_hw_speaker_stop( void );

/***** テーブル *****/


#endif	/* __HW_H__ */
