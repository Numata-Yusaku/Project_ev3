#include "task.h"
#include "taskin.h"

void TASK_init( void )
{
	/* キューの初期化 */
	task_init_que();
	
	/* グローバル設定 */
	task_set_Global();
	
	/* ログファイル設定 */
	task_msglog_open();
	
	return;
}

void TASK_sleep( int iCycle )
{
	task_sleep( iCycle );
	
	return;
}

int TASK_msgsend( int iTask, S_MSG_DATA* spPara )
{
	int iRet = D_TASK_OK;
	
	iRet = task_msgsend( iTask, spPara );
	
	return iRet;
}

int TASK_msgrecv( int iTask, S_MSG_DATA* spPara )
{
	int iRet = D_TASK_OK;
	
	iRet = task_msgrecv( iTask, spPara );
	
	return iRet;
}
