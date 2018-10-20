#include "motor.h"

/*** motor ***/

/********************************************************/
/* ���[�^�|�[�g��ݒ肷��								*/
/********************************************************/
int RSI_motor_config( int iPort,  int iType )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_config( (motor_port_t)iPort, (motor_type_t)iType );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],Motor Set,%d\n", iPort );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* ���[�^�|�[�g�̃��[�^�^�C�v���擾����					*/
/********************************************************/
unsigned int RSI_motor_get_type( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_get_type( (motor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	printf("[MOTOR],Get Type,%d/%d\n", iPort, iRet );
	
	return iRet;	/* Ret�F���[�^�^�C�v */
}

/********************************************************/
/* ���[�^�̊p�ʒu���擾����								*/
/********************************************************/
int RSI_motor_get_counts( int iPort )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_get_counts( (motor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],@@Counts@@,%d\n", iRet );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F�p�ʒu */
}

/********************************************************/
/* ���[�^�̊p�ʒu���[���Ƀ��Z�b�g����					*/
/********************************************************/
int RSI_motor_reset_counts( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_reset_counts( (motor_port_t) iPort);
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],@@Counts Reset@@,%d\n",iPort );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* ���[�^�̃p���[��ݒ肷��								*/
/********************************************************/
int RSI_motor_set_power( int iPort, int iPower )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_set_power( (motor_port_t)iPort, iPower );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],@@Set Power@@,%d,%d\n",iPort,iPower);
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* ���[�^�̃p���[���擾����								*/
/********************************************************/
int RSI_motor_get_power( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_get_power( (motor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],@@Get Power@@,%d,%d\n",iPort ,iRet );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���[�^�̃p���[ */
}

/********************************************************/
/* ���[�^���~����										*/
/********************************************************/
int RSI_motor_stop( int iPort, int iBrake )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_stop( (motor_port_t)iPort, (bool_t)iBrake );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],@@Motor Stop@@\n");
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* ���[�^���w�肵���p�x������]������					*/
/********************************************************/
int RSI_motor_rotate( int iPort, int iDegrees, signed int siSpeedAbs, int iBlocking )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_rotate( (motor_port_t)iPort, iDegrees, (uint32_t)siSpeedAbs, (bool_t)iBlocking );
#endif	/* __VC_DEBUG__ */
	
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[MOTOR],Deg/SPD,%d,%d\n",iDegrees, siSpeedAbs );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* �Q�̃��[�^�Ń��{�b�g�̃X�e�A�����O������s��		*/
/********************************************************/
int RSI_motor_steer( int iLeftMotor, int iRightMotor, int iPower, int iTurnRatio)
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_motor_steer( (motor_port_t)iLeftMotor, (motor_port_t)iRightMotor, iPower, iTurnRatio );
#endif	/* __VC_DEBUG__ */
	printf("[MOTOR],POW/TURN,%d,%d\n", iPower, iTurnRatio );
	
	return iRet;	/* Ret�F���� */
}


