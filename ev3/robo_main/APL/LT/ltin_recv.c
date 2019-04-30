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

void lt_rcv_Timer_res( S_MSG_DATA* spRecv )
{
	int iRetry = 0;
	int iTimerId = 0;
	S_LT_TIMERINFO* spTimerInfo = (S_LT_TIMERINFO*)NULL;
	S_LT* spLt = (S_LT*)NULL;

	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if ((S_LT*)NULL == spLt)
	{
		return;
	}
	
	spTimerInfo = (S_LT_TIMERINFO*)spRecv->vpPara;
	iTimerId = spTimerInfo->iTimerId;
	
	switch( iTimerId )
	{
		case E_TIMERID_LT_WUPCHK:
			/* 起動調停 */
			iRetry = lt_chk_WupChkRetry();
			if( D_LT_NOTRETRY == iRetry )
			{
				/* タイマ削除 */
				lt_del_Timer( E_TIMERID_LT_WUPCHK );
			}
			else
			{
				/* リトライ */
				lt_send_Wupchk_req_Retry();
			}
			
			break;
		
		case E_TIMERID_LT_STOPCHK:
			/* 停止調停 */
			iRetry = lt_chk_StopChkRetry();
			if( D_LT_NOTRETRY == iRetry )
			{
				/* タイマ削除 */
				lt_del_Timer( E_TIMERID_LT_STOPCHK );
			}
			else
			{
				/* リトライ */
				lt_send_Stop_req_Retry();
			}
			
			break;
		
		case E_TIMERID_LT_LOGDUMP:
				/* タイマ削除 */
				lt_del_Timer( E_TIMERID_LT_LOGDUMP );
				
				/* 停止 */
				spLt->iStatus = E_LT_STATUS_STOP;
				
			break;
		
		default:
			/* フェール処理 */
			break;
	}
	
	return;
}

void lt_rcv_TouchButton_req( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}

	switch( spLt->iStatus )
	{
		case E_LT_STATUS_CALIBLATE_GYRO:
		case E_LT_STATUS_CALIBLATE_BLACK:
		case E_LT_STATUS_CALIBLATE_WHITE:
			lt_Caliblate();
			break;
			
		case E_LT_STATUS_CORRECT_ANGLE_CALIB:
#if (__VC_DEBUG__)
			printf("ANGLE_WAIT...\n");
#endif /* __VC_DEBUG__ */
			spLt->iStatus = E_LT_STATUS_CORRECT_ANGLE_WAIT;
			break;
			
		case E_LT_STATUS_CORRECT_ANGLE_WAIT:
			spLt->iStatus = E_LT_STATUS_CORRECTING_ANGLE;
#if (__VC_DEBUG__)
			printf("Goto The Start Ready ...\n");
#endif /* __VC_DEBUG__ */
			break;
			
		case E_LT_STATUS_CORRECTING_ANGLE:
			lt_send_staRunning_req();
			spLt->iStatus = E_LT_STATUS_RUN_STANDUP;
#if (__VC_DEBUG__)
			printf("Gooooooooooooo!!!\n");
#endif /* __VC_DEBUG__ */
			break;
		default:
			/* フェール処理 */
			break;
	}

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
		
		case E_MSGID_LD_WUPCHK_RES:
			spLt->iWupChk[E_LT_WUPCHK_LD] = D_LT_FLAG_ON;
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
		
		case E_MSGID_LD_STOP_RES:
			spLt->iStopChk[E_LT_STOP_LD] = D_LT_FLAG_ON;
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
	S_TASK_CHGCALIBRATION_RES* spRecvPara = (S_TASK_CHGCALIBRATION_RES*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	spRecvPara = (S_TASK_CHGCALIBRATION_RES*)(spRecv->vpPara);
	if( (S_TASK_CHGCALIBRATION_RES*)NULL == spRecvPara )
	{
		return;
	}
	
	printf("%c\n", spRecvPara->cCmd);
	
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
	
	if(E_LT_STATUS_CORRECTING_ANGLE == spLt->iStatus )
	{
		lt_send_staRunning_req();
		spLt->iStatus = E_LT_STATUS_RUN_STANDUP;
#if (__VC_DEBUG__)
		printf("[Remote]Gooooooooooooo!!!\n");
#endif /* __VC_DEBUG__ */
	}
	return;
}

void lt_rcv_staLogDump_res( S_MSG_DATA* spRecv )
{
#if (__VC_DEBUG__)
//	printf("LogDump ===START===\n");
#endif /* __VC_DEBUG__ */
	
	return;
}

void lt_rcv_chgLogDump_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	S_TASK_CHGLOGDUMP_RES* spRecvPara = (S_TASK_CHGLOGDUMP_RES*)NULL;
	
	if( (S_MSG_DATA*)NULL == spRecv )
	{
		return;
	}

	spRecvPara = (S_TASK_CHGLOGDUMP_RES*)(spRecv->vpPara);
	if( (S_TASK_CHGLOGDUMP_RES*)NULL == spRecvPara )
	{
		return;
	}

	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	if( E_LT_STATUS_STOP_WAIT != spLt->iStatus )
	{
		/* 走行体完全停止中でなければ通知は破棄する */
		return;
	}

#if (__VC_DEBUG__)
	printf("Dump:%2d /%2d %3d%%\n",
		spRecvPara->iNowLogNo,
		spRecvPara->iAllLogNum,
		spRecvPara->iProgress );
#endif /* __VC_DEBUG__ */
	
	/* ログダンプ完了 */
	if( ( spRecvPara->iAllLogNum == spRecvPara->iNowLogNo ) &&
		( 100 == spRecvPara->iProgress ))
	{
		lt_send_endLogDump_req();
	}
	
	return;
}

void lt_rcv_endLogDump_res( S_MSG_DATA* spRecv )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
#if (__VC_DEBUG__)
//	printf("\nLogDump ===END===\n");
#endif /* __VC_DEBUG__ */
	
	/* 走行体完全停止 */
	spLt->iStatus = E_LT_STATUS_STOP;

	return;
}
