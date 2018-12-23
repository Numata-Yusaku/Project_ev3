#ifndef	__TASK_H__
#define	__TASK_H__

/***** インクルード *****/
#include "task_msgid.h"
#include "task_msgdata.h"

/***** 定数 *****/
#define	D_TASK_OK				(0)
#define	D_TASK_NG				(-1)

#define	D_TASK_MODE_ON			(1)
#define	D_TASK_MODE_OFF			(0)

#define	D_TASK_QUE_MAX			(256)

/* タスクサイクル */
#define	D_TASK_CYCLE_LT			(4)
#define	D_TASK_CYCLE_BT			(1000)
#define	D_TASK_CYCLE_LD			(1000)

enum EN_TASK_MSGDIR
{
	E_TASK_MSGDIR_SEND = 0,
	E_TASK_MSGDIR_RECV,
};

/***** 構造体 *****/
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
/***** 関数プロトタイプ *****/
void TASK_init( void );
void TASK_sleep( int iCycle );

/* イベント */
int TASK_msgsend( int iTask, S_MSG_DATA* spPara );
int TASK_msgrecv( int iTask, S_MSG_DATA* spPara );

/***** テーブル *****/


#endif	/* __TASK_H__ */
