#ifndef	__SENSOR_H__
#define	__SENSOR_H__

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
#define		D_RSI_SENSOR_IR_RED_UP_BUTTON		(1)
#define		D_RSI_SENSOR_IR_RED_DOWN_BUTTON		(2)
#define		D_RSI_SENSOR_IR_BLUE_UP_BUTTON		(4)
#define		D_RSI_SENSOR_IR_BLUE_DOWN_BUTTON	(8)
#define		D_RSI_SENSOR_IR_BEACON_BUTTON		(16)

#define		D_RSI_SENSOR_CHANNEL_NUM			(4)		/* チャンネル数 */



enum EN_RSI_SENSOR_PORT
{
	E_RSI_SENSOR_PORT_1 = 0,		/* ポート1 */
	E_RSI_SENSOR_PORT_2,			/* ポート2 */
	E_RSI_SENSOR_PORT_3,			/* ポート3 */
	E_RSI_SENSOR_PORT_4,			/* ポート4 */

	/* ここより上に定義すること */
	E_RSI_SENSOR_PORT_NUM,			/* ポート数 */
};

enum EN_RSI_SENSOR_TYPE
{
	E_RSI_SENSOR_TYPE_NONE = 0,			/* センサ未接続 */
	E_RSI_SENSOR_TYPE_ULTRASONIC,		/* 超音波センサ */
	E_RSI_SENSOR_TYPE_GYRO,				/* ジャイロセンサ */
	E_RSI_SENSOR_TYPE_TOUCH,			/* タッチセンサ */
	E_RSI_SENSOR_TYPE_COLOR,			/* カラーセンサ */
	E_RSI_SENSOR_TYPE_HT_NXT_ACCEL,		/* 加速度センサ */
	E_RSI_SENSOR_TYPE_NXT_TEMP,			/* NXT温度センサ */

	/* ここより上に定義すること */
	E_RSI_SENSOR_TYPE_NUM,				/* センサタイプ数 */
};

enum EN_RSI_SENSOR_COLOR
{
	E_RSI_SENSOR_COLOR_NONE = 0,		/* 無色 */
	E_RSI_SENSOR_COLOR_BLACK,			/* 黒 */
	E_RSI_SENSOR_COLOR_BLUE,			/* 青 */
	E_RSI_SENSOR_COLOR_GREEN,			/* 緑 */
	E_RSI_SENSOR_COLOR_YELLOW,			/* 黄 */
	E_RSI_SENSOR_COLOR_RED,				/* 赤 */
	E_RSI_SENSOR_COLOR_WHITE,			/* 白 */
	E_RSI_SENSOR_COLOR_BROWN,			/* 茶 */

	/* ここより上に定義すること */
	E_RSI_SENSOR_COLOR_NUM,				/* カラー数 */
};

/***** 構造体 *****/
typedef struct
{
	unsigned short usR;			/* 赤 */
	unsigned short usG;			/* 緑 */
	unsigned short usB;			/* 青 */
}S_RSI_SENSOR_RGB_RAW;

typedef struct
{
	signed char scHeading[D_RSI_SENSOR_CHANNEL_NUM];	/* 全チャンネルの方位 */
	signed char scDistance[D_RSI_SENSOR_CHANNEL_NUM];	/* 全チャンネルの距離 */
}S_RSI_SENSOR_IR_SEEK;

typedef struct
{
	signed char scChannel[D_RSI_SENSOR_CHANNEL_NUM];	/* 全チャンネルのボタン入力パターンd */
}S_RSI_SENSOR_IR_REMOTE;

/***** 関数プロトタイプ *****/
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


/***** テーブル *****/


#endif	/* __SENSOR_H__ */
