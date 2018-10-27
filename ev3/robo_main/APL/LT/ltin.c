#include "ltin.h"
#include "ltin_porttable.h"

S_LT* gspLt = (S_LT*)NULL;

/* startup */
void lt_main( void )
{
	int			iRet		= D_LT_NG;
	S_MSG_DATA*	psRecvData	= (S_MSG_DATA*)NULL;
	
	/* 領域確保 */
	psRecvData = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psRecvData)
	{
		goto END;
	}
	
	/* 初期化 */
	memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
	
	/* 起動準備 */
	lt_init();
	
	/* LT_TASK */
	while(1)
	{
		iRet = TASK_msgrecv( E_TASK_TASKID_LT, psRecvData );
		if( ( D_TASK_OK == iRet ) &&
			( E_MSGID_LT_INVALID != psRecvData->iMsgid) )
		{
			/* 受信処理 */
			lt_recv( psRecvData );
			
		}
		
		/* 受信データクリア */
		if((void*)NULL != psRecvData->vpPara)
		{
			free( psRecvData->vpPara );
			psRecvData->vpPara = (void*)NULL;
		}
		
		memset( psRecvData, 0x00, sizeof( S_MSG_DATA ) );
		
		/* 常駐処理 */
		lt_proc();
		
		/* タスクサイクル(ms) */
		TASK_sleep( D_TASK_CYCLE_LT );
	}

END:
	/*** 解放処理 ***/
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
	RSI_hw_speaker_set_volume( D_LT_TONE_VOLUME );
	
	/* ログ */
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
	
	/* 初期化 */
	memset( spLt, 0x00, sizeof(S_LT) );
	
	/*** 初期化値設定 ***/
	
	/* グローバル設定 */
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
	
	/* クラスステータス取得 */
	iStatus = spLt->iStatus;
	if( E_LT_STATUS_INVALID == iStatus )
	{
		return;
	}
	
	/* ログ出力 */
	lt_log_set_Statuslog();
	
	/* 状態に応じて処理実行 */
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
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* WUPCHK */
	iWupChk = lt_send_Wupchk_req();
	if( E_LT_WUPCHK_NUM == iWupChk )
	{
		spLt->iStatus = E_LT_STATUS_IDLE;
	}
	
	return;
}

void lt_proc_Idle( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* Bluetoothによるキャリブレーション通信を開始 */
	lt_send_staCalibration_req();
	
	/* 初期化完了 */
	RSI_hw_led_set_color( E_RSI_HW_LEDCOLOR_ORANGE );
	
	/* 状態遷移 */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_GYRO;
	
	return;
}

void lt_proc_CalibrateGyro( void )
{
	int iGyro = 0;
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	S_TASK_SETCLIENTSEND_GYRO stSend;
	
	/* 初期化 */
	memset( &stSend, 0x00, sizeof(S_TASK_SETCLIENTSEND_GYRO) );
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	iGyro = RSI_gyro_sensor_get_angle( spLt->stPort.iSensor.iGyro );
	if( spLt->stOldCalibrateInfo.iGyro != iGyro)
	{
		/*** データ変化あり ***/
		
		/* 情報表示 */
		if( D_LT_CLIENTSENDTIME_GYRO <= spLt->iClientSendCount[E_LT_CLIENTSEND_GYRO] )
		{
			stSend.iGyro = iGyro;
			/* ジャイロをサンプリング */
			lt_send_setClientSendGyro_req( &stSend );
		
			/*カウンタクリア*/
			spLt->iClientSendCount[E_LT_CLIENTSEND_GYRO] = 0;
		}
		
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_C5 ,D_LT_TONE_DURATION );
	}
	else
	{
		/*** データ変化なし ***/
		
		if (D_LT_SAMPLETIME_GYRO <= spLt->iClientSendCount[E_LT_CLIENTSEND_GYRO])
		{
			lt_Caliblate();
		}
	}
	
	/* データ更新 */
	spLt->stOldCalibrateInfo.iGyro = iGyro;
		
	/* カウンタ更新 */
	spLt->iClientSendCount[E_LT_CLIENTSEND_GYRO] ++;
	
	/*** 基準ジャイロの決定 ***/
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		/* ボタン押下でジャイロリセット */
		RSI_gyro_sensor_reset( spLt->stPort.iSensor.iGyro );
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_B6 ,D_LT_TONE_DURATION );
		
	}
	
	return;
}

void lt_proc_CalibrateTail( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	RSI_motor_reset_counts( spLt->stPort.iMotor.iTail );
	
	/* 尻尾の回転 */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_CALIBRATE_DEGREES, D_LT_TAIL_CALIBRATE_SPEED, D_LT_TRUE );
	
	/* 尻尾を固定 */
	RSI_motor_stop( spLt->stPort.iMotor.iTail, D_LT_TRUE );
	
	/* 状態遷移 */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_BLACK;
	
	return;
}

void lt_proc_CalibrateBlack( void )
{
	
	int isPressed = D_LT_FALSE;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
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
	
	/* グローバル領域取得 */
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
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	isPressed = RSI_touch_sensor_is_pressed( spLt->stPort.iSensor.iTouch );
	if ( D_LT_TRUE == isPressed )
	{
		lt_send_staRunning_req();
		spLt->iStatus = E_LT_STATUS_RUN_STANDUP;
	}
	
	return;
}

void lt_proc_StandUp( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/*** 車輪制御 ***/
	/* モータの角速度リセット */
	RSI_motor_reset_counts( spLt->stPort.iMotor.iLeftWheel );
	RSI_motor_reset_counts( spLt->stPort.iMotor.iRightWheel );
	
	/*** ジャイロ制御 ***/
	/* ジャイロセンサリセット */
	RSI_gyro_sensor_reset( spLt->stPort.iSensor.iGyro );
	
	/* 倒立振子初期化 */
	lt_balance_init();

	/*** 尻尾制御 ***/
#if 1	/* T.B.D ▲1 */
	/* キックスタート */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_STANDUP_KICK_DEGREES, D_LT_TAIL_STANDUP_SPEED, D_LT_TRUE );
	
	/* 尻尾を戻す */
	RSI_motor_rotate( spLt->stPort.iMotor.iTail, D_LT_TAIL_STANDUP_KICK_DEGREES, D_LT_TAIL_STANDUP_SPEED, D_LT_TRUE );

#else	/* T.B.D ▲1 */
	lt_set_TailAngle( D_LT_TAIL_STANDUP_KICK_DEGREES );
#endif	/* T.B.D */
	
	/* 走行制御 */
	lt_Running( D_LT_FORWORD_PAUSE, D_LT_TURN_RUN );
	
	/* 状態遷移 ▲1 */
	spLt->iStatus = E_LT_STATUS_RUN_LOWSPEED;
	
	return;
}

void lt_proc_LowSpeed( void )
{
	printf("■\n");
	
	/* 走行制御 */
	lt_Running( D_LT_FORWORD_LOWSPEED, D_LT_TURN_RUN );
	
	return;
}

void lt_proc_Pause( void )
{
	/* 走行制御 */
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
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* STOP */
	iStopChk = lt_send_Stop_req();
	if( E_LT_STOP_NUM == iStopChk )
	{
		/* モータの固定を解除 */
		RSI_motor_stop( spLt->stPort.iMotor.iTail, D_LT_FALSE);
		RSI_motor_stop( spLt->stPort.iMotor.iLeftWheel, D_LT_FALSE);
		RSI_motor_stop( spLt->stPort.iMotor.iRightWheel, D_LT_FALSE);
		
		/* システム終了 */
		lt_shutdown();
		lt_send_ShutDown_res();
	}
	
	return;
}

/* port */
void lt_set_Port( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* センサのポート設定をする */
	lt_set_SensorPort();
	
	/* モータのポート設定をする */
	lt_set_MotorPort();
	
	/* ポート保持 */
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
	
	/* センサのポート設定をする */
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
	
	return iRet;		/* Ret:ポート */
}

void lt_set_MotorPort( void )
{
	int iLoop = 0;
	S_LT_PORTINFO* spMotorTable = T_LT_MOTORPORT_TABLE;
	
	/* モータのポート設定をする */
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
	
	return iRet;		/* Ret:ポート */
}

/* calibrate */
void lt_Caliblate( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
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
			/* フェール処理 */
			break;
	}
	
	return;
}

void lt_set_CalibrateGyro( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* データ設定 */
	spLt->stCalibrateInfo.iGyro = RSI_gyro_sensor_get_angle( spLt->stPort.iSensor.iGyro );
	
	/* 設定完了通知 */
	RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_C4, D_LT_TONE_DURATION );
	
	/* 状態遷移 */
	spLt->iStatus = E_LT_STATUS_CALIBLATE_TAIL;
	
	return;
}

void lt_set_CalibrateBlack( void )
{
	int iColor = 0;
	int iReflect = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 反射光の強さを取得 */
#if	(__VC_DEBUG__)
	iColor = E_RSI_SENSOR_COLOR_BLACK;
#else	/* __VC_DEBUG__ */
	iColor = RSI_color_sensor_get_color( spLt->stPort.iSensor.iColor );
#endif	/* __VC_DEBUG__ */
	
	/* 反射光の強さを取得 */
	iReflect = RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	if( E_RSI_SENSOR_COLOR_BLACK == iColor )
	{
		/* データ設定 */
		spLt->stCalibrateInfo.stBlack.iColor = iColor;
		spLt->stCalibrateInfo.stBlack.iReflect = iReflect;
		
		/* 設定完了通知 */
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_D4, D_LT_TONE_DURATION );
		
		/* 状態遷移 */
		spLt->iStatus = E_LT_STATUS_CALIBLATE_WHITE;
	}
	
	return;
}

void lt_set_CalibrateWhite( void )
{
	int iColor = 0;
	int iReflect = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 反射光の強さを取得 */
#if	(__VC_DEBUG__)
	iColor = E_RSI_SENSOR_COLOR_WHITE;
#else	/* __VC_DEBUG__ */
	iColor = RSI_color_sensor_get_color( spLt->stPort.iSensor.iColor );
#endif	/* __VC_DEBUG__ */
	
	/* 反射光の強さを取得 */
	iReflect = RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	if( E_RSI_SENSOR_COLOR_WHITE == iColor )
	{
		/* データ設定 */
		spLt->stCalibrateInfo.stWhite.iColor = iColor;
		spLt->stCalibrateInfo.stWhite.iReflect = iReflect;
		
		/* Bluetoothによるキャリブレーション通信を終了 */
		lt_send_endCalibration_req();
		
		/* 設定完了通知 */
		RSI_hw_speaker_play_tone( D_RSI_HW_NOTE_E4, D_LT_TONE_DURATION );
		
		/* キャリブレーションログ出力 */
		lt_log_set_Calibratelog();
		
		/* すぐ状態遷移するとタッチセンサを検知してしまうのでWaitをかける */
		TASK_sleep( D_LT_CALIBRATEEND_WAIT );
		
		/* 状態遷移 */
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
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 障害物判定 */
	iAlert = lt_get_SonarAlert();
	if( D_LT_SONAR_ARERT_NON_OBSTRUCTION != iAlert )
	{
		spLt->stBacanceControl.fCmdForward = 0;
		spLt->stBacanceControl.fCmdTurn = 0;
		/* 停止する */
		spLt->iStatus = E_LT_STATUS_RUN_PAUSE;
	}
	else
	{
		/* 前進指令値取得 */
		spLt->stBacanceControl.fCmdForward = (float)iForwardLevel;
		
		/* 旋回指令値取得 */
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
	/* 倒立制御					*/
	/****************************/
	/* バックラッシュキャンセル */
	lt_balance_set_BacklashCancel();
	
	/* 倒立走行パラメータより、左右のモータ出力を取得 */
	lt_balance_set_BalanceInfo();
	
	/* モータ稼働 */
#if	(__VC_DEBUG__)
	lt_balance_set_DummyMotorPower();
#endif	/* __VC_DEBUG__ */
	iRet = lt_balance_set_MotorPower();
	if( D_LT_OK != iRet )
	{
		/* 緊急停止 */
		lt_send_Stop_req();
	}
	
	/* システムログ出力 */
	lt_log_set_Systemlog();
	
	return;
}

int lt_get_RunningTurnDir( void )
{
	int iTurnDir = D_LT_TURN_STOP;
	int iReflect = 0;
	int iThreshold = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return iTurnDir;
	}
	
	/* 路面の反射光を取得 */
	iReflect = (int)RSI_color_sensor_get_reflect( spLt->stPort.iSensor.iColor );
	
	/* 路面の反射光平均値を取得 */
#if 1	/* T.B.D ▲3 */
	iThreshold = (D_LT_COLORSENSOR_REFLECT_WHITE + D_LT_COLORSENSOR_REFLECT_BLACK) / 2;
#else	/* T.B.D ▲3 */
	iThreshold = ( spLt->stCalibrateInfo.stWhite.iReflect + spLt->stCalibrateInfo.stBlack.iReflect ) / 2;
#endif	/* T.B.D ▲3 */
	if ( iReflect >= iThreshold )
	{
		iTurnDir = D_LT_TURN_LEFT;		/* 左旋回命令 */
	}
	else
	{
		iTurnDir = D_LT_TURN_RIGHT;		/* 右旋回命令 */
	}	
	
	return iTurnDir;		/* 旋回方向 */
}

/* other I/F */
void lt_set_TailAngle( int iAngle )
{
	signed int pwm = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	pwm = (signed int)((iAngle - RSI_motor_get_counts( spLt->stPort.iMotor.iTail )) * D_LT_P_GAIN);
	/* PWM出力飽和処理 */
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
/* T.B.D ▲2 */
/*
	超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
	NXTの場合は、40msec周期程度が経験上の最短測定周期です。
	EV3の場合は、要確認
*/
	int iAlert = D_LT_SONAR_ARERT_NON_OBSTRUCTION;
	unsigned int counter = 0;
	
	signed int distance;
	
	if (++counter == 40/4) /* 約40msec周期毎に障害物検知  */
	{
		distance = RSI_ultrasonic_sensor_get_distance(E_LT_PARTS_SONAR_SENSOR);
	if ((distance <= D_LT_SONAR_ALERT_DISTANCE) && (distance >= 0))
	{
		iAlert = D_LT_SONAR_ARERT_OBSTRUCTION; /* 障害物を検知 */
	}
	else
	{
		iAlert = D_LT_SONAR_ARERT_NON_OBSTRUCTION; /* 障害物無し */
	}
		counter = 0;
	}
	
	return iAlert;
}

int lt_get_StopState( void )
{
	int iLoop = 0;
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
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