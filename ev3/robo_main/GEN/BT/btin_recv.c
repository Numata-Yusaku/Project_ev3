#include "bt.h"
#include "btin.h"
#include "btin_recvtable.h"

/* FrameWork */
void bt_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_BT_RECVFUNCPTR pvRecvFunc = (F_BT_RECVFUNCPTR)NULL;
	
	/* ���s�֐��擾 */
	pvRecvFunc = bt_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* ��M�֐����s */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_BT_RECVFUNCPTR bt_get_RecvFunc( int iMsgId )
{
	F_BT_RECVFUNCPTR func = (F_BT_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_BT_RECV_TABLE* psRecvTable = (S_BT_RECV_TABLE*)NULL;
	
	/* ��M�e�[�u���ݒ� */
	psRecvTable =T_BT_RECV_TABLE;
	if((S_BT_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_BT_RECVFUNCPTR)NULL;
	}
	
	/* ��M�e�[�u���v�f���擾 */
	iNum = sizeof( T_BT_RECV_TABLE ) / sizeof( S_BT_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_BT_RECVFUNCPTR)NULL;
	}
	
	/* ��M�֐��T�� */
	for(iCount = 0; iCount < iNum; iCount++)
	{
		if( iMsgId == psRecvTable[iCount].iMsgId )
		{
			func = psRecvTable[iCount].func;
			break;
		}
	}
	
	return func;
}

/* RecvFunc */
void bt_rcv_test_req( S_MSG_DATA* spRecv )
{
	char cSendData[] = {"a4660b1234s"};
//	char cSendData[] = {"p4660"};
	
	bt_set_SerialMessage( cSendData, sizeof(cSendData) - 1 );
	bt_send_test_res( spRecv );
	return;
}

void bt_rcv_Wupchk_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* BT�^�X�N�N�������� */
	if( ( E_BT_STATUS_READY != spBt->iStatus) &&
		( D_BT_FLAG_ON != spBt->iWupChk ) )
	{
		bt_send_Wupchk_res( spRecv );
		spBt->iWupChk = D_BT_FLAG_ON;
	}
	
	return;
}

void bt_rcv_Stop_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	/* ���łɒ�~���̏ꍇ�͏������Ȃ� */
	if( E_BT_STATUS_STOP == spBt->iStatus )
	{
		return;
	}
	
	if( (FILE*)NULL != spBt->BtFile )
	{
		fclose(spBt->BtFile);
		spBt->BtFile = (FILE*)NULL;
	}
	
	spBt->iWupChk = D_BT_FLAG_OFF;
		
	bt_send_Stop_res( spRecv );
	
	spBt->iStatus = E_BT_STATUS_STOP;
	
	return;
}

void bt_rcv_staCalibration_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spBt->iStatus = E_BT_STATUS_CALIBLATE;
	
	return;
}

void bt_rcv_endCalibration_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spBt->iStatus = E_BT_STATUS_WAITING;
	
	return;
}

void bt_rcv_staRunning_req( S_MSG_DATA* spRecv )
{
	S_BT* spBt = (S_BT*)NULL;
	
	/* �O���[�o���̈�擾 */
	spBt = bt_get_Global();
	if( (S_BT*)NULL == spBt )
	{
		return;
	}
	
	spBt->iStatus = E_BT_STATUS_RUN;
	
	return;
}
