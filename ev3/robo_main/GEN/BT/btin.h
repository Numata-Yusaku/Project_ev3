#ifndef	__BTIN_H__
#define	__BTIN_H__

/***** �C���N���[�h *****/
/*** APL ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* BT */
#include "bt.h"

/***** �萔 *****/
#define	D_BT_FLAG_ON		(1)
#define	D_BT_FLAG_OFF		(0)

#define	D_BT_CHECK_OK		(1)
#define	D_BT_CHECK_NG		(0)

#define	D_BT_RECVDATA_SIZE	(128)

/* ���O�t�@�C�� */
#define	D_BT_FILENAME_STATUSLOG					"OutData/StatusLog_Bt.csv"

/*** ���O�o�� ***/
#define	D_BT_LOGMODE_STATUS						(D_BT_FLAG_ON)


enum EN_BT_STATUS
{
	E_BT_STATUS_READY = 0,		/* �N�������� */
	E_BT_STATUS_IDLE,			/* �N���� */
	E_BT_STATUS_CALIBLATE,		/* �L�����u���[�V������ */
	E_BT_STATUS_WAITING,		/* �ҋ@�� */	
	E_BT_STATUS_RUN,			/* ���s�� */
	E_BT_STATUS_STOP,			/* ��~�� */
	
	/* ��������ɒ�`���邱�� */
	E_BT_STATUS_INVALID = -1
};

/***** �\���� *****/
typedef void( *F_BT_RECVFUNCPTR )( S_MSG_DATA* spRecv );
typedef void( *F_BT_RECVCMDFUNCPTR )( char* cpRecvData, int iSize );

/* �풓�̈� */
typedef struct
{
	int iStatus;		/* �N���X�X�e�[�^�X */
	int iWupChk;
	FILE* fpBtFile;		/* Bluetoo�ʐM�|�[�g */
	FILE* fpStatusLog;
}S_BT;

typedef struct
{
	int iMsgId;
	void* func;
}S_BT_RECV_TABLE;

typedef struct
{
	char cCommand;
	int iSize;
	void* vpFunc;
}S_BT_MESSAGE_TABLE;

/***** �֐��v���g�^�C�v *****/
/* startup */
void bt_main( void );
void bt_init( void );
void bt_shutdown( void );

/* global */
void bt_set_Global( void );
S_BT* bt_get_Global( void );

/* proc */
void bt_proc( void );
void bt_proc_Ready( void );
void bt_proc_Calibrate( void );
void bt_proc_Waiting( void );

/*** btin_recv.c **/
/* FrameWork */
void bt_recv( S_MSG_DATA* spRecv );
F_BT_RECVFUNCPTR bt_get_RecvFunc( int iMsgId );

/* RecvFunc */
void bt_rcv_test_req( S_MSG_DATA* spRecv );							/* �e�X�g */
void bt_rcv_Wupchk_req( S_MSG_DATA* spRecv );						/* �N�� */
void bt_rcv_Stop_req( S_MSG_DATA* spRecv );							/* ��~ */
void bt_rcv_staCalibration_req( S_MSG_DATA* spRecv );				/* �L�����u���[�V�����J�n */
void bt_rcv_endCalibration_req( S_MSG_DATA* spRecv );				/* �L�����u���[�V�����I�� */
void bt_rcv_staRunning_req( S_MSG_DATA* spRecv );					/* ���s�J�n */
void bt_rcv_setClientSendGyro_req( S_MSG_DATA* spRecv );			/* �N���C�A���g���M�F�W���C�� */
void bt_rcv_setClientSendColor_req( S_MSG_DATA* spRecv );			/* �N���C�A���g���M�F�J���[ */

/*** btin_send.c **/
void bt_send_test_res( S_MSG_DATA* spSend );							/* �e�X�g */
void bt_send_Wupchk_res( void );										/* �N�� */
void bt_send_Stop_res( void );											/* ��~ */
void bt_send_chgCalibration_res( S_TASK_CHGCALIBRATION_RES* spSend );	/* �L�����u���[�V�����X�V */
void bt_send_RemoteStart_res( void );									/* �����[�g�X�^�[�g */

/*** btin_message.c **/
void bt_set_SerialMessage( char* cpSendData, int iSize );
int bt_get_SerialMessage( char* cpRecvData, int iSize );
void bt_check_SerialMessageRecv( void );
int bt_get_MessageSize( char cCmd );
F_BT_RECVCMDFUNCPTR bt_get_MessageRecvFunc( char cCmd );
int bt_check_SerialMessageCommand( char cVal );
int bt_check_SerialMessageNumber( char cVal );
/* RecvCmdFunc */
void bt_recvCmd_s( char* cpRecvData, int iSize );

/*** btin_log.c **/
void bt_log_Statuslog_open( void );
void bt_log_set_Statuslog( void );

#endif	/* __BTIN_H__ */
