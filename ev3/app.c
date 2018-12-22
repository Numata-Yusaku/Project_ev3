#include <stdio.h>

#include "main.h"

void Main_task(intptr_t exinf )
{
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	MAIN_init();
	MAIN_task();
	return;
}

void MAIN_ev3_cyc_run(intptr_t exinf )
{
#if	(__TARGET_EV3__)
	act_tsk( LT_TASK );
#endif	/* __TARGET_EV3__ */
	return;
}

void Bluetooth_task( intptr_t exinf )
{
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	BT_main();
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
