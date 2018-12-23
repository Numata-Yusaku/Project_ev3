#ifndef	__TM_H__
#define	__TM_H__

/***** インクルード *****/
/*** GEN ***/
#include "common.h"
#include "task.h"

/***** 定数 *****/
#define	D_TM_OK		(0)
#define	D_TM_NG		(-1)

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
void TM_startup( void );
void TM_main( void );
void TM_main_debug( void );

/***** テーブル *****/

#endif	/* __TM_H__ */
