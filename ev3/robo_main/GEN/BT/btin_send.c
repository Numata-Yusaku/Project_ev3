#include "bt.h"
#include "btin.h"

void bt_send_test_res( S_MSG_DATA* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	void* spSendPara = (void*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( int ) );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_TEST_RES;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_MAIN, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_Wupchk_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	void* spSendPara = (void*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( int ) );
	
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_WUPCHK_RES;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_Stop_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	void* spSendPara = (void*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( int ) );
	
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_STOP_RES;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_chgCalibration_res( S_TASK_CHGCALIBRATION_RES* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_TASK_CHGCALIBRATION_RES* spSendPara = (void*)NULL;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		goto END;
	}
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_TASK_CHGCALIBRATION_RES*)malloc( sizeof( S_TASK_CHGCALIBRATION_RES ) );
	if ((S_TASK_CHGCALIBRATION_RES*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_TASK_CHGCALIBRATION_RES ) );
	
	/* 送信パラメータ設定 */
	spSendPara->cCmd = spSend->cCmd;
	spSendPara->iSize= spSend->iSize;
	memcpy( spSendPara->aData, spSend->aData, spSend->iSize );

	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_CHGCALIBRATION_RES;
	spSendData->iSize = sizeof( S_TASK_CHGCALIBRATION_RES );
	spSendData->vpPara = (void*)spSendPara;
	
	/* CHG通知可能な状態かチェック */
	if( ( E_BT_STATUS_CALIBLATE == spBt->iStatus) ||
		( E_BT_STATUS_WAITING == spBt->iStatus) )
	{
		/* MSG送信 */
		iRet = TASK_msgsend( E_TASK_TASKID_LT, spSendData );
		if( D_TASK_OK != iRet )
		{
			printf("MSG_send err\n");
		}
	}

END:
	/*** 解放処理 ***/
	if ((S_TASK_CHGCALIBRATION_RES*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (S_TASK_CHGCALIBRATION_RES*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_RemoteStart_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	void* spSendPara = (void*)NULL;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		goto END;
	}
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( int ) );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_REMOTESTART_RES;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* リモートスタート通知可能な状態かチェック */
	if ( E_BT_STATUS_WAITING == spBt->iStatus)
	{
		/* MSG送信 */
		iRet = TASK_msgsend( E_TASK_TASKID_LT, spSendData );
		if (D_TASK_OK != iRet)
		{
			printf( "MSG_send err\n" );
		}
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_setLog_StatusLog_req( S_BT_LOGINFO_STATUSLOG* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_TASK_LOGINFO_STATUSLOG* spSendPara = (S_TASK_LOGINFO_STATUSLOG*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_TASK_LOGINFO_STATUSLOG*)malloc( sizeof( S_TASK_LOGINFO_STATUSLOG ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_TASK_LOGINFO_STATUSLOG ) );
	
	/* データ設定 */
	spSendPara->iLogNum = spSend->iLogNum;
	memcpy( &(spSendPara->stLog[0]), &(spSend->stLog[0]), sizeof( S_TASK_LOGDATA_STATUSLOG ) * D_TASK_BUFFNUM_STATUSLOG );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_LD_SETLOG_STATUSLOG_REQ;
	spSendData->iSize = sizeof( S_TASK_LOGINFO_STATUSLOG );
	spSendData->vpPara = (void*)spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LD, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_setLog_LogLast_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	void* spSendPara = (void*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( int ) );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_SETLOG_LOGLAST_RES;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != spSendPara)
	{
		free( spSendPara );
		spSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != spSendData)
	{
		free( spSendData );
		spSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}
