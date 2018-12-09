#include "fs.h"

/*** sdcard ***/

/********************************************************/
/* ディレクトリをオープンする							*/
/********************************************************/
int RSI_fs_sdcard_opendir( const char* aName )
{
	int iRet = 0;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_sdcard_opendir( aName );
#else	/* __TARGET_EV3__ */
	printf("[FS],@@SD OpenDir@@\n");
#endif	/* __TARGET_EV3__ */
	
	return iRet;	/* オープンディレクトリID */
}

/********************************************************/
/* ディレクトリ内のファイル情報を読み込む				*/
/********************************************************/
int RSI_fs_sdcard_readdir( signed int siDirid, S_RSI_FILEINFO* 	spFileinfo )
{
	int iRet = D_RSI_OK;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_sdcard_readdir( (ID)siDirid, (fileinfo_t*)spFileinfo );
#else	/* __TARGET_EV3__ */
	printf("[FS],@@SD ReadDir@@\n");
#endif	/* __TARGET_EV3__ */
	
	return iRet;	/* 結果 */
}


/********************************************************/
/* ディレクトリをクローズする							*/
/********************************************************/
int RSI_fs_sdcard_closedir( signed int siDirid )
{
	int iRet = D_RSI_OK;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_sdcard_closedir( (ID)siDirid );
#else	/* __TARGET_EV3__ */
	printf("[FS],@@SD CloseDir@@\n");
#endif	/* __TARGET_EV3__ */
	
	return iRet;	/* 結果 */
}

/*** memfile ***/

/********************************************************/
/* SDカードのファイルをメモリファイルとしてロードする	*/
/********************************************************/
int RSI_fs_memfile_load( const char* aPath, S_RSI_MEMFILE* spMemfile )
{
	int iRet = D_RSI_OK;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_memfile_load( aPath, (memfile_t*)spMemfile );
#else	/* __TARGET_EV3__ */
	printf("[FS],@@MemFile Load@@\n");
#endif	/* __TARGET_EV3__ */
	
	return iRet;	/* 結果 */
}

/********************************************************/
/* メモリファイルを解放する								*/
/********************************************************/
int RSI_fs_memfile_free( S_RSI_MEMFILE* spMemfile )
{
	int iRet = D_RSI_OK;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_memfile_free( (memfile_t*)spMemfile );
#else	/* __TARGET_EV3__ */
	printf("[FS],@@MemFile Free@@\n");
#endif	/* __TARGET_EV3__ */
	
	return iRet;	/* 結果 */
}

/*** Serial ***/

/********************************************************/
/* シリアルポートをファイルとしてオープンする			*/
/********************************************************/
FILE* RSI_fs_serial_open_file( int iSerialPort )
{
	FILE* spFile = (FILE*)NULL;

#if	(__TARGET_EV3__)
	spFile = ev3_serial_open_file( (serial_port_t)iSerialPort );
#else	/* __TARGET_EV3__ */
	spFile = fopen( D_RSI_FS_SERIALPORT, "w+b" );
#endif	/* __TARGET_EV3__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[FS]","Serial Open",iSerialPort ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return spFile;
}

/*** Bluetooth ***/

/********************************************************/
/* 	Bluetoothが接続されているかどうかをチェックする		*/
/********************************************************/
int RSI_fs_bluetooth_is_connected( void )
{
	int iRet = D_RSI_FALSE;

#if	(__TARGET_EV3__)
	iRet = (int)ev3_bluetooth_is_connected();
#else	/* __TARGET_EV3__ */
	iRet = D_RSI_TRUE;
#endif	/* __TARGET_EV3__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[FS]","BT Connect",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;
}
