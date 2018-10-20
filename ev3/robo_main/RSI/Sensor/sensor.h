#ifndef	__SENSOR_H__
#define	__SENSOR_H__

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
#define		D_RSI_SENSOR_IR_RED_UP_BUTTON		(1)
#define		D_RSI_SENSOR_IR_RED_DOWN_BUTTON		(2)
#define		D_RSI_SENSOR_IR_BLUE_UP_BUTTON		(4)
#define		D_RSI_SENSOR_IR_BLUE_DOWN_BUTTON	(8)
#define		D_RSI_SENSOR_IR_BEACON_BUTTON		(16)

#define		D_RSI_SENSOR_CHANNEL_NUM			(4)		/* �`�����l���� */



enum EN_RSI_SENSOR_PORT
{
	E_RSI_SENSOR_PORT_1 = 0,		/* �|�[�g1 */
	E_RSI_SENSOR_PORT_2,			/* �|�[�g2 */
	E_RSI_SENSOR_PORT_3,			/* �|�[�g3 */
	E_RSI_SENSOR_PORT_4,			/* �|�[�g4 */

	/* ��������ɒ�`���邱�� */
	E_RSI_SENSOR_PORT_NUM,			/* �|�[�g�� */
};

enum EN_RSI_SENSOR_TYPE
{
	E_RSI_SENSOR_TYPE_NONE = 0,			/* �Z���T���ڑ� */
	E_RSI_SENSOR_TYPE_ULTRASONIC,		/* �����g�Z���T */
	E_RSI_SENSOR_TYPE_GYRO,				/* �W���C���Z���T */
	E_RSI_SENSOR_TYPE_TOUCH,			/* �^�b�`�Z���T */
	E_RSI_SENSOR_TYPE_COLOR,			/* �J���[�Z���T */
	E_RSI_SENSOR_TYPE_HT_NXT_ACCEL,		/* �����x�Z���T */
	E_RSI_SENSOR_TYPE_NXT_TEMP,			/* NXT���x�Z���T */

	/* ��������ɒ�`���邱�� */
	E_RSI_SENSOR_TYPE_NUM,				/* �Z���T�^�C�v�� */
};

enum EN_RSI_SENSOR_COLOR
{
	E_RSI_SENSOR_COLOR_NONE = 0,		/* ���F */
	E_RSI_SENSOR_COLOR_BLACK,			/* �� */
	E_RSI_SENSOR_COLOR_BLUE,			/* �� */
	E_RSI_SENSOR_COLOR_GREEN,			/* �� */
	E_RSI_SENSOR_COLOR_YELLOW,			/* �� */
	E_RSI_SENSOR_COLOR_RED,				/* �� */
	E_RSI_SENSOR_COLOR_WHITE,			/* �� */
	E_RSI_SENSOR_COLOR_BROWN,			/* �� */

	/* ��������ɒ�`���邱�� */
	E_RSI_SENSOR_COLOR_NUM,				/* �J���[�� */
};

/***** �\���� *****/
typedef struct
{
	unsigned short usR;			/* �� */
	unsigned short usG;			/* �� */
	unsigned short usB;			/* �� */
}S_RSI_SENSOR_RGB_RAW;

typedef struct
{
	signed char scHeading[D_RSI_SENSOR_CHANNEL_NUM];	/* �S�`�����l���̕��� */
	signed char scDistance[D_RSI_SENSOR_CHANNEL_NUM];	/* �S�`�����l���̋��� */
}S_RSI_SENSOR_IR_SEEK;

typedef struct
{
	signed char scChannel[D_RSI_SENSOR_CHANNEL_NUM];	/* �S�`�����l���̃{�^�����̓p�^�[��d */
}S_RSI_SENSOR_IR_REMOTE;

/***** �֐��v���g�^�C�v *****/
/* sensor */
int RSI_sensor_config( int iPort, int iType );
unsigned int RSI_sensor_get_type( int iPort );
int RSI_color_sensor_get_color( int iPort );

/* color_sensor */
unsigned char RSI_color_sensor_get_reflect( int iPort );
unsigned char RSI_color_sensor_get_ambient( int iPort );
void RSI_color_sensor_get_rgb_raw( int iPort, S_RSI_SENSOR_RGB_RAW* spVal );

/* gyro_sensor */
signed short RSI_gyro_sensor_get_angle( int iPort );
signed short RSI_gyro_sensor_get_rate( int iPort );
int RSI_gyro_sensor_reset( int iPort );

/* ultrasonic_sensor */
signed short RSI_ultrasonic_sensor_get_distance( int iPort );
int RSI_ultrasonic_sensor_listen( int iPort );

/* infrared_sensor */
signed char RSI_infrared_sensor_get_distance( int iPort );
S_RSI_SENSOR_IR_SEEK RSI_infrared_sensor_seek( int iPort );
S_RSI_SENSOR_IR_REMOTE RSI_infrared_sensor_get_remote( int iPort );

/* touch_sensor */
int RSI_touch_sensor_is_pressed( int iPort );

/* ht_nxt_accel_sensor */
int RSI_ht_nxt_accel_sensor_measure( int iPort, signed short ssAxes );

/* RSI_nxt_temp_sensor */
int RSI_nxt_temp_sensor_measure( int iPort, float* fpTemp );


/***** �e�[�u�� *****/


#endif	/* __SENSOR_H__ */
