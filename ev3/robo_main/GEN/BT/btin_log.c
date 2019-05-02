#include "btin.h"

void bt_log_set_Statuslog( void )
{
#if	D_BT_LOGMODE_STATUS
	S_BT* spBt = (S_BT*)NULL;
	S_TM_DAYTIME stDayTime;
	S_BT_LOGDATA_STATUSLOG stLogData;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* 初期化 */
	memset( &stDayTime, 0x00, sizeof(S_TM_DAYTIME) );
	memset( &stLogData, 0x00, sizeof(S_BT_LOGDATA_STATUSLOG) );
	
	TM_get_NowTime( &stDayTime );
	
	/* カウンタ */
	memcpy( &stLogData.stDayTime, &stDayTime, sizeof(S_TM_DAYTIME) );
	
	/* 走行状態 */
	stLogData.iStatus = spBt->iStatus;
	
	/* タスクID */
	stLogData.iTaskId = E_TASK_TASKID_BT;
	
	/* データ設定 */
	memcpy( &(spBt->stLogInfo.stStatusLog.stLog[spBt->stLogInfo.stStatusLog.iLogNum]), &stLogData, sizeof(S_BT_LOGDATA_STATUSLOG) );
	
	/* ログ数更新 */
	spBt->stLogInfo.stStatusLog.iLogNum ++;
	if( D_BT_BUFFNUM_STATUSLOG == spBt->stLogInfo.stStatusLog.iLogNum )
	{
		/* ログ送信 */
		bt_send_setLog_StatusLog_req( &(spBt->stLogInfo.stStatusLog) );
		
		/* メモリクリア */
		memset( &(spBt->stLogInfo.stStatusLog), 0x00, sizeof(S_BT_LOGINFO_STATUSLOG));
	}
#endif	/* D_BT_LOGMODE_STATUS */
	return;
}

void bt_log_set_LastLog_Statuslog( void )
{
#if	D_BT_LOGMODE_STATUS
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* ログ送信 */
	bt_send_setLog_StatusLog_req( &(spBt->stLogInfo.stStatusLog) );
	
	/* メモリクリア */
	memset( &(spBt->stLogInfo.stStatusLog), 0x00, sizeof(S_BT_LOGINFO_STATUSLOG));
#endif	/* D_BT_LOGMODE_STATUS */
	return;
}
