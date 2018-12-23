#ifndef	__TMIN_RECVTABLE_H__
#define	__TMIN_RECVTABLE_H__

/***** インクルード *****/
#include "tmin.h"

/***** テーブル *****/
S_TM_RECV_TABLE T_TM_RECV_TABLE[] =
{
	/* MSGID								,	RecvFunc						*/

	/* ここより上に定義すること */
	{ E_MSGID_TM_TEST_REQ					,	tm_rcv_test_req					},
};

#endif	/* __TMIN_RECVTABLE_H__ */
