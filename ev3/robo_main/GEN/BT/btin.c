#include "btin.h"

S_BT* gspBt = (S_BT*)NULL;

/* startup */
void bt_main( void )
{
	static int count = 0;
	int iRet				= D_BT_NG;
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
	bt_init();
	
	/* BT_TASK */
	while(1)
	{
		COMMON_lcd_draw_stringAndDec((const char*)"BT_task", count++ , 0, 70);
		iRet = TASK_msgrecv( E_TASK_TASKID_BT, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_BT_INVALID != psRecvData->iMsgid) )
		{
			/* 受信処理 */
			bt_recv( psRecvData );
			
		}
		
		/* 受信データクリア */
		if ((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		bt_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_BT );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	bt_shutdown();
	
	return;
}

void bt_init( void )
{
	bt_set_Global();
	return;
}

void bt_shutdown( void )
{
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	ter_tsk( BT_TASK );
#endif	/* __VC_DEBUG__ */
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
			break;
	}
	
	return;
}

void bt_proc_Ready( void )
{
	int iConnect = D_RSI_FALSE;
	S_BT* spBt = (S_BT*)NULL;
	FILE* spBtFile = (FILE*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* 接続状況確認 */
	iConnect = RSI_fs_bluetooth_is_connected();
	if( D_RSI_TRUE != iConnect )
	{
		return;
	}
	
	/* Bluetooth通信確立 */
	spBtFile = RSI_fs_serial_open_file( E_RSI_FS_SERIALPORT_BT );
	if( (FILE*)NULL == spBtFile )
	{
		return;
	}
	else
	{
		/* グローバル保持 */
		spBt->BtFile = spBtFile;
	}
	
	/* 状態遷移 */
	spBt->iStatus = E_BT_STATUS_IDLE;
	
	return;
}

void bt_proc_Calibrate( void )
{
	bt_check_SerialMessageRecv();
	return;
}

void bt_proc_Waiting( void )
{
	bt_check_SerialMessageRecv();
	return;
}

/* serial */
void bt_set_SerialMessage( char* cpSendData, int iSize )
{
	int iLoop = 0;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	if( (FILE*)NULL == spBt->BtFile )
	{
		printf("Serial_set error\n");
		return;
	}
	
	for( iLoop = 0; iLoop < iSize; iLoop++ )
	{
		fprintf( spBt->BtFile, "%c", cpSendData[iLoop] );
	}
	fseek( spBt->BtFile, -(iSize), SEEK_CUR );
	
	return;
}

char bt_get_SerialMessage( char* cpData )
{
	int iLoop = 0;
	int iCheck = 0;
	S_BT* spBt = (S_BT*)NULL;
	char aTemp[D_BT_RECVDATA_SIZE +1 ];
	char cRecvData = ' ';
	char cRet = ' ';
	
	/* 初期化 */
	memset( &aTemp, 0x00, sizeof(aTemp) );
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return ' ';
	}
	
	if( (FILE*)NULL == spBt->BtFile )
	{
		printf("Serial_get error\n");
		return ' ';
	}
	
	/* データ受信 */
	cRecvData = fgetc( spBt->BtFile );
	if (EOF == cRecvData)
	{
		/* 受信データがない場合処理なし */
		return ' ';
	}
	
	/* コマンド判定 */
	iCheck = bt_check_SerialMessageCommand( cRecvData );
	if (D_BT_CHECK_OK != iCheck)
	{
		/* コマンドでないデータは無視 */
		return ' ';
	}
	
	/* コマンド設定 */
	cRet = cRecvData;
	
	/* データ部受信(固定長) */
	for( iLoop = 0; iLoop < D_BT_RECVDATA_SIZE; iLoop++ )
	{
		cRecvData = fgetc( spBt->BtFile );
		if (EOF == cRecvData)
		{
			/* 終端到達した場合、データ欠損 or 桁足らず */
			/* 受信できたデータまでは保証する */
			break;
		}
		
		/* 数値判定 */
		iCheck = bt_check_SerialMessageNumber( cRecvData );
		if( D_BT_CHECK_OK == iCheck )
		{
			aTemp[iLoop] = cRecvData;
		}
		else
		{
			/* 終端をいれることで受信できたデータまでは保証する */
			aTemp[iLoop] = 0x00;
		}
	}
	
	/* 受信データ設定 */
	memcpy( cpData, &aTemp, D_BT_RECVDATA_SIZE );
	
	return cRet;
}

void bt_check_SerialMessageRecv( void )
{
	char cCmd = ' ';
	char* cpData = (char*)NULL;
	S_BT_CHGCALIBRATION_RES stChgData;
	
	/* 初期化 */
	memset( &stChgData, 0x00, sizeof(S_BT_CHGCALIBRATION_RES) );
	
	cpData = (char*)malloc( D_BT_RECVDATA_SIZE );
	if( (char*)NULL == cpData )
	{
		goto END;
	}
	memset( cpData, 0x00, D_BT_RECVDATA_SIZE );

	/* メッセージ取得 */
	cCmd = bt_get_SerialMessage( cpData );
	if( ' ' != cCmd )
	{
		
		switch( cCmd )
		{
			case 's':
				bt_send_RemoteStart_res( NULL );
				break;
			
			default:
				/* 送信データ設定 */
				stChgData.iSize = D_BT_RECVDATA_SIZE;
				memcpy( &(stChgData.aData), cpData, D_BT_RECVDATA_SIZE );
				stChgData.cCmd = cCmd;
				
				bt_send_chgCalibration_res( &stChgData );
				break;
			
		}
		
	}

END:
	
	if( (char*)NULL != cpData )
	{
		free(cpData);
		cpData = (char*)NULL;
	}
	
	return;
}

int bt_check_SerialMessageCommand( char cVal )
{
	int iRet = D_BT_CHECK_NG;
	
	if( (('a' <= cVal) && ('z' >= cVal)) ||
		(('A' <= cVal) && ('Z' >= cVal)) )
	{
		iRet = D_BT_CHECK_OK;
	}
	
	return iRet;
}

int bt_check_SerialMessageNumber( char cVal )
{
	int iRet = D_BT_CHECK_NG;
	
	if( ('0' <= cVal) && ('9' >= cVal) )
	{
		iRet = D_BT_CHECK_OK;
	}
	
	return iRet;
}
