#include "ldin.h"

S_LD* gspLd = (S_LD*)NULL;

/* startup */
void ld_main( void )
{
	int iRet				= D_LD_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	ld_init();
	
	/* LD_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_LD, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_LD_INVALID != psRecvData->iMsgid) )
		{
			/* 受信処理 */
			ld_recv( psRecvData );
			
		}
		
		/* 受信データクリア */
		if ((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		ld_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_LD );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	ld_shutdown();
	
	return;
}

void ld_init( void )
{
	ld_set_Global();
	
	return;
}

void ld_shutdown( void )
{
#if	(__TARGET_EV3__)
	ter_tsk( LD_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void ld_set_Global( void )
{
	S_LD* spLd = (S_LD*)NULL;
	
	spLd = (S_LD*)malloc( sizeof(S_LD) );
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 初期化 */
	memset( spLd, 0x00, sizeof(S_LD) );
	
	/* 初期化値設定 */

	/* グローバル設定 */
	gspLd = spLd;
	
	return;
}

S_LD* ld_get_Global( void )
{
	return (S_LD*)gspLd;
}

/* proc */
void ld_proc( void )
{
	int iStatus = E_LD_STATUS_INVALID;
	S_LD* spLd = (S_LD*)NULL;
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* クラスステータス取得 */
	iStatus = spLd->iStatus;
	if( E_LD_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	///* ログ出力 */
	//ld_log_set_Statuslog();
	//printf("%d",iStatus);
	
	/* 状態に応じて処理実行 */
	switch (iStatus)
	{
		case E_LD_STATUS_READY:
			ld_proc_Ready();
			break;
		
		case E_LD_STATUS_IDLE:
			/* 処理しない */
			break;
		
		case E_LD_STATUS_RUN:
			/* 処理しない */
			break;
		
		default:
			break;
	}
	
	return;
}

void ld_proc_Ready( void )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 状態遷移 */
	spLd->iStatus = E_LD_STATUS_IDLE;
	
	return;
}
