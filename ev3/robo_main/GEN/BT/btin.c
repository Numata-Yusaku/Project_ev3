#include "btin.h"

S_BT* gspBt = (S_BT*)NULL;

/* startup */
void bt_main( void )
{
	int iRet				= D_BT_NG;
	S_MSG_DATA*	spRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	spRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	bt_init();
	
	/* BT_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_BT, spRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_BT_INVALID != spRecvData->iMsgid) )
		{
			/* 受信処理 */
			bt_recv( spRecvData );
		}
		
		/* 受信データクリア */
		if ((void*)NULL != spRecvData->vpPara)
		{
			free( spRecvData->vpPara );
			spRecvData->vpPara = (void*)NULL;
		}
		
		memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		bt_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_BT );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spRecvData)
	{
		free( spRecvData );
		spRecvData = (S_MSG_DATA*)NULL;
	}
	
	bt_shutdown();
	
	return;
}

void bt_init( void )
{
	bt_set_Global();
	
	/* ログ */
	bt_log_Statuslog_open();
	
	return;
}

void bt_shutdown( void )
{
#if	(__TARGET_EV3__)
	ter_tsk( BT_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void bt_set_Global( void )
{
	S_BT* spBt = (S_BT*)NULL;
	
	spBt = (S_BT*)malloc( sizeof(S_BT) );
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* 初期化 */
	memset( spBt, 0x00, sizeof(S_BT) );
	
	/* 初期化値設定 */
	
	/* グローバル設定 */
	gspBt = spBt;
	
	return;
}

S_BT* bt_get_Global( void )
{
	return (S_BT*)gspBt;
}

/* proc */
void bt_proc( void )
{
	int iStatus = E_BT_STATUS_INVALID;
	S_BT* spBt = (S_BT*)NULL;
	
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* クラスステータス取得 */
	iStatus = spBt->iStatus;
	if( E_BT_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* ログ出力 */
	bt_log_set_Statuslog();
	
	/* 状態に応じて処理実行 */
	switch (iStatus)
	{
		case E_BT_STATUS_READY:
			bt_proc_Ready();
			break;
		
		case E_BT_STATUS_IDLE:
			/* 処理しない */
			break;
		
		case E_BT_STATUS_CALIBLATE:
			bt_proc_Calibrate();
			break;
			
		case E_BT_STATUS_WAITING:
			bt_proc_Waiting();
			break;
			
		case E_BT_STATUS_RUN:
			/* 処理しない */
			break;
		
		default:
			/* フェール処理 */
			break;
	}
	
	return;
}

void bt_proc_Ready( void )
{
	int iConnect = D_RSI_FALSE;
	S_BT* spBt = (S_BT*)NULL;
	FILE* fpBtFile = (FILE*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* 接続状況確認 */
	iConnect = RSI_fs_bluetooth_is_connected();
	if( D_RSI_TRUE == iConnect )
	{
		/* Bluetooth通信確立 */
		fpBtFile = RSI_fs_serial_open_file( E_RSI_FS_SERIALPORT_BT );
		if( (FILE*)NULL == fpBtFile )
		{
			return;
		}
		else
		{
			/* グローバル保持 */
			spBt->fpBtFile = fpBtFile;
		}
	}
	
	/* 状態遷移 */
	spBt->iStatus = E_BT_STATUS_IDLE;
	
	return;
}

void bt_proc_Calibrate( void )
{
#if	(__VC_DEBUG__)
	bt_check_SerialMessageRecv();
#endif	/* __VC_DEBUG__ */
	return;
}

void bt_proc_Waiting( void )
{
	bt_check_SerialMessageRecv();
	return;
}
