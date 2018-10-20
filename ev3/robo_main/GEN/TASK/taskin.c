#include "taskin.h"

S_TASK* gspTask = (S_TASK*)NULL;
S_MSG_QUE pgQue[E_TASK_TASKID_NUM];

/* startup */
void task_init_que( void )
{
	memset( pgQue, 0x00, ( sizeof( S_MSG_QUE )* E_TASK_TASKID_NUM) );
	
	return;
}

void task_sleep( int iCycle )
{
	
#if	(__VC_DEBUG__)
	Sleep(iCycle);
#else	/* __VC_DEBUG__ */
	
#endif	/* __VC_DEBUG__ */
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
	S_MSG_QUE* psQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* psSend = (S_MSG_DATA*)NULL;
	void* psData = (void*)NULL;
	
	/* 引数チェック */
	if(E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara )
	{
		return D_TASK_NG;
	}
	
	/* 領域確保 */
	psSend = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psSend)
	{
		goto END;
	}
	memset( psSend, 0x00, sizeof( S_MSG_DATA ) );
	
	/* キュー取得 */
	psQue = &pgQue[iTask];
	if( (S_MSG_QUE*)NULL == psQue )
	{
		goto END;
	}
	
	/* キュー溢れ */
	if( D_TASK_QUE_MAX <= psQue->stStatus.iNum )
	{
		printf( "que over: %08x\n",iTask);
		goto END;
	}
	
	/* 送信データ退避 */
	psSend->iMsgid = spPara->iMsgid;
	psSend->iSize = spPara->iSize;
	if( 0 >= psSend->iSize )
	{
		goto END;
	}
	
	psData = (void*)malloc( psSend->iSize );
	if ((void*)NULL == psData)
	{
		goto END;
	}
	memset( psData, 0x00, psSend->iSize );
	memcpy( psData, spPara->vpPara, psSend->iSize );
	psSend->vpPara = psData;
	
	psQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	
	/*** データ設定 ***/
	/* ID */
	psQue->stData[psQue->stStatus.iTail].iMsgid = psSend->iMsgid;
	/* パラメータサイズ */
	psQue->stData[psQue->stStatus.iTail].iSize = psSend->iSize;
	/* パラメータアドレス */
	psQue->stData[psQue->stStatus.iTail].vpPara = psSend->vpPara;
	
	/* ログ出力 */
	task_msglog( E_TASK_MSGDIR_SEND, iTask, psSend->iMsgid );
	
	/*** 状態更新 ***/
	/* キュー数 */
	psQue->stStatus.iNum++;
	/* 終端 */
	psQue->stStatus.iTail++;
	
	/* 終端の場合は先頭に戻す */
	if (D_TASK_QUE_MAX == psQue->stStatus.iTail)
	{
		psQue->stStatus.iTail = 0;
	}
	
	/************/
	psQue->stStatus.iFlag = D_TASK_MODE_OFF;	
	
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psSend)
	{
		free( psSend );
		psSend = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_OK;

END:
	/*** 解放処理 ***/
	if ( (S_MSG_DATA*)NULL != psSend)
	{
		free( psSend );
		psSend = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == psData)
	{
		free( psData );
		psData = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_NG;
}

int task_msgrecv( int iTask, S_MSG_DATA* spPara )
{
	S_MSG_QUE* psQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* psRecv = (S_MSG_DATA*)NULL;
	void* psData = (void*)NULL;
	
	/* 引数チェック */
	if ( E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara)
	{
		return D_TASK_NG;
	}
	
	/* 領域確保 */
	psRecv = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecv)
	{
		goto END;
	}
	memset( psRecv, 0x00, sizeof( S_MSG_DATA ) );
	
	/* キュー取得 */
	psQue = &pgQue[iTask];
	if ((S_MSG_QUE*)NULL == psQue)
	{
		goto END;
	}
	
	/* イベントなし */
	if (0 == psQue->stStatus.iNum)
	{
		goto END;
	}
	
	psQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	/*** データ取得 ***/
	/* ID */
	psRecv->iMsgid = psQue->stData[psQue->stStatus.iHead].iMsgid;
	/* パラメータサイズ */
	psRecv->iSize = psQue->stData[psQue->stStatus.iHead].iSize;
	/* パラメータアドレス */
	psRecv->vpPara = psQue->stData[psQue->stStatus.iHead].vpPara;
	
	psData = (void*)malloc( psRecv->iSize );
	if ((void*)NULL == psData)
	{
		goto END;
	}
	memset( psData, 0x00, psRecv->iSize );
	memcpy( psData, psRecv->vpPara, psRecv->iSize );
	
	/* ログ出力 */
	task_msglog( E_TASK_MSGDIR_RECV, iTask, psRecv->iMsgid );
	
	/* 出力に設定 */
	/* ID */
	spPara->iMsgid = psRecv->iMsgid;
	/* パラメータサイズ */
	spPara->iSize = psRecv->iSize;
	/* パラメータアドレス */
	spPara->vpPara = psData;
	
	/*** データクリア ***/
	/* ID */
	psQue->stData[psQue->stStatus.iHead].iMsgid = D_TASK_MSGID_INVALID;
	/* パラメータサイズ */
	psQue->stData[psQue->stStatus.iHead].iSize = 0;
	/* パラメータアドレス */
	if( (void*)NULL != psQue->stData[psQue->stStatus.iHead].vpPara)
	{
		free( psQue->stData[psQue->stStatus.iHead].vpPara );
		psQue->stData[psQue->stStatus.iHead].vpPara = (void*)NULL;
		psRecv->vpPara = (void*)NULL;
	}
	
	/*** 状態更新 ***/
	/* キュー数 */
	psQue->stStatus.iNum--;
	/* 先頭 */
	psQue->stStatus.iHead++;
	
	/* 終端の場合は先頭に戻す */
	if (D_TASK_QUE_MAX == psQue->stStatus.iHead)
	{
		psQue->stStatus.iHead = 0;
	}
	
	/************/
	psQue->stStatus.iFlag = D_TASK_MODE_OFF;
	
	return D_TASK_OK;

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecv)
	{
		free( psRecv );
		psRecv = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == psData)
	{
		free( psData );
		psData = (S_MSG_DATA*)NULL;
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
	fprintf( fpMsgLog, "Dir[Send/Recv],Task[Que],MsgId[Hex]\n");
#endif	/* D_TASK_LOGMODE */
	
	return;
}

void task_msglog( int iDir, int iTask, int iMsgId )
{
#if	(D_TASK_LOGMODE)
	S_TASK* spTask = (S_TASK*)NULL;
	
	spTask = task_get_Global();
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	if( (FILE*)NULL == spTask->fpMsgLog )
	{
		return;
	}
	
	switch( iDir )
	{
		case E_TASK_MSGDIR_SEND:
//			printf("[SEND],%08x,0x%08x\n", iTask, iMsgId);
			fprintf( spTask->fpMsgLog, "[SEND],0x%08x,0x%08x\n", iTask, iMsgId );
			break;
		
		case E_TASK_MSGDIR_RECV:
//			printf("[RECV],%08x,0x%08x\n", iTask, iMsgId);
			fprintf( spTask->fpMsgLog, "[RECV],0x%08x,0x%08x\n", iTask, iMsgId );
			break;
		
		default:
			/* フェール処理 */
			break;
	}
#endif	/* D_TASK_LOGMODE */
	return;
}

