#include <stdio.h>

#include "main.h"

void Main_task(intptr_t exinf )
{
	MAIN_init();
	MAIN_task();
	return;
}

void Bluetooth_task( intptr_t exinf )
{
//	BT_main();
	return;
}

void LineTrace_task( intptr_t exinf )
{
//	LT_main();
	return;
}
