#include "tm.h"
#include "tmin.h"

void tm_send_test_res( S_MSG_DATA* spSend )
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
	spSendData->iMsgid = E_MSGID_TM_TEST_RES;
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
