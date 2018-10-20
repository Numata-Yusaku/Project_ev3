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

#define	D_BT_RECVDATA_SIZE	(4)

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
typedef void( *F_BT_RECVFUNCPTR )(S_MSG_DATA* spRecv);

/* 常駐領域 */
typedef struct
{
	int iStatus;		/* クラスステータス */
	int iWupChk;
	FILE* BtFile;		/* Bluetoo通信ポート */
}S_BT;

/*** 送信データ ***/

/* キャリブレーションパラメータ通知 */
typedef struct
{
	int iSize;
	char aData[D_BT_RECVDATA_SIZE];
	char cCmd;
}S_BT_CHGCALIBRATION_RES;

typedef struct
{
	int iMsgId;
	void* func;
}S_BT_RECV_TABLE;

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

/* serial */
void bt_set_SerialMessage( char* cpSendData, int iSize );
char bt_get_SerialMessage( char* cpData );
void bt_check_SerialMessageRecv( void );
int bt_check_SerialMessageCommand( char cVal );
int bt_check_SerialMessageNumber( char cVal );

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

/*** btin_send.c **/
void bt_send_test_res( S_MSG_DATA* spSend );						/* テスト */
void bt_send_Wupchk_res( S_MSG_DATA* spSend );						/* 起動 */
void bt_send_Stop_res( S_MSG_DATA* spSend );						/* 停止 */
void bt_send_chgCalibration_res( S_BT_CHGCALIBRATION_RES* send );	/* キャリブレーション更新 */
void bt_send_RemoteStart_res( S_MSG_DATA* spSend );					/* リモートスタート */

#endif	/* __BTIN_H__ */
