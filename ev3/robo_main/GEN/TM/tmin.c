#include "tmin.h"

S_TM* gspTm = (S_TM*)NULL;

/* startup */
void tm_startup( void )
{
	tm_init();
	
	/* サイクル起動 */
	RSI_extend_sta_cyc( D_EV3_CYC_RUN_TM );
	
	return;
}

void tm_main( void )
{
	int iRet				= D_TM_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* TM_TASK */
	iRet = TASK_msgrecv( E_TASK_TASKID_TM, psRecvData );
	if( ( D_TASK_OK == iRet ) &&
		( E_MSGID_TM_INVALID != psRecvData->iMsgid) )
	{
		/* 受信処理 */
		tm_recv( psRecvData );
		
	}
	
	/* 受信データクリア */
	if ((void*)NULL != psRecvData->vpPara)
	{
		free( psRecvData->vpPara );
		psRecvData->vpPara = (void*)NULL;
	}
	
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
	/* 常駐処理 */
	tm_proc();
	

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void tm_main_debug( void )
{
	int			iRet		= D_TM_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	tm_init();
	
	/* TM_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_TM, psRecvData );
		if ((D_TASK_OK == iRet) &&
			(E_MSGID_TM_INVALID != psRecvData->iMsgid))
		{
			/* 受信処理 */
			tm_recv( psRecvData );
			
		}
		
		/* 受信データクリア */
		if ((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		tm_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_TM );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	tm_shutdown();
	
	return;
}

void tm_init( void )
{
	tm_set_Global();
	
	return;
}

void tm_shutdown( void )
{
#if	(__TARGET_EV3__)
	ter_tsk( TM_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void tm_set_Global( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	spTm = (S_TM*)malloc( sizeof(S_TM) );
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* 初期化 */
	memset( spTm, 0x00, sizeof(S_TM) );
	
	/* 初期化値設定 */
	
	/* グローバル設定 */
	gspTm = spTm;
	
	return;
}

S_TM* tm_get_Global( void )
{
	return (S_TM*)gspTm;
}

/* proc */
void tm_proc( void )
{
	int iStatus = E_TM_STATUS_INVALID;
	S_TM* spTm = (S_TM*)NULL;
	
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* クラスステータス取得 */
	iStatus = spTm->iStatus;
	if( E_TM_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	///* ログ出力 */
	//tm_log_set_Statuslog();
	//printf("%d",iStatus);
	
	/* 状態に応じて処理実行 */
	switch (iStatus)
	{
		case E_TM_STATUS_READY:
			tm_proc_Ready();
			break;
		
		case E_TM_STATUS_IDLE:
			tm_proc_Idle();
			break;
		
		default:
			break;
	}
	
	return;
}

void tm_proc_Ready( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* 状態遷移 */
	spTm->iStatus = E_TM_STATUS_IDLE;
	
	return;
}

void tm_proc_Idle( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* カウンタ更新 */
	spTm->stSysCount.uiCount++;
	
	/* 経過秒更新 */
	if( ( spTm->stSysCount.uiCount % 10 ) == 0 )
	{
		spTm->stSysCount.uiSec++;
	}
	
	return;
}
