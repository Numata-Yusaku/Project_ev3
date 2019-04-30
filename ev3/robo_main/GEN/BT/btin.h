#ifndef	__BTIN_H__
#define	__BTIN_H__

/***** インクルード *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* BT */
#include "bt.h"

/***** 定数 *****/
#define	D_BT_FLAG_ON		(1)
#define	D_BT_FLAG_OFF		(0)

#define	D_BT_CHECK_OK		(1)
#define	D_BT_CHECK_NG		(0)

#define	D_BT_RECVDATA_SIZE	(128)

/*** ログ出力 ***/
#define	D_BT_LOGMODE_STATUS						(D_BT_FLAG_OFF)


enum EN_BT_STATUS
{
	E_BT_STATUS_READY = 0,		/* 起動準備中 */
	E_BT_STATUS_IDLE,			/* 起動中 */
	E_BT_STATUS_CALIBLATE,		/* キャリブレーション中 */
	E_BT_STATUS_WAITING,		/* 待機中 */	
	E_BT_STATUS_RUN,			/* 走行中 */
	E_BT_STATUS_STOP,			/* 停止中 */
	
	/* ここより上に定義すること */
	E_BT_STATUS_INVALID = -1
};

/***** 構造体 *****/
typedef void( *F_BT_RECVFUNCPTR )( S_MSG_DATA* spRecv );
typedef void( *F_BT_RECVCMDFUNCPTR )( char* cpRecvData, int iSize );

/* 常駐領域 */
typedef struct
{
	int		iStatus;		/* クラスステータス */
	int		iWupChk;
	FILE*	fpBtFile;		/* Bluetoo通信ポート */
	FILE*	fpStatusLog;
}S_BT;

typedef struct
{
	int		iMsgId;
	void*	func;
}S_BT_RECV_TABLE;

typedef struct
{
	char	cCommand;
	int		iSize;
	void*	vpFunc;
}S_BT_MESSAGE_TABLE;

/***** 関数プロトタイプ *****/
/* startup */
void bt_main( void );
void bt_init( void );
void bt_shutdown( void );

/* global */
void bt_set_Global( void );
S_BT* bt_get_Global( void );

/* proc */
void bt_proc( void );
void bt_proc_Ready( void );
void bt_proc_Calibrate( void );
void bt_proc_Waiting( void );

/*** btin_recv.c **/
/* FrameWork */
void bt_recv( S_MSG_DATA* spRecv );
F_BT_RECVFUNCPTR bt_get_RecvFunc( int iMsgId );

/* RecvFunc */
void bt_rcv_test_req( S_MSG_DATA* spRecv );							/* テスト */
void bt_rcv_Wupchk_req( S_MSG_DATA* spRecv );						/* 起動 */
void bt_rcv_Stop_req( S_MSG_DATA* spRecv );							/* 停止 */
void bt_rcv_staCalibration_req( S_MSG_DATA* spRecv );				/* キャリブレーション開始 */
void bt_rcv_endCalibration_req( S_MSG_DATA* spRecv );				/* キャリブレーション終了 */
void bt_rcv_staRunning_req( S_MSG_DATA* spRecv );					/* 走行開始 */
void bt_rcv_setClientSendGyro_req( S_MSG_DATA* spRecv );			/* クライアント送信：ジャイロ */
void bt_rcv_setClientSendColor_req( S_MSG_DATA* spRecv );			/* クライアント送信：カラー */

/*** btin_send.c **/
void bt_send_test_res( S_MSG_DATA* spSend );							/* テスト */
void bt_send_Wupchk_res( void );										/* 起動 */
void bt_send_Stop_res( void );											/* 停止 */
void bt_send_chgCalibration_res( S_TASK_CHGCALIBRATION_RES* spSend );	/* キャリブレーション更新 */
void bt_send_RemoteStart_res( void );									/* リモートスタート */

/*** btin_message.c **/
void bt_set_SerialMessage( char* cpSendData, int iSize );
int bt_get_SerialMessage( char* cpRecvData, int iSize );
void bt_check_SerialMessageRecv( void );
int bt_get_MessageSize( char cCmd );
F_BT_RECVCMDFUNCPTR bt_get_MessageRecvFunc( char cCmd );
int bt_check_SerialMessageCommand( char cVal );
int bt_check_SerialMessageNumber( char cVal );
/* RecvCmdFunc */
void bt_recvCmd_s( char* cpRecvData, int iSize );

/*** btin_log.c **/
void bt_log_Statuslog_open( void );
void bt_log_set_Statuslog( void );

#endif	/* __BTIN_H__ */
