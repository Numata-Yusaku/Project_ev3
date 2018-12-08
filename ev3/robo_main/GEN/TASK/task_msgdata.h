#ifndef	__TASK_MSGDATA_H__
#define	__TASK_MSGDATA_H__

/*************************************************************/
/* MSGで送受信するデータの定義値／構造体を定義すること		 */
/*************************************************************/
#define	D_TASK_RECVDATA_SIZE			(4)


/* キャリブレーションパラメータ通知 */
typedef struct
{
	int iSize;
	char aData[D_TASK_RECVDATA_SIZE];
	char cCmd;
}S_TASK_CHGCALIBRATION_RES;


/* クライアント送信：GYRO */
typedef struct
{
	int iGyro;
}S_TASK_SETCLIENTSEND_GYRO;


#endif	/* __TASK_MSGDATA_H__ */
