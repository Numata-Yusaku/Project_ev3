#include "main.h"

#if (__VC_DEBUG__)
int main(void)
{
	MAIN_init();

	/* スレッドの生成 */
	main_make_thread();
	
	/* メインタスク起動 */
	MAIN_task();
}

void main_make_thread( void )
{
	int iMsgThId = 0;
	/* GEN */
	HANDLE	hBt = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)BT_main, NULL, 0, &iMsgThId);
	/* APL */
	HANDLE	hLt = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)LT_main, NULL, 0, &iMsgThId);
	return;
}
#endif	/* __VC_DEBUG__ */

void MAIN_init( void )
{
	/* TASK初期化 */
	TASK_init();
	
	/* RSI初期化 */
	RSI_init();

	return;
}

void MAIN_task(void)
{
	int iRet = D_MAIN_NG;
	S_MSG_DATA* psRecvData = (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* MAIN_TASK */
	while (1)	/* loop sta*/
	{
		/* MSG受信 */
		iRet = TASK_msgrecv( E_TASK_TASKID_MAIN, psRecvData );
		if ( ( D_TASK_OK == iRet) &&
				( E_MSGID_MAIN_INVALID != psRecvData->iMsgid ) )
		{
			
			/* 受信処理 */
			main_recv( psRecvData );
			
			/* 受信データクリア */
			if ((void*)NULL != psRecvData->vpPara)
			{
				free( psRecvData->vpPara );
				psRecvData->vpPara = (void*)NULL;
			}
			memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		}
		
#if	(__VC_DEBUG__)
		/* キー入力の監視 */
		main_recv_cmd();
#endif	/* __VC_DEBUG__ */
		
	}			/* loop end */
	
	return;

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	main_shutdown();
	
	return;
}

void main_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	
	if( E_MSGID_LT_SHUTDOWN_RES == iMsgId )
	{
		main_shutdown();
	}
	
	return;
}

void main_shutdown( void )
{
#if	(__VC_DEBUG__)
	exit(1);
#else	/* __VC_DEBUG__ */
	ext_tsk();
#endif	/* __VC_DEBUG__ */
		return;
}

#if	(__VC_DEBUG__)
void main_recv_cmd( void )
{
	int iKey = 0;
//	F_MAIN_CMDRECVFUNCPTR pvRecvFunc = (F_MAIN_CMDRECVFUNCPTR)NULL;
	

	/* キー入力がある場合 */
	if ( _kbhit() )
	{
		/* キーを取得 */
		iKey = _getch();
		switch(iKey)
		{
			case 'e':	/* アプリケーション終了 */
				main_shutdown();
				break;
				
			case 't':	/* テスト通信 */
				main_rcv_cmd_t();
				break;
			
			/* 走行体疑似トリガー */
			case 'T':	/* タッチセンサ押下 */
				main_rcv_cmd_T();
				break;
				
			case 'B':	/* バックボタン押下 */
				main_rcv_cmd_B();
				break;
				
			case 'U':	/* 上ボタン押下 */
				main_rcv_cmd_U();
				break;
				
			case 'D':	/* 下ボタン押下 */
				main_rcv_cmd_D();
				break;
				
			case 'L':	/* 左ボタン押下 */
				main_rcv_cmd_L();
				break;
				
			case 'R':	/* 右ボタン押下 */
				main_rcv_cmd_R();
				break;
				
			case 'C':	/* 中央ボタン押下 */
				main_rcv_cmd_C();
				break;
				
			default:
				break;
		}
	}	
	return;
}
#endif	/* __VC_DEBUG__ */

void main_rcv_cmd_t( void )
{
	/* テスト送信 */
	main_send_test_req( NULL );
	return;
}

void main_rcv_cmd_T( void )
{
	/* ボタン(タッチセンサ)押下 */
	main_send_TouchButton_req( NULL );
	return;
}

void main_rcv_cmd_B( void )
{
	/* ボタン(バックボタン)押下 */
	main_send_BackButton_req( NULL );
	return;
}

void main_rcv_cmd_U( void )
{
	/* ボタン(上ボタン)押下 */
	main_send_UpButton_req( NULL );
	return;
}

void main_rcv_cmd_D( void )
{
	/* ボタン(下ボタン)押下 */
	main_send_DownButton_req( NULL );
	return;
}

void main_rcv_cmd_L( void )
{
	/* ボタン(左ボタン)押下 */
	main_send_LeftButton_req( NULL );
	return;
}

void main_rcv_cmd_R( void )
{
	/* ボタン(右ボタン)押下 */
	main_send_RightButton_req( NULL );
	return;
}

void main_rcv_cmd_C( void )
{
	/* ボタン(中央ボタン)押下 */
	main_send_CenterButton_req( NULL );
	return;
}

void main_send_test_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_TEST_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

/* TEST */
	psSendData->iMsgid = E_MSGID_BT_TEST_REQ;
	iRet = TASK_msgsend( E_TASK_TASKID_BT, psSendData );
/* TEST */

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

void main_send_TouchButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_TOUCHBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_BackButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_BACKBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_UpButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_UPBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_DownButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_DOWNBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_LeftButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_LEFTBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_RightButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_RIGHTBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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

void main_send_CenterButton_req( S_MSG_DATA* spSend )
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
	psSendData->iMsgid = E_MSGID_LT_CENTERBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG送信 */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
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
