#ifndef	__TM_H__
#define	__TM_H__

/***** インクルード *****/
/*** GEN ***/
#include "common.h"
#include "task.h"

/***** 定数 *****/
#define	D_TM_OK				(0)
#define	D_TM_NG				(-1)
#define	D_TM_NG_PARA_ERR	(-2)
#define	D_TM_NG_READY		(-3)

/* APL */
enum EN_TIMERID_LT
{
	E_TIMERID_LT_WUPCHK =				( ( E_TASK_TASKID_LT << 24) | 0x00000001 ),
	E_TIMERID_LT_STOPCHK,
	E_TIMERID_BUTTON_WAIT_TIMER,
	E_TIMERID_LT_LOGDUMP,

	/* ここより上に定義すること */
	E_TIMERID_LT_INVALID = 0x00000000,
};

/***** 構造体 *****/
typedef void( *F_TM_CALLBACKFUNCPTR )(void);

/* タイマ情報 */
typedef struct
{
	int						iId;
	int						iCycle;
	F_TM_CALLBACKFUNCPTR	pFunc;
}S_TM_TIMERINFO;

/* 日時情報 */
typedef struct
{
	unsigned short	usYear;
	unsigned short	usMonth;
	unsigned short	usDay;
	unsigned short	usHour;
	unsigned short	usMinute;
	unsigned short	usSecond;
	unsigned short	usMilliSec;
}S_TM_DAYTIME;

/***** 関数プロトタイプ *****/
void TM_startup( void );
void TM_main( void );
void TM_main_debug( void );

int TM_cre_Timer( S_TM_TIMERINFO* spTimerInfo );
int TM_del_Timer( int iId );
int TM_sta_Timer( int iId );
int TM_stp_Timer( int iId );
int TM_get_NowTime( S_TM_DAYTIME* spDayTime );

/***** テーブル *****/

#endif	/* __TM_H__ */
