﻿#include "tmin.h"

S_TM* gspTm = (S_TM*)NULL;

/* startup */
void tm_startup( void )
{
	tm_init();
	
	/* サイクル起動 */
	RSI_extend_sta_cyc( D_EV3_CYC_RUN_TM );
	
	return;
}

void tm_main( void )
{
	int iRet				= D_TM_NG;
	S_MSG_DATA*	spRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	spRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* TM_TASK */
	iRet = TASK_msgrecv( E_TASK_TASKID_TM, spRecvData );
	if( ( D_TASK_OK == iRet ) &&
		( E_MSGID_TM_INVALID != spRecvData->iMsgid) )
	{
		/* 受信処理 */
		tm_recv( spRecvData );
	}
	
	/* 受信データクリア */
	if ((void*)NULL != spRecvData->vpPara)
	{
		free( spRecvData->vpPara );
		spRecvData->vpPara = (void*)NULL;
	}
	
	memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
	/* 常駐処理 */
	tm_proc();
	

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spRecvData)
	{
		free( spRecvData );
		spRecvData = (S_MSG_DATA*)NULL;
	}
	
	return;
}

void tm_main_debug( void )
{
	int			iRet		= D_TM_NG;
	S_MSG_DATA*	spRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	spRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == spRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	tm_init();
	
	/* TM_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_TM, spRecvData );
		if ((D_TASK_OK == iRet) &&
			(E_MSGID_TM_INVALID != spRecvData->iMsgid))
		{
			/* 受信処理 */
			tm_recv( spRecvData );
			
		}
		
		/* 受信データクリア */
		if ((void*)NULL != spRecvData->vpPara)
		{
			free( spRecvData->vpPara );
			spRecvData->vpPara = (void*)NULL;
		}
		
		memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		tm_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_TM );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spRecvData)
	{
		free( spRecvData );
		spRecvData = (S_MSG_DATA*)NULL;
	}
	
	tm_shutdown();
	
	return;
}

void tm_init( void )
{
	tm_set_Global();
	
	return;
}

void tm_shutdown( void )
{
#if	(__TARGET_EV3__)
	ter_tsk( TM_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void tm_set_Global( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	spTm = (S_TM*)malloc( sizeof(S_TM) );
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* 初期化 */
	memset( spTm, 0x00, sizeof(S_TM) );
	
	/* 初期化値設定 */
#if	(__TARGET_EV3__)
	spTm->ulStartCount = TSI_TimeMng_get_tim();
#endif	/* __TARGET_EV3__ */
	
	/* グローバル設定 */
	gspTm = spTm;
	
	return;
}

S_TM* tm_get_Global( void )
{
	return (S_TM*)gspTm;
}

/* proc */
void tm_proc( void )
{
	int iStatus = E_TM_STATUS_INVALID;
	S_TM* spTm = (S_TM*)NULL;
	
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* クラスステータス取得 */
	iStatus = spTm->iStatus;
	if( E_TM_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* 状態に応じて処理実行 */
	switch (iStatus)
	{
		case E_TM_STATUS_READY:
			tm_proc_Ready();
			break;
		
		case E_TM_STATUS_IDLE:
			tm_proc_Idle();
			break;
		
		default:
			break;
	}
	
	return;
}

void tm_proc_Ready( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* 状態遷移 */
	spTm->iStatus = E_TM_STATUS_IDLE;
	
	return;
}

void tm_proc_Idle( void )
{
	/* カウンタ更新 */
	tm_upd_Count();
	
	/* タイマーチェック */
	tm_chk_Timer();
	
	return;
}

void tm_upd_Count( void )
{
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* カウンタ更新 */
	spTm->stSysCount.uiCount++;
	
	/* 経過秒更新 */
	if( ( spTm->stSysCount.uiCount % 10 ) == 0 )
	{
		spTm->stSysCount.uiSec++;
	}
	
	return;
}

void tm_chk_Timer( void )
{
	int iLoopModuleId = 0;
	int iLoopEventId = 0;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return;
	}
	
	/* タイマ情報設定 */
	for( iLoopModuleId = 0; iLoopModuleId < E_TASK_TASKID_NUM; iLoopModuleId++ )
	{
		for( iLoopEventId = 0; iLoopEventId < D_TM_TIMER_NUM; iLoopEventId++ )
		{
			if( D_TM_FLAG_ON == spTm->stTimerData[iLoopModuleId][iLoopEventId].iRegist )
			{
				if( D_TM_FLAG_ON == spTm->stTimerData[iLoopModuleId][iLoopEventId].iRunStat )
				{
					/* タイマカウンタ更新 */
					spTm->stTimerData[iLoopModuleId][iLoopEventId].iCount++;
					
					/* タイマ満了 */
					if( spTm->stTimerData[iLoopModuleId][iLoopEventId].iCycCount == spTm->stTimerData[iLoopModuleId][iLoopEventId].iCount )
					{
						/* タイマコールバック実施 */
						if( (F_TM_CALLBACKFUNCPTR)NULL != spTm->stTimerData[iLoopModuleId][iLoopEventId].pFunc )
						{
							spTm->stTimerData[iLoopModuleId][iLoopEventId].pFunc();
						}
						
						/* タイマカウンタクリア */
						spTm->stTimerData[iLoopModuleId][iLoopEventId].iCount = 0;
					}
				}
				else
				{
					/* タイマ停止中は何もしない */
				}
			}
			else
			{
				/* タイマ削除 */
				spTm->stTimerData[iLoopModuleId][iLoopEventId].iRunStat = D_TM_FLAG_OFF;
				spTm->stTimerData[iLoopModuleId][iLoopEventId].iCount = 0;
			}
		}
	}
	
	return;
}

int tm_cre_Timer( S_TM_TIMERINFO* spTimerInfo )
{
	int iModuleId = 0;
	int iEventId = 0;
	int iCycCount = 0;
	int iLoopModuleId = 0;
	int iLoopEventId = 0;
	F_TM_CALLBACKFUNCPTR pFunc = (F_TM_CALLBACKFUNCPTR)NULL;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return D_TM_NG;
	}
	
	/* 起動状態確認 */
	if( E_TM_STATUS_READY == spTm->iStatus )
	{
		return D_TM_NG_READY;
	}
	
	/* ID確認 */
	iModuleId = tm_get_ModuleId( spTimerInfo->iId );
	iEventId = tm_get_EventId( spTimerInfo->iId );
	if( ( 0 > iModuleId) ||
		( E_TASK_TASKID_NUM < iEventId ) )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマサイクル確認 */
	/* ※100msecより小さい刻みは切り捨てる */
	iCycCount = spTimerInfo->iCycle / D_TASK_CYCLE_TM;
	if( 0 >= iCycCount )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマコールバック */
	pFunc = spTimerInfo->pFunc;
	if( (F_TM_CALLBACKFUNCPTR)NULL == pFunc )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマ情報設定 */
	for( iLoopModuleId = 0; iLoopModuleId < E_TASK_TASKID_NUM; iLoopModuleId++ )
	{
		for( iLoopEventId = 0; iLoopEventId < D_TM_TIMER_NUM; iLoopEventId++ )
		{
			if( ( iModuleId == iLoopModuleId ) &&
				( iEventId == iLoopEventId ) )
			{
				/* タイマサイクル */
				spTm->stTimerData[iModuleId][iEventId].iCycCount = iCycCount;
				/* タイマコールバック */
				spTm->stTimerData[iModuleId][iEventId].pFunc = pFunc;
				/* 登録状態 */
				spTm->stTimerData[iModuleId][iEventId].iRegist = D_TM_FLAG_ON;
				
				break;
			}
		}
	}
	
	return D_TM_OK;
}

int tm_del_Timer( int iId )
{
	int iModuleId = 0;
	int iEventId = 0;
	int iLoopModuleId = 0;
	int iLoopEventId = 0;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return D_TM_NG;
	}
	
	/* 起動状態確認 */
	if( E_TM_STATUS_READY == spTm->iStatus )
	{
		return D_TM_NG_READY;
	}
	
	/* ID確認 */
	iModuleId = tm_get_ModuleId( iId );
	iEventId = tm_get_EventId( iId );
	if( ( 0 > iModuleId) ||
		( E_TASK_TASKID_NUM < iEventId ) )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマ情報設定 */
	for( iLoopModuleId = 0; iLoopModuleId < E_TASK_TASKID_NUM; iLoopModuleId++ )
	{
		for( iLoopEventId = 0; iLoopEventId < D_TM_TIMER_NUM; iLoopEventId++ )
		{
			if( ( iModuleId == iLoopModuleId ) &&
				( iEventId == iLoopEventId ) )
			{
				/* タイマサイクル */
				spTm->stTimerData[iModuleId][iEventId].iCycCount = 0;
				/* タイマコールバック */
				spTm->stTimerData[iModuleId][iEventId].pFunc = (F_TM_CALLBACKFUNCPTR)NULL;
				/* 登録状態 */
				spTm->stTimerData[iModuleId][iEventId].iRegist = D_TM_FLAG_OFF;
				
				break;
			}
		}
	}
	
	return D_TM_OK;
}

int tm_sta_Timer( int iId )
{
	int iModuleId = 0;
	int iEventId = 0;
	int iLoopModuleId = 0;
	int iLoopEventId = 0;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return D_TM_NG;
	}
	
	/* 起動状態確認 */
	if( E_TM_STATUS_READY == spTm->iStatus )
	{
		return D_TM_NG_READY;
	}
	
	/* ID確認 */
	iModuleId = tm_get_ModuleId( iId );
	iEventId = tm_get_EventId( iId );
	if( ( 0 > iModuleId) ||
		( E_TASK_TASKID_NUM < iEventId ) )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマ情報設定 */
	for( iLoopModuleId = 0; iLoopModuleId < E_TASK_TASKID_NUM; iLoopModuleId++ )
	{
		for( iLoopEventId = 0; iLoopEventId < D_TM_TIMER_NUM; iLoopEventId++ )
		{
			if( ( iModuleId == iLoopModuleId ) &&
				( iEventId == iLoopEventId ) )
			{
				/* 実行状態 */
				spTm->stTimerData[iModuleId][iEventId].iRunStat = D_TM_FLAG_ON;
				
				break;
			}
		}
	}
	
	return D_TM_OK;
}

int tm_stp_Timer( int iId )
{
	int iModuleId = 0;
	int iEventId = 0;
	int iLoopModuleId = 0;
	int iLoopEventId = 0;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return D_TM_NG;
	}
	
	/* 起動状態確認 */
	if( E_TM_STATUS_READY == spTm->iStatus )
	{
		return D_TM_NG_READY;
	}
	
	/* ID確認 */
	iModuleId = tm_get_ModuleId( iId );
	iEventId = tm_get_EventId( iId );
	if( ( 0 > iModuleId) ||
		( E_TASK_TASKID_NUM < iEventId ) )
	{
		return D_TM_NG_PARA_ERR;
	}
	
	/* タイマ情報設定 */
	for( iLoopModuleId = 0; iLoopModuleId < E_TASK_TASKID_NUM; iLoopModuleId++ )
	{
		for( iLoopEventId = 0; iLoopEventId < D_TM_TIMER_NUM; iLoopEventId++ )
		{
			if( ( iModuleId == iLoopModuleId ) &&
				( iEventId == iLoopEventId ) )
			{
				/* 実行状態 */
				spTm->stTimerData[iModuleId][iEventId].iRunStat = D_TM_FLAG_OFF;
				
				break;
			}
		}
	}
	
	return D_TM_OK;
}

int tm_get_NowTime( S_TM_DAYTIME* spDayTime )
{
#if	(__TARGET_EV3__)
	unsigned long ulMsecCount = 0;
	unsigned long ulNow = 172800001;
	S_TM* spTm = (S_TM*)NULL;
	
	/* グローバル領域取得 */
	spTm = tm_get_Global();
	if( (S_TM*)NULL == spTm )
	{
		return D_TM_NG;
	}
	
	/* 現在時刻(msecカウンタ)取得 */
	ulMsecCount = TSI_TimeMng_get_tim();
	
	/* 現在の経過時刻(msec換算)取得 */
	ulNow = ulMsecCount - spTm->ulStartCount;
	
	/* 出力に設定 */
	spDayTime->usMilliSec =	(unsigned) ( ulNow % 1000 );
	spDayTime->usSecond =	(unsigned)(  ( ulNow / 1000 ) % 60 );
	spDayTime->usMinute =	(unsigned)(( ( ulNow / 1000 ) / 60 ) % 60 );
	spDayTime->usHour =		(unsigned)(( ( ulNow / 1000 ) / 3600 ) % 24 );

	/* 年月日(未実装) */
	spDayTime->usYear = 1990;
	spDayTime->usMonth = 0;
	spDayTime->usDay =		(unsigned)(( ( ulNow / 1000 ) / 3600 ) / 24 );
#else	/* __TARGET_EV3__ */
	SYSTEMTIME stSysTime;
	memset( &stSysTime, 0x00, sizeof(SYSTEMTIME) );

	GetSystemTime( &stSysTime );

	/* 出力に設定 */
	spDayTime->usMilliSec = stSysTime.wMilliseconds;
	spDayTime->usSecond = stSysTime.wSecond;
	spDayTime->usMinute = stSysTime.wMinute;
	spDayTime->usHour = stSysTime.wHour;
	
	/* 年月日 */
	spDayTime->usYear = stSysTime.wYear;
	spDayTime->usMonth = stSysTime.wMonth;
	spDayTime->usDay = stSysTime.wDay;
#endif	/* __TARGET_EV3__ */
	return D_TM_OK;
}

int tm_get_ModuleId( int iTimerId )
{
	int iModuleId = D_TM_NG;
	
	iModuleId = ( iTimerId >> 24 );
	
	return iModuleId;
}

int tm_get_EventId( int iTimerId )
{
	int iEventId = D_TM_NG;
	
	iEventId = ( iTimerId & 0x00FFFFFF );
	
	return iEventId;
}
