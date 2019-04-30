#include "tm.h"
#include "tmin.h"

void TM_startup( void )
{
	tm_startup();
	
	return;
}

void TM_main( void )
{
	tm_main();
	
	return;
}

void TM_main_debug( void )
{
	tm_main_debug();
	
	return;
}

int TM_cre_Timer( S_TM_TIMERINFO* spTimerInfo )
{
	int iRet = D_TM_NG;
	iRet = tm_cre_Timer( spTimerInfo );
	
	return iRet;
}

int TM_del_Timer( int iId )
{
	int iRet = D_TM_NG;
	iRet = tm_del_Timer( iId );
	
	return iRet;
}

int TM_sta_Timer( int iId )
{
	int iRet = D_TM_NG;
	iRet = tm_sta_Timer( iId );
	
	return iRet;
}

int TM_stp_Timer( int iId )
{
	int iRet = D_TM_NG;
	iRet = tm_stp_Timer( iId );
	
	return iRet;
}
