#include "btin.h"
#include "btin_messagetable.h"

void bt_set_SerialMessage( char* cpSendData, int iSize )
{
	int iLoop = 0;
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
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
	///* 初期化 */
	//memset( &aTemp, 0x00, sizeof(aTemp) );
	//
	///* グローバル領域取得 */
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
	///* データ受信 */
	//cRecvData = fgetc( spBt->fpBtFile );
	//if (EOF == cRecvData)
	//{
	//	/* 受信データがない場合処理なし */
	//	return ' ';
	//}
	//
	///* コマンド判定 */
	//iCheck = bt_check_SerialMessageCommand( cRecvData );
	//if (D_BT_CHECK_OK != iCheck)
	//{
	//	/* コマンドでないデータは無視 */
	//	return ' ';
	//}
	//
	///* コマンド設定 */
	//cRet = cRecvData;
	//
	///* データ部受信(固定長) */
	//for( iLoop = 0; iLoop < D_BT_RECVDATA_SIZE; iLoop++ )
	//{
	//	cRecvData = fgetc( spBt->fpBtFile );
	//	if (EOF == cRecvData)
	//	{
	//		/* 終端到達した場合、データ欠損 or 桁足らず */
	//		/* 受信できたデータまでは保証する */
	//		break;
	//	}
	//	
	//	/* 数値判定 */
	//	iCheck = bt_check_SerialMessageNumber( cRecvData );
	//	if( D_BT_CHECK_OK == iCheck )
	//	{
	//		aTemp[iLoop] = cRecvData;
	//	}
	//	else
	//	{
	//		/* 終端をいれることで受信できたデータまでは保証する */
	//		aTemp[iLoop] = 0x00;
	//	}
	//}
	//
	///* 受信データ設定 */
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
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* コマンド取得 */
	cCmd = fgetc( spBt->fpBtFile ); /* 受信 */
	
	/* コマンドチェック */
	iCheck = bt_check_SerialMessageCommand( cCmd );
	if ( D_BT_CHECK_OK != iCheck )
	{
		goto END;
	}
	
	/* パラメータサイズ取得 */
	iSize = bt_get_MessageSize( cCmd );
	if ( 0 > iSize )
	{
		goto END;
	}
	else if( 0 < iSize )
	{
		/* 領域確保 */
		cpData = (char*)malloc( iSize );
		if( (char*)NULL == cpData )
		{
			goto END;
		}
		
		memset( cpData, 0x00, iSize );
		
		/* 受信データ取得 */
		iRet = bt_get_SerialMessage( cpData, iSize );
		if( D_BT_OK != iRet )
		{
			goto END;
		}
	}
	else
	{
		/* サイズが0の場合は受信データ取得しない */
	}
	
	
	/* 受信コマンド関数取得 */
	pvRecvCmdFunc = bt_get_MessageRecvFunc( cCmd );
	if( (F_BT_RECVCMDFUNCPTR)NULL != pvRecvCmdFunc)
	{
		/* 受信コマンド関数実行 */
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
	
	/* テーブル設定 */
	psMessageTable =T_BT_MESSAGE_TABLE;
	if((S_BT_MESSAGE_TABLE*)NULL == psMessageTable )
	{
		return D_BT_NG;
	}
	
	/* テーブル要素数取得 */
	iNum = sizeof( T_BT_MESSAGE_TABLE ) / sizeof( S_BT_MESSAGE_TABLE );
	if( 0 >= iNum )
	{
		return D_BT_NG;
	}
	
	/* 受信関数探索 */
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
	
	/* テーブル設定 */
	psMessageTable =T_BT_MESSAGE_TABLE;
	if((S_BT_MESSAGE_TABLE*)NULL == psMessageTable )
	{
		return (F_BT_RECVCMDFUNCPTR)NULL;
	}
	
	/* テーブル要素数取得 */
	iNum = sizeof( T_BT_MESSAGE_TABLE ) / sizeof( S_BT_MESSAGE_TABLE );
	if( 0 >= iNum )
	{
		return (F_BT_RECVCMDFUNCPTR)NULL;
	}
	
	/* 受信関数探索 */
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
	
	/* グローバル領域取得 */
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
