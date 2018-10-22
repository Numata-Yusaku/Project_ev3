#include "sensor.h"

/*** sensor ***/

/********************************************************/
/* センサポートを設定する								*/
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
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* センサポートのセンサタイプを取得する					*/
/********************************************************/
unsigned int RSI_sensor_get_type( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],Get Type,%d/%d\n", iPort, iRet );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sensor_get_type( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：センサタイプ */
}

/********************************************************/
/* カラーセンサでカラーを識別する						*/
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
	
	return iRet;	/* Ret：識別したカラー */
}

/*** color_sensor ***/

/********************************************************/
/* カラーセンサで反射光の強さを測定する					*/
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
	
	return ucRet;	/* Ret：反射光の強さ(0-100) */
}

/********************************************************/
/* カラーセンサで環境光の強さを測定する					*/
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
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* カラーセンサでRGB Raw値を測定する					*/
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
/* ジャイロセンサで角位置を測定する						*/
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
	
	return iRet;	/* Ret：角位置 */
}

/********************************************************/
/* ジャイロセンサで角速度を測定する						*/
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
	
	return iRet;	/* Ret：角速度 */
}

/********************************************************/
/* ジャイロセンサの角位置をゼロにリセットする			*/
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
	
	return iRet;	/* Ret：結果 */
}

/*** ultrasonic_sensor ***/

/********************************************************/
/* 超音波センサで距離を測定する							*/
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
	
	return iRet;	/* Ret：距離(%) */
}

/********************************************************/
/* 超音波センサで超音波信号を検出する					*/
/********************************************************/
int RSI_ultrasonic_sensor_listen( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_ultrasonic_sensor_listen( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：検出結果 */
}

/*** infrared_sensor ***/

/********************************************************/
/* IRセンサで距離を測定する								*/
/********************************************************/
signed char RSI_infrared_sensor_get_distance( int iPort )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_infrared_sensor_get_distance( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* IRセンサでIRビーコンの方位と距離を測定する			*/
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
	
	return stSeek;	/* Ret：方位と距離 */
}

/********************************************************/
/* IRセンサでIRビーコンのボタン入力を検出する			*/
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
	
	return stRemote;	/* Ret：ボタン入力のパターン */
}

/*** touch_sensor ***/

/********************************************************/
/* タッチセンサの状態を検出する							*/
/********************************************************/
int RSI_touch_sensor_is_pressed( int iPort )
{
	int iRet = D_RSI_FALSE;
	
#if	(__VC_DEBUG__)
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	/* ログ出力抑制 */
	if( D_RSI_FALSE != iRet )
	{
		fprintf( spRsi->fpRsiLog, "[SENSOR],Touch,%d\n", iRet );
	}
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_touch_sensor_is_pressed( (sensor_port_t)iPort );
#endif	/* __VC_DEBUG__ */
	
	
	return iRet;	/* Ret：押下状態 */
}

/*** ht_nxt_accel_sensor ***/

/********************************************************/
/* 加速度センサ（HiTechnic社製）で加速度を測定する		*/
/********************************************************/
int RSI_ht_nxt_accel_sensor_measure( int iPort, signed short ssAxes )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
//	iRet = (int)ht_nxt_accel_sensor_measure( (sensor_port_t)iPort, (int16_t)ssAxes );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：更新状態 */
}

/*** RSI_nxt_temp_sensor ***/

/********************************************************/
/* NXT温度センサ（9749）で温度を測定する				*/
/********************************************************/
int RSI_nxt_temp_sensor_measure( int iPort, float* fpTemp )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SENSOR],%d\n", iPort );
#else	/* __VC_DEBUG__ */
	iRet = (int)nxt_temp_sensor_measure( (sensor_port_t)iPort, fpTemp );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：更新状態 */
}

