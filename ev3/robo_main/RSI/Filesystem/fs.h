#ifndef	__FS_H__
#define	__FS_H__

/***** インクルード *****/
#include <stdio.h>

#include "rsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */
/*** GEN ***/

/*** APL ***/

/***** 定数 *****/
#define	D_RSI_FS_SERIALPORT		"OutData/serial.txt"

enum EN_RSI_FS_SERIALPORT
{
	E_RSI_FS_SERIALPORT_DEFAULT = 0,
	E_RSI_FS_SERIALPORT_UART,
	E_RSI_FS_SERIALPORT_BT,
};
/***** 構造体 *****/


/***** 関数プロトタイプ *****/

/* sdcard */
int RSI_fs_sdcard_opendir( const char* aName );
int RSI_fs_sdcard_readdir( signed int siDirid, S_RSI_FILEINFO* 	spFileinfo );
int RSI_fs_sdcard_closedir( signed int siDirid );

/* memfile */
int RSI_fs_memfile_load( const char* aPath, S_RSI_MEMFILE* spMemfile );
int RSI_fs_memfile_free( S_RSI_MEMFILE* spMemfile );

/* Serial */
FILE* RSI_fs_serial_open_file( int iSerialPort );

/* Bluetooth */
int RSI_fs_bluetooth_is_connected( void );

/***** テーブル *****/


#endif	/* __FS_H__ */
