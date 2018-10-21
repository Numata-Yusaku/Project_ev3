#include "ltin.h"

void lt_log_Statuslog_open( void )
{
#if	(D_LT_LOGMODE_STATUS)
	S_LT* spLt = (S_LT*)NULL;
	FILE* fpStatusLog = (FILE*)NULL;
	
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	fpStatusLog = fopen( D_LT_FILENAME_STATUSLOG, "w");
	if( (FILE*)NULL == fpStatusLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLt->fpStatusLog = fpStatusLog;
	
	/* ヘッダ出力 */
#if	(__VC_DEBUG__)
#if	(D_LT_LOGMODE_STATUS_TIME)
	fprintf( spLt->fpStatusLog, "Time(YYMMDD-hhmmss),");
#else	/* D_LT_LOGMODE_STATUS_TIME */
	fprintf( spLt->fpStatusLog, "SysClock(msec),");
#endif	/* D_LT_LOGMODE_STATUS_TIME */
#endif	/* __VC_DEBUG__ */
	
	fprintf( spLt->fpStatusLog, "Status,");
	
	fprintf( spLt->fpStatusLog, "\n");
	fflush( stdout );
#endif	/* D_LT_LOGMODE_STATUS */
	return;
}

void lt_log_Calibratelog_open( void )
{
#if	(D_LT_LOGMODE_CALIBRATE)
	S_LT* spLt = (S_LT*)NULL;
	FILE* fpCalirateLog = (FILE*)NULL;
	
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	fpCalirateLog = fopen( D_LT_FILENAME_CALIBRATELOG, "w");
	if( (FILE*)NULL == fpCalirateLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLt->fpCalirateLog = fpCalirateLog;
	
	/* ヘッダ出力 */
	/* ジャイロ */
	fprintf( spLt->fpCalirateLog, "iGyro,");
	
	/* 黒 */
	fprintf( spLt->fpCalirateLog, "stBlack.iColor,");
	fprintf( spLt->fpCalirateLog, "stBlack.iReflect,");
	/* 白s */
	fprintf( spLt->fpCalirateLog, "stWhite.iColor,");
	fprintf( spLt->fpCalirateLog, "stWhite.iReflect,");
	
	fprintf( spLt->fpCalirateLog, "\n");
#endif	/* D_LT_LOGMODE_CALIBRATE */
	return;
}

void lt_log_Systemlog_open( void )
{
#if	(D_LT_LOGMODE_SYSTEM)
	S_LT* spLt = (S_LT*)NULL;
	FILE* fpSystemLog = (FILE*)NULL;
	
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	fpSystemLog = fopen( D_LT_FILENAME_SYSTEMLOG, "w");
	if( (FILE*)NULL == fpSystemLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLt->fpSystemLog = fpSystemLog;
	
	/* ヘッダ出力 */
#if	(D_LT_LOGMODE_SYSTEM_BALANCEINFO)
	/* バランス制御情報 */
	fprintf( spLt->fpSystemLog, "fErr_theta,");
	fprintf( spLt->fpSystemLog, "fPsi,");
	fprintf( spLt->fpSystemLog, "fThetaLpf,");
	fprintf( spLt->fpSystemLog, "fThetaRef,");
	fprintf( spLt->fpSystemLog, "fThetadotCmdLpf,");
#endif	/* D_LT_LOGMODE_SYSTEM_BALANCEINFO */
	
#if	(D_LT_LOGMODE_SYSTEM_BALANCECONTROL)
	/* バランスコントロール */
	fprintf( spLt->fpSystemLog, "fCmdForward,");
	fprintf( spLt->fpSystemLog, "fCmdTurn,");
	fprintf( spLt->fpSystemLog, "fGyro,");
	fprintf( spLt->fpSystemLog, "fGyroOffset,");
	fprintf( spLt->fpSystemLog, "fThetaMLeft,");
	fprintf( spLt->fpSystemLog, "fThetaMRight,");
	fprintf( spLt->fpSystemLog, "fBattery,");
	fprintf( spLt->fpSystemLog, "scPwmLeft,");
	fprintf( spLt->fpSystemLog, "scPwmRight,");
#endif	/* D_LT_LOGMODE_SYSTEM_BALANCECONTROL */
	
	fprintf( spLt->fpSystemLog, "\n");
	fflush( stdout );
#endif	/* D_LT_LOGMODE_SYSTEM */
	return;
}

void lt_log_set_Statuslog( void )
{
#if	(D_LT_LOGMODE_STATUS)
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	if( (FILE*)NULL == spLt->fpStatusLog )
	{
		return;
	}
	
#if	(__VC_DEBUG__)
#if	(D_LT_LOGMODE_STATUS_TIME)
	time_t stTime = 0;
	struct tm* spLocalTime = (struct tm*)NULL;
	
	/* 時刻を取得 */
	stTime = time(NULL);
	spLocalTime = localtime(&stTime);
	
	fprintf( spLt->fpStatusLog, "%04d%02d%02d-%02d%02d%02d,",
		spLocalTime->tm_year + 1900,
		spLocalTime->tm_mon + 1,
		spLocalTime->tm_mday,
		spLocalTime->tm_hour,
		spLocalTime->tm_min,
		spLocalTime->tm_sec );
	
#else	/* D_LT_LOGMODE_STATUS_TIME */
	static clock_t stStartClock = 0;
	clock_t stNowClock = 0;
	clock_t stClock = 0;
	if (0 == stStartClock)
	{
		stStartClock = clock();
	}
	else
	{
		stNowClock = clock();
		stClock = stNowClock - stStartClock;
	}
	
	fprintf( spLt->fpStatusLog, "%08ld,",stClock);
#endif	/* D_LT_LOGMODE_STATUS_TIME */
#endif	/* __VC_DEBUG__ */
	
	fprintf( spLt->fpStatusLog, "%d,",spLt->iStatus);
	
	fprintf( spLt->fpStatusLog, "\n");
#endif	/* D_LT_LOGMODE_STATUS */
	
	return;
}

void lt_log_set_Calibratelog( void )
{
#if	(D_LT_LOGMODE_CALIBRATE)
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	if( (FILE*)NULL == spLt->fpCalirateLog )
	{
		return;
	}
	
	/* バランスコントロール */
	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.iGyro);
	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stBlack.iColor);
	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stBlack.iReflect);
	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stWhite.iColor);
	fprintf( spLt->fpCalirateLog, "%d,",spLt->stCalibrateInfo.stWhite.iReflect);
	
	fprintf( spLt->fpCalirateLog, "\n");
	fflush( stdout );
#endif	/* D_LT_LOGMODE_CALIBRATE */
	
	return;
}

void lt_log_set_Systemlog( void )
{
#if	(D_LT_LOGMODE_SYSTEM)
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	if( (FILE*)NULL == spLt->fpSystemLog )
	{
		return;
	}
	
#if	(D_LT_LOGMODE_SYSTEM_BALANCEINFO)
	/* バランス制御情報 */
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fErr_theta);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fPsi);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetaLpf);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetaRef);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBalanceInfo.fThetadotCmdLpf);
#endif	/* D_LT_LOGMODE_SYSTEM_BALANCEINFO */
	
#if	(D_LT_LOGMODE_SYSTEM_BALANCECONTROL)
	/* バランスコントロール */
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fCmdForward);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fCmdTurn);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fGyro);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fGyroOffset);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fThetaMLeft);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fThetaMRight);
	fprintf( spLt->fpSystemLog, "%lf,",spLt->stBacanceControl.fBattery);
	fprintf( spLt->fpSystemLog, "%d,",spLt->stBacanceControl.scPwmLeft);
	fprintf( spLt->fpSystemLog, "%d,",spLt->stBacanceControl.scPwmRight);
#endif	/* D_LT_LOGMODE_SYSTEM_BALANCECONTROL */
	
	fprintf( spLt->fpSystemLog, "\n");
	fflush( stdout );
#endif	/* D_LT_LOGMODE_SYSTEM */
	
	return;
}
