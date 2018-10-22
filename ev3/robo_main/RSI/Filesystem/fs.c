#include "fs.h"

/*** sdcard ***/

/********************************************************/
/* �f�B���N�g�����I�[�v������							*/
/********************************************************/
int RSI_fs_sdcard_opendir( const char* aName )
{
	int iRet = 0;

#if	(__VC_DEBUG__)
	printf("[FS],@@SD OpenDir@@\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sdcard_opendir( aName );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* �I�[�v���f�B���N�g��ID */
}

/********************************************************/
/* �f�B���N�g�����̃t�@�C������ǂݍ���				*/
/********************************************************/
int RSI_fs_sdcard_readdir( signed int siDirid, S_RSI_FILEINFO* 	spFileinfo )
{
	int iRet = D_RSI_OK;

#if	(__VC_DEBUG__)
	printf("[FS],@@SD ReadDir@@\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sdcard_readdir( (ID)siDirid, (fileinfo_t*)spFileinfo );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* ���� */
}


/********************************************************/
/* �f�B���N�g�����N���[�Y����							*/
/********************************************************/
int RSI_fs_sdcard_closedir( signed int siDirid )
{
	int iRet = D_RSI_OK;

#if	(__VC_DEBUG__)
	printf("[FS],@@SD CloseDir@@\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_sdcard_closedir( (ID)siDirid );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* ���� */
}

/*** memfile ***/

/********************************************************/
/* SD�J�[�h�̃t�@�C�����������t�@�C���Ƃ��ă��[�h����	*/
/********************************************************/
int RSI_fs_memfile_load( const char* aPath, S_RSI_MEMFILE* spMemfile )
{
	int iRet = D_RSI_OK;

#if	(__VC_DEBUG__)
	printf("[FS],@@MemFile Load@@\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_memfile_load( aPath, (memfile_t*)spMemfile );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* ���� */
}

/********************************************************/
/* �������t�@�C�����������								*/
/********************************************************/
int RSI_fs_memfile_free( S_RSI_MEMFILE* spMemfile )
{
	int iRet = D_RSI_OK;

#if	(__VC_DEBUG__)
	printf("[FS],@@MemFile Free@@\n");
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_memfile_free( (memfile_t*)spMemfile );
#endif	/* __VC_DEBUG__ */
	
	return iRet;	/* ���� */
}

/*** Serial ***/

/********************************************************/
/* �V���A���|�[�g���t�@�C���Ƃ��ăI�[�v������			*/
/********************************************************/
FILE* RSI_fs_serial_open_file( int iSerialPort )
{
	FILE* spFile = (FILE*)NULL;

#if	(__VC_DEBUG__)
	spFile = fopen( D_RSI_FS_SERIALPORT, "w+b" );
#else	/* __VC_DEBUG__ */
	spFile = ev3_serial_open_file( (serial_port_t)iSerialPort );
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[FS]","Serial Open",0 ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return spFile;
}

/*** Bluetooth ***/

/********************************************************/
/* 	Bluetooth���ڑ�����Ă��邩�ǂ������`�F�b�N����		*/
/********************************************************/
int RSI_fs_bluetooth_is_connected( void )
{
	int iRet = D_RSI_FALSE;

#if	(__VC_DEBUG__)
	iRet = D_RSI_TRUE;
#else	/* __VC_DEBUG__ */
	iRet = (int)ev3_bluetooth_is_connected();
#endif	/* __VC_DEBUG__ */
#if	(D_RSI_LOGMODE)
	rsi_set_rsilog( "[FS]","BT Connect",iRet ,0 );
#endif	/* D_RSI_LOGMODE */
	
	return iRet;
}
