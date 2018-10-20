#ifndef	__HW_H__
#define	__HW_H__

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
#define	D_RSI_HW_SOUND_MANUAL_STOP		(-1)		/* �����̍Đ����蓮�Œ�~���邽�߂̃t���O */
#define	D_RSI_HW_NOTE_C4				(unsigned short)(261.63)	/* �m�[�gC4�̎��g�� */
#define	D_RSI_HW_NOTE_CS4				(unsigned short)(277.18)	/* �m�[�gC#4�̎��g�� */
#define	D_RSI_HW_NOTE_D4				(unsigned short)(293.66)	/* �m�[�gD4�̎��g�� */
#define	D_RSI_HW_NOTE_DS4				(unsigned short)(311.13)	/* �m�[�gD#4�̎��g�� */
#define	D_RSI_HW_NOTE_E4				(unsigned short)(329.63)	/* �m�[�gE4�̎��g�� */
#define	D_RSI_HW_NOTE_F4				(unsigned short)(349.23)	/* �m�[�gF4�̎��g�� */
#define	D_RSI_HW_NOTE_FS4				(unsigned short)(369.99)	/* �m�[�gF#4�̎��g�� */
#define	D_RSI_HW_NOTE_G4				(unsigned short)(392.00)	/* �m�[�gG4�̎��g�� */
#define	D_RSI_HW_NOTE_GS4				(unsigned short)(415.30)	/* �m�[�gG#4�̎��g�� */
#define	D_RSI_HW_NOTE_A4				(unsigned short)(440.00)	/* �m�[�gA4�̎��g�� */
#define	D_RSI_HW_NOTE_AS4				(unsigned short)(466.16)	/* �m�[�gA#4�̎��g�� */
#define	D_RSI_HW_NOTE_B4				(unsigned short)(493.88)	/* �m�[�gB4�̎��g�� */
#define	D_RSI_HW_NOTE_C5				(unsigned short)(523.25)	/* �m�[�gC5�̎��g�� */
#define	D_RSI_HW_NOTE_CS5				(unsigned short)(554.37)	/* �m�[�gC#5�̎��g�� */
#define	D_RSI_HW_NOTE_D5				(unsigned short)(587.33)	/* �m�[�gD5�̎��g�� */
#define	D_RSI_HW_NOTE_DS5				(unsigned short)(622.25)	/* �m�[�gD#5�̎��g�� */
#define	D_RSI_HW_NOTE_E5				(unsigned short)(659.25)	/* �m�[�gE5�̎��g�� */
#define	D_RSI_HW_NOTE_F5				(unsigned short)(698.46)	/* �m�[�gF5�̎��g�� */
#define	D_RSI_HW_NOTE_FS5				(unsigned short)(739.99)	/* �m�[�gF#5�̎��g�� */
#define	D_RSI_HW_NOTE_G5				(unsigned short)(783.99)	/* �m�[�gG5�̎��g�� */
#define	D_RSI_HW_NOTE_GS5				(unsigned short)(830.61)	/* �m�[�gG#5�̎��g�� */
#define	D_RSI_HW_NOTE_A5				(unsigned short)(880.00)	/* �m�[�gA5�̎��g�� */
#define	D_RSI_HW_NOTE_AS5				(unsigned short)(932.33)	/* �m�[�gA#5�̎��g�� */
#define	D_RSI_HW_NOTE_B5				(unsigned short)(987.77)	/* �m�[�gB5�̎��g�� */
#define	D_RSI_HW_NOTE_C6				(unsigned short)(1046.50)	/* �m�[�gC6�̎��g�� */
#define	D_RSI_HW_NOTE_CS6				(unsigned short)(1108.73)	/* �m�[�gC#6�̎��g�� */
#define	D_RSI_HW_NOTE_D6				(unsigned short)(1174.66)	/* �m�[�gD6�̎��g�� */
#define	D_RSI_HW_NOTE_DS6				(unsigned short)(1244.51)	/* �m�[�gD#6�̎��g�� */
#define	D_RSI_HW_NOTE_E6				(unsigned short)(1318.51)	/* �m�[�gE6�̎��g�� */
#define	D_RSI_HW_NOTE_F6				(unsigned short)(1396.91)	/* �m�[�gF6�̎��g�� */
#define	D_RSI_HW_NOTE_FS6				(unsigned short)(1479.98)	/* �m�[�gF#6�̎��g�� */
#define	D_RSI_HW_NOTE_G6				(unsigned short)(1567.98)	/* �m�[�gG6�̎��g�� */
#define	D_RSI_HW_NOTE_GS6				(unsigned short)(1661.22)	/* �m�[�gG#6�̎��g�� */
#define	D_RSI_HW_NOTE_A6				(unsigned short)(1760.00)	/* �m�[�gA6�̎��g�� */
#define	D_RSI_HW_NOTE_AS6				(unsigned short)(1864.66)	/* �m�[�gA#6�̎��g�� */
#define	D_RSI_HW_NOTE_B6				(unsigned short)(1975.53)	/* �m�[�gB6�̎��g�� */

enum EN_RSI_HW_BUTTON
{
	E_RSI_HW_BUTTON_LEFT = 0,	/* ���{�^�� */
	E_RSI_HW_BUTTON_RIGHT,		/* �E�{�^�� */
	E_RSI_HW_BUTTON_UP,			/* ��{�^�� */
	E_RSI_HW_BUTTON_DOWN,		/* ���{�^�� */
	E_RSI_HW_BUTTON_ENTER,		/* �����{�^�� */
	E_RSI_HW_BUTTON_BACK,		/* �߂�{�^�� */

	/* ��������ɒ�`���邱�� */
	E_RSI_HW_BUTTON_TNUM,		/* �{�^���̐� */
};

enum EN_RSI_HW_LEDCOLOR
{
	E_RSI_HW_LEDCOLOR_OFF = 0,								/* �I�t */
	E_RSI_HW_LEDCOLOR_RED = 1 << 0,							/* �� */
	E_RSI_HW_LEDCOLOR_GREEN = 1 << 1,						/* �� */
	E_RSI_HW_LEDCOLOR_ORANGE								/* �I�����W */
		= E_RSI_HW_LEDCOLOR_RED | E_RSI_HW_LEDCOLOR_GREEN,
};
/***** �\���� *****/

/***** �֐��v���g�^�C�v *****/
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

/***** �e�[�u�� *****/


#endif	/* __HW_H__ */
