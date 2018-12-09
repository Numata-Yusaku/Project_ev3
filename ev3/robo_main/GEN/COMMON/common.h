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
#define	D_EV3_CYC_RUN				(1)		/* ダミー定義 */
#endif	/* __VC_DEBUG__ */


/***** 構造体 *****/

/***** 関数プロトタイプ *****/

/***** テーブル *****/


#endif	/* __COMMON_H__ */
