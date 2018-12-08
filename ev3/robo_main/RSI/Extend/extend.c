#include "extend.h"

/*** font ***/

/********************************************************/
/* EV3用周期ハンドラの動作を開始する					*/
/********************************************************/
int RSI_extend_sta_cyc( signed int siCycId )
{
	int iRet = D_RSI_OK;
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sta_cyc( siCycId );
#endif	/* __VC_DEBUG__ */
	return iRet;
}

/********************************************************/
/* EV3用周期ハンドラの動作を停止する					*/
/********************************************************/
int RSI_extend_stp_cyc( signed int siCycId )
{
	int iRet = D_RSI_OK;
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sta_cyc( siCycId );
#endif	/* __VC_DEBUG__ */
	return iRet;
}
