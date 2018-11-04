#include "btin.h"

S_BT* gspBt = (S_BT*)NULL;

/* startup */
void bt_main( void )
{
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
	
	/* ���O */
	bt_log_Statuslog_open();
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
	
	/* ���O�o�� */
	bt_log_set_Statuslog();
	
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
	FILE* fpBtFile = (FILE*)NULL;
	
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
	fpBtFile = RSI_fs_serial_open_file( E_RSI_FS_SERIALPORT_BT );
	if( (FILE*)NULL == fpBtFile )
	{
		return;
	}
	else
	{
		/* �O���[�o���ێ� */
		spBt->fpBtFile = fpBtFile;
	}
	
	/* ��ԑJ�� */
	spBt->iStatus = E_BT_STATUS_IDLE;
	
	return;
}

void bt_proc_Calibrate( void )
{
#if	(__VC_DEBUG__)
	bt_check_SerialMessageRecv();
#else	/* __VC_DEBUG__ */
#endif	/* __VC_DEBUG__ */
	return;
}

void bt_proc_Waiting( void )
{
	bt_check_SerialMessageRecv();
	return;
}
