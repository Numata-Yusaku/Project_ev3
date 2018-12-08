#ifndef	__BTIN_MESSAGETABLE_H__
#define	__BTIN_MESSAGETABLE_H__

/***** インクルード *****/
#include "btin.h"

/***** テーブル *****/
/*
	Command
		'a'-'z''A'-'Z'が使用可能
	Size
		0の場合：受信データを無視しコマンドのみ検知する
*/

S_BT_MESSAGE_TABLE T_BT_MESSAGE_TABLE[] =
{
	/* Command	,	Size	, Func				*/
	{ 's'		,	0		,	bt_recvCmd_s	},

	/* ここより上に定義すること */
	{ ' '		,	-1		,	NULL			},
};

#endif	/* __BTIN_MESSAGETABLE_H__ */
