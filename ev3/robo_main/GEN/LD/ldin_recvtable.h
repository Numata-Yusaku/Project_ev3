#ifndef	__LDIN_RECVTABLE_H__
#define	__LDIN_RECVTABLE_H__

/***** インクルード *****/
#include "ldin.h"

/***** テーブル *****/
S_LD_RECV_TABLE T_LD_RECV_TABLE[] =
{
	/* MSGID								,	RecvFunc							*/
	{ E_MSGID_LD_WUPCHK_REQ					,	ld_rcv_Wupchk_req					},
	{ E_MSGID_LD_STOP_REQ					,	ld_rcv_Stop_req						},
	{ E_MSGID_LD_STARUNNING_REQ				,	ld_rcv_staRunning_req				},
	{ E_MSGID_LD_SETLOG_STATUSLOG_REQ		,	ld_rcv_setLog_StatusLog_req			},
	{ E_MSGID_LD_SETLOG_CALIBRATELOG_REQ	,	ld_rcv_setLog_CalibrateLog_req		},
	{ E_MSGID_LD_SETLOG_SYSTEMLOG_REQ		,	ld_rcv_setLog_SystemLog_req			},

	/* ここより上に定義すること */
	{ E_MSGID_LD_TEST_REQ					,	ld_rcv_test_req						},
};

#endif	/* __LDIN_RECVTABLE_H__ */
