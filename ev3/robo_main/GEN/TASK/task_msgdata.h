#ifndef	__TASK_MSGDATA_H__
#define	__TASK_MSGDATA_H__

/*************************************************************/
/* MSG�ő���M����f�[�^�̒�`�l�^�\���̂��`���邱��		 */
/*************************************************************/
#define	D_TASK_RECVDATA_SIZE			(4)


/* �L�����u���[�V�����p�����[�^�ʒm */
typedef struct
{
	int iSize;
	char aData[D_TASK_RECVDATA_SIZE];
	char cCmd;
}S_TASK_CHGCALIBRATION_RES;


/* �N���C�A���g���M�FGYRO */
typedef struct
{
	int iGyro;
}S_TASK_SETCLIENTSEND_GYRO;


#endif	/* __TASK_MSGDATA_H__ */
