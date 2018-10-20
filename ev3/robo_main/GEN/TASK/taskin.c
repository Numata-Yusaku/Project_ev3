#include "taskin.h"

S_TASK* gspTask = (S_TASK*)NULL;
S_MSG_QUE pgQue[E_TASK_TASKID_NUM];

/* startup */
void task_init_que( void )
{
	memset( pgQue, 0x00, ( sizeof( S_MSG_QUE )* E_TASK_TASKID_NUM) );
	
	return;
}

void task_sleep( int iCycle )
{
	
#if	(__VC_DEBUG__)
	Sleep(iCycle);
#else	/* __VC_DEBUG__ */
	
#endif	/* __VC_DEBUG__ */
	return;
}

/* global */
void task_set_Global( void )
{
	S_TASK* spTask = (S_TASK*)NULL;
	
	spTask = (S_TASK*)malloc( sizeof(S_TASK) );
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	/* ������ */
	memset( spTask, 0x00, sizeof(S_TASK) );
	
	/*** �������l�ݒ� ***/
	
	/* �O���[�o���ݒ� */
	gspTask = spTask;
	
	return;
}

S_TASK* task_get_Global( void )
{
	return (S_TASK*)gspTask;
}

/* Message */
int task_msgsend( int iTask, S_MSG_DATA* spPara )
{
	S_MSG_QUE* psQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* psSend = (S_MSG_DATA*)NULL;
	void* psData = (void*)NULL;
	
	/* �����`�F�b�N */
	if(E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara )
	{
		return D_TASK_NG;
	}
	
	/* �̈�m�� */
	psSend = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if((S_MSG_DATA*)NULL == psSend)
	{
		goto END;
	}
	memset( psSend, 0x00, sizeof( S_MSG_DATA ) );
	
	/* �L���[�擾 */
	psQue = &pgQue[iTask];
	if( (S_MSG_QUE*)NULL == psQue )
	{
		goto END;
	}
	
	/* �L���[��� */
	if( D_TASK_QUE_MAX <= psQue->stStatus.iNum )
	{
		printf( "que over: %08x\n",iTask);
		goto END;
	}
	
	/* ���M�f�[�^�ޔ� */
	psSend->iMsgid = spPara->iMsgid;
	psSend->iSize = spPara->iSize;
	if( 0 >= psSend->iSize )
	{
		goto END;
	}
	
	psData = (void*)malloc( psSend->iSize );
	if ((void*)NULL == psData)
	{
		goto END;
	}
	memset( psData, 0x00, psSend->iSize );
	memcpy( psData, spPara->vpPara, psSend->iSize );
	psSend->vpPara = psData;
	
	psQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	
	/*** �f�[�^�ݒ� ***/
	/* ID */
	psQue->stData[psQue->stStatus.iTail].iMsgid = psSend->iMsgid;
	/* �p�����[�^�T�C�Y */
	psQue->stData[psQue->stStatus.iTail].iSize = psSend->iSize;
	/* �p�����[�^�A�h���X */
	psQue->stData[psQue->stStatus.iTail].vpPara = psSend->vpPara;
	
	/* ���O�o�� */
	task_msglog( E_TASK_MSGDIR_SEND, iTask, psSend->iMsgid );
	
	/*** ��ԍX�V ***/
	/* �L���[�� */
	psQue->stStatus.iNum++;
	/* �I�[ */
	psQue->stStatus.iTail++;
	
	/* �I�[�̏ꍇ�͐擪�ɖ߂� */
	if (D_TASK_QUE_MAX == psQue->stStatus.iTail)
	{
		psQue->stStatus.iTail = 0;
	}
	
	/************/
	psQue->stStatus.iFlag = D_TASK_MODE_OFF;	
	
	/*** ������� ***/
	if ((S_MSG_DATA*)NULL != psSend)
	{
		free( psSend );
		psSend = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_OK;

END:
	/*** ������� ***/
	if ( (S_MSG_DATA*)NULL != psSend)
	{
		free( psSend );
		psSend = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == psData)
	{
		free( psData );
		psData = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_NG;
}

int task_msgrecv( int iTask, S_MSG_DATA* spPara )
{
	S_MSG_QUE* psQue = (S_MSG_QUE*)NULL;
	S_MSG_DATA* psRecv = (S_MSG_DATA*)NULL;
	void* psData = (void*)NULL;
	
	/* �����`�F�b�N */
	if ( E_TASK_TASKID_NUM < iTask ||
		(S_MSG_DATA*)NULL == spPara)
	{
		return D_TASK_NG;
	}
	
	/* �̈�m�� */
	psRecv = (S_MSG_DATA*)malloc( sizeof( S_MSG_DATA ) );
	if ((S_MSG_DATA*)NULL == psRecv)
	{
		goto END;
	}
	memset( psRecv, 0x00, sizeof( S_MSG_DATA ) );
	
	/* �L���[�擾 */
	psQue = &pgQue[iTask];
	if ((S_MSG_QUE*)NULL == psQue)
	{
		goto END;
	}
	
	/* �C�x���g�Ȃ� */
	if (0 == psQue->stStatus.iNum)
	{
		goto END;
	}
	
	psQue->stStatus.iFlag = D_TASK_MODE_ON;
	/************/
	/*** �f�[�^�擾 ***/
	/* ID */
	psRecv->iMsgid = psQue->stData[psQue->stStatus.iHead].iMsgid;
	/* �p�����[�^�T�C�Y */
	psRecv->iSize = psQue->stData[psQue->stStatus.iHead].iSize;
	/* �p�����[�^�A�h���X */
	psRecv->vpPara = psQue->stData[psQue->stStatus.iHead].vpPara;
	
	psData = (void*)malloc( psRecv->iSize );
	if ((void*)NULL == psData)
	{
		goto END;
	}
	memset( psData, 0x00, psRecv->iSize );
	memcpy( psData, psRecv->vpPara, psRecv->iSize );
	
	/* ���O�o�� */
	task_msglog( E_TASK_MSGDIR_RECV, iTask, psRecv->iMsgid );
	
	/* �o�͂ɐݒ� */
	/* ID */
	spPara->iMsgid = psRecv->iMsgid;
	/* �p�����[�^�T�C�Y */
	spPara->iSize = psRecv->iSize;
	/* �p�����[�^�A�h���X */
	spPara->vpPara = psData;
	
	/*** �f�[�^�N���A ***/
	/* ID */
	psQue->stData[psQue->stStatus.iHead].iMsgid = D_TASK_MSGID_INVALID;
	/* �p�����[�^�T�C�Y */
	psQue->stData[psQue->stStatus.iHead].iSize = 0;
	/* �p�����[�^�A�h���X */
	if( (void*)NULL != psQue->stData[psQue->stStatus.iHead].vpPara)
	{
		free( psQue->stData[psQue->stStatus.iHead].vpPara );
		psQue->stData[psQue->stStatus.iHead].vpPara = (void*)NULL;
		psRecv->vpPara = (void*)NULL;
	}
	
	/*** ��ԍX�V ***/
	/* �L���[�� */
	psQue->stStatus.iNum--;
	/* �擪 */
	psQue->stStatus.iHead++;
	
	/* �I�[�̏ꍇ�͐擪�ɖ߂� */
	if (D_TASK_QUE_MAX == psQue->stStatus.iHead)
	{
		psQue->stStatus.iHead = 0;
	}
	
	/************/
	psQue->stStatus.iFlag = D_TASK_MODE_OFF;
	
	return D_TASK_OK;

END:
	/*** ������� ***/
	if ((S_MSG_DATA*)NULL != psRecv)
	{
		free( psRecv );
		psRecv = (S_MSG_DATA*)NULL;
	}
	
	if ((void*)NULL == psData)
	{
		free( psData );
		psData = (S_MSG_DATA*)NULL;
	}
	
	return D_TASK_NG;
}

/* log */
void task_msglog_open( void )
{
#if	(D_TASK_LOGMODE)
	S_TASK* spTask = (S_TASK*)NULL;
	FILE* fpMsgLog = (FILE*)NULL;
	
	spTask = task_get_Global();
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	fpMsgLog = fopen( D_TASK_FILENAME_MSGLOG, "w");
	if( (FILE*)NULL == fpMsgLog )
	{
		return;
	}
	
	/* �O���[�o���ɐݒ� */
	spTask->fpMsgLog = fpMsgLog;
	
	/* �w�b�_�o�� */
	fprintf( fpMsgLog, "Dir[Send/Recv],Task[Que],MsgId[Hex]\n");
#endif	/* D_TASK_LOGMODE */
	
	return;
}

void task_msglog( int iDir, int iTask, int iMsgId )
{
#if	(D_TASK_LOGMODE)
	S_TASK* spTask = (S_TASK*)NULL;
	
	spTask = task_get_Global();
	if( (S_TASK*)NULL == spTask )
	{
		return;
	}
	
	if( (FILE*)NULL == spTask->fpMsgLog )
	{
		return;
	}
	
	switch( iDir )
	{
		case E_TASK_MSGDIR_SEND:
//			printf("[SEND],%08x,0x%08x\n", iTask, iMsgId);
			fprintf( spTask->fpMsgLog, "[SEND],0x%08x,0x%08x\n", iTask, iMsgId );
			break;
		
		case E_TASK_MSGDIR_RECV:
//			printf("[RECV],%08x,0x%08x\n", iTask, iMsgId);
			fprintf( spTask->fpMsgLog, "[RECV],0x%08x,0x%08x\n", iTask, iMsgId );
			break;
		
		default:
			/* �t�F�[������ */
			break;
	}
#endif	/* D_TASK_LOGMODE */
	return;
}

