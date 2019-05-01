#ifndef	__TASKIN_H__
#define	__TASKIN_H__

/***** インクルード *****/
#include <stdio.h>

#include "common.h"
#include "tm.h"
#include "task.h"

/***** 定数 *****/
#define	D_TASK_MSGID_INVALID		(0x00000000)

/* ログ出力 */
#define	D_TASK_FILENAME_MSGLOG		"OutData/[TASK]msglog.csv"
#define	D_TASK_PRINTLINE_NUM			(512)

#if	(__TARGET_EV3__)
#define	D_TASK_LOGMODE				(D_TASK_MODE_OFF)
#else	/* __TARGET_EV3__ */
#define	D_TASK_LOGMODE				(D_TASK_MODE_ON)
#endif	/* __TARGET_EV3__ */

/***** 構造体 *****/
/* 常駐領域 */
typedef struct
{
	FILE*	fpMsgLog;
}S_TASK;
/***** 関数プロトタイプ *****/
/* startup */
void task_init_que( void );
void task_sleep( int iCycle );

/* global */
void task_set_Global( void );
S_TASK* task_get_Global( void );

/* Message */
int task_msgsend( int iTask, S_MSG_DATA* spPara );
int task_msgrecv( int iTask, S_MSG_DATA* spPara );

/* log */
void task_msglog_open( void );
void task_msglog( int iDir, int iTask, int iMsgId );

/***** テーブル *****/

#endif	/* __TASKIN_H__ */
