#include "ltin.h"

void lt_log_set_Statuslog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LT_LOGDATA_STATUSLOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LT_LOGDATA_STATUSLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &stLogData.stDayTime, &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.iStatus = spLt->iStatus;
	
	/* タスクID */
	stLogData.iTaskId = E_TASK_TASKID_LT;
	
	/* データ設定 */
	memcpy( &(spLt->stLogInfo.stStatusLog.stLog[spLt->stLogInfo.stStatusLog.iLogNum]), &stLogData, sizeof(S_LT_LOGDATA_STATUSLOG) );
	
	/* ログ数更新 */
	spLt->stLogInfo.stStatusLog.iLogNum ++;
	if( D_LT_BUFFNUM_STATUSLOG == spLt->stLogInfo.stStatusLog.iLogNum )
	{
		/* ログ送信 */
		lt_send_setLog_StatusLog_req( &(spLt->stLogInfo.stStatusLog) );
		
		/* メモリクリア */
		memset( &(spLt->stLogInfo.stStatusLog), 0x00, sizeof(S_LT_LOGINFO_STATUSLOG));
	}
	
	return;
}

void lt_log_set_Calibratelog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LT_LOGINFO_CALIBRATELOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LT_LOGINFO_CALIBRATELOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &(stLogData.stLog[D_LT_BUFFNUM_CALIBRATELOG -1].stDayTime ), &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.stLog[D_LT_BUFFNUM_CALIBRATELOG -1].iLtStatus = spLt->iStatus;
	
	/* キャリブレーション情報 */
	memcpy( &(stLogData.stLog[D_LT_BUFFNUM_CALIBRATELOG -1].stCalibrateInfo), &(spLt->stCalibrateInfo), sizeof(S_LT_CALIBRATEINFO) );

	/* ログ数 */
	stLogData.iLogNum = D_LT_BUFFNUM_CALIBRATELOG;
	stLogData.stLog[D_LT_BUFFNUM_CALIBRATELOG -1].iLogNum = D_LT_BUFFNUM_CALIBRATELOG;
	
	/* ログ送信 */
	lt_send_setLog_CalibrateLog_req( &stLogData );
	
	return;
}

void lt_log_set_Systemlog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LT_LOGDATA_SYSTEMLOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &stLogData.stDayTime, &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.iLtStatus = spLt->iStatus;

	/* バランス制御情報 */
	memcpy( &(stLogData.stBalanceInfo), &(spLt->stBalanceInfo), sizeof(S_LT_BALANCEINFO) );
	
	/* バランスコントロール */
	memcpy( &(stLogData.stBacanceControl), &(spLt->stBacanceControl), sizeof(S_LT_BALANCE_CONTROL) );
	
	/* データ設定 */
	memcpy( &(spLt->stLogInfo.stSystemLog.stLog[spLt->stLogInfo.stSystemLog.iLogNum]), &stLogData, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
	/* ログ数更新 */
	spLt->stLogInfo.stSystemLog.iLogNum ++;
	if( D_LT_BUFFNUM_SYSTEMLOG == spLt->stLogInfo.stSystemLog.iLogNum )
	{
		/* ログ送信 */
		lt_send_setLog_SystemLog_req( &(spLt->stLogInfo.stSystemLog) );
		
		/* メモリクリア */
		memset( &(spLt->stLogInfo.stSystemLog), 0x00, sizeof(S_LT_LOGINFO_SYSTEMLOG));
	}
	
	return;
}

void lt_log_set_LastLog( void )
{
	lt_log_set_LastLog_Systemlog();
	lt_log_set_LastLog_Statuslog();
	
	/* ラストログ設定要求 */
	lt_send_setLog_LogLast_req();

	return;
}

void lt_log_set_LastLog_Statuslog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* ログ送信 */
	lt_send_setLog_StatusLog_req( &(spLt->stLogInfo.stStatusLog) );
	
	/* メモリクリア */
	memset( &(spLt->stLogInfo.stStatusLog), 0x00, sizeof(S_LT_LOGINFO_STATUSLOG));
	
	return;
}

void lt_log_set_LastLog_Systemlog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LT_LOGDATA_SYSTEMLOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &stLogData.stDayTime, &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.iLtStatus = spLt->iStatus;

	/* バランス制御情報 */
	memcpy( &(stLogData.stBalanceInfo), &(spLt->stBalanceInfo), sizeof(S_LT_BALANCEINFO) );
	
	/* バランスコントロール */
	memcpy( &(stLogData.stBacanceControl), &(spLt->stBacanceControl), sizeof(S_LT_BALANCE_CONTROL) );
	
	/* データ設定 */
	memcpy( &(spLt->stLogInfo.stSystemLog.stLog[spLt->stLogInfo.stSystemLog.iLogNum]), &stLogData, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
	/* ログ数更新 */
	spLt->stLogInfo.stSystemLog.iLogNum ++;
	
	/* ログ送信 */
	lt_send_setLog_SystemLog_req( &(spLt->stLogInfo.stSystemLog) );
	
	/* メモリクリア */
	memset( &(spLt->stLogInfo.stSystemLog), 0x00, sizeof(S_LT_LOGINFO_SYSTEMLOG));
	
	return;
}
