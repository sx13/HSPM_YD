/*
// Version: V1.0
//
// Date: 	Dec 21, 2012
//
// Author:	chenchangjiang @YD
//==================================================
//
// 文件名:    SysCtl_ScopeVar.c
//
// 用途:   	  变量波形显示
//
// 函数：     fnVarScopeInit()    //初始化函数
//            fnVarScopeAssign()  //波形变量存储

//==================================================
*/

#include "SysCtl_AllHeaders.h"
//#pragma CODE_SECTION(fnVarScopeAssign, "ramfuncs")
//#pragma CODE_SECTION(fnVarScopeInit, "XPRORAM")

//=========保存Scope数据 ===========================
void fnVarScopeAssign(void)
{

	ScopeDATAUpLoad->VarScope[0] = AnalogInput.fADResult[0];//Iu

	ScopeDATAUpLoad->VarScope[1] = AnalogInput.fADResult[1];//Iv

	ScopeDATAUpLoad->VarScope[2] = PMSM.Ialpha*PMSM.Cur_base;

	ScopeDATAUpLoad->VarScope[3] = PMSM.Ialpha_est;

	ScopeDATAUpLoad->VarScope[4] = PMSM.Ibeta*PMSM.Cur_base;

	ScopeDATAUpLoad->VarScope[5] = PMSM.Ibeta_est;

	ScopeDATAUpLoad->VarScope[6] = AnalogInput.fADResult[6];//Vdc

	ScopeDATAUpLoad->VarScope[7] = PMSM.SpeedRef*60/PI2/PMSM.p;  //

	ScopeDATAUpLoad->VarScope[8] = PMSM.Speed_est*60/PI2/PMSM.p;  //

	ScopeDATAUpLoad->VarScope[9] = PMSM.Iq_ref*PMSM.Cur_base; //

	ScopeDATAUpLoad->VarScope[10] = PMSM.Iq*PMSM.Cur_base; //

	ScopeDATAUpLoad->VarScope[11] = PMSM.Id_ref*PMSM.Cur_base; //

	ScopeDATAUpLoad->VarScope[12] = PMSM.Id*PMSM.Cur_base;

	ScopeDATAUpLoad->VarScope[13] = PMSM.Ud;

	ScopeDATAUpLoad->VarScope[14] = PMSM.Uq;

	ScopeDATAUpLoad->VarScope[15] = PMSM.back_EMF_alpha; //

	ScopeDATAUpLoad->VarScope[16] = PMSM.back_EMF_beta; //

	ScopeDATAUpLoad->VarScope[17] = PMSM.Theta; //

	ScopeDATAUpLoad->VarScope[18] = PMSM.Theta_PLL; //

	ScopeDATAUpLoad->VarScope[19] = PMSM.PI_Speed.out; //

	ScopeDATAUpLoad->VarScope[20] = PMSM.we; //

	ScopeDATAUpLoad->VarScope[21] = AnalogInput.fADResult_Offseted[2];//

	ScopeDATAUpLoad->VarScope[22] = AnalogInput.fADResult_Offseted[3];//

	ScopeDATAUpLoad->VarScope[23] = PMSM.Ls_inv;//
	ScopeDATAUpLoad->VarScope[24] = PMSM.PI_Speed.ui;//
	ScopeDATAUpLoad->VarScope[25] = PMSM.Theta_est;//
	ScopeDATAUpLoad->VarScope[26] = PMSM.Uu;//
	ScopeDATAUpLoad->VarScope[27] = PMSM.Uv;//
	ScopeDATAUpLoad->VarScope[28] = PMSM.Uw;//

	DAOut.fDA_DataCh1 = ScopeDATAUpLoad->VarScope[DAOut.uDA_NumCh1-1];
	DAOut.fDA_DataCh2 = ScopeDATAUpLoad->VarScope[DAOut.uDA_NumCh2-1];
}

//==================================================
// No more.
//==================================================

