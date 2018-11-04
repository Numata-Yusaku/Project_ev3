#include "btin.h"
#include "btin_messagetable.h"

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
	
	if( (FILE*)NULL == spBt->fpBtFile )
	{
		printf("Serial_set error\n");
		return;
	}
	
	for( iLoop = 0; iLoop < iSize; iLoop++ )
	{
		fprintf( spBt->fpBtFile, "%c", cpSendData[iLoop] );
		fflush( spBt->fpBtFile );
	}
	
//	fseek( spBt->fpBtFile, -(iSize), SEEK_CUR );
	
	return;
}

int bt_get_SerialMessage( char* cpRecvData, int iSize )
{
	int iRet = D_BT_NG;
	iRet = D_BT_OK;
	//int iLoop = 0;
	//int iCheck = 0;
	//S_BT* spBt = (S_BT*)NULL;
	//char aTemp[D_BT_RECVDATA_SIZE +1 ];
	//char cRecvData = ' ';
	//char cRet = ' ';
	//
	///* ������ */
	//memset( &aTemp, 0x00, sizeof(aTemp) );
	//
	///* �O���[�o���̈�擾 */
	//spBt = bt_get_Global();
	//if( (S_BT*)NULL == spBt )
	//{
	//	return ' ';
	//}
	//
	//if( (FILE*)NULL == spBt->fpBtFile )
	//{
	//	printf("Serial_get error\n");
	//	return ' ';
	//}
	//
	///* �f�[�^��M */
	//cRecvData = fgetc( spBt->fpBtFile );
	//if (EOF == cRecvData)
	//{
	//	/* ��M�f�[�^���Ȃ��ꍇ�����Ȃ� */
	//	return ' ';
	//}
	//
	///* �R�}���h���� */
	//iCheck = bt_check_SerialMessageCommand( cRecvData );
	//if (D_BT_CHECK_OK != iCheck)
	//{
	//	/* �R�}���h�łȂ��f�[�^�͖��� */
	//	return ' ';
	//}
	//
	///* �R�}���h�ݒ� */
	//cRet = cRecvData;
	//
	///* �f�[�^����M(�Œ蒷) */
	//for( iLoop = 0; iLoop < D_BT_RECVDATA_SIZE; iLoop++ )
	//{
	//	cRecvData = fgetc( spBt->fpBtFile );
	//	if (EOF == cRecvData)
	//	{
	//		/* �I�[���B�����ꍇ�A�f�[�^���� or �����炸 */
	//		/* ��M�ł����f�[�^�܂ł͕ۏ؂��� */
	//		break;
	//	}
	//	
	//	/* ���l���� */
	//	iCheck = bt_check_SerialMessageNumber( cRecvData );
	//	if( D_BT_CHECK_OK == iCheck )
	//	{
	//		aTemp[iLoop] = cRecvData;
	//	}
	//	else
	//	{
	//		/* �I�[������邱�ƂŎ�M�ł����f�[�^�܂ł͕ۏ؂��� */
	//		aTemp[iLoop] = 0x00;
	//	}
	//}
	//
	///* ��M�f�[�^�ݒ� */
	//memcpy( cpData, &aTemp, D_BT_RECVDATA_SIZE );
	//
	return iRet;
}

void bt_check_SerialMessageRecv( void )
{
	int iRet = D_BT_NG;
	int iCheck = D_BT_CHECK_NG;
	int iSize = 0;
	S_BT* spBt = (S_BT*)NULL;
	char* cpData = (char*)NULL;
	F_BT_RECVCMDFUNCPTR pvRecvCmdFunc = (F_BT_RECVCMDFUNCPTR)NULL;
	char cCmd = ' ';
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* �R�}���h�擾 */
	cCmd = fgetc( spBt->fpBtFile ); /* ��M */
	
	/* �R�}���h�`�F�b�N */
	iCheck = bt_check_SerialMessageCommand( cCmd );
	if ( D_BT_CHECK_OK != iCheck )
	{
		goto END;
	}
	
	/* �p�����[�^�T�C�Y�擾 */
	iSize = bt_get_MessageSize( cCmd );
	if ( 0 > iSize )
	{
		goto END;
	}
	else if( 0 < iSize )
	{
		/* �̈�m�� */
		cpData = (char*)malloc( iSize );
		if( (char*)NULL == cpData )
		{
			goto END;
		}
		
		memset( cpData, 0x00, iSize );
		
		/* ��M�f�[�^�擾 */
		iRet = bt_get_SerialMessage( cpData, iSize );
		if( D_BT_OK != iRet )
		{
			goto END;
		}
	}
	else
	{
		/* �T�C�Y��0�̏ꍇ�͎�M�f�[�^�擾���Ȃ� */
	}
	
	
	/* ��M�R�}���h�֐��擾 */
	pvRecvCmdFunc = bt_get_MessageRecvFunc( cCmd );
	if( (F_BT_RECVCMDFUNCPTR)NULL != pvRecvCmdFunc)
	{
		/* ��M�R�}���h�֐����s */
		pvRecvCmdFunc( cpData, iSize );
	}

END:
	
	if( (char*)NULL != cpData )
	{
		free(cpData);
		cpData = (char*)NULL;
	}
	
	return;
}

int bt_get_MessageSize( char cCmd )
{
	int iSize = 0;
	int iNum = 0;
	int iLoop = 0;
	S_BT_MESSAGE_TABLE* psMessageTable = (S_BT_MESSAGE_TABLE*)NULL;
	
	/* �e�[�u���ݒ� */
	psMessageTable =T_BT_MESSAGE_TABLE;
	if((S_BT_MESSAGE_TABLE*)NULL == psMessageTable )
	{
		return D_BT_NG;
	}
	
	/* �e�[�u���v�f���擾 */
	iNum = sizeof( T_BT_MESSAGE_TABLE ) / sizeof( S_BT_MESSAGE_TABLE );
	if( 0 >= iNum )
	{
		return D_BT_NG;
	}
	
	/* ��M�֐��T�� */
	for( iLoop = 0; iLoop < iNum; iLoop++ )
	{
		if( cCmd == psMessageTable[iLoop].cCommand )
		{
			iSize = psMessageTable[iLoop].iSize;
			break;
		}
	}
	
	return iSize;
}

F_BT_RECVCMDFUNCPTR bt_get_MessageRecvFunc( char cCmd )
{
	F_BT_RECVCMDFUNCPTR func = (F_BT_RECVCMDFUNCPTR)NULL;
	int iNum = 0;
	int iLoop = 0;
	S_BT_MESSAGE_TABLE* psMessageTable = (S_BT_MESSAGE_TABLE*)NULL;
	
	/* �e�[�u���ݒ� */
	psMessageTable =T_BT_MESSAGE_TABLE;
	if((S_BT_MESSAGE_TABLE*)NULL == psMessageTable )
	{
		return (F_BT_RECVCMDFUNCPTR)NULL;
	}
	
	/* �e�[�u���v�f���擾 */
	iNum = sizeof( T_BT_MESSAGE_TABLE ) / sizeof( S_BT_MESSAGE_TABLE );
	if( 0 >= iNum )
	{
		return (F_BT_RECVCMDFUNCPTR)NULL;
	}
	
	/* ��M�֐��T�� */
	for( iLoop = 0; iLoop < iNum; iLoop++ )
	{
		if( cCmd == psMessageTable[iLoop].cCommand )
		{
			func = (F_BT_RECVCMDFUNCPTR)psMessageTable[iLoop].vpFunc;
			break;
		}
	}
	
	return func;
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

/* RecvCmdFunc */
void bt_recvCmd_s( char* cpRecvData, int iSize )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	fprintf( spBt->fpBtFile, "Go!!!");
	RSI_lcd_draw_string("Go!!!", 0, 70);
	bt_send_RemoteStart_res();
	
	return;
}
