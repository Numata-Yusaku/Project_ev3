#include "ltin.h"
#include "ltin_porttable.h"

S_LT* gspLt = (S_LT*)NULL;

/* startup */
void lt_main( void )
{
	int			iRet		= D_LT_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* �̈�m�� */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* ������ */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* �N������ */
	lt_init();
	
	/* LT_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_LT, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_LT_INVALID != psRecvData->iMsgid) )
		{
			/* ��M���� */
			lt_recv( psRecvData );
			
		}
		
		/* ��M�f�[�^�N���A */
		if((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* �풓���� */
		lt_proc();
		
		/* �^�X�N�T�C�N��(ms) */
		TASK_sleep( D_TASK_CYCLE_LT );
	}

END:
	/*** ������� ***/
	if ((S_MSG_DATA*)NULL != psRecvData)
	{
		free( psRecvData );
		psRecvData = (S_MSG_DATA*)NULL;
	}
	
	lt_shutdown();
	
	return;
}

void lt_init( void )
{
	lt_set_Global();
	lt_set_Port();
	
	/* ���O */
	lt_log_Statuslog_open();
	lt_log_Calibratelog_open();
	lt_log_Systemlog_open();
	
	return;
}

void lt_shutdown( void )
{
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	ter_tsk( LT_TASK );
#endif	/* __VC_DEBUG__ */
	return;
}

/* global */
void lt_set_Global( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	spLt = (S_LT*)malloc( sizeof(S_LT) );
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* ������ */
	memset( spLt, 0x00, sizeof(S_LT) );
	
	/*** �������l�ݒ� ***/
	
	/* �O���[�o���ݒ� */
	gspLt = spLt;
	
	return;
}

S_LT* lt_get_Global( void )
{
	return (S_LT*)gspLt;
}

/* proc */
void lt_proc( void )
{
	int iStatus = E_LT_STATUS_INVALID;
	S_LT* spLt = (S_LT*)NULL;
	
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* �N���X�X�e�[�^�X�擾 */
	iStatus = spLt->iStatus;
	if( E_LT_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* ���O�o�� */
	lt_log_set_Statuslog();
	
	/* ��Ԃɉ����ď������s */
	switch( iStatus )
	{
		case E_LT_STATUS_READY:
			lt_proc_Ready();
			break;
		
		case E_LT_STATUS_IDLE:
			lt_proc_Idle();
			break;
		
		case E_LT_STATUS_CALIBLATE_GYRO:
			lt_proc_CalibrateGyro();
			break;
			
		case E_LT_STATUS_CALIBLATE_TAIL:
			lt_proc_CalibrateTail();
			break;
			
		case E_LT_STATUS_CALIBLATE_BLACK:
			lt_proc_CalibrateBlack();
			/* �������Ȃ� */
			break;
			
		case E_LT_STATUS_CALIBLATE_WHITE:
			lt_proc_CalibrateWhite();
			break;
			
		case E_LT_STATUS_WAITING:
			lt_proc_Waiting();
			break;
		
		case E_LT_STATUS_RUN_STANDUP:
			lt_proc_StandUp();
			break;
		
		case E_LT_STATUS_RUN_PAUSE:
			lt_proc_Pause();
			break;
		
		case E_LT_STATUS_RUN_LOWSPEED:
			lt_proc_LowSpeed();
			break;
		
		case E_LT_STATUS_STOP_WAIT:
			lt_proc_StopWait();
			break;
		
		case E_LT_STATUS_STOP:
			lt_proc_Stop();
			break;
		
		default:
			break;
	}
	
	return;
}

void lt_proc_Ready( void )
{
	int iWupChk = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* WUPCHK */
	iWupChk = lt_send_Wupchk_req( NULL );
	if( E_LT_WUPCHK_NUM == iWupChk )
	{
		spLt->iStatus = E_LT_STATUS_IDLE;
	}
	
	return;
}

void lt_proc_Idle( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* Bluetooth�ɂ��L�����u���[�V�����ʐM���J�n */
	lt_send_staCalibration_req( NULL );
	
	/* ���������� */
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_ORANGE );
	
	/* ��ԑJ�� */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_GYRO;
	
	return;
}

void lt_proc_CalibrateGyro( void )
{
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		lt_Caliblate();
	}
	
	return;
}

void lt_proc_CalibrateTail( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* �K���̉�] */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_CALIBRATE_DEGREES, D_LT_TAIL_CALIBRATE_SPEED, D_LT_TRUE );
	
	/* �K�����Œ� */
	RSI_motor_stop( spLt->stPort.iMotor.iTail, D_LT_TRUE );
	
	/* ��ԑJ�� */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_BLACK;
	
	return;
}

void lt_proc_CalibrateBlack( void )
{
	
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		lt_Caliblate();
	}
	
	return;
}

void lt_proc_CalibrateWhite( void )
{
	
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		lt_Caliblate();
	}
	
	return;
}

void lt_proc_Waiting( void )
{
	
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		lt_send_staRunning_req( NULL );
		spLt->iStatus = E_LT_STATUS_RUN_STANDUP;
	}
	
	return;
}

void lt_proc_StandUp( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/*** �ԗ֐��� ***/
	/* ���[�^�̊p���x���Z�b�g */
	RSI_motor_reset_counts( spLt->stPort.iMotor.iLeftWheel );
	RSI_motor_reset_counts( spLt->stPort.iMotor.iRightWheel );
	
	/*** �W���C������ ***/
	/* �W���C���Z���T���Z�b�g */
	RSI_gyro_sensor_reset( spLt->stPort.iSensor.iGyro );
	
	/* �|���U�q������ */
	lt_balance_init();

	/*** �K������ ***/
#if 1	/* T.B.D ��1 */
	/* �L�b�N�X�^�[�g */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_STANDUP_KICK_DEGREES, D_LT_TAIL_STANDUP_SPEED, D_LT_TRUE );
	
	/* �K����߂� */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_STANDUP_KICK_DEGREES, D_LT_TAIL_STANDUP_SPEED, D_LT_TRUE );

#else	/* T.B.D ��1 */
	lt_set_TailAngle( D_LT_TAIL_STANDUP_KICK_DEGREES );
#endif	/* T.B.D */
	
	/* ���s���� */
	lt_Running( D_LT_FORWORD_PAUSE, D_LT_TURN_RUN );
	
	/* ��ԑJ�� ��1 */
	spLt->iStatus = E_LT_STATUS_RUN_LOWSPEED;
	
	return;
}

void lt_proc_LowSpeed( void )
{
	printf("��\n");
	
	/* ���s���� */
	lt_Running( D_LT_FORWORD_LOWSPEED, D_LT_TURN_RUN );
	
	return;
}

void lt_proc_Pause( void )
{
	/* ���s���� */
	lt_Running( D_LT_FORWORD_PAUSE, D_LT_TURN_STOP );
	
	return;
}

void lt_proc_StopWait( void )
{
	return;
}

void lt_proc_Stop( void )
{
	int iStopChk = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* STOP */
	iStopChk = lt_send_Stop_req( NULL );
	if( E_LT_STOP_NUM == iStopChk )
	{
		/* �V�X�e���I�� */
		lt_shutdown();
		lt_send_ShutDown_res( NULL );
	}
	
	return;
}

/* port */
void lt_set_Port( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* �Z���T�̃|�[�g�ݒ������ */
	lt_set_SensorPort();
	
	/* ���[�^�̃|�[�g�ݒ������ */
	lt_set_MotorPort();
	
	/* �|�[�g�ێ� */
	spLt->stPort.iSensor.iTouch = lt_get_SensorPort( E_LT_PARTS_TOUCH_SENSOR );
	spLt->stPort.iSensor.iColor = lt_get_SensorPort( E_LT_PARTS_COLOR_SENSOR );
	spLt->stPort.iSensor.iGyro = lt_get_SensorPort( E_LT_PARTS_GYRO_SENSOR );
	spLt->stPort.iSensor.iSonar = lt_get_SensorPort( E_LT_PARTS_SONAR_SENSOR );
	spLt->stPort.iMotor.iLeftWheel = lt_get_MotorPort( E_LT_PARTS_LEFT_MOTOR );
	spLt->stPort.iMotor.iRightWheel = lt_get_MotorPort( E_LT_PARTS_RIGHT_MOTOR );
	spLt->stPort.iMotor.iTail = lt_get_MotorPort( E_LT_PARTS_TAIL_MOTOR );

	return;
}

void lt_set_SensorPort( void )
{
	int iLoop = 0;
	S_LT_PORTINFO* spSensorTable = T_LT_SENSORPORT_TABLE;
	
	/* �Z���T�̃|�[�g�ݒ������ */
	for( iLoop = 0; iLoop < E_RSI_SENSOR_PORT_NUM; iLoop++ )
	{
		if( E_LT_PARTS_NONE != spSensorTable[iLoop].iParts )
		{
			RSI_sensor_config( spSensorTable[iLoop].iPort, spSensorTable[iLoop].iType );
		}
		
	}
	
	return;
}

int lt_get_SensorPort( int iParts )
{
	int iRet = 0;
	int iLoop = 0;
	S_LT_PORTINFO* spSensorTable = T_LT_SENSORPORT_TABLE;
	
	for( iLoop = 0; iLoop < E_RSI_SENSOR_PORT_NUM; iLoop++ )
	{
		if( iParts == spSensorTable[iLoop].iParts )
		{
			iRet = spSensorTable[iLoop].iPort;
			break;
		}
		
	}
	
	return iRet;		/* Ret:�|�[�g */
}

void lt_set_MotorPort( void )
{
	int iLoop = 0;
	S_LT_PORTINFO* spMotorTable = T_LT_MOTORPORT_TABLE;
	
	/* ���[�^�̃|�[�g�ݒ������ */
	for( iLoop = 0; iLoop < E_RSI_MOTOR_PORT_NUM; iLoop++ )
	{
		if( E_LT_PARTS_NONE != spMotorTable[iLoop].iParts )
		{
			RSI_motor_config( spMotorTable[iLoop].iPort, spMotorTable[iLoop].iType );
		}
		
	}
	
	return;
}

int lt_get_MotorPort( int iParts )
{
	int iRet = 0;
	int iLoop = 0;
	S_LT_PORTINFO* spMotorTable = T_LT_MOTORPORT_TABLE;
	
	for( iLoop = 0; iLoop < E_RSI_MOTOR_PORT_NUM; iLoop++ )
	{
		if( iParts == spMotorTable[iLoop].iParts )
		{
			iRet = spMotorTable[iLoop].iPort;
			break;
		}
		
	}
	
	return iRet;		/* Ret:�|�[�g */
}

/* calibrate */
void lt_Caliblate( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	switch( spLt->iStatus )
	{
		case E_LT_STATUS_CALIBLATE_GYRO:
			lt_set_CalibrateGyro();
			break;
		
		case E_LT_STATUS_CALIBLATE_BLACK:
			lt_set_CalibrateBlack();
			break;
		
		case E_LT_STATUS_CALIBLATE_WHITE:
			lt_set_CalibrateWhite();
			printf("Goto The Start Ready ...\n");
			break;
		
		default:
			/* �t�F�[������ */
			break;
	}
	
	return;
}

void lt_set_CalibrateGyro( void )
{
	int iGyro = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* �W���C�����Z�b�g */
	RSI_gyro_sensor_reset( spLt->stPort.iSensor.iGyro );
	
	/* �W���C����\�� */
	iGyro = RSI_gyro_sensor_get_angle( spLt->stPort.iSensor.iGyro );
	RSI_lcd_draw_stringAndDec("Gyro:", iGyro, 0, 30 );
	
	/* �f�[�^�ݒ� */
	spLt->stCalibrateInfo.iGyro = iGyro;
	
	/* �ݒ芮���ʒm */
	RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_C4, D_LT_TONE_DURATION );
	
	/* ��ԑJ�� */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_TAIL;
	
	return;
}

void lt_set_CalibrateBlack( void )
{
	int iColor = 0;
	int iReflect = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* ���ˌ��̋������擾 */
#if	(__VC_DEBUG__)
	iColor = E_RSI_SENSOR_COLOR_BLACK;
#else	/* __VC_DEBUG__ */
	iColor = RSI_color_sensor_get_color( spLt->stPort.iSensor.iColor );
#endif	/* __VC_DEBUG__ */
	
	/* ���ˌ��̋������擾 */
	iReflect = RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	if( E_RSI_SENSOR_COLOR_BLACK == iColor )
	{
		/* �f�[�^�ݒ� */
		spLt->stCalibrateInfo.stBlack.iColor = iColor;
		spLt->stCalibrateInfo.stBlack.iReflect = iReflect;
		
		/* �ݒ芮���ʒm */
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_D4, D_LT_TONE_DURATION );
		
		/* ��ԑJ�� */
		spLt->iStatus = E_LT_STATUS_CALIBLATE_WHITE;
	}
	
	return;
}

void lt_set_CalibrateWhite( void )
{
	int iColor = 0;
	int iReflect = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* ���ˌ��̋������擾 */
#if	(__VC_DEBUG__)
	iColor = E_RSI_SENSOR_COLOR_WHITE;
#else	/* __VC_DEBUG__ */
	iColor = RSI_color_sensor_get_color( spLt->stPort.iSensor.iColor );
#endif	/* __VC_DEBUG__ */
	
	/* ���ˌ��̋������擾 */
	iReflect = RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	if( E_RSI_SENSOR_COLOR_WHITE == iColor )
	{
		/* �f�[�^�ݒ� */
		spLt->stCalibrateInfo.stWhite.iColor = iColor;
		spLt->stCalibrateInfo.stWhite.iReflect = iReflect;
		
		/* Bluetooth�ɂ��L�����u���[�V�����ʐM���I�� */
		lt_send_endCalibration_req( NULL );
		
		/* �ݒ芮���ʒm */
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_E4, D_LT_TONE_DURATION );
		
		/* �L�����u���[�V�������O�o�� */
		lt_log_set_Calibratelog();
		
		/* ������ԑJ�ڂ���ƃ^�b�`�Z���T�����m���Ă��܂��̂�Wait�������� */
		TASK_sleep( D_LT_CALIBRATEEND_WAIT );
		
		/* ��ԑJ�� */
		spLt->iStatus = E_LT_STATUS_WAITING;
		
	}
	
	return;
}

/* running */
void lt_Running( int iForwardLevel, int iTurnMode )
{
	int iRet = D_LT_NG;
	int iAlert = D_LT_SONAR_ARERT_NON_OBSTRUCTION;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* ��Q������ */
	iAlert = lt_get_SonarAlert();
	if( D_LT_SONAR_ARERT_NON_OBSTRUCTION != iAlert )
	{
		spLt->stBacanceControl.fCmdForward = 0;
		spLt->stBacanceControl.fCmdTurn = 0;
		/* ��~���� */
		spLt->iStatus = E_LT_STATUS_RUN_PAUSE;
	}
	else
	{
		/* �O�i�w�ߒl�擾 */
		spLt->stBacanceControl.fCmdForward = (float)iForwardLevel;
		
		/* ����w�ߒl�擾 */
		if( D_LT_TURN_STOP != iTurnMode )
		{
			spLt->stBacanceControl.fCmdTurn = (float)lt_get_RunningTurnDir();
		}
	}
	
	spLt->stBacanceControl.fThetaMLeft = (float)RSI_motor_get_counts( spLt->stPort.iMotor.iLeftWheel );
	spLt->stBacanceControl.fThetaMRight = (float)RSI_motor_get_counts( spLt->stPort.iMotor.iRightWheel );
	spLt->stBacanceControl.fGyro = RSI_gyro_sensor_get_rate( spLt->stPort.iSensor.iGyro );
	spLt->stBacanceControl.fBattery = (float)RSI_hw_battery_voltage_mV();
	
	/****************************/
	/* �|������					*/
	/****************************/
	/* �o�b�N���b�V���L�����Z�� */
	lt_balance_set_BacklashCancel();
	
	/* �|�����s�p�����[�^���A���E�̃��[�^�o�͂��擾 */
	lt_balance_set_BalanceInfo();
	
	/* ���[�^�ғ� */
	iRet = lt_balance_set_MotorPower();
	if( D_LT_OK != iRet )
	{
		/* �ً}��~ */
		lt_send_Stop_req( NULL );
	}
	
	/* �V�X�e�����O�o�� */
	lt_log_set_Systemlog();
	
	return;
}

int lt_get_RunningTurnDir( void )
{
	int iTurnDir = D_LT_TURN_STOP;
	int iReflect = 0;
	int iThreshold = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return iTurnDir;
	}
	
	/* �H�ʂ̔��ˌ����擾 */
	iReflect = (int)RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	/* �H�ʂ̔��ˌ����ϒl���擾 */
#if 1	/* T.B.D ��3 */
	iThreshold = (D_LT_COLORSENSOR_REFLECT_WHITE + D_LT_COLORSENSOR_REFLECT_BLACK) / 2;
#else	/* T.B.D ��3 */
	iThreshold = ( spLt->stCalibrateInfo.stWhite.iReflect + spLt->stCalibrateInfo.stBlack.iReflect ) / 2;
#endif	/* T.B.D ��3 */
	if ( iReflect >= iThreshold )
	{
		iTurnDir = D_LT_TURN_LEFT;		/* �����񖽗� */
	}
	else
	{
		iTurnDir = D_LT_TURN_RIGHT;		/* �E���񖽗� */
	}	
	
	return iTurnDir;		/* ������� */
}

/* other I/F */
void lt_set_TailAngle( int iAngle )
{
	signed int pwm = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	pwm = (signed int)((iAngle - RSI_motor_get_counts( spLt->stPort.iMotor.iTail )) * D_LT_P_GAIN);
	/* PWM�o�͖O�a���� */
	if (pwm > D_LT_PWM_ABS_MAX)
	{
		pwm = D_LT_PWM_ABS_MAX;
	}
	else if (pwm < -D_LT_PWM_ABS_MAX)
	{
		pwm = -D_LT_PWM_ABS_MAX;
	}
	
	if (pwm == 0)
	{
		RSI_motor_stop( spLt->stPort.iMotor.iTail, D_LT_TRUE);
	}
	else
	{
		RSI_motor_set_power( spLt->stPort.iMotor.iTail, (signed char)pwm);
	}
	return;
}

int lt_get_SonarAlert( void )
{
/* T.B.D ��2 */
/*
	�����g�Z���T�ɂ�鋗����������́A�����g�̌��������Ɉˑ����܂��B
	NXT�̏ꍇ�́A40msec�������x���o����̍ŒZ��������ł��B
	EV3�̏ꍇ�́A�v�m�F
*/
	int iAlert = D_LT_SONAR_ARERT_NON_OBSTRUCTION;
	unsigned int counter = 0;
	
	signed int distance;
	
	if (++counter == 40/4) /* ��40msec�������ɏ�Q�����m  */
	{
		distance = RSI_ultrasonic_sensor_get_distance(E_LT_PARTS_SONAR_SENSOR);
	if ((distance <= D_LT_SONAR_ALERT_DISTANCE) && (distance >= 0))
	{
		iAlert = D_LT_SONAR_ARERT_OBSTRUCTION; /* ��Q�������m */
	}
	else
	{
		iAlert = D_LT_SONAR_ARERT_NON_OBSTRUCTION; /* ��Q������ */
	}
		counter = 0;
	}
	
	return iAlert;
}

int lt_get_StopState( void )
{
	int iLoop = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return D_LT_NG;
	}
	
	for( iLoop = 0; iLoop < E_LT_STOP_NUM; iLoop++ )
	{
		if( D_LT_FLAG_ON != spLt->iStopChk[iLoop] )
		{
			return D_LT_NG;
		}
	}
	
	return D_LT_OK;
}