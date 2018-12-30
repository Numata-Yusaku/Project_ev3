#ifndef	__LTIN_TIMERTABLE_H__
#define	__LTIN_TIMERTABLE_H__

/***** インクルード *****/
#include "ltin.h"

/***** テーブル *****/
S_TM_TIMERINFO T_LT_TIMER_TABLE[] =
{
	/* TIMERID						,	Cycle	,	CallbackFunc										*/
	{ E_TIMERID_LT_WUPCHK			,	1000	,	lt_WupChkTimer_CallBack		},
};

#endif	/* __LTIN_TIMERTABLE_H__ */
