#include "btin.h"

void bt_log_Statuslog_open( void )
{
#if	(D_BT_LOGMODE_STATUS)
	S_BT* spBt = (S_BT*)NULL;
	FILE* fpStatusLog = (FILE*)NULL;
	
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	fpStatusLog = fopen( D_BT_FILENAME_STATUSLOG, "w");
	if( (FILE*)NULL == fpStatusLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spBt->fpStatusLog = fpStatusLog;
	
	/* ヘッダ出力 */
	fprintf( spBt->fpStatusLog, "Status,");
	
	fprintf( spBt->fpStatusLog, "\n");
	fflush( spBt->fpStatusLog );
#endif	/* D_BT_LOGMODE_STATUS */
	return;
}

void bt_log_set_Statuslog( void )
{
#if	(D_BT_LOGMODE_STATUS)
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	if( (FILE*)NULL == spBt->fpStatusLog )
	{
		return;
	}
		
	fprintf( spBt->fpStatusLog, "%d,",spBt->iStatus);
	
	fprintf( spBt->fpStatusLog, "\n");
	fflush( spBt->fpStatusLog );
#endif	/* D_BT_LOGMODE_STATUS */
	
	return;
}

void bt_log_set_Calibratelog( void )
{
#if	(D_BT_LOGMODE_CALIBRATE)
	S_BT* spBt = (S_BT*)NULL;
	
	/* グローバル領域取得 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	if( (FILE*)NULL == spBt->fpCalirateLog )
	{
		return;
	}
	
	/* バランスコントロール */
	fprintf( spBt->fpCalirateLog, "%d,",spBt->stCalibrateInfo.iGyro);
	fprintf( spBt->fpCalirateLog, "%d,",spBt->stCalibrateInfo.stBlack.iColor);
	fprintf( spBt->fpCalirateLog, "%d,",spBt->stCalibrateInfo.stBlack.iReflect);
	fprintf( spBt->fpCalirateLog, "%d,",spBt->stCalibrateInfo.stWhite.iColor);
	fprintf( spBt->fpCalirateLog, "%d,",spBt->stCalibrateInfo.stWhite.iReflect);
	
	fprintf( spBt->fpCalirateLog, "\n");
	fflush( spBt->fpCalirateLog );
#endif	/* D_BT_LOGMODE_CALIBRATE */
	
	return;
}