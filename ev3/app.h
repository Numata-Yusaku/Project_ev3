#ifndef	__APP_H__
#define	__APP_H__

/* �^�[�Q�b�g�ˑ��̒�` */
#include "target_test.h"

/* �^�X�N�̗D��x */
#define	D_APP_PRIORITY_MAIN			(5)	/* ���C���^�X�N(���D��x���ŏ�ʂƂȂ邱��) */

#define D_APP_PRIORITY_HIGH			(9)
#define D_APP_PRIORITY_MID			(10)
#define D_APP_PRIORITY_LOW			(11)

/* �^�[�Q�b�g�Ɉˑ�����\���̂���萔�̒�` */
#define	D_APP_STACK_SIZE			(4096)	/* �^�X�N�̃X�^�b�N�T�C�Y */

/* Tasks */
extern void	Main_task(intptr_t exinf);
extern void	Bluetooth_task(intptr_t exinf);
extern void	LineTrace_task(intptr_t exinf);

#endif	/* __APP_H__ */
