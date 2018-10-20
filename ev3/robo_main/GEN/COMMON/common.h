#ifndef	__COMMON_H__
#define	__COMMON_H__

/***** インクルード *****/
/* 標準ライブラリ */
#if	(__VC_DEBUG__)
#include <Windows.h>
#include <process.h>
#else	/* __VC_DEBUG__ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif	/* __VC_DEBUG__ */

/* RSI */
#include "fs.h"
#include "hw.h"
#include "lcd.h"
#include "motor.h"
#include "sensor.h"

/* TOPPERS */


/* メイン */

/***** 定数 *****/

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
void COMMON_dummy( void );

/***** テーブル *****/


#endif	/* __COMMON_H__ */
