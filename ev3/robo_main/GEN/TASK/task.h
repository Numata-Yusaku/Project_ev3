#ifndef	__TASK_H__
#define	__TASK_H__

/***** �C���N���[�h *****/
#include "task_msgid.h"

/***** �萔 *****/
#define	D_TASK_OK				(0)
#define	D_TASK_NG				(-1)

#define	D_TASK_MODE_ON			(1)
#define	D_TASK_MODE_OFF			(0)

#define	D_TASK_QUE_MAX			(256)

/* �^�X�N�T�C�N�� */
#define	D_TASK_CYCLE_LT			(5)
#define	D_TASK_CYCLE_BT			(100)

enum EN_TASK_MSGDIR
{
	E_TASK_MSGDIR_SEND = 0,
	E_TASK_MSGDIR_RECV,
};

/***** �\���� *****/
typedef struct
{
	int		iMsgid;
	int		iSize;
	void*	vpPara;
}S_MSG_DATA;

typedef struct
{
	int		iFlag;
	int		iHead;
	int		iTail;
	int		iNum;
}S_MSG_STATUS;

typedef struct
{
	S_MSG_STATUS stStatus;
	S_MSG_DATA stData[D_TASK_QUE_MAX];
}S_MSG_QUE;
/***** �֐��v���g�^�C�v *****/
void TASK_init( void );
void TASK_sleep( int iCycle );

/* �C�x���g */
int TASK_msgsend( int iTask, S_MSG_DATA* spPara );
int TASK_msgrecv( int iTask, S_MSG_DATA* spPara );

/***** �e�[�u�� *****/


#endif	/* __TASK_H__ */
