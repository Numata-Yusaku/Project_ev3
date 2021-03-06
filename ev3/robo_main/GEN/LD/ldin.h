﻿#ifndef	__LDIN_H__
#define	__LDIN_H__

/***** インクルード *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* GEN */
#include "tm.h"

/* LD */
#include "ld.h"

/***** 定数 *****/
#define	D_LD_FLAG_ON		(1)
#define	D_LD_FLAG_OFF		(0)

#define	D_LD_CHECK_OK		(1)
#define	D_LD_CHECK_NG		(0)

#define	D_LD_PRINTLINE_NUM	(512)

/*** ログ出力 ***/
/* ログファイル */
#define	D_LD_FILENAME_STATUSLOG					"OutData/[LD]StatusLog.csv"
#define	D_LD_FILENAME_CALIBRATELOG				"OutData/[LD]CalibrateLog.csv"
#define	D_LD_FILENAME_SYSTEMLOG					"OutData/[LD]SystemLog.csv"

#define	D_LD_LOGMODE_STATUS						D_COMMON_LOGMODE_STATUS
#define	D_LD_LOGMODE_CALIBRATE					D_COMMON_LOGMODE_CALIBRATE
#define	D_LD_LOGMODE_SYSTEM						D_COMMON_LOGMODE_SYSTEM
#define	D_LD_LOGMODE_SYSTEM_BALANCEINFO			D_LD_FLAG_ON
#define	D_LD_LOGMODE_SYSTEM_BALANCECONTROL		D_LD_FLAG_ON

/* ログ数(1ページ内のログ数) */
#define	D_LD_BUFFNUM_STATUSLOG					D_TASK_BUFFNUM_STATUSLOG
#define	D_LD_BUFFNUM_CALIBRATELOG				D_TASK_BUFFNUM_CALIBRATELOG
#define	D_LD_BUFFNUM_SYSTEMLOG					D_TASK_BUFFNUM_SYSTEMLOG

enum EN_LD_STATUS
{
	E_LD_STATUS_READY = 0,		/* 起動準備中 */
	E_LD_STATUS_IDLE,			/* 起動中 */
	E_LD_STATUS_CALIBLATE,		/* キャリブレーション中 */
	E_LD_STATUS_WAITING,		/* 待機中 */	
	E_LD_STATUS_RUN,			/* 走行中 */
	E_LD_STATUS_LOGDUMP,		/* ログダンプ */
	E_LD_STATUS_STOP,			/* 停止中 */
	
	/* ここより上に定義すること */
	E_LD_STATUS_INVALID = -1
};

enum EN_LD_LOGKIND
{
#if	D_LD_LOGMODE_STATUS
	E_LD_LOGKIND_STATUSLOG = 0,
#endif	/* D_LD_LOGMODE_STATUS */
#if	D_LD_LOGMODE_CALIBRATE
	E_LD_LOGKIND_CALIBRATELOG,
#endif	/* D_LD_LOGMODE_CALIBRATE */
#if	D_LD_LOGMODE_SYSTEM
	E_LD_LOGKIND_SYSTEMLOG,
#endif	/* D_LD_LOGMODE_SYSTEM */

	/* ここより上に定義すること */
	E_LD_LOGKIND_NUM,
	E_LD_LOGKIND_END = E_LD_LOGKIND_NUM,
	E_LD_LOGKIND_STOP
};

/***** 構造体 *****/
typedef void( *F_LD_RECVFUNCPTR )( S_MSG_DATA* spRecv );
typedef void( *F_LD_RECVCMDFUNCPTR )( char* cpRecvData, int iSize );

/* ステータスログ */
typedef struct
{
	S_TM_DAYTIME	stDayTime;
	int				iStatus;	/* 状態 */
	int				iTaskId;
}S_LD_LOGDATA_STATUSLOG;

typedef struct
{
	int							iLogNum;
	S_LD_LOGDATA_STATUSLOG		stLog[D_LD_BUFFNUM_STATUSLOG];
}S_LD_LOGINFO_STATUSLOG;

/* ログ情報 */
typedef struct
{
	S_LD_LOGINFO_STATUSLOG		stStatusLog;
}S_LD_LOGINFO;

/* ファイルデータ */
typedef struct
{
	int		iWritePageNum;
	FILE*	fpFile;
}S_LD_FILEDATA;

/* ファイルポインタ */
typedef struct
{
	S_LD_FILEDATA	fpStatusLog;
	S_LD_FILEDATA	fpCalibrateLog;
	S_LD_FILEDATA	fpSystemLog;
}S_LD_FILEINFO;

/*** ステータスログ ***/
/* ログリストページ */
typedef struct S_LD_LOGLISTPAGE_STATUSLOG
{
	int										iPageNo;		/* ページ数 */
	S_TASK_LOGINFO_STATUSLOG*				spData;			/* データ */
	struct S_LD_LOGLISTPAGE_STATUSLOG*		spNextPage;		/* 次データへのリンクアドレス */
}S_LD_LOGLISTPAGE_STATUSLOG;

/* ログリスト */
typedef struct
{
	int										iAllPageNum;	/* 総ページ数 */
	S_LD_LOGLISTPAGE_STATUSLOG*				spList;			/* リストデータトップ */
}S_LD_LOGLISTINFO_STATUSLOG;

/*** キャリブレーションログ ***/
/* ログリストページ */
typedef struct S_LD_LOGLISTPAGE_CALIBRATELOG
{
	int										iPageNo;		/* ページ数 */
	S_TASK_LOGINFO_CALIBRATELOG*			spData;			/* データ */
	struct S_LD_LOGLISTPAGE_CALIBRATELOG*	spNextPage;		/* 次データへのリンクアドレス */
}S_LD_LOGLISTPAGE_CALIBRATELOG;

/* ログリスト */
typedef struct
{
	int										iAllPageNum;	/* 総ページ数 */
	S_LD_LOGLISTPAGE_CALIBRATELOG*			spList;			/* リストデータトップ */
}S_LD_LOGLISTINFO_CALIBRATELOG;

/*** システムログ ***/
/* ログリストページ */
typedef struct S_LD_LOGLISTPAGE_SYSTEMLOG
{
	int										iPageNo;		/* ページ数 */
	S_TASK_LOGINFO_SYSTEMLOG*				spData;			/* データ */
	struct S_LD_LOGLISTPAGE_SYSTEMLOG*		spNextPage;		/* 次データへのリンクアドレス */
}S_LD_LOGLISTPAGE_SYSTEMLOG;

/* ログリスト */
typedef struct
{
	int										iAllPageNum;	/* 総ページ数 */
	S_LD_LOGLISTPAGE_SYSTEMLOG*				spList;			/* リストデータトップ */
}S_LD_LOGLISTINFO_SYSTEMLOG;

typedef struct
{
	int								iNowWrite;
#if	D_LD_LOGMODE_STATUS
	S_LD_LOGLISTINFO_STATUSLOG		stLogListInfo_StatusLog;
#endif	/* D_LD_LOGMODE_STATUS */
#if	D_LD_LOGMODE_CALIBRATE
	S_LD_LOGLISTINFO_CALIBRATELOG	stLogListInfo_CalibrateLog;
#endif	/* D_LD_LOGMODE_CALIBRATE */
#if	D_LD_LOGMODE_SYSTEM
	S_LD_LOGLISTINFO_SYSTEMLOG		stLogListInfo_SystemLog;
#endif	/* D_LD_LOGMODE_SYSTEM */
}S_LD_LOGLIST;

/* 常駐領域 */
typedef struct
{
	int				iStatus;		/* クラスステータス */
	int				iOldStatus;
	int				iWupChk;
	S_LD_FILEINFO	stFileInfo;
	S_LD_LOGINFO	stLogInfo;
	S_LD_LOGLIST	stLogList;
}S_LD;

typedef struct
{
	int		iMsgId;
	void*	func;
}S_LD_RECV_TABLE;

typedef struct
{
	char	cCommand;
	int		iSize;
	void*	vpFunc;
}S_LD_MESSAGE_TABLE;

/***** 関数プロトタイプ *****/
/* startup */
void ld_main( void );
void ld_init( void );
void ld_shutdown( void );

/* global */
void ld_set_Global( void );
S_LD* ld_get_Global( void );

/* proc */
void ld_proc( void );
void ld_proc_Ready( void );
void ld_proc_LogDump( void );

void ld_log_set_Statuslog( void );
void ld_log_set_LastLog_Statuslog( void );

void ld_log_Dump( void );

void ld_log_Statuslog_open( void );
void ld_log_Calibratelog_open( void );
void ld_log_Systemlog_open( void );

int ld_log_DumpStatuslog( void );
int ld_log_DumpCalibratelog( void );
int ld_log_DumpSystemlog( void );

/*** ldin_recv.c **/
/* FrameWork */
void ld_recv( S_MSG_DATA* spRecv );
F_LD_RECVFUNCPTR ld_get_RecvFunc( int iMsgId );

/* RecvFunc */
void ld_rcv_test_req( S_MSG_DATA* spRecv );								/* テスト */
void ld_rcv_Wupchk_req( S_MSG_DATA* spRecv );							/* 起動 */
void ld_rcv_Stop_req( S_MSG_DATA* spRecv );								/* 停止 */
void ld_rcv_staRunning_req( S_MSG_DATA* spRecv );						/* 走行開始 */
void ld_rcv_setLog_StatusLog_req( S_MSG_DATA* spRecv );					/* ログ設定：ステータスログ */
void ld_rcv_setLog_CalibrateLog_req( S_MSG_DATA* spRecv );				/* ログ設定：キャリブレーションログ */
void ld_rcv_setLog_SystemLog_req( S_MSG_DATA* spRecv );					/* ログ設定：システムログ */
void ld_rcv_setLog_LogLast_req( S_MSG_DATA* spRecv );					/* 最終ログ設定 */
void ld_rcv_staLogDump_req( S_MSG_DATA* spRecv );						/* ログダンプ開始 */
void ld_rcv_endLogDump_req( S_MSG_DATA* spRecv );						/* ログダンプ終了 */

/*** ldin_send.c **/
void ld_send_test_res( S_MSG_DATA* spSend );							/* テスト */
void ld_send_Wupchk_res( void );										/* 起動 */
void ld_send_Stop_res( void );											/* 停止 */
void ld_send_setLog_StatusLog_req( S_LD_LOGINFO_STATUSLOG* spSend );	/* ログ設定：ステータスログ */
void ld_send_setLog_LogLast_res( void );								/* 最終ログ設定 */
void ld_send_staLogDump_res( void );									/* ログダンプ開始 */
void ld_send_chgLogDump_res( S_TASK_CHGLOGDUMP_RES* psSend );			/* ログダンプ状態更新 */
void ld_send_endLogDump_res( void );									/* ログダンプ終了 */

#endif	/* __LDIN_H__ */
