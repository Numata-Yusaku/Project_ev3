#ifndef	__COMMON_H__
#define	__COMMON_H__

/***** インクルード *****/
/* 標準ライブラリ */
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
#include "extend.h"

/* TOPPERS */


/* メイン */

/***** 定数 *****/

/***** 構造体 *****/

/***** 関数プロトタイプ *****/

/***** テーブル *****/


#endif	/* __COMMON_H__ */
