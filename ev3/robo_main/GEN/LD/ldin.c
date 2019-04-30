#include "ldin.h"

S_LD* gspLd = (S_LD*)NULL;

/* startup */
void ld_main( void )
{
	int iRet				= D_LD_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	ld_init();
	
	/* LD_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_LD, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_LD_INVALID != psRecvData->iMsgid) )
		{
			/* 受信処理 */
			ld_recv( psRecvData );
			
		}
		
		/* 受信データクリア */
		if ((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		ld_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_LD );
	}

END:
	/*** 解放処理 ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
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
			case E_LD_LOGKIND_SYSTEMLOG:
				iProgress = ld_log_DumpSystemlog();
				break;
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
	
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	fpStatusLog = fopen( D_LD_FILENAME_STATUSLOG_LT, "w");
	if( (FILE*)NULL == fpStatusLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spLd->stFileInfo.fpStatusLog_Lt.fpFile = fpStatusLog;
	
	/* ヘッダ出力 */
#if	(__TARGET_EV3__)
	fprintf( spLd->stFileInfo.fpStatusLog_Lt.fpFile, "SysClock(msec),");
#else	/* __TARGET_EV3__ */
	fprintf( spLd->stFileInfo.fpStatusLog_Lt.fpFile, "SysCount,");
#endif	/* __TARGET_EV3__ */
	fprintf( spLd->stFileInfo.fpStatusLog_Lt.fpFile, "Status,");
	
	fprintf( spLd->stFileInfo.fpStatusLog_Lt.fpFile, "\n");
	fflush( spLd->stFileInfo.fpStatusLog_Lt.fpFile );	
#endif	/* D_LD_LOGMODE_STATUS */
	return;
}

void ld_log_Calibratelog_open( void )
{
#if	(D_LD_LOGMODE_CALIBRATE)
	S_LD* spLd = (S_LD*)NULL;
	FILE* fpCalirateLog = (FILE*)NULL;
	
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
	/* ジャイロ */
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "iGyro,");
	/* 黒 */
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "stBlack.iColor,");
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "stBlack.iReflect,");
	/* 白 */
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "stWhite.iColor,");
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "stWhite.iReflect,");
	
	fprintf( spLd->stFileInfo.fpCalibrateLog.fpFile, "\n");
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
#if	(__TARGET_EV3__)
	sprintf( cPrintLine, "SysClock(msec),");
#else	/* __TARGET_EV3__ */
	sprintf( cPrintLine, "SysCount,");
#endif	/* __TARGET_EV3__ */
	
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

int ld_log_DumpSystemlog( void )
{
	int iProgress = 0;			/* 進捗率 */
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
	/* ログ出力 */
	sprintf( cPrintLine, "%ld,",stSystemLogData.ulTime );
	
#if	(D_LD_LOGMODE_SYSTEM_BALANCEINFO)
	/* バランス制御情報 */
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBalanceInfo.fErr_theta );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBalanceInfo.fPsi );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBalanceInfo.fThetaLpf );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBalanceInfo.fThetaRef );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBalanceInfo.fThetadotCmdLpf );
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCEINFO */
	
#if	(D_LD_LOGMODE_SYSTEM_BALANCECONTROL)
	/* バランスコントロール */
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fCmdForward );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fCmdTurn );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fGyro );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fGyroOffset );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fThetaMLeft );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fThetaMRight );
	sprintf( cPrintLine, "%s%lf,",cPrintLine, stSystemLogData.stBacanceControl.fBattery );
	sprintf( cPrintLine, "%s%d,",cPrintLine, stSystemLogData.stBacanceControl.scPwmLeft );
	sprintf( cPrintLine, "%s%d,",cPrintLine, stSystemLogData.stBacanceControl.scPwmRight );
#endif	/* D_LD_LOGMODE_SYSTEM_BALANCECONTROL */
	
	fprintf( spLd->stFileInfo.fpSystemLog.fpFile, "%s\n", cPrintLine );
	fflush( spLd->stFileInfo.fpSystemLog.fpFile );
	
	}
	/***********************/
	
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

	return iProgress;
}