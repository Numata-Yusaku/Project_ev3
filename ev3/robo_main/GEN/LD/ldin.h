#ifndef	__LDIN_H__
#define	__LDIN_H__

/***** インクルード *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* LD */
#include "ld.h"

/***** 定数 *****/
#define	D_LD_FLAG_ON		(1)
#define	D_LD_FLAG_OFF		(0)

#define	D_LD_CHECK_OK		(1)
#define	D_LD_CHECK_NG		(0)

#define	D_LD_RECVDATA_SIZE	(128)


/* ログファイル */
//#define	D_LD_FILENAME_STATUSLOG					"OutData/StatusLog_Ld.csv"
//#define	D_LD_LOGMODE_STATUS						(D_LD_FLAG_OFF)

#define	D_LD_FILENAME_STATUSLOG_LT				"OutData/StatusLog_Lt.csv"
#define	D_LD_FILENAME_CALIBRATELOG				"OutData/CalibrateLog.csv"
#define	D_LD_FILENAME_SYSTEMLOG					"OutData/SystemLog.csv"

#define	D_LD_BUFFNUM_STATUSLOG					D_TASK_BUFFNUM_STATUSLOG
#define	D_LD_BUFFNUM_CALIBRATELOG				D_TASK_BUFFNUM_CALIBRATELOG
#define	D_LD_BUFFNUM_SYSTEMLOG					D_TASK_BUFFNUM_SYSTEMLOG

/*** ログ出力 ***/
#if	(__TARGET_EV3__)
/* ログファイル */
#define	D_LD_LOGMODE_STATUS						(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_STATUS_TIME				(D_LD_FLAG_ON)

#define	D_LD_LOGMODE_CALIBRATE					(D_LD_FLAG_ON)

#define	D_LD_LOGMODE_SYSTEM						(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_SYSTEM_BALANCEINFO			(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_SYSTEM_BALANCECONTROL		(D_LD_FLAG_ON)

/* シリアルログ */
#define	D_LD_LOGMODE_GYRO						(D_LD_FLAG_OFF)
#else	/* __TARGET_EV3__ */
/* ログファイル */
#define	D_LD_LOGMODE_STATUS						(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_STATUS_TIME				(D_LD_FLAG_ON)

#define	D_LD_LOGMODE_CALIBRATE					(D_LD_FLAG_ON)

#define	D_LD_LOGMODE_SYSTEM						(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_SYSTEM_BALANCEINFO			(D_LD_FLAG_ON)
#define	D_LD_LOGMODE_SYSTEM_BALANCECONTROL		(D_LD_FLAG_ON)

/* シリアルログ */
#define	D_LD_LOGMODE_GYRO						(D_LD_FLAG_OFF)
#endif	/* __TARGET_EV3__ */



enum EN_LD_STATUS
{
	E_LD_STATUS_READY = 0,		/* 起動準備中 */
	E_LD_STATUS_IDLE,			/* 起動中 */
	E_LD_STATUS_CALIBLATE,		/* キャリブレーション中 */
	E_LD_STATUS_WAITING,		/* 待機中 */	
	E_LD_STATUS_RUN,			/* 走行中 */
	E_LD_STATUS_STOP,			/* 停止中 */
	
	/* ここより上に定義すること */
	E_LD_STATUS_INVALID = -1
};

/***** 構造体 *****/
typedef void( *F_LD_RECVFUNCPTR )( S_MSG_DATA* spRecv );
typedef void( *F_LD_RECVCMDFUNCPTR )( char* cpRecvData, int iSize );

/* 常駐領域 */
typedef struct
{
	FILE* fpStatusLog_Lt;
	FILE* fpCalibrateLog;
	FILE* fpSystemLog;
}S_LD_FILEINFO;

/* 常駐領域 */
typedef struct
{
	int iStatus;		/* クラスステータス */
	int iWupChk;
	FILE* fpLdFile;		/* Bluetoo通信ポート */
	S_LD_FILEINFO stFileInfo;
}S_LD;

typedef struct
{
	int iMsgId;
	void* func;
}S_LD_RECV_TABLE;

typedef struct
{
	char cCommand;
	int iSize;
	void* vpFunc;
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

void ld_log_Statuslog_open( void );
void ld_log_Calibratelog_open( void );
void ld_log_Systemlog_open( void );

/*** ldin_recv.c **/
/* FrameWork */
void ld_recv( S_MSG_DATA* spRecv );
F_LD_RECVFUNCPTR ld_get_RecvFunc( int iMsgId );

/* RecvFunc */
void ld_rcv_test_req( S_MSG_DATA* spRecv );						/* テスト */
void ld_rcv_Wupchk_req( S_MSG_DATA* spRecv );					/* 起動 */
void ld_rcv_Stop_req( S_MSG_DATA* spRecv );						/* 停止 */
void ld_rcv_staRunning_req( S_MSG_DATA* spRecv );				/* 走行開始 */
void ld_rcv_setLog_StatusLog_req( S_MSG_DATA* spRecv );			/* ログ設定：ステータスログ */
void ld_rcv_setLog_CalibrateLog_req( S_MSG_DATA* spRecv );		/* ログ設定：キャリブレーションログ */
void ld_rcv_setLog_SystemLog_req( S_MSG_DATA* spRecv );			/* ログ設定：システムログ */

/*** ldin_send.c **/
void ld_send_test_res( S_MSG_DATA* spSend );							/* テスト */
void ld_send_Wupchk_res( void );										/* 起動 */
void ld_send_Stop_res( void );											/* 停止 */

#endif	/* __LDIN_H__ */
