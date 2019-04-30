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
//#if	(D_LT_LOGMODE_CALIBRATE)
//	S_LT* spLt = (S_LT*)NULL;
//	
//	/* グローバル領域取得 */
//	spLt = lt_get_Global();
//	if( (S_LT*)NULL == spLt )
//	{
//		return;
//	}
//	
//	if( (FILE*)NULL == spLt->fpCalirateLog )
//	{
//		return;
//	}
//	
//	/* バランスコントロール */
//	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.iGyro);
//	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stBlack.iColor);
//	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stBlack.iReflect);
//	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stWhite.iColor);
//	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stWhite.iReflect);
//	
//	fprintf( spLt->fpCalirateLog, "\n");
//	fflush( spLt->fpCalirateLog );
//#endif	/* D_LT_LOGMODE_CALIBRATE */
	
	return;
}

void lt_log_set_Systemlog( void )
{
	S_LT* spLt = (S_LT*)NULL;
	unsigned long ulTime = 0;
	S_LT_LOGDATA_SYSTEMLOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stLogData, 0x00, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
#if	(__TARGET_EV3__)
	/* 現在時刻取得 */
	get_tim(&ulTime);
#else	/* __TARGET_EV3__ */
	spLt->stLogInfo.ulSystemLogCounta ++;
	ulTime = spLt->stLogInfo.ulSystemLogCounta;
#endif	/* __TARGET_EV3__ */
	
	/* カウンタ */
	stLogData.ulTime							= ulTime;
	
	/* バランス制御情報 */
	stLogData.stBalanceInfo.fErr_theta			= spLt->stBalanceInfo.fErr_theta;
	stLogData.stBalanceInfo.fPsi				= spLt->stBalanceInfo.fPsi;
	stLogData.stBalanceInfo.fThetaLpf			= spLt->stBalanceInfo.fThetaLpf;
	stLogData.stBalanceInfo.fThetaRef			= spLt->stBalanceInfo.fThetaRef;
	stLogData.stBalanceInfo.fThetadotCmdLpf		= spLt->stBalanceInfo.fThetadotCmdLpf;
	
	/* バランスコントロール */
	stLogData.stBacanceControl.fCmdForward		= spLt->stBacanceControl.fCmdForward;
	stLogData.stBacanceControl.fCmdTurn			= spLt->stBacanceControl.fCmdTurn;
	stLogData.stBacanceControl.fGyro			= spLt->stBacanceControl.fGyro;
	stLogData.stBacanceControl.fGyroOffset		= spLt->stBacanceControl.fGyroOffset;
	stLogData.stBacanceControl.fThetaMLeft		= spLt->stBacanceControl.fThetaMLeft;
	stLogData.stBacanceControl.fThetaMRight		= spLt->stBacanceControl.fThetaMRight;
	stLogData.stBacanceControl.fBattery			= spLt->stBacanceControl.fBattery;
	stLogData.stBacanceControl.scPwmLeft		= spLt->stBacanceControl.scPwmLeft;
	stLogData.stBacanceControl.scPwmRight		= spLt->stBacanceControl.scPwmRight;
	
	/* データ設定 */
	memcpy( &(spLt->stLogInfo.stSystemLog.stLog[spLt->stLogInfo.stSystemLog.iLogNum]), &stLogData, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
	/* ログ数更新 */
	spLt->stLogInfo.stSystemLog.iLogNum ++;
	if( D_TASK_BUFFNUM_SYSTEMLOG == spLt->stLogInfo.stSystemLog.iLogNum )
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
	unsigned long ulTime = 0;
	S_LT_LOGDATA_SYSTEMLOG stLogData;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stLogData, 0x00, sizeof(S_LT_LOGDATA_SYSTEMLOG) );
	
#if	(__TARGET_EV3__)
	/* 現在時刻取得 */
	get_tim(&ulTime);
#else	/* __TARGET_EV3__ */
	spLt->stLogInfo.ulSystemLogCounta ++;
	ulTime = spLt->stLogInfo.ulSystemLogCounta;
#endif	/* __TARGET_EV3__ */
	
	/* カウンタ */
	stLogData.ulTime							= ulTime;
	
	/* バランス制御情報 */
	stLogData.stBalanceInfo.fErr_theta			= spLt->stBalanceInfo.fErr_theta;
	stLogData.stBalanceInfo.fPsi				= spLt->stBalanceInfo.fPsi;
	stLogData.stBalanceInfo.fThetaLpf			= spLt->stBalanceInfo.fThetaLpf;
	stLogData.stBalanceInfo.fThetaRef			= spLt->stBalanceInfo.fThetaRef;
	stLogData.stBalanceInfo.fThetadotCmdLpf		= spLt->stBalanceInfo.fThetadotCmdLpf;
	
	/* バランスコントロール */
	stLogData.stBacanceControl.fCmdForward		= spLt->stBacanceControl.fCmdForward;
	stLogData.stBacanceControl.fCmdTurn			= spLt->stBacanceControl.fCmdTurn;
	stLogData.stBacanceControl.fGyro			= spLt->stBacanceControl.fGyro;
	stLogData.stBacanceControl.fGyroOffset		= spLt->stBacanceControl.fGyroOffset;
	stLogData.stBacanceControl.fThetaMLeft		= spLt->stBacanceControl.fThetaMLeft;
	stLogData.stBacanceControl.fThetaMRight		= spLt->stBacanceControl.fThetaMRight;
	stLogData.stBacanceControl.fBattery			= spLt->stBacanceControl.fBattery;
	stLogData.stBacanceControl.scPwmLeft		= spLt->stBacanceControl.scPwmLeft;
	stLogData.stBacanceControl.scPwmRight		= spLt->stBacanceControl.scPwmRight;
	
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
