#ifndef	__TASK_MSGID_H__
#define	__TASK_MSGID_H__

/***************************************************************/
/* MSGの定義は「REQ:奇数」「RES:偶数」となるように定義すること */
/***************************************************************/

/***** インクルード *****/

/***** 定数 *****/
enum EN_TASK_TASKID
{
	E_TASK_TASKID_MAIN = 0,
	/* GEN */
	E_TASK_TASKID_BT,
	/* APL */
	E_TASK_TASKID_LT,

	/* ここより上に定義すること */
	E_TASK_TASKID_NUM,
};

enum EN_MSGID_MAIN
{
	E_MSGID_MAIN_TEST_REQ =			( ( E_TASK_TASKID_MAIN << 24) | 0x00000001 ),
	E_MSGID_MAIN_TEST_RES,
	
	/* ここより上に定義すること */
	E_MSGID_MAIN_INVALID = 0x00000000,
};
/* GEN */
enum EN_MSGID_BT
{
	E_MSGID_BT_TEST_REQ =			( ( E_TASK_TASKID_BT << 24) | 0x00000001 ),
	E_MSGID_BT_TEST_RES,
	E_MSGID_BT_WUPCHK_REQ,
	E_MSGID_BT_WUPCHK_RES,
	E_MSGID_BT_STOP_REQ,
	E_MSGID_BT_STOP_RES,
	E_MSGID_BT_STACALIBRATION_REQ,
	E_MSGID_BT_STACALIBRATION_RES,
	E_MSGID_BT_CHGCALIBRATION_REQ,
	E_MSGID_BT_CHGCALIBRATION_RES,
	E_MSGID_BT_ENDCALIBRATION_REQ,
	E_MSGID_BT_ENDCALIBRATION_RES,
	E_MSGID_BT_REMOTESTART_REQ,
	E_MSGID_BT_REMOTESTART_RES,
	E_MSGID_BT_STARUNNING_REQ,
	E_MSGID_BT_STARUNNING_RES,
	E_MSGID_BT_ENDRUNNING_REQ,
	E_MSGID_BT_ENDRUNNING_RES,

	/* ここより上に定義すること */
	E_MSGID_BT_INVALID = 0x00000000,
};

/* APL */
enum EN_MSGID_LT
{
	E_MSGID_LT_TEST_REQ =			( ( E_TASK_TASKID_LT << 24) | 0x00000001 ),
	E_MSGID_LT_TEST_RES,
	E_MSGID_LT_WUPCHK_REQ,
	E_MSGID_LT_WUPCHK_RES,
	E_MSGID_LT_SHUTDOWN_REQ,
	E_MSGID_LT_SHUTDOWN_RES,
	E_MSGID_LT_TOUCHBUTTON_REQ,
	E_MSGID_LT_TOUCHBUTTON_RES,
	E_MSGID_LT_BACKBUTTON_REQ,
	E_MSGID_LT_BACKBUTTON_RES,
	E_MSGID_LT_UPBUTTON_REQ,
	E_MSGID_LT_UPBUTTON_RES,
	E_MSGID_LT_DOWNBUTTON_REQ,
	E_MSGID_LT_DOWNBUTTON_RES,
	E_MSGID_LT_LEFTBUTTON_REQ,
	E_MSGID_LT_LEFTBUTTON_RES,
	E_MSGID_LT_RIGHTBUTTON_REQ,
	E_MSGID_LT_RIGHTBUTTON_RES,
	E_MSGID_LT_CENTERBUTTON_REQ,
	E_MSGID_LT_CENTERBUTTON_RES,

	/* ここより上に定義すること */
	E_MSGID_LT_INVALID = 0x00000000,
};

/***** 構造体 *****/

/***** 関数プロトタイプ *****/

/***** テーブル *****/


#endif	/* __TASK_MSGID_H__ */
