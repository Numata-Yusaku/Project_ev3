#ifndef	__MAIN_H__
#define	__MAIN_H__

/***** インクルード *****/
/* 標準ライブラリ */
#include <stdio.h>
#if __VC_DEBUG__
#include <Windows.h>
#include <process.h>
#include <conio.h>
#endif /* __VC_DEBUG__ */
/* TOPPERS */


/* メイン */
#include "task.h"
#include "bt.h"
#include "lt.h"

/***** 定数 *****/
#define D_MAIN_OK	(0)
#define D_MAIN_NG	(-1)

#define	D_MAIN_STARTUP_WAIT			(100)

/***** 構造体 *****/

/***** 関数プロトタイプ *****/
void main_make_thread( void );
void MAIN_init( void );
void MAIN_task( void );
void main_DispReady( void );
void main_shutdown( void );

void main_recv( S_MSG_DATA* spRecv );
#if	(__VC_DEBUG__)
void main_recv_cmd( void );
#else	/* __VC_DEBUG__ */
void main_recv_ButtonPressed( void );
#endif	/* __VC_DEBUG__ */

void main_rcv_cmd_t( void );
void main_rcv_cmd_T( void );
void main_rcv_cmd_B( void );
void main_rcv_cmd_U( void );
void main_rcv_cmd_D( void );
void main_rcv_cmd_L( void );
void main_rcv_cmd_R( void );
void main_rcv_cmd_C( void );


void main_send_test_req( S_MSG_DATA* spSend );
void main_send_TouchButton_req( S_MSG_DATA* spSend );
void main_send_BackButton_req( S_MSG_DATA* spSend );
void main_send_UpButton_req( S_MSG_DATA* spSend );
void main_send_DownButton_req( S_MSG_DATA* spSend );
void main_send_LeftButton_req( S_MSG_DATA* spSend );
void main_send_RightButton_req( S_MSG_DATA* spSend );
void main_send_CenterButton_req( S_MSG_DATA* spSend );
/***** テーブル *****/


#endif	/* __MAIN_H__ */
