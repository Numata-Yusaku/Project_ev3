#include "main.h"

#if (__VC_DEBUG__)
int main(void)
{
	/* ������ */
	MAIN_init();
	
	/* �X���b�h�̐��� */
	main_make_thread();
	
	/* ���C���^�X�N�N�� */
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
	/* ���C���N�� */
	main_DispReady();
	
	/* TASK������ */
	TASK_init();
	
	/* RSI������ */
	RSI_init();
	
	return;
}

void MAIN_task(void)
{
	static int count = 0;
	int iRet = D_MAIN_NG;
	S_MSG_DATA* psRecvData = (S_MSG_DATA*)NULL;
	
	/* �̈�m�� */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	/* ������ */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* MAIN_TASK */
	while (1)	/* loop sta*/
	{
		COMMON_lcd_draw_stringAndDec((const char*)"MAIN_task", count++ , 0, 50);

		/* MSG��M */
		iRet = TASK_msgrecv( E_TASK_TASKID_MAIN, psRecvData );
		if ( ( D_TASK_OK == iRet) &&
				( E_MSGID_MAIN_INVALID != psRecvData->iMsgid ) )
		{
			
			/* ��M���� */
			main_recv( psRecvData );
			
			/* ��M�f�[�^�N���A */
			if ((void*)NULL != psRecvData->vpPara)
			{
				free( psRecvData->vpPara );
				psRecvData->vpPara = (void*)NULL;
			}
			memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		}
		
		/* �L�[���͂̊Ď� */
#if	(__VC_DEBUG__)
		main_recv_cmd();
#else	/* __VC_DEBUG__ */
		main_recv_ButtonPressed();
#endif	/* __VC_DEBUG__ */
	}			/* loop end */
	
	return;

END:
	/*** ������� ***/
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
	/* �N���҂� */
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_RED );
	TASK_sleep( 100 );
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_ORANGE );
	TASK_sleep( 100 );
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_GREEN );
	TASK_sleep( 100 );
	
	/* ��ʏ����� */
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
	
	/* �L�[���͂�����ꍇ */
	if ( _kbhit() )
	{
		/* �L�[���擾 */
		iKey = _getch();
		switch( iKey )
		{
			case 'e':	/* �A�v���P�[�V�����I�� */
				main_shutdown();
				break;
				
			case 't':	/* �e�X�g�ʐM */
				main_rcv_cmd_t();
				break;
			
			/* ���s�̋^���g���K�[ */
			case 'T':	/* �^�b�`�Z���T���� */
				main_rcv_cmd_T();
				break;
				
			case 'L':	/* ���{�^������ */
				main_rcv_cmd_L();
				break;
				
			case 'R':	/* �E�{�^������ */
				main_rcv_cmd_R();
				break;
				
			case 'U':	/* ��{�^������ */
				main_rcv_cmd_U();
				break;
				
			case 'D':	/* ���{�^������ */
				main_rcv_cmd_D();
				break;
				
			case 'C':	/* �����{�^������ */
				main_rcv_cmd_C();
				break;
				
			case 'B':	/* �o�b�N�{�^������ */
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
	
	/* �L�[���͂�����ꍇ */
	if( E_RSI_HW_BUTTON_INVALID != iKey )
	{
		switch( iKey )
		{
			case E_RSI_HW_BUTTON_LEFT:	/* ���{�^������ */
				main_rcv_cmd_L();
				break;
				
			case E_RSI_HW_BUTTON_RIGHT:	/* �E�{�^������ */
				main_rcv_cmd_R();
				break;
				
			case E_RSI_HW_BUTTON_UP:	/* ��{�^������ */
				main_rcv_cmd_U();
				break;
				
			case E_RSI_HW_BUTTON_DOWN:	/* ���{�^������ */
				main_rcv_cmd_D();
				break;
				
			case E_RSI_HW_BUTTON_ENTER:	/* �����{�^������ */
				main_rcv_cmd_C();
				break;
				
			case E_RSI_HW_BUTTON_BACK:	/* �o�b�N�{�^������ */
				main_rcv_cmd_B();
				
				/* T.B.D :�f�o�b�O�̂��߂ɋ����E�o(LT�������ł�����폜)*/
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
	/* �e�X�g���M */
	main_send_test_req( NULL );
	return;
}

void main_rcv_cmd_T( void )
{
	/* �{�^��(�^�b�`�Z���T)���� */
	main_send_TouchButton_req( NULL );
	return;
}

void main_rcv_cmd_B( void )
{
	/* �{�^��(�o�b�N�{�^��)���� */
	main_send_BackButton_req( NULL );
	return;
}

void main_rcv_cmd_U( void )
{
	/* �{�^��(��{�^��)���� */
	main_send_UpButton_req( NULL );
	return;
}

void main_rcv_cmd_D( void )
{
	/* �{�^��(���{�^��)���� */
	main_send_DownButton_req( NULL );
	return;
}

void main_rcv_cmd_L( void )
{
	/* �{�^��(���{�^��)���� */
	main_send_LeftButton_req( NULL );
	return;
}

void main_rcv_cmd_R( void )
{
	/* �{�^��(�E�{�^��)���� */
	main_send_RightButton_req( NULL );
	return;
}

void main_rcv_cmd_C( void )
{
	/* �{�^��(�����{�^��)���� */
	main_send_CenterButton_req( NULL );
	return;
}

void main_send_test_req( S_MSG_DATA* spSend )
{
	int iRet = D_TASK_NG;
	S_MSG_DATA* psSendData = (S_MSG_DATA*)NULL;
	void* psSendPara = (void*)NULL;
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_TEST_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
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
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_TOUCHBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_BACKBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_UPBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_DOWNBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_LEFTBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_RIGHTBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
	
	/* �̈�m�� */
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
	
	/* ������ */
	memset( psSendData, 0x00, sizeof( S_MSG_DATA ) );
	memset( psSendPara, 0x00, sizeof( int ) );
	
	/* ���M�f�[�^�ݒ� */
	psSendData->iMsgid = E_MSGID_LT_CENTERBUTTON_REQ;
	psSendData->iSize = sizeof( S_MSG_DATA );
	psSendData->vpPara = psSendPara;
	
	/* MSG���M */
	iRet = TASK_msgsend( E_TASK_TASKID_LT, psSendData );
	if( D_TASK_OK != iRet )
	{
		printf("send err:%x\n",psSendData->iMsgid);
	}

END:
	/*** ������� ***/
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
