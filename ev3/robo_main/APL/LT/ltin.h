#ifndef	__LTIN_H__
#define	__LTIN_H__

/***** �C���N���[�h *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* LT */
#include "lt.h"

/***** �萔 *****/
#define	D_LT_FLAG_ON		(1)
#define	D_LT_FLAG_OFF		(0)

#define	D_LT_TRUE			(1)
#define	D_LT_FALSE			(0)

/* Wait */
#define	D_LT_CALIBRATEEND_WAIT					(100)

/* �N���C�A���g���M�����J�E���^ */
#define	D_LT_CLIENTSENDTIME_GYRO				( 1000 / ( D_TASK_CYCLE_BT ) )

/* �T���v�����O���� */
/* �u�N���C�A���g���M����莞�Ԃ���Ȃ��Ȃ��� �v= �u�T���v�����O�����肵���v */
#define	D_LT_SAMPLETIME_GYRO					( D_LT_CLIENTSENDTIME_GYRO * 50 )

/* �]�|�^�C���A�E�g */
#define	D_LT_FALLDOWNTIME						( 1000 / ( D_TASK_CYCLE_LT ) )

/* ���O�t�@�C�� */
#define	D_LT_FILENAME_STATUSLOG					"OutData/StatusLog_Lt.csv"
#define	D_LT_FILENAME_CALIBRATELOG				"OutData/CalibrateLog.csv"
#define	D_LT_FILENAME_SYSTEMLOG					"OutData/SystemLog.csv"

/*** ���O�o�� ***/
/* ���O�t�@�C�� */
#define	D_LT_LOGMODE_STATUS						(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_STATUS_TIME				(D_LT_FLAG_OFF)

#define	D_LT_LOGMODE_CALIBRATE					(D_LT_FLAG_ON)

#define	D_LT_LOGMODE_SYSTEM						(D_LT_FLAG_ON)
#define	D_LT_LOGMODE_SYSTEM_BALANCEINFO			(D_LT_FLAG_OFF)
#define	D_LT_LOGMODE_SYSTEM_BALANCECONTROL		(D_LT_FLAG_ON)

/* �V���A�����O */
#define	D_LT_LOGMODE_GYRO						(D_LT_FLAG_OFF)


/* ���� */
#define	D_LT_TONE_VOLUME				(1)		/* ���� */
#define	D_LT_TONE_DURATION				(100)	/* �����p������ */

/* �K�� */
#define	D_LT_TAIL_CALIBRATE_DEGREES		(88)	/* �K����]�p�x */
#define	D_LT_TAIL_CALIBRATE_SPEED		(10)	/* �K����]���x */

#define	D_LT_TAIL_STANDUP_KICK_DEGREES	(10)
#define	D_LT_TAIL_STANDUP_BACK_DEGREES	(D_LT_TAIL_CALIBRATE_DEGREES + D_LT_TAIL_STANDUP_KICK_DEGREES)
#define	D_LT_TAIL_STANDUP_SPEED			(50)

#define	D_LT_RECVDATA_SIZE				(4)		/* ��M�f�[�^�T�C�Y */

/* �F */
#define	D_LT_COLORSENSOR_REFLECT_BLACK		(0)		/* �� */
#define	D_LT_COLORSENSOR_REFLECT_WHITE		(55)	/* �� */

/* �����g�Z���T */
#define	D_LT_SONAR_ARERT_NON_OBSTRUCTION	(0)	/* ��Q�Ȃ� */
#define	D_LT_SONAR_ARERT_OBSTRUCTION		(1)	/* ��Q���� */

#define D_LT_SONAR_ALERT_DISTANCE			(30) /* �����g�Z���T�ɂ���Q�����m����[cm] */

/*** ���s�w�ߒl ***/
/* �O��i�w�� */
#define	D_LT_FORWORD_LOWSPEED				(0)
//#define	D_LT_FORWORD_LOWSPEED				(30)
#define	D_LT_FORWORD_PAUSE					(0)

/* PWM */
#define	D_LT_PWM_MAX						(100)
#define	D_LT_PWM_MIN						(-100)

/* ����w�� */
#define	D_LT_TURN_STOP						(0)		/* ���񂵂Ȃ� */
#define	D_LT_TURN_RUN						(1)		/* ���񂷂� */
#define	D_LT_TURN_RIGHT						(-20)	/* ���񂷂�F�E���� */
#define	D_LT_TURN_LEFT						(20)	/* ���񂷂�F�E���� */

#define rt_SATURATE(sig,ll,ul)	(((sig) >= (ul)) ? (ul) : (((sig) <= (ll)) ? (ll) : (sig)) )

/* �o�b�N���b�V�� */
#define	D_LT_BACKLASH_HALF		(4)			/* �o�b�N���b�V���̔���[deg] */

/* �W���C���I�t�Z�b�g */
#define	D_LT_GYRO_OFFSET		(0)

/*** �o�����X����l ***/
#define	D_LT_CMD_MAX			(100.0F)			/* �O�i/���񖽗ߐ�΍ő�l */
#define	D_LT_DEG2RAD			(0.01745329238F)	/* �p�x�P�ʕϊ��W��(=pi/180) */
#define	D_LT_EXEC_PERIOD		(0.00450000000F)	/* �o�����X������s����(�b) */

#define	D_LT_A_D				(0.8F)				/* ���[�p�X�t�B���^�W��(���E�ԗւ̕��ω�]�p�x�p) */
#define	D_LT_A_R				(0.996F)			/* ���[�p�X�t�B���^�W��(���E�ԗւ̖ڕW���ω�]�p�x�p) */

#if 1	/* �Q�C������ */
/* ��ԃt�B�[�h�o�b�N�W�� */
/* ***2018�N�x*** */
#define	D_LT_K_F1				(-5.0F)			/* �ԗ։�]�p�x�W�� */
#define	D_LT_K_F2				(-40.0F)		/* �ԑ̌X�Ίp�x�W�� */
#define	D_LT_K_F3				(-2.0F)			/* �ԗ։�]�p���x�W�� */
#define	D_LT_K_F4				(-4.0F)			/* �ԑ̌X�Ίp���x�W�� */

#define	D_LT_K_I				(-0.2F)			/* �T�[�{����p�ϕ��t�B�[�h�o�b�N�W�� */
#define	D_LT_K_PHIDOT			(25.0F*2.75F)	/* �ԑ̖ڕW����p���x�W�� */
#define	D_LT_K_THETADOT			(6.00F)			/* ���[�^�ڕW��]�p���x�W�� */

#define	D_LT_BATTERY_GAIN		(0.001089F)		/* PWM�o�͎Z�o�p�o�b�e���d���␳�W�� */
#define	D_LT_BATTERY_OFFSET		(0.625F)		/* PWM�o�͎Z�o�p�o�b�e���d���␳�I�t�Z�b�g */

#define D_LT_P_GAIN					(2.5F)		/* ���S��~�p���[�^�[������W�� */
#define D_LT_PWM_ABS_MAX			(60)		/* ���S��~�p���[�^�[����PWM��΍ő�l */
#else	/* �Q�C������ */
:/* �T���v�������l */
:/* ��ԃt�B�[�h�o�b�N�W�� */
:#define	D_LT_K_F1				(-0.86526F)			/* �ԗ։�]�p�x�W�� */
:#define	D_LT_K_F2				(-30.73965F)		/* �ԑ̌X�Ίp�x�W�� */
:#define	D_LT_K_F3				(-1.14828F*0.70F)	/* �ԗ։�]�p���x�W�� */
:#define	D_LT_K_F4				(-2.29757F)			/* �ԑ̌X�Ίp���x�W�� */
:#define	D_LT_K_I				(-0.44721F)			/* �T�[�{����p�ϕ��t�B�[�h�o�b�N�W�� */
:#define	D_LT_K_PHIDOT			(25.0F*2.75F)		/* �ԑ̖ڕW����p���x�W�� */
:#define	D_LT_K_THETADOT			(6.00F)				/* ���[�^�ڕW��]�p���x�W�� */

:#define	D_LT_BATTERY_GAIN		(0.001089F)			/* PWM�o�͎Z�o�p�o�b�e���d���␳�W�� */
:#define	D_LT_BATTERY_OFFSET		(0.625F)			/* PWM�o�͎Z�o�p�o�b�e���d���␳�I�t�Z�b�g */

:#define D_LT_P_GAIN				(2.5F)				/* ���S��~�p���[�^�[������W�� */
:#define D_LT_PWM_ABS_MAX			(60)				/* ���S��~�p���[�^�[����PWM��΍ő�l */
#endif	/* �Q�C������ */


enum EN_LT_STATUS
{
	E_LT_STATUS_READY = 0,			/* �N�������� */
	E_LT_STATUS_IDLE,				/* �N���� */
	E_LT_STATUS_CALIBLATE_GYRO,		/* �L�����u���[�V������(�W���C��) */
	E_LT_STATUS_CALIBLATE_TAIL,		/* �L�����u���[�V������(�K��) */
	E_LT_STATUS_CALIBLATE_BLACK,	/* �L�����u���[�V������(��) */
	E_LT_STATUS_CALIBLATE_WHITE,	/* �L�����u���[�V������(��) */
	E_LT_STATUS_WAITING,			/* �ҋ@�� */
	E_LT_STATUS_RUN_STANDUP,		/* ���s��(�N��) */
	E_LT_STATUS_RUN_LOWSPEED,		/* ���s��(�ᑬ) */
	E_LT_STATUS_RUN_PAUSE,			/* ���s��(��~) */
	E_LT_STATUS_STOP_WAIT,			/* ���s�̊��S��~�҂� */
	E_LT_STATUS_STOP,				/* ���s�̊��S��~ */
	
	/* ��������ɒ�`���邱�� */
	E_LT_STATUS_INVALID = -1
};

/* WUPCHK�Ǘ����W���[�� */
enum EN_LT_WUPCHK
{
	E_LT_WUPCHK_BT = 0,

	/* ��������ɒ�`���邱�� */
	E_LT_WUPCHK_NUM
};

/* STOP�Ǘ����W���[�� */
enum EN_LT_STOP
{
	E_LT_STOP_BT = 0,

	/* ��������ɒ�`���邱�� */
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

	/* ��������ɒ�`���邱�� */
	E_LT_PARTS_NONE = 0,			/* ���ݒ� */
};

/* �N���C�A���g���M�J�E���^ */
enum EN_LT_CLIENTSEND
{
	E_LT_CLIENTSEND_GYRO = 0,
	E_LT_CLIENTSEND_COLOR,

	/* ��������ɒ�`���邱�� */
	E_LT_CLIENTSEND_NUM
};

/***** �\���� *****/
typedef void( *F_LT_RECVFUNCPTR )(S_MSG_DATA* spRecv);

/* �Z���T�[ */
typedef struct
{
	int iTouch;
	int iColor;
	int iGyro;
	int iSonar;
}S_LT_PORT_SENSOR;

/* ���[�^ */
typedef struct
{
	int iLeftWheel;
	int iRightWheel;
	int iTail;
}S_LT_PORT_MOTOR;

/* �|�[�g */
typedef struct
{
	S_LT_PORT_SENSOR iSensor;
	S_LT_PORT_MOTOR iMotor;
}S_LT_PORT;

/* �J���[�Z���T */
typedef struct
{
	int iColor;
	int iReflect;
}S_LT_COLORINFO;

/* �L�����u���[�V������� */
typedef struct
{
	int iGyro;
	S_LT_COLORINFO stBlack;
	S_LT_COLORINFO stWhite;
}S_LT_CALIBRATEINFO;

/* �o�����X������ */
typedef struct
{
	float	fErr_theta;			/* ���E�ԗւ̕��ω�]�p�x(��)�ڕW�덷��Ԓl */
	float	fPsi;				/* �ԑ̃s�b�`�p�x(��)��Ԓl */
	float	fThetaLpf;			/* ���E�ԗւ̕��ω�]�p�x(��)��Ԓl */
	float	fThetaRef;			/* ���E�ԗւ̖ڕW���ω�]�p�x(��)��Ԓl */
	float	fThetadotCmdLpf;	/* ���E�ԗւ̖ڕW���ω�]�p���x(d��/dt)��Ԓl */
}S_LT_BALANCEINFO;

/* �o�����X�R���g���[�� */
typedef struct
{
	float			fCmdForward;		/* �O��i���ߒl		100(�O�i�ő�)�`100(��i�ő�) */
	float			fCmdTurn;			/* ���񖽗ߒl		100(�E����ő�)�`-100(������ő�) */
	float			fGyro;				/* �W���C���Z���T�l */
	float			fGyroOffset;		/* �W���C���Z���T�I�t�Z�b�g�l */
	float			fThetaMLeft;		/* �����[�^�G���R�[�_�l[�x] */
	float			fThetaMRight;		/* �E���[�^�G���R�[�_�l[�x] */
	float			fBattery;			/* �o�b�e���d���l[mV] */
	signed char		scPwmLeft;			/* �����[�^ PWM �o�͒l */
	signed char		scPwmRight;			/* �E���[�^ PWM �o�͒l */
}S_LT_BALANCE_CONTROL;

/* �풓�̈� */
typedef struct
{
	int							iStatus;
	int							iWupChk[E_LT_WUPCHK_NUM];
	int							iStopChk[E_LT_STOP_NUM];
	int							iFallDownCount;
	int							iClientSendCount[E_LT_CLIENTSEND_NUM];
	FILE*						fpStatusLog;
	FILE*						fpCalirateLog;
	FILE*						fpSystemLog;
	S_LT_PORT					stPort;
	S_LT_CALIBRATEINFO			stCalibrateInfo;
	S_LT_CALIBRATEINFO			stOldCalibrateInfo;
	S_LT_BALANCEINFO			stBalanceInfo;					/* �o�����X������ */
	S_LT_BALANCE_CONTROL		stBacanceControl;
}S_LT;

typedef struct
{
	int		iMsgId;
	void*	func;
}S_LT_RECV_TABLE;

/* �|�[�g��� */
typedef struct
{
	int		iParts;
	int		iPort;
	int		iType;
}S_LT_PORTINFO;

/***** �֐��v���g�^�C�v *****/

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
void lt_proc_Waiting( void );
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

/* calibrate */
void lt_Caliblate( void );
void lt_set_CalibrateGyro( void );
void lt_set_CalibrateBlack( void );
void lt_set_CalibrateWhite( void );

/* running */
void lt_Running( int iForwardLevel, int iTurnMode );
int lt_get_RunningTurnDir( void );

/* other I/F */
void lt_set_TailAngle( int iAngle );
int lt_get_SonarAlert( void );
int lt_get_StopState( void );

/*** ltin_recv.c **/
/* FrameWork */
void lt_recv( S_MSG_DATA* spRecv );
F_LT_RECVFUNCPTR lt_get_RecvFunc( int iMsgId );

/* RecvFunc */
void lt_rcv_test_req( S_MSG_DATA* spRecv );					/* �e�X�g */
void lt_rcv_TouchButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FTouchButton���� */
void lt_rcv_BackButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FBackButton���� */
void lt_rcv_UpButton_req( S_MSG_DATA* spRecv );				/* �L�[�{�[�h�FUpButton���� */
void lt_rcv_DownButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FDownButton���� */
void lt_rcv_LeftButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FLeftButton���� */
void lt_rcv_RightButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FRightButton���� */
void lt_rcv_CenterButton_req( S_MSG_DATA* spRecv );			/* �L�[�{�[�h�FCenterButton���� */
void lt_rcv_Wupchk_res( S_MSG_DATA* spRecv );				/* �N�� */
void lt_rcv_Stop_res( S_MSG_DATA* spRecv );					/* ��~ */
void lt_rcv_ChgCalibration_res( S_MSG_DATA* spRecv );		/* �L�����u���[�V�����X�V */
void lt_rcv_RemoteStart_res( S_MSG_DATA* spRecv );			/* �����[�g�X�^�[�g */

/*** ltin_send.c **/
void lt_send_test_res( S_MSG_DATA* spSend );								/* �e�X�g */
int lt_send_Wupchk_req( void );												/* �N�� */
void lt_send_Wupchk_bt_req( void );											/* �N���FBT */
int lt_send_Stop_req( void );												/* ��~ */
void lt_send_Stop_bt_req( void );											/* ��~�FBT */
void lt_send_ShutDown_res( void );											/* �V���b�g�_�E�� */
void lt_send_staCalibration_req( void );									/* �L�����u���[�V�����J�n */
void lt_send_endCalibration_req( void );									/* �L�����u���[�V�����I�� */
void lt_send_staRunning_req( void );										/* ���s�J�n */
void lt_send_endRunning_req( void );										/* ���s��~ */
void lt_send_setClientSendGyro_req( S_TASK_SETCLIENTSEND_GYRO* spSend );	/* �N���C�A���g���M�F�W���C�� */
void lt_send_setClientSendColor_req( void );								/* �N���C�A���g���M�F�J���[ */

/*** ltin_barance.c **/
void lt_balance_init( void );
void lt_balance_set_BalanceInfo( void );
void lt_balance_set_BacklashCancel( void );
int lt_balance_set_MotorPower( void );
void lt_balance_set_DummyMotorPower( void );

/*** ltin_log.c **/
void lt_log_Statuslog_open( void );
void lt_log_set_Calibratelog( void );
void lt_log_set_Systemlog( void );
void lt_log_set_Statuslog( void );
void lt_log_Calibratelog_open( void );
void lt_log_Systemlog_open( void );

#endif	/* __LTIN_H__ */
