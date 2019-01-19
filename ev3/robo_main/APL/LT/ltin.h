#ifndef	__LTIN_H__
#define	__LTIN_H__

/***** インクルード *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* GEN */
#include "tm.h"

/* LT */
#include "lt.h"

/***** 定数 *****/
#define	D_LT_FLAG_ON		(1)
#define	D_LT_FLAG_OFF		(0)

#define	D_LT_TRUE			(1)
#define	D_LT_FALSE			(0)

#define	D_LT_NOTRETRY		(0)
#define	D_LT_RETRY			(1)

/* Wait */
#define	D_LT_CALIBRATEEND_WAIT					(100)

/* クライアント送信満了カウンタ */
#define	D_LT_CLIENTSENDTIME_GYRO				( 1000 / ( D_TASK_CYCLE_BT ) )

/* サンプリング期間 */
/* 「クライアント送信が一定時間されなくなった 」= 「サンプリングが安定した」 */
#define	D_LT_SAMPLETIME_GYRO					( D_LT_CLIENTSENDTIME_GYRO * 50 )

/* 転倒タイムアウト */
#define	D_LT_FALLDOWNTIME						( 1000 / ( D_TASK_CYCLE_LT ) )

/* ログファイル */
//#define	D_LT_FILENAME_STATUSLOG					"OutData/StatusLog_Lt.csv"
#define	D_LT_FILENAME_CALIBRATELOG				"OutData/CalibrateLog.csv"
#define	D_LT_FILENAME_SYSTEMLOG					"OutData/SystemLog.csv"

#define	D_LT_BUFFNUM_STATUSLOG					D_TASK_BUFFNUM_STATUSLOG
#define	D_LT_BUFFNUM_CALIBRATELOG				D_TASK_BUFFNUM_CALIBRATELOG
#define	D_LT_BUFFNUM_SYSTEMLOG					D_TASK_BUFFNUM_SYSTEMLOG

/*** ログ出力 ***/
#if	(__TARGET_EV3__)
/* ログファイル */
#define	D_LT_LOGMODE_STATUS						(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_STATUS_TIME				(D_LT_FLAG_ON)

#define	D_LT_LOGMODE_CALIBRATE					(D_LT_FLAG_OFF)

#define	D_LT_LOGMODE_SYSTEM						(D_LT_FLAG_OFF)
#define	D_LT_LOGMODE_SYSTEM_BALANCEINFO			(D_LT_FLAG_OFF)
#define	D_LT_LOGMODE_SYSTEM_BALANCECONTROL		(D_LT_FLAG_ON)

/* シリアルログ */
#define	D_LT_LOGMODE_GYRO						(D_LT_FLAG_OFF)
#else	/* __TARGET_EV3__ */
/* ログファイル */
#define	D_LT_LOGMODE_STATUS						(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_STATUS_TIME				(D_LT_FLAG_ON)

#define	D_LT_LOGMODE_CALIBRATE					(D_LT_FLAG_ON)

#define	D_LT_LOGMODE_SYSTEM						(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_SYSTEM_BALANCEINFO			(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_SYSTEM_BALANCECONTROL		(D_LT_FLAG_ON)

/* シリアルログ */
#define	D_LT_LOGMODE_GYRO						(D_LT_FLAG_OFF)
#endif	/* __TARGET_EV3__ */


/* 音響 */
#define	D_LT_TONE_VOLUME				(1)		/* 音量 */
#define	D_LT_TONE_DURATION				(100)	/* 音響継続時間 */

/* 尻尾 */
#define	D_LT_TAIL_CALIBRATE_DEGREES		(88)	/* 尻尾回転角度 */
#define	D_LT_TAIL_CALIBRATE_SPEED		(10)	/* 尻尾回転速度 */

#define	D_LT_TAIL_STANDUP_KICK_DEGREES	(10)
#define	D_LT_TAIL_STANDUP_BACK_DEGREES	(D_LT_TAIL_CALIBRATE_DEGREES + D_LT_TAIL_STANDUP_KICK_DEGREES)
#define	D_LT_TAIL_STANDUP_SPEED			(50)

#define	D_LT_RECVDATA_SIZE				(4)		/* 受信データサイズ */

/* 色 */
#define	D_LT_COLORSENSOR_REFLECT_BLACK		(0)		/* 黒 */
#define	D_LT_COLORSENSOR_REFLECT_WHITE		(55)	/* 白 */

/* 超音波センサ */
#define	D_LT_SONAR_ARERT_NON_OBSTRUCTION	(0)	/* 障害なし */
#define	D_LT_SONAR_ARERT_OBSTRUCTION		(1)	/* 障害あり */

#define D_LT_SONAR_ALERT_DISTANCE			(30) /* 超音波センサによる障害物検知距離[cm] */

/*** 走行指令値 ***/
/* 前後進指令 */
#define	D_LT_FORWORD_LOWSPEED				(40)
#define	D_LT_FORWORD_PAUSE					(40)

/* PWM */
#define	D_LT_PWM_MAX						(100)
#define	D_LT_PWM_MIN						(-100)

/* 旋回指令 */
#define	D_LT_TURN_STOP						(0)		/* 旋回しない */
#define	D_LT_TURN_RUN						(1)		/* 旋回する */
#define	D_LT_TURN_RIGHT						(-20)	/* 旋回する：右旋回 */
#define	D_LT_TURN_LEFT						(20)	/* 旋回する：右旋回 */

#define rt_SATURATE(sig,ll,ul)	(((sig) >= (ul)) ? (ul) : (((sig) <= (ll)) ? (ll) : (sig)) )

/* バックラッシュ */
#define	D_LT_BACKLASH_HALF		(4)			/* バックラッシュの半分[deg] */

/* ジャイロオフセット */
#define	D_LT_GYRO_OFFSET		(0)

/*** ライントレース制御値 ***/
#define	D_LT_LINETRACE_P		(1.2F)
#define	D_LT_LINETRACE_I		(0.0F)
#define	D_LT_LINETRACE_D		(0.3F)

#define D_LT_KPID_EDGE_FACTOR	(-1)	/* ライントレース方向 1 or -1 */
#define D_LT_KPID_TURN_LIMIT	(100)	/* 旋回指示値 限界値 */

/*** バランス制御値 ***/
#define	D_LT_CMD_MAX			(100.0F)			/* 前進/旋回命令絶対最大値 */
#define	D_LT_DEG2RAD			(0.01745329238F)	/* 角度単位変換係数(=pi/180) */
#define	D_LT_EXEC_PERIOD		(0.00500000000F)	/* バランス制御実行周期(秒) */

#define	D_LT_A_D				(0.8F)				/* ローパスフィルタ係数(左右車輪の平均回転角度用) */
#define	D_LT_A_R				(0.996F)			/* ローパスフィルタ係数(左右車輪の目標平均回転角度用) */

#if 1	/* ゲイン調整 */
/* 状態フィードバック係数 */
/* ***2018年度*** */
#define	D_LT_K_F1				(-5.0F)			/* 車輪回転角度係数 */
#define	D_LT_K_F2				(-40.0F)		/* 車体傾斜角度係数 */
#define	D_LT_K_F3				(-2.0F)			/* 車輪回転角速度係数 */
#define	D_LT_K_F4				(-4.0F)			/* 車体傾斜角速度係数 */

#define	D_LT_K_I				(-0.2F)			/* サーボ制御用積分フィードバック係数 */
#define	D_LT_K_PHIDOT			(25.0F*2.75F)	/* 車体目標旋回角速度係数 */
#define	D_LT_K_THETADOT			(6.00F)			/* モータ目標回転角速度係数 */

#define	D_LT_BATTERY_GAIN		(0.001089F)		/* PWM出力算出用バッテリ電圧補正係数 */
#define	D_LT_BATTERY_OFFSET		(0.625F)		/* PWM出力算出用バッテリ電圧補正オフセット */

#define D_LT_P_GAIN					(2.5F)		/* 完全停止用モーター制御比例係数 */
#define D_LT_PWM_ABS_MAX			(60)		/* 完全停止用モーター制御PWM絶対最大値 */
#else	/* ゲイン調整 */
:/* サンプル初期値 */
:/* 状態フィードバック係数 */
:#define	D_LT_K_F1				(-0.86526F)			/* 車輪回転角度係数 */
:#define	D_LT_K_F2				(-30.73965F)		/* 車体傾斜角度係数 */
:#define	D_LT_K_F3				(-1.14828F*0.70F)	/* 車輪回転角速度係数 */
:#define	D_LT_K_F4				(-2.29757F)			/* 車体傾斜角速度係数 */
:#define	D_LT_K_I				(-0.44721F)			/* サーボ制御用積分フィードバック係数 */
:#define	D_LT_K_PHIDOT			(25.0F*2.75F)		/* 車体目標旋回角速度係数 */
:#define	D_LT_K_THETADOT			(6.00F)				/* モータ目標回転角速度係数 */

:#define	D_LT_BATTERY_GAIN		(0.001089F)			/* PWM出力算出用バッテリ電圧補正係数 */
:#define	D_LT_BATTERY_OFFSET		(0.625F)			/* PWM出力算出用バッテリ電圧補正オフセット */

:#define D_LT_P_GAIN				(2.5F)				/* 完全停止用モーター制御比例係数 */
:#define D_LT_PWM_ABS_MAX			(60)				/* 完全停止用モーター制御PWM絶対最大値 */
#endif	/* ゲイン調整 */

/* デバッグ用 */
extern float debug_pre_angle;
extern int button_valid;

enum EN_LT_STATUS
{
	E_LT_STATUS_READY = 0,			/* 起動準備中 */
	E_LT_STATUS_IDLE,				/* 起動中 */
	E_LT_STATUS_CALIBLATE_GYRO,		/* キャリブレーション中(ジャイロ) */
	E_LT_STATUS_CALIBLATE_TAIL,		/* キャリブレーション中(尻尾) */
	E_LT_STATUS_CALIBLATE_BLACK,	/* キャリブレーション中(黒) */
	E_LT_STATUS_CALIBLATE_WHITE,	/* キャリブレーション中(白) */
	E_LT_STATUS_CORRECT_ANGLE_CALIB,/* 姿勢角を調整開始初期化処理待ち */
	E_LT_STATUS_CORRECT_ANGLE_WAIT,	/* 姿勢角を調整開始指示待ち中*/
	E_LT_STATUS_CORRECTING_ANGLE,	/* 姿勢角を調整中*/
//	E_LT_STATUS_WAITING,			/* 待機中 */
	E_LT_STATUS_RUN_STANDUP,		/* 走行中(起動) */
	E_LT_STATUS_RUN_LOWSPEED,		/* 走行中(低速) */
	E_LT_STATUS_RUN_PAUSE,			/* 走行中(停止) */
	E_LT_STATUS_STOP_WAIT,			/* 走行体完全停止待ち */
	E_LT_STATUS_STOP,				/* 走行体完全停止 */
	
	/* ここより上に定義すること */
	E_LT_STATUS_INVALID = -1
};

enum EN_LT_WUPSTATE
{
	E_LT_WUPSTATE_READY = 0,		/* 未起動 */
	E_LT_WUPSTATE_WAIT,				/* 応答待ち */
	E_LT_WUPSTATE_DONE,				/* 応答完了 */
	
	/* ここより上に定義すること */
	E_LT_WUPSTATE_INVALID = -1
};

/* WUPCHK管理モジュール */
enum EN_LT_WUPCHK
{
	E_LT_WUPCHK_BT = 0,
	E_LT_WUPCHK_LD,

	/* ここより上に定義すること */
	E_LT_WUPCHK_NUM
};

/* STOP管理モジュール */
enum EN_LT_STOP
{
	E_LT_STOP_BT = 0,
	E_LT_STOP_LD,

	/* ここより上に定義すること */
	E_LT_STOP_NUM
};

enum EN_LT_PARTS
{
	E_LT_PARTS_TOUCH_SENSOR = 1,
	E_LT_PARTS_COLOR_SENSOR,
	E_LT_PARTS_GYRO_SENSOR,
	E_LT_PARTS_SONAR_SENSOR,
	E_LT_PARTS_LEFT_MOTOR,
	E_LT_PARTS_RIGHT_MOTOR,
	E_LT_PARTS_TAIL_MOTOR,

	/* ここより上に定義すること */
	E_LT_PARTS_NONE = 0,			/* 未設定 */
};

/* クライアント送信カウンタ */
enum EN_LT_CLIENTSEND
{
	E_LT_CLIENTSEND_GYRO = 0,
	E_LT_CLIENTSEND_COLOR,

	/* ここより上に定義すること */
	E_LT_CLIENTSEND_NUM
};

/***** 構造体 *****/
typedef void( *F_LT_RECVFUNCPTR )(S_MSG_DATA* spRecv);

/* タイマー情報 */
typedef struct
{
	int iTimerId;
}S_LT_TIMERINFO;

/* センサー */
typedef struct
{
	int iTouch;
	int iColor;
	int iGyro;
	int iSonar;
}S_LT_PORT_SENSOR;

/* モータ */
typedef struct
{
	int iLeftWheel;
	int iRightWheel;
	int iTail;
}S_LT_PORT_MOTOR;

/* ポート */
typedef struct
{
	S_LT_PORT_SENSOR iSensor;
	S_LT_PORT_MOTOR iMotor;
}S_LT_PORT;

/* カラーセンサ */
typedef struct
{
	int iColor;
	int iReflect;
}S_LT_COLORINFO;

/* キャリブレーション情報 */
typedef struct
{
	int iGyro;
	S_LT_COLORINFO stBlack;
	S_LT_COLORINFO stWhite;
}S_LT_CALIBRATEINFO;

/* バランス制御情報 */
typedef struct
{
	int iIntegral;
	int iDeviation;
}S_LT_LINETRACEINFO;

/* バランス制御情報 */
typedef struct
{
	float	fErr_theta;			/* 左右車輪の平均回転角度(θ)目標誤差状態値 */
	float	fPsi;				/* 車体ピッチ角度(ψ)状態値 */
	float	fThetaLpf;			/* 左右車輪の平均回転角度(θ)状態値 */
	float	fThetaRef;			/* 左右車輪の目標平均回転角度(θ)状態値 */
	float	fThetadotCmdLpf;	/* 左右車輪の目標平均回転角速度(dθ/dt)状態値 */
}S_LT_BALANCEINFO;

/* バランスコントロール */
typedef struct
{
	float			fCmdForward;		/* 前後進命令値		100(前進最大)～100(後進最大) */
	float			fCmdTurn;			/* 旋回命令値		100(右旋回最大)～-100(左旋回最大) */
	float			fGyro;				/* ジャイロセンサ値 */
	float			fGyroOffset;		/* ジャイロセンサオフセット値 */
	float			fThetaMLeft;		/* 左モータエンコーダ値[度] */
	float			fThetaMRight;		/* 右モータエンコーダ値[度] */
	float			fBattery;			/* バッテリ電圧値[mV] */
	signed char		scPwmLeft;			/* 左モータ PWM 出力値 */
	signed char		scPwmRight;			/* 右モータ PWM 出力値 */
}S_LT_BALANCE_CONTROL;

/* ステータスログ */
typedef struct
{
	unsigned long ulTime;		/* 経過時刻(msec) */
	int iStatus;				/* 状態 */
}S_LT_LOGDATA_STATUSLOG;

typedef struct
{
	int							iLogNum;
	S_LT_LOGDATA_STATUSLOG		stLog[D_LT_BUFFNUM_STATUSLOG];
}S_LT_LOGINFO_STATUSLOG;

typedef struct
{
	int							iLogNum;
	S_LT_CALIBRATEINFO			stLog[D_TASK_BUFFNUM_STATUSLOG];
}S_LT_LOGINFO_CALIBRATELOG;

typedef struct
{
	S_LT_BALANCEINFO			stBalanceInfo;
	S_LT_BALANCE_CONTROL		stBacanceControl;
}S_LT_LOGDATA_SYSTEMLOG;

typedef struct
{
	int							iLogNum;
	S_TASK_LOGDATA_SYSTEMLOG	stLog[D_TASK_BUFFNUM_STATUSLOG];
}S_LT_LOGINFO_SYSTEMLOG;

/* ログ情報 */
typedef struct
{
	S_LT_LOGINFO_STATUSLOG		stStatusLog;
	S_LT_LOGINFO_CALIBRATELOG	stCalibrateLog;
	S_LT_LOGINFO_SYSTEMLOG		stSystemLog;
}S_LT_LOGINFO;

/* 常駐領域 */
typedef struct
{
	int							iStatus;
	int							iWupStatus;
	int							iWupChk[E_LT_WUPCHK_NUM];
	int							iStopChk[E_LT_STOP_NUM];
	int							iFallDownCount;
	int							iClientSendCount[E_LT_CLIENTSEND_NUM];
	S_LT_PORT					stPort;
	S_LT_CALIBRATEINFO			stCalibrateInfo;
	S_LT_CALIBRATEINFO			stOldCalibrateInfo;
	S_LT_LINETRACEINFO			stLineTraceInfo;
	S_LT_BALANCEINFO			stBalanceInfo;					/* バランス制御情報 */
	S_LT_BALANCE_CONTROL		stBacanceControl;
	S_LT_LOGINFO				stLogInfo;
}S_LT;

typedef struct
{
	int		iMsgId;
	void*	func;
}S_LT_RECV_TABLE;

/* ポート情報 */
typedef struct
{
	int		iParts;
	int		iPort;
	int		iType;
}S_LT_PORTINFO;

/***** 関数プロトタイプ *****/

/*** ltin_recv.c **/
/* startup */
void lt_startup( void );
void lt_main( void );
void lt_main_debug( void );
void lt_init( void );
void lt_shutdown( void );

/* global */
void lt_set_Global( void );
S_LT* lt_get_Global( void );

/* proc */
void lt_proc( void );
void lt_proc_Ready( void );
void lt_proc_Idle( void );
void lt_proc_CalibrateGyro( void );
void lt_proc_CalibrateTail( void );
void lt_proc_CalibrateBlack( void );
void lt_proc_CalibrateWhite( void );
void lt_proc_Correct_Calib(void);
void lt_proc_Correct_Wait( void );
void lt_proc_Correcting( void );
//void lt_proc_Waiting( void );
void lt_proc_StandUp( void );
void lt_proc_LowSpeed( void );
void lt_proc_Pause( void );
void lt_proc_StopWait( void );
void lt_proc_Stop( void );

/* port */
void lt_set_Port( void );
void lt_set_SensorPort( void );
int lt_get_SensorPort( int iParts );
void lt_set_MotorPort( void );
int lt_get_MotorPort( int iParts );

/* WUPCHK */
int lt_chk_WupChkRetry( void );
int lt_get_WupchkNum( void );

/* calibrate */
void lt_Caliblate( void );
void lt_set_CalibrateGyro( void );
void lt_set_CalibrateBlack( void );
void lt_set_CalibrateWhite( void );

/* running */
void lt_Running( int iForwardLevel, int iTurnMode );
int lt_get_RunningTurnDir( void );
int lt_get_ControlLedValiable( int iDeviation );

/* other I/F */
int lt_get_SonarAlert( void );
int lt_get_StopState( void );

/* per_angle_calculation */
float calc_pre_angle( int mode );

/*** ltin_recv.c **/
/* FrameWork */
void lt_recv( S_MSG_DATA* spRecv );
F_LT_RECVFUNCPTR lt_get_RecvFunc( int iMsgId );

/* RecvFunc */
void lt_rcv_test_req( S_MSG_DATA* spRecv );					/* テスト */
void lt_rcv_Timer_res( S_MSG_DATA* spRecv );				/* タイマーコールバック受信 */
void lt_rcv_TouchButton_req( S_MSG_DATA* spRecv );			/* キーボード：TouchButton押下 */
void lt_rcv_BackButton_req( S_MSG_DATA* spRecv );			/* キーボード：BackButton押下 */
void lt_rcv_UpButton_req( S_MSG_DATA* spRecv );				/* キーボード：UpButton押下 */
void lt_rcv_DownButton_req( S_MSG_DATA* spRecv );			/* キーボード：DownButton押下 */
void lt_rcv_LeftButton_req( S_MSG_DATA* spRecv );			/* キーボード：LeftButton押下 */
void lt_rcv_RightButton_req( S_MSG_DATA* spRecv );			/* キーボード：RightButton押下 */
void lt_rcv_CenterButton_req( S_MSG_DATA* spRecv );			/* キーボード：CenterButton押下 */
void lt_rcv_Wupchk_res( S_MSG_DATA* spRecv );				/* 起動 */
void lt_rcv_Stop_res( S_MSG_DATA* spRecv );					/* 停止 */
void lt_rcv_ChgCalibration_res( S_MSG_DATA* spRecv );		/* キャリブレーション更新 */
void lt_rcv_RemoteStart_res( S_MSG_DATA* spRecv );			/* リモートスタート */

/*** ltin_send.c **/
void lt_send_test_res( S_MSG_DATA* spSend );								/* テスト */
void lt_send_Timer_res( S_LT_TIMERINFO* spSend );							/* タイマーコールバック受信 */
void lt_send_Wupchk_req( void );											/* 起動 */
void lt_send_Wupchk_req_Retry( void );										/* 起動リトライ */
void lt_send_Wupchk_bt_req( void );											/* 起動：BT */
void lt_send_Wupchk_ld_req( void );											/* 起動：LD */
int lt_send_Stop_req( void );												/* 停止 */
void lt_send_Stop_bt_req( void );											/* 停止：BT */
void lt_send_Stop_ld_req( void );											/* 停止：LD */
void lt_send_ShutDown_res( void );											/* シャットダウン */
void lt_send_staCalibration_req( void );									/* キャリブレーション開始 */
void lt_send_endCalibration_req( void );									/* キャリブレーション終了 */
void lt_send_staRunning_req( void );										/* 走行開始 */
void lt_send_endRunning_req( void );										/* 走行停止 */
void lt_send_setClientSendGyro_req( S_TASK_SETCLIENTSEND_GYRO* spSend );	/* クライアント送信：ジャイロ */
void lt_send_setClientSendColor_req( void );								/* クライアント送信：カラー */
void lt_send_setLog_StatusLog_req( S_LT_LOGINFO_STATUSLOG* spSend );		/* ログ設定：ステータスログ */
void lt_send_setLog_CalibrateLog_req( S_LT_LOGINFO_CALIBRATELOG* spSend );	/* ログ設定：キャリブレーションログ */
void lt_send_setLog_SystemLog_req( S_LT_LOGINFO_SYSTEMLOG* spSend );		/* ログ設定：システムログ */


/*** ltin_timer.c ***/
int lt_cre_Timer( int iTimerId );
int lt_del_Timer( int iTimerId );
int lt_sta_Timer( int iTimerId );
void lt_WupChkTimer_CallBack( void );
void lt_ButtonTimer_CallBack( void );

/*** ltin_barance.c **/
void lt_balance_init( void );
void lt_balance_set_BalanceInfo( void );
void lt_balance_set_BacklashCancel( void );
int lt_balance_set_MotorPower( void );

/*** ltin_log.c **/
void lt_log_set_Calibratelog( void );
void lt_log_set_Systemlog( void );
void lt_log_set_Statuslog( void );

#endif	/* __LTIN_H__ */
