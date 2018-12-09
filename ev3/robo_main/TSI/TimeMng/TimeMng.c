#include "TimeMng.h"

/*** 時間管理機能 ***/
/*** システム時刻管理 ***/
/********************************************************/
/* システム時刻の参照									*/
/********************************************************/
int TSI_TimeMng_get_tim( unsigned long int* uiSystime )
{
	int iRet = D_TSI_OK;
#if	(__TARGET_EV3__)
	iRet = (int)get_tim( (SYSTIM*)uiSystime );
#endif	/* __TARGET_EV3__ */
	return iRet;
}

/*** 周期ハンドラ ***/
/*** アラームハンドラ ***/
/*** オーバランハンドラ ***/




