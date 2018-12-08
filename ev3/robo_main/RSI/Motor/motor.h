#ifndef	__MOTOR_H__
#define	__MOTOR_H__

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
enum EN_RSI_MOTOR_PORT
{
	E_RSI_MOTOR_PORT_A = 0,		/* ポートA */
	E_RSI_MOTOR_PORT_B,			/* ポートB */
	E_RSI_MOTOR_PORT_C,			/* ポートC */
	E_RSI_MOTOR_PORT_D,			/* ポートD */

	/* ここより上に定義すること */
	E_RSI_MOTOR_PORT_NUM,		/* ポート数 */
};

enum EN_RSI_MOTOR_TYPE
{
	E_RSI_MOTOR_TYPE_NONE = 0,		/* モータ未接続 */
	E_RSI_MOTOR_TYPE_MEDIUM,		/* サーボモータM */
	E_RSI_MOTOR_TYPE_LARGE,			/* サーボモータL */
	E_RSI_MOTOR_TYPE_UNREGULATED,	/* 未調整モータ */

	/* ここより上に定義すること */
	E_RSI_MOTOR_TYPE_NUM,			/* モータタイプ数 */
};

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
/* motor */
int RSI_motor_config( int iPort,  int iType );
unsigned int RSI_motor_get_type( int iPort );
int RSI_motor_get_counts( int iPort );
int RSI_motor_reset_counts( int iPort );
int RSI_motor_set_power( int iPort, int iPower );
int RSI_motor_get_power( int iPort );
int RSI_motor_stop( int iPort, int iBrake );
int RSI_motor_rotate( int iPort, int iDegrees, signed int siSpeedAbs, int iBlocking );
int RSI_motor_steer( int iLeftMotor, int iRightMotor, int iPower, int iTurnRatio);

/***** テーブル *****/


#endif	/* __MOTOR_H__ */
