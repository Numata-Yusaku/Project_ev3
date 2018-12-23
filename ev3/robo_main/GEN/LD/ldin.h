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
#define	D_LD_FILENAME_STATUSLOG					"OutData/StatusLog_Ld.csv"

/*** ログ出力 ***/
#define	D_LD_LOGMODE_STATUS						(D_LD_FLAG_OFF)


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
	int iStatus;		/* クラスステータス */
	int iWupChk;
	FILE* fpLdFile;		/* Bluetoo通信ポート */
	FILE* fpStatusLog;
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
void ld_proc_Calibrate( void );
void ld_proc_Waiting( void );

/*** ldin_recv.c **/
/* FrameWork */
void ld_recv( S_MSG_DATA* spRecv );
F_LD_RECVFUNCPTR ld_get_RecvFunc( int iMsgId );

/* RecvFunc */
void ld_rcv_test_req( S_MSG_DATA* spRecv );							/* テスト */
void ld_rcv_Wupchk_req( S_MSG_DATA* spRecv );						/* 起動 */
void ld_rcv_Stop_req( S_MSG_DATA* spRecv );							/* 停止 */
void ld_rcv_staCalibration_req( S_MSG_DATA* spRecv );				/* キャリブレーション開始 */
void ld_rcv_endCalibration_req( S_MSG_DATA* spRecv );				/* キャリブレーション終了 */
void ld_rcv_staRunning_req( S_MSG_DATA* spRecv );					/* 走行開始 */
void ld_rcv_setClientSendGyro_req( S_MSG_DATA* spRecv );			/* クライアント送信：ジャイロ */
void ld_rcv_setClientSendColor_req( S_MSG_DATA* spRecv );			/* クライアント送信：カラー */

/*** ldin_send.c **/
void ld_send_test_res( S_MSG_DATA* spSend );							/* テスト */
void ld_send_Wupchk_res( void );										/* 起動 */
void ld_send_Stop_res( void );											/* 停止 */
void ld_send_chgCalibration_res( S_TASK_CHGCALIBRATION_RES* spSend );	/* キャリブレーション更新 */
void ld_send_RemoteStart_res( void );									/* リモートスタート */

/*** ldin_message.c **/
void ld_set_SerialMessage( char* cpSendData, int iSize );
int ld_get_SerialMessage( char* cpRecvData, int iSize );
void ld_check_SerialMessageRecv( void );
int ld_get_MessageSize( char cCmd );
F_LD_RECVCMDFUNCPTR ld_get_MessageRecvFunc( char cCmd );
int ld_check_SerialMessageCommand( char cVal );
int ld_check_SerialMessageNumber( char cVal );
/* RecvCmdFunc */
void ld_recvCmd_s( char* cpRecvData, int iSize );

/*** ldin_log.c **/
void ld_log_Statuslog_open( void );
void ld_log_set_Statuslog( void );

#endif	/* __LDIN_H__ */
