﻿#include "ld.h"
#include "ldin.h"
#include "ldin_recvtable.h"

/* FrameWork */
void ld_recv( S_MSG_DATA* spRecv)
{
	int iMsgId = spRecv->iMsgid;
	F_LD_RECVFUNCPTR pvRecvFunc = (F_LD_RECVFUNCPTR)NULL;
	
	/* 実行関数取得 */
	pvRecvFunc = ld_get_RecvFunc( iMsgId );
	if( (void*)NULL != pvRecvFunc)
	{
		/* 受信関数実行 */
		pvRecvFunc( spRecv );
	}
	
	return;
}

F_LD_RECVFUNCPTR ld_get_RecvFunc( int iMsgId )
{
	F_LD_RECVFUNCPTR func = (F_LD_RECVFUNCPTR)NULL;
	int iNum = 0;
	int iCount = 0;
	S_LD_RECV_TABLE* psRecvTable = (S_LD_RECV_TABLE*)NULL;
	
	/* 受信テーブル設定 */
	psRecvTable =T_LD_RECV_TABLE;
	if((S_LD_RECV_TABLE*)NULL == psRecvTable )
	{
		return (F_LD_RECVFUNCPTR)NULL;
	}
	
	/* 受信テーブル要素数取得 */
	iNum = sizeof( T_LD_RECV_TABLE ) / sizeof( S_LD_RECV_TABLE );
	if( 0 >= iNum )
	{
		return (F_LD_RECVFUNCPTR)NULL;
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
void ld_rcv_test_req( S_MSG_DATA* spRecv )
{
	ld_send_test_res( spRecv );
	return;
}

void ld_rcv_Wupchk_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* LDタスク起動完了済 */
	if( ( E_LD_STATUS_READY != spLd->iStatus) &&
		( D_LD_FLAG_ON != spLd->iWupChk ) )
	{
		ld_send_Wupchk_res();
		spLd->iWupChk = D_LD_FLAG_ON;
	}
	
	return;
}

void ld_rcv_Stop_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	/* すでに停止中の場合は処理しない */
	if( E_LD_STATUS_STOP == spLd->iStatus )
	{
		return;
	}
	
	if( (FILE*)NULL != spLd->fpLdFile )
	{
		fclose(spLd->fpLdFile);
		spLd->fpLdFile = (FILE*)NULL;
	}
	
	spLd->iWupChk = D_LD_FLAG_OFF;
		
	ld_send_Stop_res();
	
	spLd->iStatus = E_LD_STATUS_STOP;
	
	return;
}

void ld_rcv_staRunning_req( S_MSG_DATA* spRecv )
{
	S_LD* spLd = (S_LD*)NULL;
	
	/* グローバル領域取得 */
	spLd = ld_get_Global();
	if( (S_LD*)NULL == spLd )
	{
		return;
	}
	
	spLd->iStatus = E_LD_STATUS_RUN;
	
	return;
}