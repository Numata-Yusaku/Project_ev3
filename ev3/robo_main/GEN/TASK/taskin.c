#include "taskin.h"

S_TASK* gspTask = (S_TASK*)NULL;
S_MSG_QUE pgQue[E_TASK_TASKID_NUM];

/* startup */
void task_init_que( void )
{
	memset( &pgQue, 0x00, ( sizeof( S_MSG_QUE )* E_TASK_TASKID_NUM) );
	
	return;
}

void task_sleep( int iCycle )
{
	
#if	(__TARGET_EV3__)
	tslp_tsk(iCycle);
#else	/* __TARGET_EV3__ */
	Sleep(iCycle);
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void task_set_Global( void )
{
	S_TASK* spTask = (S_TASK*)NULL;
	
	spTask = (S_TASK*)malloc( sizeof(S_TASK) );
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	/* 初期化 */
	memset( spTask, 0x00, sizeof(S_TASK) );
	
	/*** 初期化値設定 ***/
	
	/* グローバル設定 */
	gspTask = spTask;
	
	return;
}

S_TASK* task_get_Global( void )
{
	return (S_TASK*)gspTask;
}

/* Message */
int task_msgsend( int iTask, S_MSG_DATA* spPara )
{
	S_MSG_QUE* spQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* spSend = (S_MSG_DATA*)NULL;
	void* spData = (void*)NULL;
	
	/* 引数チェック */
	if(E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara )
	{
		return D_TASK_NG;
	}
	
	/* 領域確保 */
	spSend = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == spSend)
	{
		goto END;
	}
	memset( spSend, 0x00, sizeof( S_MSG_DATA ) );
	
	/* キュー取得 */
	spQue = &pgQue[iTask];
	if( (S_MSG_QUE*)NULL == spQue )
	{
		goto END;
	}
	
	/* キュー溢れ */
	if( D_TASK_QUE_MAX <= spQue->stStatus.iNum )
	{
		printf( "que over: %08x\n",iTask);
		goto END;
	}
	
	/* 送信データ退避 */
	spSend->iMsgid = spPara->iMsgid;
	spSend->iSize = spPara->iSize;
	if( 0 >= spSend->iSize )
	{
		goto END;
	}
	
	spData = (void*)malloc( spSend->iSize );
	if ((void*)NULL == spData)
	{
		goto END;
	}
	memset( spData, 0x00, spSend->iSize );
	memcpy( spData, spPara->vpPara, spSend->iSize );
	spSend->vpPara = spData;
	
	spQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	
	/*** データ設定 ***/
	/* ID */
	spQue->stData[spQue->stStatus.iTail].iMsgid = spSend->iMsgid;
	/* パラメータサイズ */
	spQue->stData[spQue->stStatus.iTail].iSize = spSend->iSize;
	/* パラメータアドレス */
	spQue->stData[spQue->stStatus.iTail].vpPara = spSend->vpPara;
	
	/* ログ出力 */
	task_msglog( E_TASK_MSGDIR_SEND, iTask, spSend->iMsgid );
	
	/*** 状態更新 ***/
	/* キュー数 */
	spQue->stStatus.iNum++;
	/* 終端 */
	spQue->stStatus.iTail++;
	
	/* 終端の場合は先頭に戻す */
	if (D_TASK_QUE_MAX == spQue->stStatus.iTail)
	{
		spQue->stStatus.iTail = 0;
	}
	
	/************/
	spQue->stStatus.iFlag = D_TASK_MODE_OFF;	
	
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spSend)
	{
		free( spSend );
		spSend = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_OK;

END:
	/*** 解放処理 ***/
	if ( (S_MSG_DATA*)NULL != spSend)
	{
		free( spSend );
		spSend = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == spData)
	{
		free( spData );
		spData = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_NG;
}

int task_msgrecv( int iTask, S_MSG_DATA* spPara )
{
	S_MSG_QUE* spQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* spRecv = (S_MSG_DATA*)NULL;
	void* spData = (void*)NULL;
	
	/* 引数チェック */
	if ( E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara)
	{
		return D_TASK_NG;
	}
	
	/* 領域確保 */
	spRecv = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spRecv)
	{
		goto END;
	}
	memset( spRecv, 0x00, sizeof( S_MSG_DATA ) );
	
	/* キュー取得 */
	spQue = &pgQue[iTask];
	if ((S_MSG_QUE*)NULL == spQue)
	{
		goto END;
	}
	
	/* イベントなし */
	if (0 == spQue->stStatus.iNum)
	{
		goto END;
	}
	
	spQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	/*** データ取得 ***/
	/* ID */
	spRecv->iMsgid = spQue->stData[spQue->stStatus.iHead].iMsgid;
	/* パラメータサイズ */
	spRecv->iSize = spQue->stData[spQue->stStatus.iHead].iSize;
	/* パラメータアドレス */
	spRecv->vpPara = spQue->stData[spQue->stStatus.iHead].vpPara;
	
	spData = (void*)malloc( spRecv->iSize );
	if ((void*)NULL == spData)
	{
		goto END;
	}
	memset( spData, 0x00, spRecv->iSize );
	memcpy( spData, spRecv->vpPara, spRecv->iSize );
	
	/* ログ出力 */
	task_msglog( E_TASK_MSGDIR_RECV, iTask, spRecv->iMsgid );
	
	/* 出力に設定 */
	/* ID */
	spPara->iMsgid = spRecv->iMsgid;
	/* パラメータサイズ */
	spPara->iSize = spRecv->iSize;
	/* パラメータアドレス */
	spPara->vpPara = spData;
	
	/*** データクリア ***/
	/* ID */
	spQue->stData[spQue->stStatus.iHead].iMsgid = D_TASK_MSGID_INVALID;
	/* パラメータサイズ */
	spQue->stData[spQue->stStatus.iHead].iSize = 0;
	/* パラメータアドレス */
	if( (void*)NULL != spQue->stData[spQue->stStatus.iHead].vpPara)
	{
		free( spQue->stData[spQue->stStatus.iHead].vpPara );
		spQue->stData[spQue->stStatus.iHead].vpPara = (void*)NULL;
		spRecv->vpPara = (void*)NULL;
	}
	
	/*** 状態更新 ***/
	/* キュー数 */
	spQue->stStatus.iNum--;
	/* 先頭 */
	spQue->stStatus.iHead++;
	
	/* 終端の場合は先頭に戻す */
	if (D_TASK_QUE_MAX == spQue->stStatus.iHead)
	{
		spQue->stStatus.iHead = 0;
	}
	
	/************/
	spQue->stStatus.iFlag = D_TASK_MODE_OFF;
	
	return D_TASK_OK;

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spRecv)
	{
		free( spRecv );
		spRecv = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == spData)
	{
		free( spData );
		spData = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_NG;
}

/* log */
void task_msglog_open( void )
{
#if	(D_TASK_LOGMODE)
	S_TASK* spTask = (S_TASK*)NULL;
	FILE* fpMsgLog = (FILE*)NULL;
	
	spTask = task_get_Global();
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	fpMsgLog = fopen( D_TASK_FILENAME_MSGLOG, "w");
	if( (FILE*)NULL == fpMsgLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spTask->fpMsgLog = fpMsgLog;
	
	/* ヘッダ出力 */
	fprintf( spTask->fpMsgLog, "SysClock,Dir[Send/Recv],Task[Que],MsgId[Hex]\n");
	fflush( spTask->fpMsgLog );
#endif	/* D_TASK_LOGMODE */
	
	return;
}

void task_msglog( int iDir, int iTask, int iMsgId )
{
#if	(D_TASK_LOGMODE)
	S_TASK* spTask = (S_TASK*)NULL;
	S_TM_DAYTIME stDayTime;
	char cPrintLine[D_TASK_PRINTLINE_NUM];
	
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	
	spTask = task_get_Global();
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	if( (FILE*)NULL == spTask->fpMsgLog )
	{
		return;
	}
	
	TM_get_NowTime( &stDayTime );
	/* 時刻 */
	sprintf( cPrintLine, "[%02d/%02d/%02d]%02d:%02d:%02d.%03d,",
		stDayTime.usYear, stDayTime.usMonth, stDayTime.usDay,
		stDayTime.usHour, stDayTime.usMinute, stDayTime.usSecond,
		stDayTime.usMilliSec );
	
	switch( iDir )
	{
		case E_TASK_MSGDIR_SEND:
			sprintf( cPrintLine, "%s[SEND],0x%08x,0x%08x,", cPrintLine, iTask, iMsgId );
			break;
		
		case E_TASK_MSGDIR_RECV:
			sprintf( cPrintLine, "%s[RECV],0x%08x,0x%08x,", cPrintLine, iTask, iMsgId );
			break;
		
		default:
			/* フェール処理 */
			break;
	}
	
	fprintf( spTask->fpMsgLog, "%s\n", cPrintLine );
	fflush( spTask->fpMsgLog );
#endif	/* D_TASK_LOGMODE */
	return;
}

