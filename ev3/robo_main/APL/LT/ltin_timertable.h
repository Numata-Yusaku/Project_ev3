#ifndef	__LTIN_TIMERTABLE_H__
#define	__LTIN_TIMERTABLE_H__

/***** インクルード *****/
#include "ltin.h"

/***** テーブル *****/
S_TM_TIMERINFO T_LT_TIMER_TABLE[] =
{
	/* TIMERID						,	Cycle(ms)	,	CallbackFunc				*/
	{ E_TIMERID_LT_WUPCHK			,	1000		,	lt_WupChkTimer_CallBack		},
	{ E_TIMERID_LT_STOPCHK			,	1000		,	lt_StopChkTimer_CallBack	},
	{ E_TIMERID_BUTTON_WAIT_TIMER	,	1000		,	lt_ButtonTimer_CallBack		},
	{ E_TIMERID_LT_LOGDUMP			,	20000		,	lt_LogDumpTimer_CallBack	},
};

#endif	/* __LTIN_TIMERTABLE_H__ */
