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
	LT_main();

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
	TASK_sleep( D_MAIN_STARTUP_WAIT );
#if	(__VC_DEBUG__)
	LT_main_debug();
#else	/* __VC_DEBUG__ */
	LT_startup();
#endif	/* __VC_DEBUG__ */
	return;
}
