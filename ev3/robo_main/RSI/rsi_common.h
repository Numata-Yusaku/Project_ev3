#ifndef	__RSI_COMMON_H__
#define	__RSI_COMMON_H__

/***** �C���N���[�h *****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */


/*** GEN ***/

/*** APL ***/

/***** �萔 *****/
#define		D_RSI_OK		(0)
#define		D_RSI_NG		(-1)

#define		D_RSI_TRUE		(1)
#define		D_RSI_FALSE		(0)

#define		D_RSI_TMAX_FILENAME_LEN (255)

/* ���O�o�� */
#define	D_RSI_FILENAME_MSGLOG		"OutData/RsiLog.csv"

#define	D_RSI_LOGMODE				(D_RSI_TRUE)


/***** �\���� *****/
typedef struct
{
	void*			buffer;		/* ���̃t�@�C�����i�[����Ă���o�b�t�@�ւ̃|�C���^ */
	unsigned int	filesz;		/* �t�@�C���̎��ۂ̃T�C�Y */
	unsigned int	buffersz;	/* �o�b�t�@�̍ő�T�C�Y */
}S_RSI_MEMFILE;


typedef struct
{
	unsigned int	size;									/* �t�@�C���̃T�C�Y */
	unsigned short	date;									/* �t�@�C����Last modified date */
	unsigned short	time;									/* �t�@�C����Last modified time */
	int				is_dir;									/* �t�H���_�ł��邱�Ƃ�\���t���O */
	int				is_readonly;							/* �ǂݏo����p�ł��邱�Ƃ�\���t���O */
	int				is_hidden;								/* �B���t�@�C���ł��邱�Ƃ�\���t���O */
	char			name[D_RSI_TMAX_FILENAME_LEN + 1];		/* �t�@�C���� */
}S_RSI_FILEINFO;

typedef struct
{
	FILE* fpRsiLog;
}S_RSI;

/***** �֐��v���g�^�C�v *****/
void RSI_init( void );
void rsi_set_Global( void );
S_RSI* rsi_get_Global( void );
void rsi_rsilog_open( void );
/***** �e�[�u�� *****/


#endif	/* __RSI_COMMON_H__ */
