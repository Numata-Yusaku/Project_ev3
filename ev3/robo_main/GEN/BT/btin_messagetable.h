#ifndef	__BTIN_MESSAGETABLE_H__
#define	__BTIN_MESSAGETABLE_H__

/***** �C���N���[�h *****/
#include "btin.h"

/***** �e�[�u�� *****/
/*
	Command
		'a'-'z''A'-'Z'���g�p�\
	Size
		0�̏ꍇ�F��M�f�[�^�𖳎����R�}���h�̂݌��m����
*/

S_BT_MESSAGE_TABLE T_BT_MESSAGE_TABLE[] =
{
	/* Command	,	Size	, Func				*/
	{ 's'		,	0		,	bt_recvCmd_s	},

	/* ��������ɒ�`���邱�� */
	{ ' '		,	-1		,	NULL			},
};

#endif	/* __BTIN_MESSAGETABLE_H__ */
