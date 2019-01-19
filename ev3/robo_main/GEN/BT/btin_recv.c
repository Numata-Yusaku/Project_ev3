#include "bt.h"
#include "btin.h"
#include "btin_recvtable.h"

/* FrameWork */
void bt_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_BT_RECVFUNCPTR pvRecvFunc = (F_BT_RECVFUNCPTR)NULL;
	
//	printf("%08x\n",iMsgId);
	/* 実行関数取得 */
	pvRecvFunc = bt_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* 受信関数実行 */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_BT_RECVFUNCPTR bt_get_RecvFunc( int iMsgId )
{
	F_BT_RECVFUNCPTR func = (F_BT_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_BT_RECV_TABLE* psRecvTable = (S_BT_RECV_TABLE*)NULL;
	
	/* 受信テーブル設定 */
	psRecvTable =T_BT_RECV_TABLE;
	if((S_BT_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_BT_RECVFUNCPTR)NULL;
	}
	
	/* 受信テーブル要素数取得 */
	iNum = sizeof( T_BT_RECV_TABLE ) / sizeof( S_BT_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_BT_RECVFUNCPTR)NULL;
	}
	
	/* 受信関数探索 */
	for(iCount = 0; iCount < iNum; iCount++)
	{
		if( iMsgId == psRecvTable[iCount].iMsgId )
		{
			func = psRecvTable[iCount].func;
			break;
		}
	}
	
	return func;
}

/* RecvFunc */
void bt_rcv_test_req( S_MSG_DATA* spRecv )
{
	char cSendData[] = {"a4660b1234s"};
	
	bt_set_SerialMessage( cSendData, sizeof(cSendData) - 1 );
	bt_send_test_res( spRecv );
	return;
}

void bt_rcv_Wupchk_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* BTタスク起動完了済 */
	if( D_BT_FLAG_ON != spBt->iWupChk )
	{
		bt_send_Wupchk_res();
		spBt->iWupChk = D_BT_FLAG_ON;
	}
	
	return;
}

void bt_rcv_Stop_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* すでに停止中の場合は処理しない */
	if( E_BT_STATUS_STOP == spBt->iStatus )
	{
		return;
	}
	
	if( (FILE*)NULL != spBt->fpBtFile )
	{
		fclose(spBt->fpBtFile);
		spBt->fpBtFile = (FILE*)NULL;
	}
	
	spBt->iWupChk = D_BT_FLAG_OFF;
		
	bt_send_Stop_res();
	
	spBt->iStatus = E_BT_STATUS_STOP;
	
	return;
}

void bt_rcv_staCalibration_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spBt->iStatus = E_BT_STATUS_CALIBLATE;
	
	return;
}

void bt_rcv_endCalibration_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	char cSendData[] = {"Remote Ready:"};
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* キャリブレーション完了通知 */
	bt_set_SerialMessage( cSendData, (int)strlen(cSendData) );

	spBt->iStatus = E_BT_STATUS_WAITING;
	
	return;
}

void bt_rcv_staRunning_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spBt->iStatus = E_BT_STATUS_RUN;
	
	return;
}

void bt_rcv_setClientSendGyro_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	S_TASK_SETCLIENTSEND_GYRO* spRecvPara = (S_TASK_SETCLIENTSEND_GYRO*)NULL;
	char cSendData[D_BT_RECVDATA_SIZE];
	
	/* 初期化 */
	memset( &cSendData, 0x00, D_BT_RECVDATA_SIZE );
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spRecvPara = (S_TASK_SETCLIENTSEND_GYRO*)spRecv->vpPara;
	if( (S_TASK_SETCLIENTSEND_GYRO*)NULL == spRecvPara )
	{
		return;
	}
	
	sprintf( cSendData, "%d", spRecvPara->iGyro );
	
	bt_set_SerialMessage( cSendData, (int)strlen(cSendData) );
	
	return;
}

void bt_rcv_setClientSendColor_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	
	return;
}
