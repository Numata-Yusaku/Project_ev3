#include "tm.h"
#include "tmin.h"
#include "tmin_recvtable.h"

/* FrameWork */
void tm_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_TM_RECVFUNCPTR pvRecvFunc = (F_TM_RECVFUNCPTR)NULL;
	
//	printf("%08x\n",iMsgId);
	/* 実行関数取得 */
	pvRecvFunc = tm_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* 受信関数実行 */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_TM_RECVFUNCPTR tm_get_RecvFunc( int iMsgId )
{
	F_TM_RECVFUNCPTR func = (F_TM_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_TM_RECV_TABLE* psRecvTable = (S_TM_RECV_TABLE*)NULL;
	
	/* 受信テーブル設定 */
	psRecvTable =T_TM_RECV_TABLE;
	if((S_TM_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_TM_RECVFUNCPTR)NULL;
	}
	
	/* 受信テーブル要素数取得 */
	iNum = sizeof( T_TM_RECV_TABLE ) / sizeof( S_TM_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_TM_RECVFUNCPTR)NULL;
	}
	
	/* 受信関数探索 */
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
void tm_rcv_test_req( S_MSG_DATA* spRecv )
{
	tm_send_test_res( spRecv );
	return;
}
