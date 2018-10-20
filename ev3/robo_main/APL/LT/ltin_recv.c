#include "lt.h"
#include "ltin.h"
#include "ltin_recvtable.h"

/* FrameWork */
void lt_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_LT_RECVFUNCPTR pvRecvFunc = (F_LT_RECVFUNCPTR)NULL;
	
	/* 実行関数取得 */
	pvRecvFunc = lt_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* 受信関数実行 */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_LT_RECVFUNCPTR lt_get_RecvFunc( int iMsgId )
{
	F_LT_RECVFUNCPTR func = (F_LT_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_LT_RECV_TABLE* psRecvTable = (S_LT_RECV_TABLE*)NULL;
	
	/* 受信テーブル設定 */
	psRecvTable =T_LT_RECV_TABLE;
	if((S_LT_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_LT_RECVFUNCPTR)NULL;
	}
	
	/* 受信テーブル要素数取得 */
	iNum = sizeof( T_LT_RECV_TABLE ) / sizeof( S_LT_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_LT_RECVFUNCPTR)NULL;
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
void lt_rcv_test_req( S_MSG_DATA* spRecv )
{
	lt_send_test_res( spRecv );
	return;
}

void lt_rcv_TouchButton_req( S_MSG_DATA* spRecv )
{
	lt_Caliblate();
	return;
}

void lt_rcv_BackButton_req( S_MSG_DATA* spRecv )
{
	int iLoop = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}

	/*** 車輪制御 ***/
	/* モータの角速度リセット */
	RSI_motor_stop( spLt->stPort.iMotor.iLeftWheel, D_LT_FALSE );
	RSI_motor_stop( spLt->stPort.iMotor.iRightWheel, D_LT_FALSE );
	
	/* モジュール起動フラグ初期化 */
	for( iLoop = 0; iLoop < E_LT_WUPCHK_NUM; iLoop++ )
	{
		spLt->iWupChk[iLoop] = D_LT_FLAG_OFF;
	}
	
	spLt->iStatus = E_LT_STATUS_STOP;
	
	return;
}

void lt_rcv_UpButton_req( S_MSG_DATA* spRecv )
{
	return;
}

void lt_rcv_DownButton_req( S_MSG_DATA* spRecv )
{
	return;
}

void lt_rcv_LeftButton_req( S_MSG_DATA* spRecv )
{
	return;
}

void lt_rcv_RightButton_req( S_MSG_DATA* spRecv )
{
	return;
}

void lt_rcv_CenterButton_req( S_MSG_DATA* spRecv )
{
	printf("Center\n");
	return;
}

void lt_rcv_Wupchk_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	switch( spRecv->iMsgid )
	{
		case E_MSGID_BT_WUPCHK_RES:
			spLt->iWupChk[E_LT_WUPCHK_BT] = D_LT_FLAG_ON;
			break;
		
		default:
			/* フェール処理 */
			break;
	}
	
	return;
}

void lt_rcv_Stop_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	switch( spRecv->iMsgid )
	{
		case E_MSGID_BT_STOP_RES:
			spLt->iStopChk[E_LT_STOP_BT] = D_LT_FLAG_ON;
			break;
		
		default:
			/* フェール処理 */
			break;
	}
	
	return;
}

void lt_rcv_ChgCalibration_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	S_LT_CHGCALIBRATION_RES* spChgCalibration = (S_LT_CHGCALIBRATION_RES*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	spChgCalibration = (S_LT_CHGCALIBRATION_RES*)(spRecv->vpPara);
	if( (S_LT_CHGCALIBRATION_RES*)NULL == spChgCalibration )
	{
		return;
	}
	
	printf("%c\n", spChgCalibration->cCmd);
	
	return;
}

void lt_rcv_RemoteStart_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	if( E_LT_STATUS_WAITING == spLt->iStatus )
	{
		lt_send_staRunning_req( NULL );
		spLt->iStatus = E_LT_STATUS_RUN_STANDUP;
		printf("[Remote]Gooooooooooooo!!!\n");
	}
	return;
}
