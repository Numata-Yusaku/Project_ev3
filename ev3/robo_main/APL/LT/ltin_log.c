#include "ltin.h"

void lt_log_set_Statuslog( void )
{
#if	(D_LT_LOGMODE_STATUS)
	S_LT* spLt = (S_LT*)NULL;
	unsigned long ulTime = 0;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}

#if	(__TARGET_EV3__)
	/* 現在時刻取得 */
	get_tim(&ulTime);
#else	/* __TARGET_EV3__ */
	static unsigned long ulCounta = 0;
	ulTime = ulCounta;
	ulCounta++;
#endif	/* __TARGET_EV3__ */
	
	/* データ設定 */
	spLt->stLogInfo.stStatusLog.stLog[spLt->stLogInfo.stStatusLog.iLogNum].ulTime = ulTime;
	spLt->stLogInfo.stStatusLog.stLog[spLt->stLogInfo.stStatusLog.iLogNum].iStatus = spLt->iStatus;
	
	spLt->stLogInfo.stStatusLog.iLogNum++;
	
	/* バッファ上限に到達 */
	if( D_LT_BUFFNUM_STATUSLOG == spLt->stLogInfo.stStatusLog.iLogNum )
	{
		/* ログ出力要求 */
		lt_send_setLog_StatusLog_req( &(spLt->stLogInfo.stStatusLog) );
		
		/* ログクリア */
		memset( &(spLt->stLogInfo.stStatusLog.stLog[0]), 0x00, sizeof( S_LT_LOGDATA_STATUSLOG ) * D_LT_BUFFNUM_STATUSLOG );
		spLt->stLogInfo.stStatusLog.iLogNum = 0;
	}
#endif	/* D_LT_LOGMODE_STATUS */
	
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
