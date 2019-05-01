#ifndef	__TMIN_H__
#define	__TMIN_H__

/***** インクルード *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* TM */
#include "tm.h"

/***** 定数 *****/
#define	D_TM_FLAG_ON		(1)
#define	D_TM_FLAG_OFF		(0)

#define	D_TM_TIMER_NUM		(16)

enum EN_TM_STATUS
{
	E_TM_STATUS_READY = 0,		/* 起動準備中 */
	E_TM_STATUS_IDLE,			/* 起動中 */

	/* ここより上に定義すること */
	E_TM_STATUS_INVALID = -1
};

/***** 構造体 *****/
typedef void( *F_TM_RECVFUNCPTR )( S_MSG_DATA* spRecv );
typedef void( *F_TM_RECVCMDFUNCPTR )( char* cpRecvData, int iSize );

/* システム内部カウンタ */
typedef struct
{
	int						iCount;
	int						iRegist;
	int						iRunStat;
	int						iCycCount;
	F_TM_CALLBACKFUNCPTR	pFunc;
}S_TM_TIMERDATA;

/* システム内部カウンタ */
typedef struct
{
	unsigned long int uiCount;		/* 1カウント = 100msec */
	unsigned long int uiSec;		/* 経過秒 */
}S_TM_SYSCOUNT;

/* 常駐領域 */
typedef struct
{
	int iStatus;					/* クラスステータス */
	S_TM_SYSCOUNT	stSysCount;		/* システムカウンタ */
	S_TM_TIMERDATA	stTimerData[E_TASK_TASKID_NUM][D_TM_TIMER_NUM];
}S_TM;

typedef struct
{
	int		iMsgId;
	void*	func;
}S_TM_RECV_TABLE;

typedef struct
{
	char	cCommand;
	int		iSize;
	void*	vpFunc;
}S_TM_MESSAGE_TABLE;

/***** 関数プロトタイプ *****/
/* startup */
void tm_startup( void );
void tm_main( void );
void tm_main_debug( void );
void tm_init( void );
void tm_shutdown( void );

/* global */
void tm_set_Global( void );
S_TM* tm_get_Global( void );

/* proc */
void tm_proc( void );
void tm_proc_Ready( void );
void tm_proc_Idle( void );

/* timer */
void tm_upd_Count( void );
void tm_chk_Timer( void );
int tm_cre_Timer( S_TM_TIMERINFO* spTimerInfo );
int tm_del_Timer( int iId );
int tm_sta_Timer( int iId );
int tm_stp_Timer( int iId );
int tm_get_NowTime( S_TM_DAYTIME* spDayTime );
int tm_get_ModuleId( int iTimerId );
int tm_get_EventId( int iTimerId );

/*** tmin_recv.c **/
/* FrameWork */
void tm_recv( S_MSG_DATA* spRecv );
F_TM_RECVFUNCPTR tm_get_RecvFunc( int iMsgId );

/* RecvFunc */
void tm_rcv_test_req( S_MSG_DATA* spRecv );								/* テスト */

/*** tmin_send.c **/
void tm_send_test_res( S_MSG_DATA* spSend );							/* テスト */

#endif	/* __TMIN_H__ */
