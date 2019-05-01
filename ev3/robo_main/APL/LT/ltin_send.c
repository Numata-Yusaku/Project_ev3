#include "lt.h"
#include "ltin.h"

void lt_send_test_res( S_MSG_DATA* spSend )
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
	spSendData->iMsgid = E_MSGID_LT_TEST_RES;
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

void lt_send_Timer_res( S_LT_TIMERINFO* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_LT_TIMERINFO* spSendPara = (S_LT_TIMERINFO*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_LT_TIMERINFO*)malloc( sizeof( S_LT_TIMERINFO ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_LT_TIMERINFO ) );
	
	/* データ設定 */
	spSendPara->iTimerId = spSend->iTimerId;
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_LT_TIMER_RES;
	spSendData->iSize = sizeof( S_LT_TIMERINFO );
	spSendData->vpPara = (void*)spSendPara;
	
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

void lt_send_Wupchk_req( void )
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
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* BT */
	spSendData->iMsgid = E_MSGID_BT_WUPCHK_REQ;
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}
	
	/* LD */
	spSendData->iMsgid = E_MSGID_LD_WUPCHK_REQ;
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

void lt_send_Wupchk_req_Retry( void )
{
	int iLoop = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	for( iLoop = 0; iLoop < E_LT_WUPCHK_NUM; iLoop++ )
	{
		if( D_LT_FLAG_ON != spLt->iWupChk[iLoop] )
		{
			switch( iLoop )
			{
				case E_LT_WUPCHK_BT:
					lt_send_Wupchk_bt_req();
					break;
				
				case E_LT_WUPCHK_LD:
					lt_send_Wupchk_ld_req();
					break;
				
				default:
					/* フェール処理 */
					break;
			}
		}
	}
	
	return;
}

void lt_send_Wupchk_bt_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_WUPCHK_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_Wupchk_ld_req( void )
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
	spSendData->iMsgid = E_MSGID_LD_WUPCHK_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
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

void lt_send_Stop_req( void )
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
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* BT */
	spSendData->iMsgid = E_MSGID_BT_STOP_REQ;
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}
	
	/* LD */
	spSendData->iMsgid = E_MSGID_LD_STOP_REQ;
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

void lt_send_Stop_req_Retry( void )
{
	int iLoop = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	for( iLoop = 0; iLoop < E_LT_STOP_NUM; iLoop++ )
	{
		if( D_LT_FLAG_ON != spLt->iStopChk[iLoop] )
		{
			switch( iLoop )
			{
				case E_LT_WUPCHK_BT:
					lt_send_Stop_bt_req();
					break;
				
				case E_LT_WUPCHK_LD:
					lt_send_Stop_ld_req();
					break;
				
				default:
					/* フェール処理 */
					break;
			}
		}
	}
	
	return;
}

void lt_send_Stop_bt_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_STOP_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_Stop_ld_req( void )
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
	spSendData->iMsgid = E_MSGID_LD_STOP_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
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

void lt_send_ShutDown_res( void )
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
	spSendData->iMsgid = E_MSGID_LT_SHUTDOWN_RES;
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

void lt_send_staCalibration_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_STACALIBRATION_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_endCalibration_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_ENDCALIBRATION_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_staRunning_req( void )
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
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/*** BT ***/
	spSendData->iMsgid = E_MSGID_BT_STARUNNING_REQ;
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}
	
	/*** LD ***/
	spSendData->iMsgid = E_MSGID_LD_STARUNNING_REQ;
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

void lt_send_endRunning_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_ENDRUNNING_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_setClientSendGyro_req( S_TASK_SETCLIENTSEND_GYRO* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_TASK_SETCLIENTSEND_GYRO* spSendPara = (void*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_TASK_SETCLIENTSEND_GYRO*)malloc( sizeof( S_TASK_SETCLIENTSEND_GYRO ) );
	if ((S_TASK_SETCLIENTSEND_GYRO*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_TASK_SETCLIENTSEND_GYRO ) );
	
	/* 送信パラメータ設定 */
	spSendPara->iGyro = spSend->iGyro;

	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_BT_SETCLIENTSEND_GYRO_REQ;
	spSendData->iSize = sizeof( S_TASK_SETCLIENTSEND_GYRO );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_setClientSendColor_req( void )
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
	spSendData->iMsgid = E_MSGID_BT_SETCLIENTSEND_COLOR_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
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

void lt_send_setLog_StatusLog_req( S_LT_LOGINFO_STATUSLOG* spSend )
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

void lt_send_setLog_CalibrateLog_req( S_LT_LOGINFO_CALIBRATELOG* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_TASK_LOGINFO_CALIBRATELOG* spSendPara = (S_TASK_LOGINFO_CALIBRATELOG*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_TASK_LOGINFO_CALIBRATELOG*)malloc( sizeof( S_TASK_LOGINFO_CALIBRATELOG ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_TASK_LOGINFO_CALIBRATELOG ) );
	
	/* データ設定 */
	spSendPara->iLogNum = spSend->iLogNum;
	memcpy( &(spSendPara->stLog[0]), &(spSend->stLog[0]), sizeof( S_TASK_LOGDATA_CALIBRATELOG ) * D_TASK_BUFFNUM_CALIBRATELOG );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_LD_SETLOG_CALIBRATELOG_REQ;
	spSendData->iSize = sizeof( S_TASK_LOGINFO_CALIBRATELOG );
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

void lt_send_setLog_SystemLog_req( S_LT_LOGINFO_SYSTEMLOG* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* spSendData = (S_MSG_DATA*)NULL;
	S_TASK_LOGINFO_SYSTEMLOG* spSendPara = (S_TASK_LOGINFO_SYSTEMLOG*)NULL;
	
	/* 領域確保 */
	spSendData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spSendData)
	{
		goto END;
	}
	
	spSendPara = (S_TASK_LOGINFO_SYSTEMLOG*)malloc( sizeof( S_TASK_LOGINFO_SYSTEMLOG ) );
	if ((void*)NULL == spSendPara)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( spSendPara, 0x00, sizeof( S_TASK_LOGINFO_SYSTEMLOG ) );
	
	/* データ設定 */
	spSendPara->iLogNum = spSend->iLogNum;
	memcpy( &(spSendPara->stLog[0]), &(spSend->stLog[0]), sizeof( S_TASK_LOGDATA_SYSTEMLOG ) * D_TASK_BUFFNUM_SYSTEMLOG );
	
	/* 送信データ設定 */
	spSendData->iMsgid = E_MSGID_LD_SETLOG_SYSTEMLOG_REQ;
	spSendData->iSize = sizeof( S_TASK_LOGINFO_SYSTEMLOG );
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

void lt_send_setLog_LogLast_req( void )
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
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
	/*** BT ***/
	spSendData->iMsgid = E_MSGID_BT_SETLOG_LOGLAST_REQ;
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_BT, spSendData );
	if( D_TASK_OK != iRet )
	{
		printf("MSG_send err\n");
	}
	
	/*** LD ***/
	spSendData->iMsgid = E_MSGID_LD_SETLOG_LOGLAST_REQ;
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

void lt_send_staLogDump_req( void )
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
	spSendData->iMsgid = E_MSGID_LD_STALOGDUMP_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
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

void lt_send_endLogDump_req( void )
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
	spSendData->iMsgid = E_MSGID_LD_ENDLOGDUMP_REQ;
	spSendData->iSize = sizeof( S_MSG_DATA );
	spSendData->vpPara = spSendPara;
	
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