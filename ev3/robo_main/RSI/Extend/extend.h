#ifndef	__EXTEND_H__
#define	__EXTEND_H__

/***** �C���N���[�h *****/
#include <stdio.h>
#include "rsi_common.h"

#if	(__VC_DEBUG__)
#else	/* __VC_DEBUG__ */
#include "ev3api.h"
#endif	/* __VC_DEBUG__ */

/*** GEN ***/

/*** APL ***/

/***** �萔 *****/

/***** �\���� *****/

/***** �֐��v���g�^�C�v *****/
/* RTOS */
int RSI_extend_sta_cyc( signed int siCycId );
int RSI_extend_stp_cyc( signed int siCycId );

/***** �e�[�u�� *****/


#endif	/* __EXTEND_H__ */
