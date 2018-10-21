#include <stdio.h>

#include "main.h"

void Main_task(intptr_t exinf )
{
	TASK_sleep( D_MAIN_STARTUP_WAIT );
	MAIN_init();
	MAIN_task();
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
	LT_main();
	return;
}
