#include <stdio.h>

#include "main.h"

/* MAIN */
void Main_task(intptr_t exinf )
{
	MAIN_init();
	MAIN_task();
	return;
}

void MAIN_ev3_cyc_run_LT(intptr_t exinf )
{
#if	(__TARGET_EV3__)
	act_tsk( LT_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

void MAIN_ev3_cyc_run_TM(intptr_t exinf )
{
#if	(__TARGET_EV3__)
	act_tsk( TM_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

/* BT */
void Bluetooth_task( intptr_t exinf )
{
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	BT_main();
	return;
}

/* TM */
void Time_task( intptr_t exinf )
{
#if	(__TARGET_EV3__)
	TM_main();
	ext_tsk();
#else	/* __TARGET_EV3__ */
	TASK_sleep( D_MAIN_STARTUP_WAIT );
//	TM_main_debug();
#endif	/* __TARGET_EV3__ */
	return;
}

/* LD */
void LogDump_task( intptr_t exinf )
{
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	LD_main();
	return;
}

void LineTrace_task( intptr_t exinf )
{
#if	(__TARGET_EV3__)
	LT_main();
	ext_tsk();
#else	/* __TARGET_EV3__ */
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	LT_main_debug();
#endif	/* __TARGET_EV3__ */
	return;
}
