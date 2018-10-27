#include "bt.h"
#include "btin.h"

void bt_send_test_res( S_MSG_DATA* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	void* psSendPara = (void*)NULL;
	
	/* 領域確保 */
	psSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psSendData)
	{
		goto END;
	}
	
	psSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == psSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* 送信データ設定 */
	psSendData->iMsgid = E_MSGID_BT_TEST_RES;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_MAIN, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != psSendPara)
	{
		free( psSendPara );
		psSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != psSendData)
	{
		free( psSendData );
		psSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_Wupchk_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	void* psSendPara = (void*)NULL;
	
	/* 領域確保 */
	psSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psSendData)
	{
		goto END;
	}
	
	psSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == psSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	
	/* 送信データ設定 */
	psSendData->iMsgid = E_MSGID_BT_WUPCHK_RES;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != psSendPara)
	{
		free( psSendPara );
		psSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != psSendData)
	{
		free( psSendData );
		psSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_Stop_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	void* psSendPara = (void*)NULL;
	
	/* 領域確保 */
	psSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psSendData)
	{
		goto END;
	}
	
	psSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == psSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	
	/* 送信データ設定 */
	psSendData->iMsgid = E_MSGID_BT_STOP_RES;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != psSendPara)
	{
		free( psSendPara );
		psSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != psSendData)
	{
		free( psSendData );
		psSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_chgCalibration_res( S_TASK_CHGCALIBRATION_RES* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	S_TASK_CHGCALIBRATION_RES* psSendPara = (void*)NULL;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		goto END;
	}
	
	/* 領域確保 */
	psSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psSendData)
	{
		goto END;
	}
	
	psSendPara = (S_TASK_CHGCALIBRATION_RES*)malloc( sizeof( S_TASK_CHGCALIBRATION_RES ) );
	if ((S_TASK_CHGCALIBRATION_RES*)NULL == psSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( S_TASK_CHGCALIBRATION_RES ) );
	
	/* 送信パラメータ設定 */
	psSendPara->cCmd = spSend->cCmd;
	psSendPara->iSize= spSend->iSize;
	memcpy( psSendPara->aData, spSend->aData, spSend->iSize );

	/* 送信データ設定 */
	psSendData->iMsgid = E_MSGID_BT_CHGCALIBRATION_RES;
	psSendData->iSize = sizeof( S_TASK_CHGCALIBRATION_RES );
	psSendData->vpPara = (void*)psSendPara;
	
	/* CHG通知可能な状態かチェック */
	if( ( E_BT_STATUS_CALIBLATE == spBt->iStatus) ||
		( E_BT_STATUS_WAITING == spBt->iStatus) )
	{
		/* MSG送信 */
		iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
		if( D_TASK_OK != iRet )
		{
			printf("MSG_send err\n");
		}
	}

END:
	/*** 解放処理 ***/
	if ((S_TASK_CHGCALIBRATION_RES*)NULL != psSendPara)
	{
		free( psSendPara );
		psSendPara = (S_TASK_CHGCALIBRATION_RES*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != psSendData)
	{
		free( psSendData );
		psSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void bt_send_RemoteStart_res( void )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	void* psSendPara = (void*)NULL;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		goto END;
	}
	
	/* 領域確保 */
	psSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psSendData)
	{
		goto END;
	}
	
	psSendPara = (void*)malloc( sizeof( int ) );
	if ((void*)NULL == psSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* 送信データ設定 */
	psSendData->iMsgid = E_MSGID_BT_REMOTESTART_RES;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* リモートスタート通知可能な状態かチェック */
	if ( E_BT_STATUS_WAITING == spBt->iStatus)
	{
		/* MSG送信 */
		iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
		if (D_TASK_OK != iRet)
		{
			printf( "MSG_send err\n" );
		}
	}

END:
	/*** 解放処理 ***/
	if ((void*)NULL != psSendPara)
	{
		free( psSendPara );
		psSendPara = (void*)NULL;
	}
	
	if ((S_MSG_DATA*)NULL != psSendData)
	{
		free( psSendData );
		psSendData = (S_MSG_DATA*)NULL;
	}
	
	return;
}
