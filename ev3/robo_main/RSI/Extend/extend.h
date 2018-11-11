#ifndef	__EXTEND_H__
#define	__EXTEND_H__

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

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
/* RTOS */
int RSI_extend_sta_cyc( signed int siCycId );
int RSI_extend_stp_cyc( signed int siCycId );

/***** テーブル *****/


#endif	/* __EXTEND_H__ */
