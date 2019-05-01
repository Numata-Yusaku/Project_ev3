#include "ld.h"
#include "ldin.h"
#include "ldin_recvtable.h"

/* FrameWork */
void ld_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_LD_RECVFUNCPTR pvRecvFunc = (F_LD_RECVFUNCPTR)NULL;
	
	/* 実行関数取得 */
	pvRecvFunc = ld_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* 受信関数実行 */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_LD_RECVFUNCPTR ld_get_RecvFunc( int iMsgId )
{
	F_LD_RECVFUNCPTR func = (F_LD_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_LD_RECV_TABLE* psRecvTable = (S_LD_RECV_TABLE*)NULL;
	
	/* 受信テーブル設定 */
	psRecvTable =T_LD_RECV_TABLE;
	if((S_LD_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_LD_RECVFUNCPTR)NULL;
	}
	
	/* 受信テーブル要素数取得 */
	iNum = sizeof( T_LD_RECV_TABLE ) / sizeof( S_LD_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_LD_RECVFUNCPTR)NULL;
	}
	
	/* 受信関数探索 */
	for(iCount = 0; iCount < iNum; iCount++)
	{
		if( iMsgId == psRecvTable[iCount].iMsgId )
		{
			func = psRecvTable[iCount].func;
			break;
		}
	}
	
	return func;
}

/* RecvFunc */
void ld_rcv_test_req( S_MSG_DATA* spRecv )
{
	ld_send_test_res( spRecv );
	
	return;
}

void ld_rcv_Wupchk_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* LDタスク起動完了済 */
	if( D_LD_FLAG_ON != spLd->iWupChk )
	{
		ld_send_Wupchk_res();
		spLd->iWupChk = D_LD_FLAG_ON;
	}
	
	return;
}

void ld_rcv_Stop_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* すでに停止中の場合は処理しない */
	if( E_LD_STATUS_STOP == spLd->iStatus )
	{
		return;
	}
	
	spLd->iWupChk = D_LD_FLAG_OFF;
	
	ld_send_Stop_res();
	
	spLd->iStatus = E_LD_STATUS_STOP;
	
	return;
}

void ld_rcv_staRunning_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	spLd->iStatus = E_LD_STATUS_RUN;
	
	return;
}

void ld_rcv_setLog_StatusLog_req( S_MSG_DATA* spRecv )
{
	int iLogNum = 0;
	int iLoop = 0;
	S_LD* spLd = (S_LD*)NULL;
	S_TASK_LOGINFO_STATUSLOG* psRecvPara = (S_TASK_LOGINFO_STATUSLOG*)NULL;
	S_TASK_LOGDATA_STATUSLOG* spLogData = (S_TASK_LOGDATA_STATUSLOG*)NULL;
	
	S_LD_LOGLISTPAGE_STATUSLOG* spLogListPage = (S_LD_LOGLISTPAGE_STATUSLOG*)NULL;
	S_LD_LOGLISTPAGE_STATUSLOG* spWork = (S_LD_LOGLISTPAGE_STATUSLOG*)NULL;
	
	if( (void*)NULL == spRecv->vpPara )
	{
		goto ERR;
	}
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		goto ERR;
	}
	
	/* ログ出力中はログを破棄する */
	if( E_LD_STATUS_LOGDUMP == spLd->iStatus )
	{
		goto ERR;
	}
	
	/* 受信データ取得 */
	psRecvPara = (S_TASK_LOGINFO_STATUSLOG*)spRecv->vpPara;
	
	/* ログ数取得 */
	iLogNum = psRecvPara->iLogNum;
	if( 0 >= iLogNum )
	{
		goto ERR;
	}
	
	/* ログデータ取得 */
	spLogData = (S_TASK_LOGDATA_STATUSLOG*)malloc( sizeof(S_TASK_LOGDATA_STATUSLOG) * D_TASK_BUFFNUM_STATUSLOG );
	if( (S_TASK_LOGDATA_STATUSLOG*)NULL == spLogData )
	{
		goto ERR;
	}
	
	memset( spLogData, 0x00, sizeof( S_TASK_LOGDATA_STATUSLOG ) * D_TASK_BUFFNUM_STATUSLOG );
	memcpy( spLogData, &(psRecvPara->stLog), sizeof( S_TASK_LOGDATA_STATUSLOG ) * D_TASK_BUFFNUM_STATUSLOG );
	
	/*** ページデータ作成 ***/
	spLogListPage = (S_LD_LOGLISTPAGE_STATUSLOG*)malloc( sizeof(S_LD_LOGLISTPAGE_STATUSLOG) );
	if( (S_LD_LOGLISTPAGE_STATUSLOG*)NULL == spLogListPage )
	{
		goto ERR;
	}
	
	memset( spLogListPage, 0x00, sizeof( S_LD_LOGLISTPAGE_STATUSLOG ) );

	/* ページ番号 */
	spLogListPage->iPageNo = spLd->stLogList.stLogListInfo_StatusLog.iAllPageNum + 1;
		
	/* データ設定 */
	spLogListPage->spData = (S_TASK_LOGINFO_STATUSLOG*)malloc( sizeof(S_TASK_LOGINFO_STATUSLOG) );
	if( (S_TASK_LOGINFO_STATUSLOG*)NULL == spLogListPage->spData )
	{
		goto ERR;
	}
	
	memset( spLogListPage->spData, 0x00, sizeof(S_TASK_LOGINFO_STATUSLOG) );
	
	spLogListPage->spData->iLogNum = iLogNum;
	memcpy( spLogListPage->spData->stLog, spLogData, sizeof( S_TASK_LOGDATA_STATUSLOG ) * D_TASK_BUFFNUM_STATUSLOG );
	
	/*** ログリスト設定 ***/
	if( (S_LD_LOGLISTPAGE_STATUSLOG*)NULL == spLd->stLogList.stLogListInfo_StatusLog.spList )
	{
		spLd->stLogList.stLogListInfo_StatusLog.spList = spLogListPage;
	}
	else
	{
		spWork = spLd->stLogList.stLogListInfo_StatusLog.spList;
		for( iLoop = 0; iLoop < spLd->stLogList.stLogListInfo_StatusLog.iAllPageNum; iLoop++ )
		{
			if( (S_LD_LOGLISTPAGE_STATUSLOG*)NULL != spWork->spNextPage )
			{
				/* リスト探索継続 */
				spWork = spWork->spNextPage;
			}
			else
			{
				/* 末尾にデータを設定 */
				spWork->spNextPage = spLogListPage;
				break;
			}
		}
	}
	
	/* ページ総数更新 */
	spLd->stLogList.stLogListInfo_StatusLog.iAllPageNum ++;
	
	return;

ERR:
	/*** 解放処理 ***/
	if( (S_LD_LOGLISTPAGE_STATUSLOG*)NULL != spLogListPage )
	{
		if( (S_TASK_LOGINFO_STATUSLOG*)NULL != spLogListPage->spData )
		{
			free(spLogListPage->spData);
			spLogListPage->spData = (S_TASK_LOGINFO_STATUSLOG*)NULL;
		}
		
		free(spLogListPage);
		spLogListPage = (S_LD_LOGLISTPAGE_STATUSLOG*)NULL;
	}
	
	if( (S_TASK_LOGDATA_STATUSLOG*)NULL != spLogData )
	{
		free(spLogData);
		spLogData = (S_TASK_LOGDATA_STATUSLOG*)NULL;
	}
	
	return;
}

void ld_rcv_setLog_CalibrateLog_req( S_MSG_DATA* spRecv )
{
	int iLogNum = 0;
	int iLoop = 0;
	S_LD* spLd = (S_LD*)NULL;
	S_TASK_LOGINFO_CALIBRATELOG* psRecvPara = (S_TASK_LOGINFO_CALIBRATELOG*)NULL;
	S_TASK_LOGDATA_CALIBRATELOG* spLogData = (S_TASK_LOGDATA_CALIBRATELOG*)NULL;
	
	S_LD_LOGLISTPAGE_CALIBRATELOG* spLogListPage = (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL;
	S_LD_LOGLISTPAGE_CALIBRATELOG* spWork = (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL;
	
	if( (void*)NULL == spRecv->vpPara )
	{
		goto ERR;
	}
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		goto ERR;
	}
	
	/* ログ出力中はログを破棄する */
	if( E_LD_STATUS_LOGDUMP == spLd->iStatus )
	{
		goto ERR;
	}
	
	/* 受信データ取得 */
	psRecvPara = (S_TASK_LOGINFO_CALIBRATELOG*)spRecv->vpPara;
	
	/* ログ数取得 */
	iLogNum = psRecvPara->iLogNum;
	if( 0 >= iLogNum )
	{
		goto ERR;
	}
	
	/* ログデータ取得 */
	spLogData = (S_TASK_LOGDATA_CALIBRATELOG*)malloc( sizeof(S_TASK_LOGDATA_CALIBRATELOG) * D_TASK_BUFFNUM_CALIBRATELOG );
	if( (S_TASK_LOGDATA_CALIBRATELOG*)NULL == spLogData )
	{
		goto ERR;
	}
	
	memset( spLogData, 0x00, sizeof( S_TASK_LOGDATA_CALIBRATELOG ) * D_TASK_BUFFNUM_CALIBRATELOG );
	memcpy( spLogData, &(psRecvPara->stLog), sizeof( S_TASK_LOGDATA_CALIBRATELOG ) * D_TASK_BUFFNUM_CALIBRATELOG );
	
	/*** ページデータ作成 ***/
	spLogListPage = (S_LD_LOGLISTPAGE_CALIBRATELOG*)malloc( sizeof(S_LD_LOGLISTPAGE_CALIBRATELOG) );
	if( (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL == spLogListPage )
	{
		goto ERR;
	}
	
	memset( spLogListPage, 0x00, sizeof( S_LD_LOGLISTPAGE_CALIBRATELOG ) );

	/* ページ番号 */
	spLogListPage->iPageNo = spLd->stLogList.stLogListInfo_CalibrateLog.iAllPageNum + 1;
		
	/* データ設定 */
	spLogListPage->spData = (S_TASK_LOGINFO_CALIBRATELOG*)malloc( sizeof(S_TASK_LOGINFO_CALIBRATELOG) );
	if( (S_TASK_LOGINFO_CALIBRATELOG*)NULL == spLogListPage->spData )
	{
		goto ERR;
	}
	
	memset( spLogListPage->spData, 0x00, sizeof(S_TASK_LOGINFO_CALIBRATELOG) );
	
	spLogListPage->spData->iLogNum = iLogNum;
	memcpy( spLogListPage->spData->stLog, spLogData, sizeof( S_TASK_LOGDATA_CALIBRATELOG ) * D_TASK_BUFFNUM_CALIBRATELOG );
	
	/*** ログリスト設定 ***/
	if( (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL == spLd->stLogList.stLogListInfo_CalibrateLog.spList )
	{
		spLd->stLogList.stLogListInfo_CalibrateLog.spList = spLogListPage;
	}
	else
	{
		spWork = spLd->stLogList.stLogListInfo_CalibrateLog.spList;
		for( iLoop = 0; iLoop < spLd->stLogList.stLogListInfo_CalibrateLog.iAllPageNum; iLoop++ )
		{
			if( (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL != spWork->spNextPage )
			{
				/* リスト探索継続 */
				spWork = spWork->spNextPage;
			}
			else
			{
				/* 末尾にデータを設定 */
				spWork->spNextPage = spLogListPage;
				break;
			}
		}
	}
	
	/* ページ総数更新 */
	spLd->stLogList.stLogListInfo_CalibrateLog.iAllPageNum ++;
	
	return;

ERR:
	/*** 解放処理 ***/
	if( (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL != spLogListPage )
	{
		if( (S_TASK_LOGINFO_CALIBRATELOG*)NULL != spLogListPage->spData )
		{
			free(spLogListPage->spData);
			spLogListPage->spData = (S_TASK_LOGINFO_CALIBRATELOG*)NULL;
		}
		
		free(spLogListPage);
		spLogListPage = (S_LD_LOGLISTPAGE_CALIBRATELOG*)NULL;
	}
	
	if( (S_TASK_LOGDATA_CALIBRATELOG*)NULL != spLogData )
	{
		free(spLogData);
		spLogData = (S_TASK_LOGDATA_CALIBRATELOG*)NULL;
	}
	
	return;
}

void ld_rcv_setLog_SystemLog_req( S_MSG_DATA* spRecv )
{
	int iLogNum = 0;
	int iLoop = 0;
	S_LD* spLd = (S_LD*)NULL;
	S_TASK_LOGINFO_SYSTEMLOG* psRecvPara = (S_TASK_LOGINFO_SYSTEMLOG*)NULL;
	S_TASK_LOGDATA_SYSTEMLOG* spLogData = (S_TASK_LOGDATA_SYSTEMLOG*)NULL;
	
	S_LD_LOGLISTPAGE_SYSTEMLOG* spLogListPage = (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL;
	S_LD_LOGLISTPAGE_SYSTEMLOG* spWork = (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL;
	
	if( (void*)NULL == spRecv->vpPara )
	{
		goto ERR;
	}
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		goto ERR;
	}
	
	/* ログ出力中はログを破棄する */
	if( E_LD_STATUS_LOGDUMP == spLd->iStatus )
	{
		goto ERR;
	}
	
	/* 受信データ取得 */
	psRecvPara = (S_TASK_LOGINFO_SYSTEMLOG*)spRecv->vpPara;
	
	/* ログ数取得 */
	iLogNum = psRecvPara->iLogNum;
	if( 0 >= iLogNum )
	{
		goto ERR;
	}
	
	/* ログデータ取得 */
	spLogData = (S_TASK_LOGDATA_SYSTEMLOG*)malloc( sizeof(S_TASK_LOGDATA_SYSTEMLOG) * D_TASK_BUFFNUM_SYSTEMLOG );
	if( (S_TASK_LOGDATA_SYSTEMLOG*)NULL == spLogData )
	{
		goto ERR;
	}
	
	memset( spLogData, 0x00, sizeof( S_TASK_LOGDATA_SYSTEMLOG ) * D_TASK_BUFFNUM_SYSTEMLOG );
	memcpy( spLogData, &(psRecvPara->stLog), sizeof( S_TASK_LOGDATA_SYSTEMLOG ) * D_TASK_BUFFNUM_SYSTEMLOG );
	
	/*** ページデータ作成 ***/
	spLogListPage = (S_LD_LOGLISTPAGE_SYSTEMLOG*)malloc( sizeof(S_LD_LOGLISTPAGE_SYSTEMLOG) );
	if( (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL == spLogListPage )
	{
		goto ERR;
	}
	
	memset( spLogListPage, 0x00, sizeof( S_LD_LOGLISTPAGE_SYSTEMLOG ) );

	/* ページ番号 */
	spLogListPage->iPageNo = spLd->stLogList.stLogListInfo_SystemLog.iAllPageNum + 1;
		
	/* データ設定 */
	spLogListPage->spData = (S_TASK_LOGINFO_SYSTEMLOG*)malloc( sizeof(S_TASK_LOGINFO_SYSTEMLOG) );
	if( (S_TASK_LOGINFO_SYSTEMLOG*)NULL == spLogListPage->spData )
	{
		goto ERR;
	}
	
	memset( spLogListPage->spData, 0x00, sizeof(S_TASK_LOGINFO_SYSTEMLOG) );
	
	spLogListPage->spData->iLogNum = iLogNum;
	memcpy( spLogListPage->spData->stLog, spLogData, sizeof( S_TASK_LOGDATA_SYSTEMLOG ) * D_TASK_BUFFNUM_SYSTEMLOG );
	
	/*** ログリスト設定 ***/
	if( (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL == spLd->stLogList.stLogListInfo_SystemLog.spList )
	{
		spLd->stLogList.stLogListInfo_SystemLog.spList = spLogListPage;
	}
	else
	{
		spWork = spLd->stLogList.stLogListInfo_SystemLog.spList;
		for( iLoop = 0; iLoop < spLd->stLogList.stLogListInfo_SystemLog.iAllPageNum; iLoop++ )
		{
			if( (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL != spWork->spNextPage )
			{
				/* リスト探索継続 */
				spWork = spWork->spNextPage;
			}
			else
			{
				/* 末尾にデータを設定 */
				spWork->spNextPage = spLogListPage;
				break;
			}
		}
	}
	
	/* ページ総数更新 */
	spLd->stLogList.stLogListInfo_SystemLog.iAllPageNum ++;
	
	return;

ERR:
	/*** 解放処理 ***/
	if( (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL != spLogListPage )
	{
		if( (S_TASK_LOGINFO_SYSTEMLOG*)NULL != spLogListPage->spData )
		{
			free(spLogListPage->spData);
			spLogListPage->spData = (S_TASK_LOGINFO_SYSTEMLOG*)NULL;
		}
		
		free(spLogListPage);
		spLogListPage = (S_LD_LOGLISTPAGE_SYSTEMLOG*)NULL;
	}
	
	if( (S_TASK_LOGDATA_SYSTEMLOG*)NULL != spLogData )
	{
		free(spLogData);
		spLogData = (S_TASK_LOGDATA_SYSTEMLOG*)NULL;
	}
	
	return;
}

void ld_rcv_setLog_LogLast_req( S_MSG_DATA* spRecv )
{
	ld_log_set_LastLog_Statuslog();
	ld_send_setLog_LogLast_res();
	
	return;
}

void ld_rcv_staLogDump_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* ログダンプ状態に遷移 */
	spLd->iStatus = E_LD_STATUS_LOGDUMP;
	
	/* ファイルオープン */
	ld_log_Statuslog_open();
	ld_log_Calibratelog_open();
	ld_log_Systemlog_open();
	
	/* ログダンプ開始応答 */
	ld_send_staLogDump_res();
	
	return;
}

void ld_rcv_endLogDump_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* ファイルクローズ */
	if( (FILE*)NULL != spLd->stFileInfo.fpStatusLog.fpFile )
	{
		fclose( spLd->stFileInfo.fpStatusLog.fpFile );
		spLd->stFileInfo.fpStatusLog.fpFile = (FILE*)NULL;
	}
	
	if( (FILE*)NULL != spLd->stFileInfo.fpCalibrateLog.fpFile )
	{
		fclose( spLd->stFileInfo.fpCalibrateLog.fpFile );
		spLd->stFileInfo.fpCalibrateLog.fpFile = (FILE*)NULL;
	}
	
	if( (FILE*)NULL != spLd->stFileInfo.fpSystemLog.fpFile )
	{
		fclose( spLd->stFileInfo.fpSystemLog.fpFile );
		spLd->stFileInfo.fpSystemLog.fpFile = (FILE*)NULL;
	}
	
	/* ログダンプ終了応答 */
	ld_send_endLogDump_res();
	
	return;
}
