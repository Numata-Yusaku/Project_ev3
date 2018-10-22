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
	
	/* ������ */
	memset( spRsi, 0x00, sizeof(S_RSI) );
	
	/*** �������l�ݒ� ***/
	
	/* �O���[�o���ݒ� */
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
	
	/* �O���[�o���ɐݒ� */
	spRsi->fpRsiLog = fpRsiLog;
	
	/* �w�b�_�o�� */
	fprintf( spRsi->fpRsiLog , "Class,Info,Data\n");
	fflush( spRsi->fpRsiLog  );
	
#endif	/* D_RSI_LOGMODE */
	return;
}

void rsi_set_rsilog( const char* cpClass, const char* cpInfo, int iData1, int iData2 )
{
	S_RSI* spRsi = (S_RSI*)NULL;
	FILE* fpRsiLog = (FILE*)NULL;
	
	spRsi = rsi_get_Global();
	if( (S_RSI*)NULL == spRsi )
	{
		return;
	}
	
	if( (FILE*)NULL == spRsi->fpRsiLog )
	{
		return;
	}
	
	fprintf( spRsi->fpRsiLog , cpClass );
	fprintf( spRsi->fpRsiLog , "," );
	
	fprintf( spRsi->fpRsiLog , cpInfo );
	fprintf( spRsi->fpRsiLog , "," );
	
	fprintf( spRsi->fpRsiLog , "\n" );
	fflush( spRsi->fpRsiLog  );

}