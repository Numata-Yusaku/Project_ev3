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
	
//	fprintf( spLt->fpStatusLog, "%08ld,",ulTime );
	
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
//#if	(D_LT_LOGMODE_SYSTEM)
//	S_LT* spLt = (S_LT*)NULL;
//	
//	/* グローバル領域取得 */
//	spLt = lt_get_Global();
//	if( (S_LT*)NULL == spLt )
//	{
//		return;
//	}
//	
//	if( (FILE*)NULL == spLt->fpSystemLog )
//	{
//		return;
//	}
//	
//#if	(__TARGET_EV3__)
//	SYSTIM	stime;
//	get_tim(&stime);
//	fprintf( spLt->fpSystemLog, "%08ld,",stime );
//#endif	/* __TARGET_EV3__ */
//	
//#if	(D_LT_LOGMODE_SYSTEM_BALANCEINFO)
//	/* バランス制御情報 */
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fErr_theta);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fPsi);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetaLpf);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetaRef);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetadotCmdLpf);
//#endif	/* D_LT_LOGMODE_SYSTEM_BALANCEINFO */
//	
//#if	(D_LT_LOGMODE_SYSTEM_BALANCECONTROL)
//	/* バランスコントロール */
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fCmdForward);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fCmdTurn);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fGyro);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fGyroOffset);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fThetaMLeft);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fThetaMRight);
//	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fBattery);
//	fprintf( spLt->fpSystemLog, "%d,",spLt->stBacanceControl.scPwmLeft);
//	fprintf( spLt->fpSystemLog, "%d,",spLt->stBacanceControl.scPwmRight);
//#endif	/* D_LT_LOGMODE_SYSTEM_BALANCECONTROL */
//	
//	fprintf( spLt->fpSystemLog, "\n");
//	fflush( spLt->fpSystemLog );
//#endif	/* D_LT_LOGMODE_SYSTEM */
	
	return;
}
