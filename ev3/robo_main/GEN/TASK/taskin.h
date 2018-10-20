#ifndef	__TASKIN_H__
#define	__TASKIN_H__

/***** �C���N���[�h *****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "task.h"

/***** �萔 *****/
#define	D_TASK_MSGID_INVALID		(0x00000000)

/* ���O�o�� */
#if	(__VC_DEBUG__)
#define	D_TASK_FILENAME_MSGLOG		"./OutData/msglog.csv"
#else	/* __VC_DEBUG__ */
#define	D_TASK_FILENAME_MSGLOG		"./msglog.csv"
#endif	/* __VC_DEBUG__ */

#define	D_TASK_LOGMODE				(D_TASK_MODE_ON)

/***** �\���� *****/
/* �풓�̈� */
typedef struct
{
	FILE*	fpMsgLog;
}S_TASK;
/***** �֐��v���g�^�C�v *****/
/* startup */
void task_init_que( void );
void task_sleep( int iCycle );

/* global */
void task_set_Global( void );
S_TASK* task_get_Global( void );

/* Message */
int task_msgsend( int iTask, S_MSG_DATA* spPara );
int task_msgrecv( int iTask, S_MSG_DATA* spPara );

/* log */
void task_msglog_open( void );
void task_msglog( int iDir, int iTask, int iMsgId );

/***** �e�[�u�� *****/


#endif	/* __TASKIN_H__ */
