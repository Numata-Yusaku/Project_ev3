#include "TimeMng.h"

/*** 時間管理機能 ***/
/*** システム時刻管理 ***/
/********************************************************/
/* システム時刻の参照									*/
/********************************************************/
int TSI_TimeMng_get_tim( unsigned long int* uiSystime )
{
	int iRet = D_TSI_OK;
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)get_tim( (SYSTIM*)uiSystime );
#endif	/* __VC_DEBUG__ */
	return iRet;
}

/*** 周期ハンドラ ***/
/*** アラームハンドラ ***/
/*** オーバランハンドラ ***/




