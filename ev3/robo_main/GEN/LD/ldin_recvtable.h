#ifndef	__LDIN_RECVTABLE_H__
#define	__LDIN_RECVTABLE_H__

/***** インクルード *****/
#include "ldin.h"

/***** テーブル *****/
S_LD_RECV_TABLE T_LD_RECV_TABLE[] =
{
	/* MSGID								,	RecvFunc						*/
	{ E_MSGID_LD_WUPCHK_REQ					,	ld_rcv_Wupchk_req				},
	{ E_MSGID_LD_STOP_REQ					,	ld_rcv_Stop_req					},
	{ E_MSGID_LD_STARUNNING_REQ				,	ld_rcv_staRunning_req			},

	/* ここより上に定義すること */
	{ E_MSGID_LD_TEST_REQ					,	ld_rcv_test_req					},
};

#endif	/* __LDIN_RECVTABLE_H__ */
