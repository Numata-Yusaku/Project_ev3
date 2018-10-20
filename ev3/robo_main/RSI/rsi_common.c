#include "rsi_common.h"

S_RSI* gspRsi = (S_RSI*)NULL;

void RSI_init( void )
{
	rsi_set_Global();
	rsi_rsilog_open();
	
	return;
}

void rsi_set_Global( void )
{
	S_RSI* spRsi = (S_RSI*)NULL;
	
	spRsi = (S_RSI*)malloc( sizeof(S_RSI) );
	if( (S_RSI*)NULL == spRsi )
	{
		return;
	}
	
	/* 初期化 */
	memset( spRsi, 0x00, sizeof(S_RSI) );
	
	/*** 初期化値設定 ***/
	
	/* グローバル設定 */
	gspRsi = spRsi;
	
	return;
}

S_RSI* rsi_get_Global( void )
{
	return (S_RSI*)gspRsi;
}

void rsi_rsilog_open( void )
{
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = (S_RSI*)NULL;
	FILE* fpRsiLog = (FILE*)NULL;
	
	spRsi = rsi_get_Global();
	if( (S_RSI*)NULL == spRsi )
	{
		return;
	}
	
	fpRsiLog = fopen( D_RSI_FILENAME_MSGLOG, "w");
	if( (FILE*)NULL == fpRsiLog )
	{
		return;
	}
	
	/* グローバルに設定 */
	spRsi->fpRsiLog = fpRsiLog;
	
	/* ヘッダ出力 */
	fprintf( fpRsiLog, "Class,Info,Data\n");
	
#endif	/* D_RSI_LOGMODE */
	return;
}
