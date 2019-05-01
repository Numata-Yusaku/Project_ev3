#ifndef	__LTIN_RECVTABLE_H__
#define	__LTIN_RECVTABLE_H__

/***** インクルード *****/
#include "ltin.h"

/***** テーブル *****/
S_LT_RECV_TABLE T_LT_RECV_TABLE[] =
{
	/* MSGID							,	RecvFunc					*/
	{ E_MSGID_LT_TIMER_RES				,	lt_rcv_Timer_res			},
	{ E_MSGID_BT_WUPCHK_RES				,	lt_rcv_Wupchk_res			},
	{ E_MSGID_LD_WUPCHK_RES				,	lt_rcv_Wupchk_res			},
	{ E_MSGID_BT_STOP_RES				,	lt_rcv_Stop_res				},
	{ E_MSGID_LD_STOP_RES				,	lt_rcv_Stop_res				},
	{ E_MSGID_LT_CENTERBUTTON_REQ		,	lt_rcv_CenterButton_req		},
	{ E_MSGID_BT_CHGCALIBRATION_RES		,	lt_rcv_ChgCalibration_res	},
	{ E_MSGID_BT_REMOTESTART_RES		,	lt_rcv_RemoteStart_res		},
	{ E_MSGID_BT_SETLOG_LOGLAST_RES		,	lt_rcv_setLog_LastLog_res	},
	{ E_MSGID_LD_SETLOG_LOGLAST_RES		,	lt_rcv_setLog_LastLog_res	},
	{ E_MSGID_LD_STALOGDUMP_RES			,	lt_rcv_staLogDump_res		},
	{ E_MSGID_LD_CHGLOGDUMP_RES			,	lt_rcv_chgLogDump_res		},
	{ E_MSGID_LD_ENDLOGDUMP_RES			,	lt_rcv_endLogDump_res		},

	/* ここより上に定義すること */
	{ E_MSGID_LT_TEST_REQ				,	lt_rcv_test_req				},
	{ E_MSGID_LT_TOUCHBUTTON_REQ		,	lt_rcv_TouchButton_req		},
	{ E_MSGID_LT_BACKBUTTON_REQ			,	lt_rcv_BackButton_req		},
	{ E_MSGID_LT_UPBUTTON_REQ			,	lt_rcv_UpButton_req			},
	{ E_MSGID_LT_DOWNBUTTON_REQ			,	lt_rcv_DownButton_req		},
	{ E_MSGID_LT_LEFTBUTTON_REQ			,	lt_rcv_LeftButton_req		},
	{ E_MSGID_LT_RIGHTBUTTON_REQ		,	lt_rcv_RightButton_req		},
};

#endif	/* __LTIN_RECVTABLE_H__ */
