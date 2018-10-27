#ifndef	__BTIN_RECVTABLE_H__
#define	__BTIN_RECVTABLE_H__

/***** インクルード *****/
#include "btin.h"

/***** テーブル *****/
S_BT_RECV_TABLE T_BT_RECV_TABLE[] =
{
	/* MSGID								,	RecvFunc						*/
	{ E_MSGID_BT_WUPCHK_REQ					,	bt_rcv_Wupchk_req				},
	{ E_MSGID_BT_STOP_REQ					,	bt_rcv_Stop_req					},
	{ E_MSGID_BT_STACALIBRATION_REQ			,	bt_rcv_staCalibration_req		},
	{ E_MSGID_BT_ENDCALIBRATION_REQ			,	bt_rcv_endCalibration_req		},
	{ E_MSGID_BT_STARUNNING_REQ				,	bt_rcv_staRunning_req			},
	{ E_MSGID_BT_SETCLIENTSEND_GYRO_REQ		,	bt_rcv_setClientSendGyro_req	},
	{ E_MSGID_BT_SETCLIENTSEND_COLOR_REQ	,	bt_rcv_setClientSendColor_req	},

	/* ここより上に定義すること */
	{ E_MSGID_BT_TEST_REQ					,	bt_rcv_test_req					},
};

#endif	/* __BTIN_RECVTABLE_H__ */
