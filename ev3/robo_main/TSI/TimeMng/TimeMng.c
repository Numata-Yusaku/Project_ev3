#include "TimeMng.h"

/*** 時間管理機能 ***/
/*** システム時刻管理 ***/
/********************************************************/
/* システム時刻の参照									*/
/********************************************************/
unsigned long TSI_TimeMng_get_tim( void )
{
	unsigned long ulTime =0;
#if	(__TARGET_EV3__)
	SYSTIM	stTime;
	get_tim(&stTime);
	ulTime = (unsigned long)stTime;
#endif	/* __TARGET_EV3__ */
	return ulTime;
}


/*** 周期ハンドラ ***/
/*** アラームハンドラ ***/
/*** オーバランハンドラ ***/




