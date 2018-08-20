
/*
//===========================================================================
//
// 文件名:    SysCtl_Moore.c
//
// 用途:   	  系统状态机
//
// 函数：     fnSysMooreReset()     //系统
//
//            fnSysMooreOut()       //状态输出
//
//===========================================================================
*/
#include "DSP2833x_Device.h"
#include "SysCtl_AllHeaders.h"
#include "DSP2833x_GlobalPrototypes.h"
//#pragma DATA_SECTION(HMIBuffer, "XDATARAM")
  
void fnSystemReadyParam(void);
void fnSystemRUNParam(void);
void fnVarCopyToRam(Uint16 *HeadAddr,float32 *pVarAddr,Uint16 AddrBias);

extern void fnSystemResetParam(void);
extern void fnSysRatedParameter(void);
//extern void fnParaUpdateHVOFF_SysSamScaParameter(void);
extern PIREG PhrPI;

/***********************************************************
//函数名称：fnSysFaultReset
//函数功能：故障复位，内部变量复位
//函数参数：无
************************************************************/
void fnSysFaultReset(void)
{
   SysErrIndexReg.all = 0;
   ARMFaultReg.all = 0;
   DSPFaultCodeReg.all = 0;
}

/***********************************************************
//函数名称：fnSysMooreCal
//函数功能：状态执行
//函数参数：结构体指针TypeSysMoore *p
************************************************************/
void fnSysMooreCal(TypeSysMoore *p)
{
//	Uint32 uState;
  SysCtlReg.all = (Uint16)*pCsvParamSysCtlWord;
  float32 fdata;
  Uint32  udata;
  //float32  udata;
  float32  fARMInterMultiple;
  Uint16   uCarrier;
  Uint16   fDspFiberChopEnable;
 //   dsp_to_arm_fault = DSPFaultCodeReg.all;
//	dsp_to_arm_state = p->SysStateNew;
	if(SysErrIndexReg.bit.SysHFaultFlag == TRUE)//系统重故障
    {
//		p->SysStateNew = SysErr;//系统故障状态

		DEP_DSP_GPWM_ENABLE = 0;

		if(SysCtlReg.bit.ResetInstr == TRUE)//系统复位,等效硬件复位
		{
			fnSysFaultReset();
			fnSystemResetParam();
			SysErrIndexReg.bit.SysHFaultFlag = FALSE;
			//p->SysStateNew = SystemReady;

			SysCtlReg.bit.ResetInstr = FALSE;
			 *(sInComm.DSP_RAM+536) = 0;
			 *(sInComm.DSP_RAM+537) = 0;
		}

    }
	else//非故障状态逻辑切换
    {

		if(p->SysStateNew==SystemRun)
		{
			fnSystemRUNParam();
		}
		else
		{
			DEP_DSP_GPWM_ENABLE = 0;
			fnSystemReadyParam();
		}

 	}

	//载波频率上传
	//*pCsvCarrierFre = 50000.0 / vDSP_GPWM_CARRIER[0]->Reg.CARRIER;

	if(SysConTest.Enable)
	{
		SysConTest.Enable = 0; //20171124gai
		fARMInterMultiple = *pCsvARMInterMultiple;
		fDspFiberChopEnable = (Uint32)*pCsvDspFiberChopEnable;

		udata = (Uint32)*pCsvCarrierFre;
		//udata = (float32)*pCsvCarrierFre;

		if (udata== 0)
			uCarrier = 65530;   //50000 / 0.77k
		else if (udata== 1)
			uCarrier = 25000;   //50000 / 2k
		else if (udata== 2)
			uCarrier = 12500;   //4k
		else if (udata== 3)
			uCarrier = 8333;    //6k
		else if (udata== 4)
			uCarrier = 6250;    //8k
		else if (udata== 5)
			uCarrier = 5000;
		else if (udata== 6)
			uCarrier = 4167;
		else if (udata== 7)
			uCarrier = 3571;
		else if (udata== 8)
			uCarrier = 3125;
		else if (udata== 9)
			uCarrier = 2778;
		else if (udata== 10)
			uCarrier = 2500;
		else if (udata== 11)
			uCarrier = 2273;
		else if (udata== 12)
			uCarrier = 2083;
		else if (udata== 13)
			uCarrier = 1923;
		else if (udata== 14)
			uCarrier = 1786;
		else if (udata== 15)
			uCarrier = 1667;
		else if (udata== 16)
			 uCarrier = 1563;
		else if (udata== 17)
			 uCarrier = 1471;
		else if (udata== 18)
			uCarrier = 1389;
		else if (udata== 19)
			 uCarrier = 1316;
		else if (udata== 20)
			 uCarrier = 1250;
		else if (udata== 21)
			 uCarrier = 1190;
		else if (udata== 22)
			uCarrier = 1136;
		else if (udata== 23)
			uCarrier = 1087;
		else if (udata== 24)
			 uCarrier = 1042;
		else if (udata== 25)
			 uCarrier = 1000;
		else if (udata== 26)
			 uCarrier = 962;
		else if (udata== 27)
			 uCarrier = 926;
		else if (udata== 28)
			 uCarrier = 893;
		else if (udata== 29)
			uCarrier = 862;
		else if (udata== 30)
			 uCarrier = 833;
		else if (udata== 31)
			 uCarrier = 806;
		else if (udata== 32)
			uCarrier = 781;
		else if (udata== 33)
			 uCarrier = 758;
		else if (udata== 34)
			 uCarrier = 735;
		else if (udata== 35)
			 uCarrier = 714;
		else if (udata== 36)
			 uCarrier = 694;
		else if (udata== 37)
			 uCarrier = 676;
		else if (udata== 38)
			 uCarrier = 658;
		else if (udata== 39)
			 uCarrier = 641;
		else if (udata== 40)
			 uCarrier = 625;
		else if (udata== 41)
			 uCarrier = 610;
		else if (udata== 42)
			uCarrier = 595;
		else if (udata== 43)
			 uCarrier = 581;
		else if (udata== 44)
			uCarrier = 568;
		else if (udata== 45)
			uCarrier = 556;
		else if (udata== 46)
			 uCarrier = 543;
		else if (udata== 47)
			uCarrier = 532;
		else if (udata== 48)
			uCarrier = 521;
		else if (udata== 49)
			uCarrier = 510;
		else if (udata== 50)
			uCarrier = 500;
		else
			uCarrier = 25000;



		vDSP_GPWM_CARRIER[0]->Reg.CARRIER = uCarrier;
		vDSP_GPWM_CARRIER[2]->Reg.CARRIER = uCarrier;
		vDSP_GPWM_CARRIER[4]->Reg.CARRIER = uCarrier;
		vDSP_FIBER_CHOP->Reg.DSP_FIBER_CHOP_ENABLE = fDspFiberChopEnable;

		if (udata>=1 && udata<=10 )  //0.76k~20k
		{
			if ((fARMInterMultiple >= 1) && (fARMInterMultiple <= 5))
		        vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = fARMInterMultiple; //luochonggai20171122
		}
		else if (udata>=11 && udata<=20 ) //22k~40k
		{
			if ((fARMInterMultiple >= 2) && (fARMInterMultiple <= 5))
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = fARMInterMultiple;
			else if(vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE < 2)
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = 2;
		}
		else if (udata>=21 && udata<=30 ) //42k~60k
		{
			if ((fARMInterMultiple >= 3) && (fARMInterMultiple <= 5))
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = fARMInterMultiple;
			else if(vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE < 3)
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = 3;
		}
		else if (udata>=31 && udata<=40 ) //62k~80k
		{
			if ((fARMInterMultiple >= 4) && (fARMInterMultiple <= 5))
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = fARMInterMultiple;
			else if(vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE < 4)
				vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = 4;
		}
		else if (udata>=41 && udata<=50 ) //82k~100k
		{
			vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = 5;  //luochonggai20171122
		}
		else if(udata == 0)
		{
			vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE = 1;
		}


		fdata = uCarrier * 0.02 *  vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE; //周期us，2PI/T
		SysVVVFCtrl.fVFPhseCoffic =  PI2 * 0.000001 * fdata;
		SysVoltBase.uCarrCount = uCarrier;

		ChopWave (&SysChoppedWave);

	}
	else
	{
		switch(vDSP_GPWM_CARRIER[0]->Reg.CARRIER)
		{
		case 65530:
			*pCsvCarrierFre = 0.38;
			 break;
		case 25000:
			*pCsvCarrierFre = 1;
			break;
		case 12500:
			*pCsvCarrierFre = 2;
			break;
		case 8333:
			*pCsvCarrierFre = 3;
			break;
		case 6250:
			*pCsvCarrierFre = 4;
			break;
		case 5000:
			*pCsvCarrierFre = 5;
			break;
		case 4167:
			*pCsvCarrierFre = 6;
			break;
		case 3571:
			*pCsvCarrierFre = 7;
			break;
		case 3125:
			*pCsvCarrierFre = 8;
			break;
		case 2778:
			*pCsvCarrierFre = 9;
			break;
		case 2500:
			*pCsvCarrierFre = 10;
			break;
		case 2273:
			*pCsvCarrierFre = 11;
			break;
		case 2083:
			*pCsvCarrierFre = 12;
			break;
        case 1923:
			*pCsvCarrierFre = 13;
			break;
		case 1786:
			*pCsvCarrierFre = 14;
			break;
		case 1667:
			*pCsvCarrierFre = 15;
			break;
		case 1563:
			*pCsvCarrierFre = 16;
			break;
		case 1471:
			*pCsvCarrierFre = 17;
			break;
		case 1389:
			*pCsvCarrierFre = 18;
			break;
		case 1316:
			*pCsvCarrierFre = 19;
			break;
		case 1250:
			*pCsvCarrierFre = 20;
			break;
		case 1190:
			*pCsvCarrierFre = 21;
			break;
		case 1136:
			*pCsvCarrierFre = 22;
			break;
		case 1087:
			*pCsvCarrierFre = 23;
			break;
		case 1042:
			*pCsvCarrierFre = 24;
			break;	
		case 1000:
			*pCsvCarrierFre = 25;
			break;
		case 962:
			*pCsvCarrierFre = 26;
			break;
        case 926:
			*pCsvCarrierFre = 27;
			break;
		case 893:
			*pCsvCarrierFre = 28;
			break;
		case 862:
			*pCsvCarrierFre = 29;
			break;
		case 833:
			*pCsvCarrierFre = 30;
			break;
		case 806:
			*pCsvCarrierFre = 31;
			break;
		case 781:
			*pCsvCarrierFre = 32;
			break;
		case 758:
			*pCsvCarrierFre = 33;
			break;
		case 735:
			*pCsvCarrierFre = 34;
			break;
		case 714:
			*pCsvCarrierFre = 35;
			break;
		case 694:
			*pCsvCarrierFre = 36;
			break;
		case 676:
			*pCsvCarrierFre = 37;
			break;
		case 658:
			*pCsvCarrierFre = 38;
			break;
		case 641:
			*pCsvCarrierFre = 39;
			break;
		case 625:
			*pCsvCarrierFre = 40;
			break;
		case 610:
			*pCsvCarrierFre = 41;
			break;
		case 595:
			*pCsvCarrierFre = 42;
			break;
		case 581:
			*pCsvCarrierFre = 43;
			break;
		case 568:
			*pCsvCarrierFre = 44;
			break;
		case 556:
			*pCsvCarrierFre = 45;
			break;
		case 543:
			*pCsvCarrierFre = 46;
			break;
		case 532:
			*pCsvCarrierFre = 47;
			break;
		case 521:
			*pCsvCarrierFre = 48;
			break;
		case 510:
			*pCsvCarrierFre = 49;
			break;
		case 500:
			*pCsvCarrierFre = 50;
			break;
		default:
			*pCsvCarrierFre = 0;
		}

		*pCsvChopwaveFre = 5000.0 / vDSP_GPWM_CARRIER[6]->Reg.CARRIER;
		*pCsvChopDutyCycle = (vDSP_GPWM_COMP[6]->all / *pCsvChopwaveFre)/5000;
	    *pCsvARMInterMultiple = vDSP_INT_MULTIPLE->Reg.DSP_MULTIPLE;
	    *pCsvDspFiberChopEnable = vDSP_FIBER_CHOP->Reg.DSP_FIBER_CHOP_ENABLE;//光纤斩波使能

	}



}


/***********************************************************
//函数名称：fnSystemInitParam
//函数功能：参数初始化
//函数参数：无
************************************************************/
void fnSystemInitParam(void)
{
	SysErrIndexReg.all = 0;
	ARMFaultReg.all = 0;
	DSPFaultCodeReg.all = 0;
	
	vDSP_GPWM_ENABLE->all = 0;

	SysSampOffset.SampOffsetOnce = 0;
	SysSampOffset.pfnSysOffsetInit(&SysSampOffset);
	SysVoltBase.pfnInit(&SysVoltBase);// 基波电压接口初始化
	SysVVVFCtrl.pfnInit(&SysVVVFCtrl);// VVVF控制初始化
	fnInitInterg_Encode();

	SysVVVFCtrl.fVFPhseCoffic =  0.0157; //lcgai20171127
	SysVoltBase.uCarrCount = 25000; //lcgai20171127
}
/***********************************************************
//函数名称：fnSystemResetParam
//函数功能：参数复位
//函数参数：无
************************************************************/
void fnSystemResetParam(void)
{
	SysVoltBase.pfnReset(&SysVoltBase);// 基波电压接口复位
	SysVVVFCtrl.pfnReset(&SysVVVFCtrl);// VVVF控制参数复位
}
/***********************************************************
//函数名称：fnSystemReadyParam
//函数功能：系统待机状态参数更新
//函数参数：无
************************************************************/
void fnSystemReadyParam(void)
{
  float32 fFreqStart = 0.0;
    FreqEn_DSPtoARM  = 0;
	fnSysRatedParameter();//额定参数更新
	
//	fnARMFaultDetec();//ARM侧故障检测


    SysBaseValue.pfnSysBaseValueCal(&SysBaseValue);//系统基值计算,SysCtl_Drive.c

    fnParaUpdateSysSamScaParameter();//采样整定系数计算

	SysConTest.fVoltageAmp_temp = 0.0;//带电抗器输出幅值清零。

	SysCtlParameter.uStartMode = (Uint16)*pCsvParaStartMod; //控制方式

	//===========零漂使能============
	SysSampOffset.uSampleOffsetEn = (Uint16)*pCsvParaSampleOffset; //零漂使能

	//===========运行环境参数设定============
	SysEnviConfg.uConRunType = (Uint16)*pCsvParaConRunType;
	//SysEnviConfg.uConStrat = (TypeSysControlStrat)*pCsvParaConStrategy;	//revised by SX 20180427
	SysEnviConfg.uVFDLoadType = (TypeSysVFDLoad)*pCsvParaVFDLoadType;

	//===========VF曲线参数设定============
	fFreqStart = *pCsvParamFreqStart;
	SysVVVFCtrl.fFreqRefMin = fFreqStart/SysRatedParameter.fMotorRatedFre;
	SysVVVFCtrl.fVoltRefMin = *pCsvParamVF_VoltMin;
	SysVVVFCtrl.fFreqRefPoint1 = *pCsvParamVF_FreqPoint1;
	SysVVVFCtrl.fVoltRefPoint1 = *pCsvParamVF_VoltPoint1;
	SysVVVFCtrl.fFreqRefPoint2 = *pCsvParamVF_FreqPoint2;
	SysVVVFCtrl.fVoltRefPoint2 = *pCsvParamVF_VoltPoint2;
	SysVVVFCtrl.fFreqRefBase = *pCsvParamVF_FreqMax;
	SysVVVFCtrl.fVoltRefMax = *pCsvParamVF_VoltMax;

	//fnInitVCinput_off();  //Remarked by SX 20180508
	PMSM.Init_Ready(&PMSM);
	SysVoltBase.fUu_base =0.0;
	SysVoltBase.fUv_base =0.0;
	SysVoltBase.fUw_base =0.0;

	//===========运行参数更新============
	fnSystemRUNParam();
}
/***********************************************************
//函数名称：fnSystemReadyParam
//函数功能：系统运行状态参数更新
//函数参数：无
************************************************************/
void fnSystemRUNParam(void)
{
   SysCtlReg.all = (Uint16)*pCsvParamSysCtlWord;
   SysProParamReg.fOCProtect = *pCsvParamOCPrtVal;//电流瞬时保护值
//	fnARMFaultDetec();

   SysEnviConfg.uConStrat = (TypeSysControlStrat)*pCsvParaConStrategy;		//Added by SX 20180427
   PMSM.Init_Run(&PMSM);		//Added by SX 20180508

   //运行参数拷贝到HMIRAM
   fnVarCopyToRam(sInComm.DSP_RAM,&PMSM.Iq_ref,140);//          //转矩电流给定值
   fnVarCopyToRam(sInComm.DSP_RAM,&PMSM.Iq,142);	      // 转矩电流实际值
   fnVarCopyToRam(sInComm.DSP_RAM,&PMSM.Id_ref,144);//		  //励磁电流给定值  SpeedTest
   fnVarCopyToRam(sInComm.DSP_RAM,&PMSM.Id,146);	      // 励磁电流实际值
   fnVarCopyToRam(sInComm.DSP_RAM,&fTimeCount,150);//		 //主中断运行时间，revised by yp 20180131

/* remarked by sunxin 20180417
 *
   float spd_tmp;
   spd_tmp = PMSM.SpeedRef * 60 / PI2 / PMSM.p;
   fnVarCopyToRam(sInComm.DSP_RAM,&spd_tmp,502);	   // 转子转速实际值  revised by yp 20180131
   spd_tmp = PMSM.Speed_est * 60 / PI2 / PMSM.p;
   fnVarCopyToRam(sInComm.DSP_RAM,&spd_tmp,506);	   // 估计转速 revised by yp 20180131
*/

}
/***********************************************************
//函数名称：fnSysParamterRef
//函数功能：非周期性参数刷新
//函数参数：无
************************************************************/
void fnSysParamterRef(void)
{
    if(*pARMParamRdFlag == 0xce)
    {
      if(SysSampOffset.SampOffsetOnce == 0)
      {
     	SysSampOffset.pfnSysOffsetInit(&SysSampOffset);
     	SysSampOffset.SampOffsetOnce = 1;
      }
    }
    DAOut.uDA_NumCh1 = (Uint16)*pCsvParamDACH1;
    if(DAOut.uDA_NumCh1>30) DAOut.uDA_NumCh1 = 30;
    if(DAOut.uDA_NumCh1<1)  DAOut.uDA_NumCh1 = 1;
    DAOut.uDA_NumCh2 = (Uint16)*pCsvParamDACH2;
    if(DAOut.uDA_NumCh2>30) DAOut.uDA_NumCh2 = 30;
    if(DAOut.uDA_NumCh2<1)  DAOut.uDA_NumCh2 = 1;
    *RdDSPtoARM = 0xfa;//DSP主循环正常运行的标志字

}
/***********************************************************
//函数名称：fnVarCopyToRam
//函数功能：参数传递基本函数
//函数参数： HeadAddr：目标起始地址
          pVarAddr：被传递参数起始地址
          AddrBias：偏移地址
************************************************************/
void fnVarCopyToRam(Uint16 *HeadAddr,float32 *pVarAddr,Uint16 AddrBias)
{
	Uint16 *pParaAddr;
	Uint16 uParaL,uParaH;
	pParaAddr = (Uint16*)pVarAddr;
	uParaL = *pParaAddr;
	uParaH = *(pParaAddr + 1);
	*(HeadAddr + AddrBias) = uParaL;
	*(HeadAddr + AddrBias + 1) = uParaH;
}
/***********************************************************
//函数名称：fnSysRatedParameter
//函数功能：额定参数更新
//函数参数：无
************************************************************/
void fnSysRatedParameter(void)                                                                        
{                                                                                                      
	 SysRatedParameter.fMotorRatedVoltage = *pCsvParamMotorRatedVoltage;  //电机额定电压                        
	 SysRatedParameter.fMotorRatedCurrent = *pCsvParamMotorRatedCurrent;  //电机额定电流                        
	 SysRatedParameter.fMotorRatedFre = *pCsvParamMotorRatedFre;          //电机额定频率                        
	 SysRatedParameter.fMotorRatedPower = *pCsvParamMotorRatedPower;      //电机额定功率                        
	 SysRatedParameter.fMotorRateSpeed = *pCsvParamMotorRateSpeed;        //电机额定转速                        
	 SysRatedParameter.fMotorPoleNum = *pCsvParamMotorPoleNum;            //电机极对数                          
	 SysRatedParameter.fMotorRatedSlip = *pCsvParamMotorRatedSlip;        //电机额定滑差                           
	 SysRatedParameter.fVFDInputVolatge = *pCsvParamVFDInputVolatge;      //变频器额定输入电压                      
	 SysRatedParameter.fVFDInputCurrent = *pCsvParamVFDInputCurrent;      //变频器额定输入电流                  
	 SysRatedParameter.fVFDRatedPower = *pCsvParamVFDRatedPower;          //变频器额定功率                      
	 SysRatedParameter.fVFDInputFre = *pCsvParamVFDInputFre;              //变频器额定输入频率                  
	 SysRatedParameter.fVFDOutputVoltage = *pCsvParamVFDOutputVoltage;    //变频器额定输出电压                  
     SysRatedParameter.fVFDOutputCurrent = *pCsvParamVFDOutputCurrent;    //变频器额定输出电流

}
/***********************************************************
//函数名称：fnSysHMICommInit
//函数功能：HMI通讯接口初始化
//函数参数：无
************************************************************/
void fnSysHMICommInit(void)
{
	sInComm.u2LineNumber = 11;  //
	                            //    
	sInComm.u2SerialNumber = 11;//
	                            //
	sInComm.u2ProductNumber = 8;//主控程序版本号008 V06
	                            //
	sInComm.u2FactoryNumber = 6;//
	                            //
	sInComm.DSP_RAM = &HMIBuffer[0];//

	                           //
	sInComm.ARMHandshakeWord=(Uint16 *)0x2803FE;
	sInComm.DSPHandshakeWord=(Uint16 *)0x2803FF;

	sInComm.ReceiveStartAdd=(Uint16 *)0x280000;
	sInComm.DSPtoARMStartAdd=(Uint16 *)0x280000;
	sInComm.WaveID_ADD=(Uint16 *)0x280000;
	sInComm.WaveData_StartADD=(Uint16 *)0x280000;
    sInComm.pfnInit(&sInComm);
}




//===========================================================================
// No more.
//===========================================================================
