#include "hw.h"

/*** battery ***/

/********************************************************/
/* �o�b�e���̓d�����擾����								*/
/********************************************************/
int RSI_hw_battery_current_mA( void )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[BATTERY],mA,%d\n",iRet );
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = ev3_battery_current_mA();
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�o�b�e���[�̓d��(mA) */
}

/********************************************************/
/* �o�b�e���̓d�����擾����								*/
/********************************************************/
int RSI_hw_battery_voltage_mV( void )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[BATTERY],mV,%d\n",iRet );
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = ev3_battery_voltage_mV();
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�o�b�e���[�̓d��(mV) */
}

/*** button ***/

/********************************************************/
/* �{�^���̉�����Ԃ��擾����							*/
/********************************************************/
int RSI_hw_button_is_pressed( int iButton )
{
	int iRet = 0;
	
#if	(__VC_DEBUG__)
	iRet = D_RSI_TRUE;
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog, "[BUTTON],Button/Pressed,%d,%d\n",iButton,iRet );
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_button_is_pressed( (button_t)iButton );
#endif	/* __VC_DEBUG__ */
	
	
	return iRet;	/* Ret�F�{�^���̉������ */
}

/********************************************************/
/* �w�肵���{�^���̃N���b�N�C�x���g�n���h����ݒ肷��	*/
/********************************************************/
int RSI_hw_button_set_on_clicked( int iButton, void* vpHandler, intptr_t exinf )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_button_set_on_clicked( (button_t)iButton, (ISR)vpHandler, exinf );
#endif	/* __VC_DEBUG__ */
	printf("[BUTTON],Button,%d\n",iButton);
	
	return iRet;	/* Ret�F�ݒ茋�� */
}

/*** led ***/

/********************************************************/
/* LED���C�g�̃J���[��ݒ肷��							*/
/********************************************************/
int RSI_hw_led_set_color( int iColor )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[LED],Set Color,%d\n",iColor);
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
//	fprintf( spRsi->fpRsiLog,"[LED],Set Color,%d\n",iColor );
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_led_set_color( (ledcolor_t)iColor );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F�ݒ茋�� */
}

/*** speaker ***/

/********************************************************/
/* ���ʂ𒲐�����										*/
/********************************************************/
int RSI_hw_speaker_set_volume( unsigned char ucVolume )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_set_volume( (uint8_t)ucVolume );
#endif	/* __VC_DEBUG__ */
	printf("[SPK],Set Volume,%d\n",ucVolume);
	
	return iRet;	/* Ret�F�ݒ茋�� */
}

/********************************************************/
/* �w�肵�����g���Ńg�[���o�͂���						*/
/********************************************************/
int RSI_hw_speaker_play_tone( unsigned short usFrequency, signed int siDuration )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
//	printf("\a");
#if	(D_RSI_LOGMODE)
	S_RSI* spRsi = rsi_get_Global();
	fprintf( spRsi->fpRsiLog,"[SPK],Freq/Dur,%d,%d\n",usFrequency, siDuration );
#endif	/* D_RSI_LOGMODE */
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_play_tone( (uint16_t)usFrequency, (int32_t)siDuration );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* �w�肵��WAV�t�@�C�����Đ�����						*/
/********************************************************/
int RSI_hw_speaker_play_file( const S_RSI_FILEINFO* spMemfile, signed int siDuration )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SPK],Durration,%d\n", siDuration );
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_play_file( (const memfile_t*)spMemfile, (int32_t)siDuration );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F���� */
}

/********************************************************/
/* ���Đ����Ă���T�E���h���~����						*/
/********************************************************/
int RSI_hw_speaker_stop( void )
{
	int iRet = D_RSI_OK;
	
#if	(__VC_DEBUG__)
	printf("[SPK],Sound Stop\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_speaker_stop();
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* Ret�F���� */
}


