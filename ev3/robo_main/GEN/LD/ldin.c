#include "ldin.h"

S_LD* gspLd = (S_LD*)NULL;

/* startup */
void ld_main( void )
{
	int iRet				= D_LD_NG;
	S_MSG_DATA*	spRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	spRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == spRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	ld_init();
	
	/* LD_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_LD, spRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_LD_INVALID != spRecvData->iMsgid) )
		{
			/* 受信処理 */
			ld_recv( spRecvData );
		}
		
		/* 受信データクリア */
		if ((void*)NULL != spRecvData->vpPara)
		{
			free( spRecvData->vpPara );
			spRecvData->vpPara = (void*)NULL;
		}
		
		memset( spRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		ld_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_LD );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != spRecvData)
	{
		free( spRecvData );
		spRecvData = (S_MSG_DATA*)NULL;
	}
	
	ld_shutdown();
	
	return;
}

void ld_init( void )
{
	ld_set_Global();
	
	return;
}

void ld_shutdown( void )
{
#if	(__TARGET_EV3__)
	ter_tsk( LD_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* global */
void ld_set_Global( void )
{
	S_LD* spLd = (S_LD*)NULL;
	
	spLd = (S_LD*)malloc( sizeof(S_LD) );
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 初期化 */
	memset( spLd, 0x00, sizeof(S_LD) );
	
	/* 初期化値設定 */
	spLd->iOldStatus = E_LD_STATUS_INVALID;
	
	/* グローバル設定 */
	gspLd = spLd;
	
	return;
}

S_LD* ld_get_Global( void )
{
	return (S_LD*)gspLd;
}

/* proc */
void ld_proc( void )
{
	int iStatus = E_LD_STATUS_INVALID;
	int iOldStatus = E_LD_STATUS_INVALID;
	S_LD* spLd = (S_LD*)NULL;
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* クラスステータス取得 */
	iStatus = spLd->iStatus;
	if( E_LD_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* 状態変化チェック */
	iOldStatus = spLd->iOldStatus;
	if( iOldStatus != iStatus )
	{
		/* ログ出力 */
		ld_log_set_Statuslog();
	}
	
	/* 旧状態更新 */
	spLd->iOldStatus = iStatus;
	
	/* 状態に応じて処理実行 */
	switch (iStatus)
	{
		case E_LD_STATUS_READY:
			ld_proc_Ready();
			break;
		
		case E_LD_STATUS_IDLE:
			/* 処理しない */
			break;
		
		case E_LD_STATUS_RUN:
			/* 処理しない */
			break;
		
		case E_LD_STATUS_LOGDUMP:
			ld_proc_LogDump();
			break;
		
		default:
			break;
	}
	
	return;
}

void ld_proc_Ready( void )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 状態遷移 */
	spLd->iStatus = E_LD_STATUS_IDLE;
	
	return;
}

void ld_log_set_Statuslog( void )
{
#if	D_LD_LOGMODE_STATUS
	S_LD* spLd = (S_LD*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LD_LOGDATA_STATUSLOG stLogData;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LD_LOGDATA_STATUSLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &stLogData.stDayTime, &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.iStatus = spLd->iStatus;
	
	/* タスクID */
	stLogData.iTaskId = E_TASK_TASKID_LD;
	
	/* データ設定 */
	memcpy( &(spLd->stLogInfo.stStatusLog.stLog[spLd->stLogInfo.stStatusLog.iLogNum]), &stLogData, sizeof(S_LD_LOGDATA_STATUSLOG) );
	
	/* ログ数更新 */
	spLd->stLogInfo.stStatusLog.iLogNum ++;
	if( D_LD_BUFFNUM_STATUSLOG == spLd->stLogInfo.stStatusLog.iLogNum )
	{
		/* ログ送信 */
		ld_send_setLog_StatusLog_req( &(spLd->stLogInfo.stStatusLog) );
		
		/* メモリクリア */
		memset( &(spLd->stLogInfo.stStatusLog), 0x00, sizeof(S_LD_LOGINFO_STATUSLOG));
	}
#endif	/* D_LD_LOGMODE_STATUS */
	return;
}

void ld_log_set_LastLog_Statuslog( void )
{
#if	D_LD_LOGMODE_STATUS
	S_LD* spLd = (S_LD*)NULL;
	S_TM_DAYTIME stDayTime;
	S_LD_LOGDATA_STATUSLOG stLogData;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_LD_LOGDATA_STATUSLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* ログ送信 */
	ld_send_setLog_StatusLog_req( &(spLd->stLogInfo.stStatusLog) );
	
	/* メモリクリア */
	memset( &(spLd->stLogInfo.stStatusLog), 0x00, sizeof(S_LD_LOGINFO_STATUSLOG));
#endif	/* D_LD_LOGMODE_STATUS */
	return;
}

void ld_proc_LogDump( void )
{
	/* ログ出力 */
	ld_log_Dump();
	
	return;
}

void ld_log_Dump( void )
{
	int iProgress = 0;
	S_LD* spLd = (S_LD*)NULL;
	S_TASK_CHGLOGDUMP_RES stSend;
	
	memset( &stSend, 0x00, sizeof(S_TASK_CHGLOGDUMP_RES) );
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	if( E_LD_LOGKIND_END > spLd->stLogList.iNowWrite )
	{
		switch( spLd->stLogList.iNowWrite )
		{
#if	D_LD_LOGMODE_STATUS
			case E_LD_LOGKIND_STATUSLOG:
				iProgress = ld_log_DumpStatuslog();
				break;
#endif	/* D_LD_LOGMODE_STATUS */
#if	D_LD_LOGMODE_CALIBRATE
			case E_LD_LOGKIND_CALIBRATELOG:
				iProgress = ld_log_DumpCalibratelog();
				break;
#endif	/* D_LD_LOGMODE_CALIBRATE */
#if	D_LD_LOGMODE_SYSTEM
			case E_LD_LOGKIND_SYSTEMLOG:
				iProgress = ld_log_DumpSystemlog();
				break;
#endif	/* D_LD_LOGMODE_SYSTEM */
			default:
				/* フェール処理 */
				break;
		}
		
		/* 送信データ設定 */
		stSend.iAllLogNum = E_LD_LOGKIND_NUM;
		stSend.iNowLogNo = spLd->stLogList.iNowWrite;
		stSend.iProgress = iProgress;
		
		/* ログダンプ状態更新通知 */
		ld_send_chgLogDump_res( &stSend );
	
		/* 進捗100%になったら次のログへ */
		if( 100 == iProgress )
		{
			spLd->stLogList.iNowWrite++;
		}
	}
	else if( E_LD_LOGKIND_END == spLd->stLogList.iNowWrite )
	{
		/*** 完了通知 ***/
		/* 送信データ設定 */
		stSend.iAllLogNum = E_LD_LOGKIND_NUM;
		stSend.iNowLogNo = E_LD_LOGKIND_NUM;
		stSend.iProgress = 100;
		
		/* ログダンプ状態更新通知 */
		ld_send_chgLogDump_res( &stSend );

		/* 通知終了 */
		spLd->stLogList.iNowWrite = E_LD_LOGKIND_STOP;
	}
	else
	{
		/* ダンプすべきログがないので何もしない */
	}
}

void ld_log_Statuslog_open( void )
{
#if	(D_LD_LOGMODE_STATUS)
	S_LD* spLd = (S_LD*)NULL;
	FILE* fpStatusLog = (FILE*)NULL;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	fpStatusLog = fopen( D_LD_FILENAME_STATUSLOG, "w");
	if( (FILE*)NULL == fpStatusLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLd->stFileInfo.fpStatusLog.fpFile = fpStatusLog;
	
	/* ヘッダ出力 */
	/* 時刻 */
	sprintf( cPrintLine, "SysClock,");
	
	/* タスクID */
	sprintf( cPrintLine, "%sTaskID,",cPrintLine);
	
	/* 状態 */
	sprintf( cPrintLine, "%sStatus,",cPrintLine);
	
	fprintf( spLd->stFileInfo.fpStatusLog.fpFile, "%s\n", cPrintLine );
	fflush( spLd->stFileInfo.fpStatusLog.fpFile );
#endif	/* D_LD_LOGMODE_STATUS */
	return;
}

void ld_log_Calibratelog_open( void )
{
#if	(D_LD_LOGMODE_CALIBRATE)
	S_LD* spLd = (S_LD*)NULL;
	FILE* fpCalirateLog = (FILE*)NULL;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	fpCalirateLog = fopen( D_LD_FILENAME_CALIBRATELOG, "w");
	if( (FILE*)NULL == fpCalirateLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLd->stFileInfo.fpCalibrateLog.fpFile = fpCalirateLog;
	
	/* ヘッダ出力 */
	/* 時刻 */
	sprintf( cPrintLine, "SysClock,");
	
	/* 走行状態 */
	sprintf( cPrintLine, "%sLT Status,",cPrintLine);
	
	/* ジャイロ */
	sprintf( cPrintLine, "%siGyro,",cPrintLine);
	
	/* 黒 */
	sprintf( cPrintLine, "%sstBlack.iColor,",cPrintLine);
	sprintf( cPrintLine, "%sstBlack.iReflect,",cPrintLine);
	
	/* 白 */
	sprintf( cPrintLine, "%sstWhite.iColor,",cPrintLine);
	sprintf( cPrintLine, "%sstWhite.iReflect,",cPrintLine);
	
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "%s\n", cPrintLine );
	fflush( spLd->stFileInfo.fpCalibrateLog.fpFile );
#endif	/* D_LD_LOGMODE_CALIBRATE */
	return;
}

void ld_log_Systemlog_open( void )
{
#if	(D_LD_LOGMODE_SYSTEM)
	S_LD* spLd = (S_LD*)NULL;
	FILE* fpSystemLog = (FILE*)NULL;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );

	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	fpSystemLog = fopen( D_LD_FILENAME_SYSTEMLOG, "w");
	if( (FILE*)NULL == fpSystemLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLd->stFileInfo.fpSystemLog.fpFile = fpSystemLog;
	
	/* ヘッダ出力 */
	/* 時刻 */
	sprintf( cPrintLine, "SysClock,");
	
	/* 走行状態 */
	sprintf( cPrintLine, "%sLT Status,",cPrintLine);

#if	(D_LD_LOGMODE_SYSTEM_BALANCEINFO)
	/* バランス制御情報 */
	sprintf( cPrintLine, "%sfErr_theta,",cPrintLine);
	sprintf( cPrintLine, "%sfPsi,",cPrintLine);
	sprintf( cPrintLine, "%sfThetaLpf,",cPrintLine);
	sprintf( cPrintLine, "%sfThetaRef,",cPrintLine);
	sprintf( cPrintLine, "%sfThetadotCmdLpf,",cPrintLine);
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCEINFO */
	
#if	(D_LD_LOGMODE_SYSTEM_BALANCECONTROL)
	/* バランスコントロール */
	sprintf( cPrintLine, "%sfCmdForward,",cPrintLine);
	sprintf( cPrintLine, "%sfCmdTurn,",cPrintLine);
	sprintf( cPrintLine, "%sfGyro,",cPrintLine);
	sprintf( cPrintLine, "%sfGyroOffset,",cPrintLine);
	sprintf( cPrintLine, "%sfThetaMLeft,",cPrintLine);
	sprintf( cPrintLine, "%sfThetaMRight,",cPrintLine);
	sprintf( cPrintLine, "%sfBattery,",cPrintLine);
	sprintf( cPrintLine, "%sscPwmLeft,",cPrintLine);
	sprintf( cPrintLine, "%sscPwmRight,",cPrintLine);
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCECONTROL */
	
	fprintf( spLd->stFileInfo.fpSystemLog.fpFile, "%s\n", cPrintLine );
	fflush( spLd->stFileInfo.fpSystemLog.fpFile );
#endif	/* D_LD_LOGMODE_SYSTEM */
	return;
}

int ld_log_DumpStatuslog( void )
{
	int iProgress = -1;			/* 進捗率 */
#if	(D_LD_LOGMODE_STATUS)
	int iAllPageNum = 0;		/* 全ページ数 */
	int iWritePage = 0;			/* 書き込みページ */
	int iLogNum = 0;			/* 1ページ内ログ数 */
	int iLoop = 0;				/* ループカウンタ */
	S_LD* spLd = (S_LD*)NULL;
	S_LD_LOGLISTPAGE_STATUSLOG* spWork = (S_LD_LOGLISTPAGE_STATUSLOG*)NULL;
	S_TASK_LOGDATA_STATUSLOG stStatusLogData;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	memset( &stStatusLogData, 0x00, sizeof(S_TASK_LOGDATA_STATUSLOG) );
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return D_LD_NG;
	}
	
	if( (FILE*)NULL == spLd->stFileInfo.fpStatusLog.fpFile )
	{
		return D_LD_NG;
	}
	
	/* 全ページ数取得 */
	iAllPageNum = spLd->stLogList.stLogListInfo_StatusLog.iAllPageNum;
	
	/* 書き込みページ取得 */
	iWritePage = spLd->stFileInfo.fpStatusLog.iWritePageNum;
	
	/* ページトップ取得 */
	spWork = spLd->stLogList.stLogListInfo_StatusLog.spList;
	
	/* 書き込みページデータアドレス取得 */
	for( iLoop = 0; iLoop < iWritePage; iLoop++ )
	{
		spWork = spWork->spNextPage;
	}
	
	if( (S_LD_LOGLISTPAGE_STATUSLOG*)NULL == spWork )
	{
		return D_LD_NG;
	}
	
	/* ログ数取得 */
	iLogNum = spWork->spData->iLogNum;
	for( iLoop = 0; iLoop < iLogNum; iLoop++ )
	{
		memset( &stStatusLogData, 0x00, sizeof(S_TASK_LOGDATA_STATUSLOG) );
		memcpy( &stStatusLogData, &(spWork->spData->stLog[iLoop]), sizeof(S_TASK_LOGDATA_STATUSLOG) );

		/***********************/
		/* 時刻 */
		sprintf( cPrintLine, "[%02d/%02d/%02d]%02d:%02d:%02d.%03d,",
			stStatusLogData.stDayTime.usYear, stStatusLogData.stDayTime.usMonth, stStatusLogData.stDayTime.usDay,
			stStatusLogData.stDayTime.usHour, stStatusLogData.stDayTime.usMinute, stStatusLogData.stDayTime.usSecond,
			stStatusLogData.stDayTime.usMilliSec );
		
		/* タスクID */
		sprintf( cPrintLine, "%s%d,",
			cPrintLine,
			stStatusLogData.iTaskId );
		
		/* 状態 */
		sprintf( cPrintLine, "%s%d,",
			cPrintLine,
			stStatusLogData.iStatus );
		
		/***********************/
		
		/* ログ書き込み */
		fprintf( spLd->stFileInfo.fpStatusLog.fpFile, "%s\n", cPrintLine );
		fflush( spLd->stFileInfo.fpStatusLog.fpFile );
	
	}
	
	/* 書き込みページ数更新 */
	spLd->stFileInfo.fpStatusLog.iWritePageNum++;
	
	/* ページ書き出し比率の確認 */
	if( iAllPageNum == spLd->stFileInfo.fpStatusLog.iWritePageNum )
	{
		iProgress = 100;
	}
	else
	{
		iProgress = (spLd->stFileInfo.fpStatusLog.iWritePageNum * 100) / iAllPageNum;
	}
#endif	/* D_LD_LOGMODE_STATUS */
	return iProgress;
}

int ld_log_DumpCalibratelog( void )
{
	int iProgress = -1;			/* 進捗率 */
#if	(D_LD_LOGMODE_CALIBRATE)
	int iAllPageNum = 0;		/* 全ページ数 */
	int iWritePage = 0;			/* 書き込みページ */
	int iLogNum = 0;			/* 1ページ内ログ数 */
	int iLoop = 0;				/* ループカウンタ */
	S_LD* spLd = (S_LD*)NULL;
	S_LD_LOGLISTPAGE_CALIBRATELOG* spWork = (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL;
	S_TASK_LOGDATA_CALIBRATELOG stCalibrateLogData;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	memset( &stCalibrateLogData, 0x00, sizeof(S_TASK_LOGDATA_CALIBRATELOG) );
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return D_LD_NG;
	}
	
	if( (FILE*)NULL == spLd->stFileInfo.fpCalibrateLog.fpFile )
	{
		return D_LD_NG;
	}
	
	/* 全ページ数取得 */
	iAllPageNum = spLd->stLogList.stLogListInfo_CalibrateLog.iAllPageNum;
	
	/* 書き込みページ取得 */
	iWritePage = spLd->stFileInfo.fpCalibrateLog.iWritePageNum;
	
	/* ページトップ取得 */
	spWork = spLd->stLogList.stLogListInfo_CalibrateLog.spList;
	
	/* 書き込みページデータアドレス取得 */
	for( iLoop = 0; iLoop < iWritePage; iLoop++ )
	{
		spWork = spWork->spNextPage;
	}
	
	if( (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL == spWork )
	{
		return D_LD_NG;
	}
	
	/* ログ数取得 */
	iLogNum = spWork->spData->iLogNum;
	for( iLoop = 0; iLoop < iLogNum; iLoop++ )
	{
		memset( &stCalibrateLogData, 0x00, sizeof(S_TASK_LOGDATA_CALIBRATELOG) );
		memcpy( &stCalibrateLogData, &(spWork->spData->stLog[iLoop]), sizeof(S_TASK_LOGDATA_CALIBRATELOG) );

		/***********************/
		/* 時刻 */
		sprintf( cPrintLine, "[%02d/%02d/%02d]%02d:%02d:%02d.%03d,",
			stCalibrateLogData.stDayTime.usYear, stCalibrateLogData.stDayTime.usMonth, stCalibrateLogData.stDayTime.usDay,
			stCalibrateLogData.stDayTime.usHour, stCalibrateLogData.stDayTime.usMinute, stCalibrateLogData.stDayTime.usSecond,
			stCalibrateLogData.stDayTime.usMilliSec );
		
		/* 走行状態 */
		sprintf( cPrintLine, "%s%d,",
			cPrintLine,
			stCalibrateLogData.iLtStatus );
	
		/* キャリブレーションログ */
		sprintf( cPrintLine, "%s%d,%d,%d,%d,%d,",
			cPrintLine,
			stCalibrateLogData.stCalibrateInfo.iGyro,
			stCalibrateLogData.stCalibrateInfo.stBlack.iColor,
			stCalibrateLogData.stCalibrateInfo.stBlack.iReflect,
			stCalibrateLogData.stCalibrateInfo.stWhite.iColor,
			stCalibrateLogData.stCalibrateInfo.stWhite.iReflect );
		/***********************/
		
		/* ログ書き込み */
		fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "%s\n", cPrintLine );
		fflush( spLd->stFileInfo.fpCalibrateLog.fpFile );
	
	}
	
	/* 書き込みページ数更新 */
	spLd->stFileInfo.fpCalibrateLog.iWritePageNum++;
	
	/* ページ書き出し比率の確認 */
	if( iAllPageNum == spLd->stFileInfo.fpCalibrateLog.iWritePageNum )
	{
		iProgress = 100;
	}
	else
	{
		iProgress = (spLd->stFileInfo.fpCalibrateLog.iWritePageNum * 100) / iAllPageNum;
	}
#endif	/* D_LD_LOGMODE_CALIBRATE */
	return iProgress;
}

int ld_log_DumpSystemlog( void )
{
	int iProgress = -1;			/* 進捗率 */
#if	(D_LD_LOGMODE_SYSTEM)
	int iAllPageNum = 0;		/* 全ページ数 */
	int iWritePage = 0;			/* 書き込みページ */
	int iLogNum = 0;			/* 1ページ内ログ数 */
	int iLoop = 0;				/* ループカウンタ */
	S_LD* spLd = (S_LD*)NULL;
	S_LD_LOGLISTPAGE_SYSTEMLOG* spWork = (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL;
	S_TASK_LOGDATA_SYSTEMLOG stSystemLogData;
	char cPrintLine[D_LD_PRINTLINE_NUM];
	
	memset( &cPrintLine, 0x00, sizeof(cPrintLine) );
	memset( &stSystemLogData, 0x00, sizeof(S_TASK_LOGDATA_SYSTEMLOG) );
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return D_LD_NG;
	}
	
	if( (FILE*)NULL == spLd->stFileInfo.fpSystemLog.fpFile )
	{
		return D_LD_NG;
	}
	
	/* 全ページ数取得 */
	iAllPageNum = spLd->stLogList.stLogListInfo_SystemLog.iAllPageNum;
	
	/* 書き込みページ取得 */
	iWritePage = spLd->stFileInfo.fpSystemLog.iWritePageNum;
	
	/* ページトップ取得 */
	spWork = spLd->stLogList.stLogListInfo_SystemLog.spList;
	
	/* 書き込みページデータアドレス取得 */
	for( iLoop = 0; iLoop < iWritePage; iLoop++ )
	{
		spWork = spWork->spNextPage;
	}
	
	if( (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL == spWork )
	{
		return D_LD_NG;
	}
	
	/* ログ数取得 */
	iLogNum = spWork->spData->iLogNum;
	for( iLoop = 0; iLoop < iLogNum; iLoop++ )
	{
		memset( &stSystemLogData, 0x00, sizeof(S_TASK_LOGDATA_SYSTEMLOG) );
		memcpy( &stSystemLogData, &(spWork->spData->stLog[iLoop]), sizeof(S_TASK_LOGDATA_SYSTEMLOG) );

		/***********************/
		/* 時刻 */
		sprintf( cPrintLine, "[%02d/%02d/%02d]%02d:%02d:%02d.%03d,",
			stSystemLogData.stDayTime.usYear, stSystemLogData.stDayTime.usMonth, stSystemLogData.stDayTime.usDay,
			stSystemLogData.stDayTime.usHour, stSystemLogData.stDayTime.usMinute, stSystemLogData.stDayTime.usSecond,
			stSystemLogData.stDayTime.usMilliSec );
		
		/* 走行状態 */
		sprintf( cPrintLine, "%s%d,",
			cPrintLine,
			stSystemLogData.iLtStatus );
		
#if	(D_LD_LOGMODE_SYSTEM_BALANCEINFO)
		/* バランス制御情報 */
		sprintf( cPrintLine, "%s%lf,%lf,%lf,%lf,%lf,",
			cPrintLine,
			stSystemLogData.stBalanceInfo.fErr_theta,
			stSystemLogData.stBalanceInfo.fPsi,
			stSystemLogData.stBalanceInfo.fThetaLpf,
			stSystemLogData.stBalanceInfo.fThetaRef,
			stSystemLogData.stBalanceInfo.fThetadotCmdLpf );
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCEINFO */
	
#if	(D_LD_LOGMODE_SYSTEM_BALANCECONTROL)
		/* バランスコントロール */
		sprintf( cPrintLine, "%s%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,",
			cPrintLine,
			stSystemLogData.stBacanceControl.fCmdForward,
			stSystemLogData.stBacanceControl.fCmdTurn,
			stSystemLogData.stBacanceControl.fGyro,
			stSystemLogData.stBacanceControl.fGyroOffset,
			stSystemLogData.stBacanceControl.fThetaMLeft,
			stSystemLogData.stBacanceControl.fThetaMRight,
			stSystemLogData.stBacanceControl.fBattery,
			stSystemLogData.stBacanceControl.scPwmLeft,
			stSystemLogData.stBacanceControl.scPwmRight );
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCECONTROL */
		/***********************/
		
		/* ログ書き込み */
		fprintf( spLd->stFileInfo.fpSystemLog.fpFile, "%s\n", cPrintLine );
		fflush( spLd->stFileInfo.fpSystemLog.fpFile );
	
	}
	
	/* 書き込みページ数更新 */
	spLd->stFileInfo.fpSystemLog.iWritePageNum++;
	
	/* ページ書き出し比率の確認 */
	if( iAllPageNum == spLd->stFileInfo.fpSystemLog.iWritePageNum )
	{
		iProgress = 100;
	}
	else
	{
		iProgress = (spLd->stFileInfo.fpSystemLog.iWritePageNum * 100) / iAllPageNum;
	}
#endif	/* D_LD_LOGMODE_SYSTEM */
	return iProgress;
}
