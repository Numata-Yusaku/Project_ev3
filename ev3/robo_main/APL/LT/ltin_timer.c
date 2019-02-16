#include "ltin.h"
#include "ltin_timertable.h"


/* �N������ */
int lt_cre_Timer( int iTimerId )
{
	int iRet = D_LT_NG;
	int iLoop = 0;
	int iNum = 0;
	S_TM_TIMERINFO* psTable = (S_TM_TIMERINFO*)NULL;
	S_TM_TIMERINFO stTimerInfo;
	
	/* ������ */
	memset( &stTimerInfo, 0x00, sizeof(S_TM_TIMERINFO) );
	
	/* ��M�e�[�u���ݒ� */
	psTable =T_LT_TIMER_TABLE;
	if((S_TM_TIMERINFO*)NULL == psTable )
	{
		return iRet;
	}
	
	/* ��M�e�[�u���v�f���擾 */
	iNum = sizeof( T_LT_TIMER_TABLE ) / sizeof( S_TM_TIMERINFO );
	if( 0 >= iNum )
	{
		return iRet;
	}

	for( iLoop = 0; iLoop < iNum; iLoop++ )
	{
		if( iTimerId == psTable[iLoop].iId )
		{
			/* �f�[�^�ݒ� */
			stTimerInfo.iId = psTable[iLoop].iId;
			stTimerInfo.iCycle = psTable[iLoop].iCycle;
			stTimerInfo.pFunc = (F_TM_CALLBACKFUNCPTR)psTable[iLoop].pFunc;
			
			/* �^�C�}���� */
			iRet = TM_cre_Timer( &stTimerInfo );
			
			break;
		}
	}
	
	return iRet;
}

int lt_del_Timer( int iTimerId )
{
	int iRet = D_LT_NG;
	
	iRet = TM_del_Timer( iTimerId );
	
	return iRet;
}

int lt_sta_Timer( int iTimerId )
{
	int iRet = D_LT_NG;
	
	iRet = TM_sta_Timer( iTimerId );
	
	return iRet;
}

/* �^�C�}�R�[���o�b�N�֐� */
void lt_WupChkTimer_CallBack( void )
{
	S_LT_TIMERINFO stTimerInfo;
	
	memset( &stTimerInfo, 0x00, sizeof(S_LT_TIMERINFO) );
	
	stTimerInfo.iTimerId = E_TIMERID_LT_WUPCHK;
	
	lt_send_Timer_res( &stTimerInfo );
	
	return;
}


void lt_ButtonTimer_CallBack(void)
{
	S_LT_TIMERINFO stTimerInfo;
	S_LT* spLt = (S_LT*)NULL;

	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if ((S_LT*)NULL == spLt)
	{
		return;
	}

	memset(&stTimerInfo, 0x00, sizeof(S_LT_TIMERINFO));

	stTimerInfo.iTimerId = E_TIMERID_BUTTON_WAIT_TIMER;

	lt_send_Timer_res(&stTimerInfo);

	spLt->button_valid = D_LT_TRUE;

	return;


}

