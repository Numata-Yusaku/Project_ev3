#include "main.h"

#if (__VC_DEBUG__)
int main(void)
{
	/* 初期化 */
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
	/* メイン起動 */
	main_DispReady();
	
	/* TASK初期化 */
	TASK_init();
	
	/* RSI初期化 */
	RSI_init();
	
	return;
}

void MAIN_task(void)
{
	static int count = 0;
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
		COMMON_lcd_draw_stringAndDec((const char*)"MAIN_task", count++ , 0, 50);

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
		
		/* キー入力の監視 */
#if	(__VC_DEBUG__)
		main_recv_cmd();
#else	/* __VC_DEBUG__ */
		main_recv_ButtonPressed();
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

void main_DispReady( void )
{
	/* 起動待ち */
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_RED );
	TASK_sleep( 100 );
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_ORANGE );
	TASK_sleep( 100 );
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_GREEN );
	TASK_sleep( 100 );
	
	/* 画面初期化 */
	RSI_lcd_fill_rect( 0, 0, 178, 128, 0 );
	COMMON_lcd_draw_string((const char*)"INIT OK", 0, 10);
	
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
	
	/* キー入力がある場合 */
	if ( _kbhit() )
	{
		/* キーを取得 */
		iKey = _getch();
		switch( iKey )
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
				
			case 'L':	/* 左ボタン押下 */
				main_rcv_cmd_L();
				break;
				
			case 'R':	/* 右ボタン押下 */
				main_rcv_cmd_R();
				break;
				
			case 'U':	/* 上ボタン押下 */
				main_rcv_cmd_U();
				break;
				
			case 'D':	/* 下ボタン押下 */
				main_rcv_cmd_D();
				break;
				
			case 'C':	/* 中央ボタン押下 */
				main_rcv_cmd_C();
				break;
				
			case 'B':	/* バックボタン押下 */
				main_rcv_cmd_B();
				break;
				
			default:
				break;
		}
	}	
	return;
}
#else	/* __VC_DEBUG__ */
void main_recv_ButtonPressed( void )
{
	int iKey =E_RSI_HW_BUTTON_INVALID;
	
	if( RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_LEFT ) )
	{
		iKey = E_RSI_HW_BUTTON_LEFT;
	}
	else if(RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_RIGHT ))
	{
		iKey = E_RSI_HW_BUTTON_RIGHT;
	}
	else if(RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_UP ))
	{
		iKey = E_RSI_HW_BUTTON_UP;
	}
	else if(RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_DOWN ))
	{
		iKey = E_RSI_HW_BUTTON_DOWN;
	}
	else if(RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_ENTER ))
	{
		iKey = E_RSI_HW_BUTTON_ENTER;
	}
	else if(RSI_hw_button_is_pressed( E_RSI_HW_BUTTON_BACK ))
	{
		iKey = E_RSI_HW_BUTTON_BACK;
	}
	
	/* キー入力がある場合 */
	if( E_RSI_HW_BUTTON_INVALID != iKey )
	{
		switch( iKey )
		{
			case E_RSI_HW_BUTTON_LEFT:	/* 左ボタン押下 */
				main_rcv_cmd_L();
				break;
				
			case E_RSI_HW_BUTTON_RIGHT:	/* 右ボタン押下 */
				main_rcv_cmd_R();
				break;
				
			case E_RSI_HW_BUTTON_UP:	/* 上ボタン押下 */
				main_rcv_cmd_U();
				break;
				
			case E_RSI_HW_BUTTON_DOWN:	/* 下ボタン押下 */
				main_rcv_cmd_D();
				break;
				
			case E_RSI_HW_BUTTON_ENTER:	/* 中央ボタン押下 */
				main_rcv_cmd_C();
				break;
				
			case E_RSI_HW_BUTTON_BACK:	/* バックボタン押下 */
				main_rcv_cmd_B();
				
				/* T.B.D :デバッグのために強制脱出(LTが実装できたら削除)*/
				main_shutdown();
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
