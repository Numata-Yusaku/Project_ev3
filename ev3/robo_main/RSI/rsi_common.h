#ifndef	__RSI_COMMON_H__
#define	__RSI_COMMON_H__

/***** インクルード *****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */


/*** GEN ***/

/*** APL ***/

/***** 定数 *****/
#define		D_RSI_OK		(0)
#define		D_RSI_NG		(-1)

#define		D_RSI_TRUE		(1)
#define		D_RSI_FALSE		(0)

#define		D_RSI_TMAX_FILENAME_LEN (255)

/* ログ出力 */
#define	D_RSI_FILENAME_MSGLOG		"OutData/RsiLog.csv"

#define	D_RSI_LOGMODE				(D_RSI_TRUE)


/***** 構造体 *****/
typedef struct
{
	void*			buffer;		/* このファイルが格納されているバッファへのポインタ */
	unsigned int	filesz;		/* ファイルの実際のサイズ */
	unsigned int	buffersz;	/* バッファの最大サイズ */
}S_RSI_MEMFILE;


typedef struct
{
	unsigned int	size;									/* ファイルのサイズ */
	unsigned short	date;									/* ファイルのLast modified date */
	unsigned short	time;									/* ファイルのLast modified time */
	int				is_dir;									/* フォルダであることを表すフラグ */
	int				is_readonly;							/* 読み出し専用であることを表すフラグ */
	int				is_hidden;								/* 隠しファイルであることを表すフラグ */
	char			name[D_RSI_TMAX_FILENAME_LEN + 1];		/* ファイル名 */
}S_RSI_FILEINFO;

typedef struct
{
	FILE* fpRsiLog;
}S_RSI;

/***** 関数プロトタイプ *****/
void RSI_init( void );
void rsi_set_Global( void );
S_RSI* rsi_get_Global( void );
void rsi_rsilog_open( void );
/***** テーブル *****/


#endif	/* __RSI_COMMON_H__ */
