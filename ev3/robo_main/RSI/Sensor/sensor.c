#include "sensor.h"

/*** sensor ***/

/********************************************************/
/* �Z���T�|�[�g��ݒ肷��								*/
/********************************************************/
int RSI_sensor_config( int iPort, int iType )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sensor_config( (sensor_port_t)iPort, (sensor_type_t)iType );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","Sensor Set",0 ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* �Z���T�|�[�g�̃Z���T�^�C�v���擾����					*/
/********************************************************/
unsigned int RSI_sensor_get_type( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],Get Type,%d/%d\n", iPort, iRet );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sensor_get_type( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�Z���T�^�C�v */
}

/********************************************************/
/* �J���[�Z���T�ŃJ���[�����ʂ���						*/
/********************************************************/
int RSI_color_sensor_get_color( int iPort )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_color_sensor_get_color( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Get Color@@",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���ʂ����J���[ */
}

/*** color_sensor ***/

/********************************************************/
/* �J���[�Z���T�Ŕ��ˌ��̋����𑪒肷��					*/
/********************************************************/
unsigned char RSI_color_sensor_get_reflect( int iPort )
{
	unsigned char ucRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	ucRet = ev3_color_sensor_get_reflect( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Color Reflect@@",ucRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return ucRet;	/* Ret�F���ˌ��̋���(0-100) */
}

/********************************************************/
/* �J���[�Z���T�Ŋ����̋����𑪒肷��					*/
/********************************************************/
unsigned char RSI_color_sensor_get_ambient( int iPort )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_color_sensor_get_ambient( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Color Ambient@@",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* �J���[�Z���T��RGB Raw�l�𑪒肷��					*/
/********************************************************/
void RSI_color_sensor_get_rgb_raw( int iPort, S_RSI_SENSOR_RGB_RAW* spVal )
{
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	ev3_color_sensor_get_rgb_raw( (sensor_port_t)iPort, (rgb_raw_t*)spVal );
#endif	/* __VC_DEBUG__ */
	
	return;
}

/*** gyro_sensor ***/

/********************************************************/
/* �W���C���Z���T�Ŋp�ʒu�𑪒肷��						*/
/********************************************************/
signed short RSI_gyro_sensor_get_angle( int iPort )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_gyro_sensor_get_angle( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Gyro Angle@@",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F�p�ʒu */
}

/********************************************************/
/* �W���C���Z���T�Ŋp���x�𑪒肷��						*/
/********************************************************/
signed short RSI_gyro_sensor_get_rate( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_gyro_sensor_get_rate( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Gyro Rate@@",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F�p���x */
}

/********************************************************/
/* �W���C���Z���T�̊p�ʒu���[���Ƀ��Z�b�g����			*/
/********************************************************/
int RSI_gyro_sensor_reset( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_gyro_sensor_reset( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Gyro Reset@@", 0 ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F���� */
}

/*** ultrasonic_sensor ***/

/********************************************************/
/* �����g�Z���T�ŋ����𑪒肷��							*/
/********************************************************/
signed short RSI_ultrasonic_sensor_get_distance( int iPort )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_ultrasonic_sensor_get_distance( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SENSOR]","@@Distance@@", iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret�F����(%) */
}

/********************************************************/
/* �����g�Z���T�Œ����g�M�������o����					*/
/********************************************************/
int RSI_ultrasonic_sensor_listen( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_ultrasonic_sensor_listen( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F���o���� */
}

/*** infrared_sensor ***/

/********************************************************/
/* IR�Z���T�ŋ����𑪒肷��								*/
/********************************************************/
signed char RSI_infrared_sensor_get_distance( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_infrared_sensor_get_distance( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* IR�Z���T��IR�r�[�R���̕��ʂƋ����𑪒肷��			*/
/********************************************************/
S_RSI_SENSOR_IR_SEEK RSI_infrared_sensor_seek( int iPort )
{
	S_RSI_SENSOR_IR_SEEK stSeek;
	memset( &stSeek, 0x00, sizeof(S_RSI_SENSOR_IR_SEEK) );
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
//	stSeekTemp = ev3_infrared_sensor_seek( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return stSeek;	/* Ret�F���ʂƋ��� */
}

/********************************************************/
/* IR�Z���T��IR�r�[�R���̃{�^�����͂����o����			*/
/********************************************************/
S_RSI_SENSOR_IR_REMOTE RSI_infrared_sensor_get_remote( int iPort )
{
	S_RSI_SENSOR_IR_REMOTE stRemote;
	
	memset( &stRemote, 0x00, sizeof(S_RSI_SENSOR_IR_REMOTE) );
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
//	spRemote = (S_RSI_SENSOR_IR_REMOTE)ev3_infrared_sensor_get_remote( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return stRemote;	/* Ret�F�{�^�����͂̃p�^�[�� */
}

/*** touch_sensor ***/

/********************************************************/
/* �^�b�`�Z���T�̏�Ԃ����o����							*/
/********************************************************/
int RSI_touch_sensor_is_pressed( int iPort )
{
	int iRet = D_RSI_FALSE;
	
#if	(__VC_DEBUG__)
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	/* ���O�o�͗}�� */
	if( D_RSI_FALSE != iRet )
	{
		fprintf( spRsi->fpRsiLog, "[SENSOR],Touch,%d\n", iRet );
	}
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_touch_sensor_is_pressed( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	
	return iRet;	/* Ret�F������� */
}

/*** ht_nxt_accel_sensor ***/

/********************************************************/
/* �����x�Z���T�iHiTechnic�А��j�ŉ����x�𑪒肷��		*/
/********************************************************/
int RSI_ht_nxt_accel_sensor_measure( int iPort, signed short ssAxes )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
//	iRet = (int)ht_nxt_accel_sensor_measure( (sensor_port_t)iPort, (int16_t)ssAxes );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�X�V��� */
}

/*** RSI_nxt_temp_sensor ***/

/********************************************************/
/* NXT���x�Z���T�i9749�j�ŉ��x�𑪒肷��				*/
/********************************************************/
int RSI_nxt_temp_sensor_measure( int iPort, float* fpTemp )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)nxt_temp_sensor_measure( (sensor_port_t)iPort, fpTemp );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�X�V��� */
}

