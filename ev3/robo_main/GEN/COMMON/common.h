#ifndef	__COMMON_H__
#define	__COMMON_H__

/***** インクルード *****/
/* 標準ライブラリ */
#if	(__VC_DEBUG__)
#include <Windows.h>
#include <process.h>
#endif	/* __VC_DEBUG__ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TSI */
#include "TimeMng.h"

/* RSI */
#include "fs.h"
#include "hw.h"
#include "lcd.h"
#include "motor.h"
#include "sensor.h"
#include "extend.h"

/* TOPPERS */


/* メイン */

/***** 定数 *****/
#if	(__VC_DEBUG__)
#define	D_EV3_CYC_RUN_LT				(1)		/* ダミー定義 */
#define	D_EV3_CYC_RUN_TM				(2)		/* ダミー定義 */
#endif	/* __VC_DEBUG__ */

#define	D_COMMON_FLAG_ON				(1)
#define	D_COMMON_FLAG_OFF				(0)

/* ログ出力 */
#if	(__VC_DEBUG__)
#define	D_COMMON_LOGMODE_STATUS			(D_COMMON_FLAG_ON)
#define	D_COMMON_LOGMODE_CALIBRATE		(D_COMMON_FLAG_ON)
#define	D_COMMON_LOGMODE_SYSTEM			(D_COMMON_FLAG_ON)
#else	/* __VC_DEBUG__ */
#define	D_COMMON_LOGMODE_STATUS			(D_COMMON_FLAG_ON)
#define	D_COMMON_LOGMODE_CALIBRATE		(D_COMMON_FLAG_ON)
#define	D_COMMON_LOGMODE_SYSTEM			(D_COMMON_FLAG_ON)
#endif	/* __VC_DEBUG__ */

/***** 構造体 *****/

/***** 関数プロトタイプ *****/

/***** テーブル *****/


#endif	/* __COMMON_H__ */
