#ifndef	__TIMEMNG_H__
#define	__TIMEMNG_H__

/***** インクルード *****/
#include <stdio.h>
#include "tsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#endif	/* __VC_DEBUG__ */

/*** GEN ***/

/*** APL ***/

/***** 定数 *****/

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
/*** システム時刻管理 ***/
int TSI_TimeMng_get_tim( unsigned long int* uiSystime );

/*** 周期ハンドラ ***/
/*** アラームハンドラ ***/
/*** オーバランハンドラ ***/

/***** テーブル *****/


#endif	/* __TIMEMNG_H__ */
