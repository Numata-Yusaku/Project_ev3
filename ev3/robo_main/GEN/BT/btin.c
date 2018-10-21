#include "btin.h"

S_BT* gspBt = (S_BT*)NULL;

/* startup */
void bt_main( void )
{
	static int count = 0;
	int iRet				= D_BT_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* �̈�m�� */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* ������ */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* �N������ */
	bt_init();
	
	/* BT_TASK */
	while(1)
	{
		COMMON_lcd_draw_stringAndDec((const char*)"BT_task", count++ , 0, 70);
		iRet = TASK_msgrecv( E_TASK_TASKID_BT, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_BT_INVALID != psRecvData->iMsgid) )
		{
			/* ��M���� */
			bt_recv( psRecvData );
			
		}
		
		/* ��M�f�[�^�N���A */
		if ((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* �풓���� */
		bt_proc();
		
		/* �^�X�N�T�C�N��(ms) */
		TASK_sleep( D_TASK_CYCLE_BT );
	}

END:
	/*** ������� ***/
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
	
	/* ������ */
	memset( spBt, 0x00, sizeof(S_BT) );
	
	/* �������l�ݒ� */

	/* �O���[�o���ݒ� */
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
	
	/* �N���X�X�e�[�^�X�擾 */
	iStatus = spBt->iStatus;
	if( E_BT_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* ��Ԃɉ����ď������s */
	switch (iStatus)
	{
		case E_BT_STATUS_READY:
			bt_proc_Ready();
			break;
		
		case E_BT_STATUS_IDLE:
			/* �������Ȃ� */
			break;
		
		case E_BT_STATUS_CALIBLATE:
			bt_proc_Calibrate();
			break;
			
		case E_BT_STATUS_WAITING:
			bt_proc_Waiting();
			break;
			
		case E_BT_STATUS_RUN:
			/* �������Ȃ� */
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
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* �ڑ��󋵊m�F */
	iConnect = RSI_fs_bluetooth_is_connected();
	if( D_RSI_TRUE != iConnect )
	{
		return;
	}
	
	/* Bluetooth�ʐM�m�� */
	spBtFile = RSI_fs_serial_open_file( E_RSI_FS_SERIALPORT_BT );
	if( (FILE*)NULL == spBtFile )
	{
		return;
	}
	else
	{
		/* �O���[�o���ێ� */
		spBt->BtFile = spBtFile;
	}
	
	/* ��ԑJ�� */
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
	
	/* �O���[�o���̈�擾 */
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
	
	/* ������ */
	memset( &aTemp, 0x00, sizeof(aTemp) );
	
	/* �O���[�o���̈�擾 */
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
	
	/* �f�[�^��M */
	cRecvData = fgetc( spBt->BtFile );
	if (EOF == cRecvData)
	{
		/* ��M�f�[�^���Ȃ��ꍇ�����Ȃ� */
		return ' ';
	}
	
	/* �R�}���h���� */
	iCheck = bt_check_SerialMessageCommand( cRecvData );
	if (D_BT_CHECK_OK != iCheck)
	{
		/* �R�}���h�łȂ��f�[�^�͖��� */
		return ' ';
	}
	
	/* �R�}���h�ݒ� */
	cRet = cRecvData;
	
	/* �f�[�^����M(�Œ蒷) */
	for( iLoop = 0; iLoop < D_BT_RECVDATA_SIZE; iLoop++ )
	{
		cRecvData = fgetc( spBt->BtFile );
		if (EOF == cRecvData)
		{
			/* �I�[���B�����ꍇ�A�f�[�^���� or �����炸 */
			/* ��M�ł����f�[�^�܂ł͕ۏ؂��� */
			break;
		}
		
		/* ���l���� */
		iCheck = bt_check_SerialMessageNumber( cRecvData );
		if( D_BT_CHECK_OK == iCheck )
		{
			aTemp[iLoop] = cRecvData;
		}
		else
		{
			/* �I�[������邱�ƂŎ�M�ł����f�[�^�܂ł͕ۏ؂��� */
			aTemp[iLoop] = 0x00;
		}
	}
	
	/* ��M�f�[�^�ݒ� */
	memcpy( cpData, &aTemp, D_BT_RECVDATA_SIZE );
	
	return cRet;
}

void bt_check_SerialMessageRecv( void )
{
	char cCmd = ' ';
	char* cpData = (char*)NULL;
	S_BT_CHGCALIBRATION_RES stChgData;
	
	/* ������ */
	memset( &stChgData, 0x00, sizeof(S_BT_CHGCALIBRATION_RES) );
	
	cpData = (char*)malloc( D_BT_RECVDATA_SIZE );
	if( (char*)NULL == cpData )
	{
		goto END;
	}
	memset( cpData, 0x00, D_BT_RECVDATA_SIZE );

	/* ���b�Z�[�W�擾 */
	cCmd = bt_get_SerialMessage( cpData );
	if( ' ' != cCmd )
	{
		
		switch( cCmd )
		{
			case 's':
				bt_send_RemoteStart_res( NULL );
				break;
			
			default:
				/* ���M�f�[�^�ݒ� */
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
