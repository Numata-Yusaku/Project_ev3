#ifndef	__TASK_MSGDATA_H__
#define	__TASK_MSGDATA_H__

/*************************************************************/
/* MSGで送受信するデータの定義値／構造体を定義すること		 */
/*************************************************************/
#define	D_TASK_RECVDATA_SIZE			(4)
#define	D_TASK_BUFFNUM_STATUSLOG		(16)
#define	D_TASK_BUFFNUM_CALIBRATELOG		(1)
#define	D_TASK_BUFFNUM_SYSTEMLOG		(526)


/* キャリブレーションパラメータ通知 */
typedef struct
{
	int		iSize;
	char	aData[D_TASK_RECVDATA_SIZE];
	char	cCmd;
}S_TASK_CHGCALIBRATION_RES;

/* クライアント送信：GYRO */
typedef struct
{
	int	iGyro;
}S_TASK_SETCLIENTSEND_GYRO;

/*** ログ設定通知 ***/
/* 日時情報 */
typedef struct
{
	unsigned short	usYear;
	unsigned short	usMonth;
	unsigned short	usDay;
	unsigned short	usHour;
	unsigned short	usMinute;
	unsigned short	usSecond;
	unsigned short	usMilliSec;
}S_TASK_DAYTIME;

/* ステータスログ */
typedef struct
{
	S_TASK_DAYTIME	stDayTime;
	int				iStatus;	/* 状態 */
	int				iTaskId;
}S_TASK_LOGDATA_STATUSLOG;

typedef struct
{
	int							iLogNum;
	S_TASK_LOGDATA_STATUSLOG	stLog[D_TASK_BUFFNUM_STATUSLOG];
}S_TASK_LOGINFO_STATUSLOG;

/* キャリブレーションログ */
typedef struct
{
	int	iColor;
	int	iReflect;
}S_TASK_COLORINFO;

typedef struct
{
	int					iGyro;
	S_TASK_COLORINFO	stBlack;
	S_TASK_COLORINFO	stWhite;
}S_TASK_CALIBRATEINFO;

typedef struct
{
	S_TASK_DAYTIME				stDayTime;
	int							iLtStatus;
	int							iLogNum;
	S_TASK_CALIBRATEINFO		stCalibrateInfo;
}S_TASK_LOGDATA_CALIBRATELOG;

typedef struct
{
	int							iLogNum;
	S_TASK_LOGDATA_CALIBRATELOG	stLog[D_TASK_BUFFNUM_CALIBRATELOG];
}S_TASK_LOGINFO_CALIBRATELOG;

/* システムログ */
/* バランス制御情報 */
typedef struct
{
	float	fErr_theta;			/* 左右車輪の平均回転角度(θ)目標誤差状態値 */
	float	fPsi;				/* 車体ピッチ角度(ψ)状態値 */
	float	fThetaLpf;			/* 左右車輪の平均回転角度(θ)状態値 */
	float	fThetaRef;			/* 左右車輪の目標平均回転角度(θ)状態値 */
	float	fThetadotCmdLpf;	/* 左右車輪の目標平均回転角速度(dθ/dt)状態値 */
}S_TASK_BALANCEINFO;

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
}S_TASK_BALANCE_CONTROL;

typedef struct
{
	S_TASK_DAYTIME				stDayTime;
	int							iLtStatus;
	S_TASK_BALANCEINFO			stBalanceInfo;
	S_TASK_BALANCE_CONTROL		stBacanceControl;
}S_TASK_LOGDATA_SYSTEMLOG;

typedef struct
{
	int							iLogNum;
	S_TASK_LOGDATA_SYSTEMLOG	stLog[D_TASK_BUFFNUM_SYSTEMLOG];
}S_TASK_LOGINFO_SYSTEMLOG;

typedef struct
{
	int	iAllLogNum;
	int	iNowLogNo;
	int	iProgress;
}S_TASK_CHGLOGDUMP_RES;

#endif	/* __TASK_MSGDATA_H__ */
