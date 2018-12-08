#include "ltin.h"

void lt_balance_init( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	spLt->stBalanceInfo.fErr_theta = 0.0F;
	spLt->stBalanceInfo.fPsi = 0.0F;
	spLt->stBalanceInfo.fThetaLpf = 0.0F;
	spLt->stBalanceInfo.fThetaRef = 0.0F;
	spLt->stBalanceInfo.fThetadotCmdLpf = 0.0F;
	
	return;
}

void lt_balance_set_BalanceInfo( void )
{
	S_LT* spLt = (S_LT*)NULL;
	S_LT_BALANCE_CONTROL* spBalanceControl = NULL;
	
	float fTmpTheta = 0.0;
	float fTmpThetaLpf = 0.0;
	float fTmpPwmRightLimiter = 0.0;
	float fTmpPsidot = 0.0;
	float fTmpPwmTurn = 0.0;
	float fTmpPwmLeftLimiter = 0.0;
	float fTmpThetadotCmdLpf = 0.0;
	float fTmp[4];
	float fTmpTheta_0[4];
	long lTmp_0;
	float fK_F[4];
	
	/* 初期化 */
	memset( &fTmp, 0x00, sizeof(fTmp) );
	memset( &fTmpTheta_0, 0x00, sizeof(fTmpTheta_0) );
	memset( &lTmp_0, 0x00, sizeof(lTmp_0) );
	memset( &fK_F, 0x00, sizeof(fK_F) );
	
	/* フィードバック係数設定 */
	fK_F[0] = D_LT_K_F1;
	fK_F[1] = D_LT_K_F2;
	fK_F[2] = D_LT_K_F3;
	fK_F[3] = D_LT_K_F4;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* バランスコントロールパラメータ取得 */
	spBalanceControl = &(spLt->stBacanceControl);
	if( (S_LT_BALANCE_CONTROL*)NULL == spBalanceControl )
	{
		return;
	}
	
	spBalanceControl->fGyroOffset = D_LT_GYRO_OFFSET;
	
	fTmpThetadotCmdLpf = 
		( ( ( spBalanceControl->fCmdForward / D_LT_CMD_MAX ) * D_LT_K_THETADOT ) * ( 1.0F- D_LT_A_R ) ) + (D_LT_A_R * spLt->stBalanceInfo.fThetadotCmdLpf );
	
	fTmpTheta = 
		(((D_LT_DEG2RAD * spBalanceControl->fThetaMLeft) + spLt->stBalanceInfo.fPsi) + ((D_LT_DEG2RAD * spBalanceControl->fThetaMRight) + spLt->stBalanceInfo.fPsi)) * 0.5F;
	
	fTmpThetaLpf = ((1.0F - D_LT_A_D) * fTmpTheta) + (D_LT_A_D * spLt->stBalanceInfo.fThetaLpf);
	
	fTmpPsidot = (spBalanceControl->fGyro - spBalanceControl->fGyroOffset) * D_LT_DEG2RAD;
	
	fTmp[0] = spLt->stBalanceInfo.fThetaRef;
	fTmp[1] = 0.0F;
	fTmp[2] = fTmpThetadotCmdLpf;
	fTmp[3] = 0.0F;
	fTmpTheta_0[0] = fTmpTheta;
	fTmpTheta_0[1] = spLt->stBalanceInfo.fPsi;
	fTmpTheta_0[2] = (fTmpThetaLpf - spLt->stBalanceInfo.fThetaLpf) / D_LT_EXEC_PERIOD;
	fTmpTheta_0[3] = fTmpPsidot;
	fTmpPwmRightLimiter = 0.0F;
	
	for (lTmp_0 = 0; lTmp_0 < 4; lTmp_0++)
	{
	  fTmpPwmRightLimiter += (fTmp[lTmp_0] - fTmpTheta_0[lTmp_0]) * fK_F[(lTmp_0)];
	}
	
	fTmpPwmRightLimiter = (((D_LT_K_I * spLt->stBalanceInfo.fErr_theta) + fTmpPwmRightLimiter) /
	((D_LT_BATTERY_GAIN * spBalanceControl->fBattery) - D_LT_BATTERY_OFFSET)) * 100.0F;
	
	fTmpPwmTurn = (spBalanceControl->fCmdTurn / D_LT_CMD_MAX) * D_LT_K_PHIDOT;
	
	fTmpPwmLeftLimiter = fTmpPwmRightLimiter + fTmpPwmTurn;
	
	fTmpPwmLeftLimiter = rt_SATURATE(fTmpPwmLeftLimiter, -100.0F, 100.0F);
	
	spBalanceControl->scPwmLeft = (signed char)fTmpPwmLeftLimiter;
	
	fTmpPwmRightLimiter -= fTmpPwmTurn;
	
	fTmpPwmRightLimiter = rt_SATURATE(fTmpPwmRightLimiter, -100.0F, 100.0F);
	
	spBalanceControl->scPwmRight = (signed char)fTmpPwmRightLimiter;
	
	fTmpPwmLeftLimiter = (D_LT_EXEC_PERIOD * fTmpThetadotCmdLpf) + spLt->stBalanceInfo.fThetaRef;
	
	fTmpPwmTurn = (D_LT_EXEC_PERIOD * fTmpPsidot) + spLt->stBalanceInfo.fPsi;
	
	fTmpPwmRightLimiter = ((spLt->stBalanceInfo.fThetaRef - fTmpTheta) * D_LT_EXEC_PERIOD) + spLt->stBalanceInfo.fErr_theta;
	
	/* バランス情報更新 */
	spLt->stBalanceInfo.fErr_theta = fTmpPwmRightLimiter;
	spLt->stBalanceInfo.fThetaRef = fTmpPwmLeftLimiter;
	spLt->stBalanceInfo.fThetadotCmdLpf = fTmpThetadotCmdLpf;
	spLt->stBalanceInfo.fPsi = fTmpPwmTurn;
	spLt->stBalanceInfo.fThetaLpf = fTmpThetaLpf;
	
	return;
}

void lt_balance_set_BacklashCancel( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return;
	}
	
	/* 左モータ */
	if(spLt->stBacanceControl.scPwmLeft < 0)
	{
		spLt->stBacanceControl.fThetaMLeft += D_LT_BACKLASH_HALF;
	}
	else if(spLt->stBacanceControl.scPwmLeft > 0)
	{
		spLt->stBacanceControl.fThetaMLeft -= D_LT_BACKLASH_HALF;
	}
	else
	{
		/* フェール処理 */
	}
	
	/* 右モータ */
	if(spLt->stBacanceControl.scPwmRight < 0)
	{
		spLt->stBacanceControl.fThetaMRight += D_LT_BACKLASH_HALF;
	}
	else if(spLt->stBacanceControl.scPwmRight > 0)
	{
		spLt->stBacanceControl.fThetaMRight -= D_LT_BACKLASH_HALF;
	}
	else
	{
		/* フェール処理 */
	}
	
	return;
}

int lt_balance_set_MotorPower( void )
{
	S_LT* spLt = (S_LT*)NULL;
	
	/* グローバル領域取得 */
	spLt = lt_get_Global();
	if( (S_LT*)NULL == spLt )
	{
		return D_LT_NG;
	}
	
	/* 転倒判定 */
	if ( ( ( D_LT_PWM_MAX <= spLt->stBacanceControl.scPwmLeft ) &&
			( D_LT_PWM_MAX <= spLt->stBacanceControl.scPwmRight ) ) ||
		( ( D_LT_PWM_MIN >= spLt->stBacanceControl.scPwmLeft ) &&
			( D_LT_PWM_MIN >=spLt->stBacanceControl.scPwmRight ) ) )
	{
		/* 転倒している */
		spLt->iFallDownCount++;
		if( D_LT_FALLDOWNTIME == spLt->iFallDownCount )
		{
			/* タイムアウトで走行停止*/
			RSI_motor_stop( spLt->stPort.iMotor.iLeftWheel, D_LT_TRUE);
			RSI_motor_stop( spLt->stPort.iMotor.iRightWheel, D_LT_TRUE);
			
			spLt->iStatus = E_LT_STATUS_STOP_WAIT;
			
			return D_LT_NG;
		}
	}
	else
	{
		/* 転倒していない */
		spLt->iFallDownCount = 0;
	}
	
	/* 左車輪 */
	if (spLt->stBacanceControl.scPwmLeft == 0)
	{
		RSI_motor_stop( spLt->stPort.iMotor.iLeftWheel, D_LT_TRUE);
	}
	else
	{
		RSI_motor_set_power(spLt->stPort.iMotor.iLeftWheel, (int)spLt->stBacanceControl.scPwmLeft);
	}
	
	/* 右車輪 */
	if (spLt->stBacanceControl.scPwmRight == 0)
	{
		RSI_motor_stop( spLt->stPort.iMotor.iRightWheel, D_LT_TRUE);
	}
	else
	{
		RSI_motor_set_power(spLt->stPort.iMotor.iRightWheel, (int)spLt->stBacanceControl.scPwmRight);
	}
	
	return D_LT_OK;
}
