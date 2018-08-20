
/*
//===========================================================================
//
// 文件名:    SysCtl_ISR.c
//
// 用途:   	  系统主中断
//
//===========================================================================
*/
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_GlobalPrototypes.h"
#include "SysCtl_AllHeaders.h"

extern void DATAPeriodDSPtoARM(void);
extern void DATAPeriodARMtoDSP(void);
extern void SysCurProtect(void);
//extern PMSM_Control PMSM;

/***********************************************************
//函数名称：SysCtl_ISR
//函数功能：系统主中断处理
//函数参数：无
************************************************************/
__interrupt	void SysCtl_ISR(void)
{
	StartCpuTimer0();
    CpuTimer0Regs.TCR.bit.TRB = 1;
	
    DATAPeriodARMtoDSP();    //ARM至DSP周期性数据传递
	//=====================AD采样=======================================
	//
    AnalogInput.pfnAISample(&AnalogInput); //取AD采样结果

    SysCurProtect();//系统电流保护

//=======================算法================================

	 if(SysMoore.SysStateNew == SystemRun)
	 {

	   switch(SysEnviConfg.uVFDLoadType)
	   {
	     case AsynMotor:   //异步电机
	     {
	  	   if((SysEnviConfg.uConStrat == PGVVVF)||(SysEnviConfg.uConStrat == NPGVVVF))//VVVF控制
	  	   {
	  		 SysVVVFCtrl.pfnCalc(&SysVVVFCtrl);
		   }
	  	   else if(SysEnviConfg.uConStrat == VC)           //有感矢量
	  	   {

	  	   }
	  	   else if(SysEnviConfg.uConStrat == SLVC)        //无感矢量
	  	   {
	  		 fnVectorCtrlInterface();
	  	   }
	    	 break;
	     }
	     case SynMotor:    //同步电机
	     {
		   if((SysEnviConfg.uConStrat == PGVVVF)||(SysEnviConfg.uConStrat == NPGVVVF))  //VVVF控制
		   {
			   //I_f control   Added by YP 20180119 || revised by SX 20180419
			   if(PMSM.fre >= 30)
			   {
				   PMSM.Observer(&PMSM);
			   }
			   PMSM.Ia = AnalogInput.fADResult[0]/PMSM.Cur_base;
			   PMSM.Ib = AnalogInput.fADResult[1]/PMSM.Cur_base;
			   PMSM.Ic = AnalogInput.fADResult[2]/PMSM.Cur_base;
			   PMSM.Vdc = AnalogInput.fADResult[6]/PMSM.Vol_base;
			   //PMSM.Ts = vDSP_GPWM_CARRIER[0]->Reg.CARRIER*0.02*fusToS * vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE;
			   PMSM.I_f_Calc(&PMSM);
			   PMSM.Uu = (Uint16)(PMSM.Ta * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//U光纤板电压			  												   //
			   PMSM.Uv = (Uint16)(PMSM.Tb * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//V光纤板电压
			   PMSM.Uw = (Uint16)(PMSM.Tc * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//W光纤板电压
			   InvModuWave(PMSM.Uu,PMSM.Uv,PMSM.Uw);
			   DEP_DSP_GPWM_ENABLE = 1;
		   }
		   else if(SysEnviConfg.uConStrat == VC)   //有感矢量
		   {
			   PMSM.Swit(&PMSM);
			   PMSM.Observer(&PMSM);
			   PMSM.Ia = AnalogInput.fADResult[0]/PMSM.Cur_base;
			   PMSM.Ib = AnalogInput.fADResult[1]/PMSM.Cur_base;
			   PMSM.Ic = AnalogInput.fADResult[2]/PMSM.Cur_base;
			   PMSM.Vdc = AnalogInput.fADResult[6]/PMSM.Vol_base;
			   PMSM.I_f_Calc(&PMSM);
			   PMSM.Uu = (Uint16)(PMSM.Ta * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//U光纤板电压			  												   //
			   PMSM.Uv = (Uint16)(PMSM.Tb * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//V光纤板电压
			   PMSM.Uw = (Uint16)(PMSM.Tc * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//W光纤板电压
			   InvModuWave(PMSM.Uu,PMSM.Uv,PMSM.Uw);
			   DEP_DSP_GPWM_ENABLE = 1;
		   }
		   else if(SysEnviConfg.uConStrat == SLVC)  //无感矢量
		   {
			   //sensorless vector control   Added by YP 20180119 || revised by SX 20180419
			   PMSM.Observer(&PMSM);
			   PMSM.Ia = AnalogInput.fADResult[0]/PMSM.Cur_base;
			   PMSM.Ib = AnalogInput.fADResult[1]/PMSM.Cur_base;
			   PMSM.Ic = AnalogInput.fADResult[2]/PMSM.Cur_base;
			   PMSM.Vdc = AnalogInput.fADResult[6]/PMSM.Vol_base;
			   //PMSM.Ts = vDSP_GPWM_CARRIER[0]->Reg.CARRIER*0.02*fusToS * vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE;
			   PMSM.SLVC_Calc(&PMSM);
			   PMSM.Uu = (Uint16)(PMSM.Ta * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//U光纤板电压			  												   //
			   PMSM.Uv = (Uint16)(PMSM.Tb * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//V光纤板电压
			   PMSM.Uw = (Uint16)(PMSM.Tc * vDSP_GPWM_CARRIER[0]->Reg.CARRIER);//W光纤板电压
			   InvModuWave(PMSM.Uu,PMSM.Uv,PMSM.Uw);
			   DEP_DSP_GPWM_ENABLE = 1;
		   }
	    	 break;
	     }
	     case Reactor:   //电抗器测试
	     {
	    	 SysConTest.pfnCalc(&SysConTest);
	    	 break;
	     }
	     default:break;
	   }
	   //commented by YP 20180119 because SVPWM is used instead of SPWM
		// SysVoltBase.pfnCalc(&SysVoltBase);  //系统电压基波计算，算法统一接口
	 }
	 else
	 {
		 SysConTest.fVoltageAmpSet = 0;
		 SysConTest.fVoltageAmp_temp = 0;
		 SysConTest.fVoltageAmpSetLast = 0;

		 DEP_DSP_GPWM_ENABLE = 0;
	 }

	 if(SysEnviConfg.uVFDLoadType == Reactor)
		 	 *pCsvParamVol_ManualSet = SysConTest.fVoltageAmpSet;
//===================算法结束=============================================

	 DATAPeriodDSPtoARM();//DSP周期性数据上传
	 if(SysMoore.SysStateNew != SysErr)
	 {
	    fnVarScopeAssign();//软件示波器数据更新
	 }

  	StopCpuTimer0();
	fTimeCount = (CpuTimer0Regs.PRD.all - CpuTimer0Regs.TIM.all)*0.0133333;  //测试中断执行时间

	PieCtrlRegs.PIEACK.bit.ACK1 = 1;//
}

__interrupt	void local_DINTCH1_ISR(void)
{
	//int i;
	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
}

__interrupt void epwm1_isr(void)
{
   //EPwm1TimerIntCount++;

   // Clear INT flag for this timer
   EPwm1Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

__interrupt void epwm2_isr(void)
{
   //EPwm2TimerIntCount++;

   // Clear INT flag for this timer
   EPwm2Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

__interrupt void epwm3_isr(void)
{
   //EPwm3TimerIntCount++;

   // Clear INT flag for this timer
   EPwm3Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

__interrupt void epwm4_isr(void)
{
   //EPwm4TimerIntCount++;

   // Clear INT flag for this timer
   EPwm4Regs.ETCLR.bit.INT = 1;

   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
/***********************************************************
//函数名称：DATAPeriodDSPtoARM
//函数功能：汇总系统周期性数据传递 DSP->ARM
//函数参数：无
************************************************************/
void DATAPeriodDSPtoARM(void)
{
	FltWord_DSPtoARM = SysErrIndexReg.all;
 	if(*pARMParamRdFlag == 0xce)
	MemCopy((Uint16*)&SysSamDSPtoARM.fSamDSPtoARMIu,(Uint16*)&SysSamDSPtoARM.fSamDSPtoARMIu + 18,(Uint16*)&DMABuf1[80]);//采样数据传递
 	sInComm.pfnWaveDisplay(&sInComm);//实时波形数据传递
	DAC_DSPtoARM1 = DAOut.fDA_DataCh1;//DA通道1数据传递
	DAC_DSPtoARM2 = DAOut.fDA_DataCh2;//DA通道2数据传递
}
/***********************************************************
//函数名称：DATAPeriodARMtoDSP
//函数功能：汇总系统周期性数据传递 ARM->DSP
//函数参数：无
************************************************************/
void DATAPeriodARMtoDSP(void)
{
    SysMoore.SysStateNew = (TypeSysMooreState)StMach_ARMtoDSP;//读ARM侧状态机
    SysVVVFCtrl.fFreqRefGive = FreqRef_ARMtoDSP;  //从ARM侧读给定频率
}
/***********************************************************
//函数名称：SysCurProtect
//函数功能：系统瞬时过流保护
//函数参数：无
************************************************************/
void SysCurProtect(void)
{
    if(SysMoore.SysStateNew == SystemRun && \
    		(AnalogInput.fADResult[0] > SysProParamReg.fOCProtect || \
    		 AnalogInput.fADResult[1] > SysProParamReg.fOCProtect || \
			 AnalogInput.fADResult[2] > SysProParamReg.fOCProtect ))
    {
    	DEP_DSP_GPWM_ENABLE = 0;
    	//SysMoore.SysStateNew = SysErr;
    	SysErrIndexReg.bit.SysHFaultFlag = TRUE;
    }
}
//===========================================================================
// No more.
//===========================================================================

