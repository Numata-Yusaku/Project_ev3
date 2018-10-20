#ifndef	__MOTOR_H__
#define	__MOTOR_H__

/***** �C���N���[�h *****/
#include <stdio.h>
#include "rsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */

/*** GEN ***/

/*** APL ***/

/***** �萔 *****/
enum EN_RSI_MOTOR_PORT
{
	E_RSI_MOTOR_PORT_A = 0,		/* �|�[�gA */
	E_RSI_MOTOR_PORT_B,			/* �|�[�gB */
	E_RSI_MOTOR_PORT_C,			/* �|�[�gC */
	E_RSI_MOTOR_PORT_D,			/* �|�[�gD */

	/* ��������ɒ�`���邱�� */
	E_RSI_MOTOR_PORT_NUM,		/* �|�[�g�� */
};

enum EN_RSI_MOTOR_TYPE
{
	E_RSI_MOTOR_TYPE_NONE = 0,		/* ���[�^���ڑ� */
	E_RSI_MOTOR_TYPE_MEDIUM,		/* �T�[�{���[�^M */
	E_RSI_MOTOR_TYPE_LARGE,			/* �T�[�{���[�^L */
	E_RSI_MOTOR_TYPE_UNREGULATED,	/* ���������[�^ */

	/* ��������ɒ�`���邱�� */
	E_RSI_MOTOR_TYPE_NUM,			/* ���[�^�^�C�v�� */
};

/***** �\���� *****/

/***** �֐��v���g�^�C�v *****/
/* motor */
int RSI_motor_config( int iPort,  int iType );
unsigned int RSI_motor_get_type( int iPort );
int RSI_motor_get_counts( int iPort );
int RSI_motor_reset_counts( int iPort );
int RSI_motor_set_power( int iPort, int iPower );
int RSI_motor_get_power( int iPort );
int RSI_motor_stop( int iPort, int iBrake );
int RSI_motor_rotate( int iPort, int iDegrees, signed int siSpeedAbs, int iBlocking );
int RSI_motor_steer( int iLeftMotor, int iRightMotor, int iPower, int iTurnRatio);

/***** �e�[�u�� *****/


#endif	/* __MOTOR_H__ */
