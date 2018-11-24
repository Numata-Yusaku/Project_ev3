#include "hw.h"

/*** battery ***/

/********************************************************/
/* バッテリの電流を取得する								*/
/********************************************************/
int RSI_hw_battery_current_mA( void )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = ev3_battery_current_mA();
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[BATTERY]","mA",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret：バッテリーの電流(mA) */
}

/********************************************************/
/* バッテリの電圧を取得する								*/
/********************************************************/
int RSI_hw_battery_voltage_mV( void )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
	iRet = 7500;
#else	/* __VC_DEBUG__ */
	iRet = ev3_battery_voltage_mV();
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[BATTERY]","mV",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret：バッテリーの電圧(mV) */
}

/*** button ***/

/********************************************************/
/* ボタンの押下状態を取得する							*/
/********************************************************/
int RSI_hw_button_is_pressed( int iButton )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
	iRet = D_RSI_TRUE;
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_button_is_pressed( (button_t)iButton );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[BUTTON]","Button/Pressed",iButton ,iRet );
#endif	/* D_RSI_LOGMODE */
	
	
	return iRet;	/* Ret：ボタンの押下状態 */
}

/********************************************************/
/* 指定したボタンのクリックイベントハンドラを設定する	*/
/********************************************************/
int RSI_hw_button_set_on_clicked( int iButton, void* vpHandler, intptr_t exinf )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_button_set_on_clicked( (button_t)iButton, (ISR)vpHandler, exinf );
#endif	/* __VC_DEBUG__ */
	printf("[BUTTON],Button,%d\n",iButton);
	
	return iRet;	/* Ret：設定結果 */
}

/*** led ***/

/********************************************************/
/* LEDライトのカラーを設定する							*/
/********************************************************/
int RSI_hw_led_set_color( int iColor )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LED],Set Color,%d\n",iColor);
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_led_set_color( (ledcolor_t)iColor );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[LED]","Set Color",iColor ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret：設定結果 */
}

/*** speaker ***/

/********************************************************/
/* 音量を調整する										*/
/********************************************************/
int RSI_hw_speaker_set_volume( unsigned char ucVolume )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_set_volume( (uint8_t)ucVolume );
#endif	/* __VC_DEBUG__ */
	printf("[SPK],Set Volume,%d\n",ucVolume);
	
	return iRet;	/* Ret：設定結果 */
}

/********************************************************/
/* 指定した周波数でトーン出力する						*/
/********************************************************/
int RSI_hw_speaker_play_tone( unsigned short usFrequency, signed int siDuration )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
//	printf("\a");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_play_tone( (uint16_t)usFrequency, (int32_t)siDuration );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[SPK]","Freq/Dur",usFrequency ,siDuration );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 指定したWAVファイルを再生する						*/
/********************************************************/
int RSI_hw_speaker_play_file( const S_RSI_FILEINFO* spMemfile, signed int siDuration )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SPK],Durration,%d\n", siDuration );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_play_file( (const memfile_t*)spMemfile, (int32_t)siDuration );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}

/********************************************************/
/* 今再生しているサウンドを停止する						*/
/********************************************************/
int RSI_hw_speaker_stop( void )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SPK],Sound Stop\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_stop();
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret：結果 */
}


