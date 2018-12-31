#ifndef	__APP_H__
#define	__APP_H__

/* ターゲット依存の定義 */
#include "target_test.h"

/* タスクの優先度 */
#define	D_APP_PRIORITY_MAIN			(10)	/* メインタスク(※優先度が最下位となること) */

#define D_APP_PRIORITY_HIGH			(1)
#define D_APP_PRIORITY_MID			(5)
#define D_APP_PRIORITY_LOW		(11)

/* ターゲットに依存する可能性のある定数の定義 */
#define	D_APP_STACK_SIZE			(4096)	/* タスクのスタックサイズ */

/* Tasks */
extern void	Main_task(intptr_t exinf);
extern void	MAIN_ev3_cyc_run_LT(intptr_t exinf);
extern void	MAIN_ev3_cyc_run_TM(intptr_t exinf);
extern void	Bluetooth_task(intptr_t exinf);
extern void	Time_task(intptr_t exinf);
extern void	LogDump_task(intptr_t exinf);
extern void	LineTrace_task(intptr_t exinf);

#endif	/* __APP_H__ */
