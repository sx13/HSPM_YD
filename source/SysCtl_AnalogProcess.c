//===========================================================================
//
// 文件名:  SysCtl_AnalogProcess.c
//
// 用途:   	模拟量处理
//
//===========================================================================
#include "SysCtl_AllHeaders.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Device.h"

#define LowVoltTest  0
//==== 片内RAM ====================================
#pragma CODE_SECTION(fnAISample, "ramfuncs")

#if LowVoltTest
float32 fUdcTest = 400.0;
#endif

/***********************************************************
//函数名称：fnAISample
//函数功能：AD采样处理
//函数参数：结构体指针TypeAnalogInput *p
************************************************************/
void fnAISample(TypeAnalogInput *p)
{
//	float32 fLVoltAB,fLVoltBC;
	Uint16 CounterTemp = 0;                          //循环变量
                                                  //
	Uint16 *pADResult = (Uint16*)&AdcRegs.ADCRESULT0;//片上AD结果寄存器指针


	//
	//============= DSP 片上AD ==================
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;//启动SEQ1
    //==============启动DMA=============================
	DMACH1AddrConfig(DMADest1 + uDMA_Addr,DMASource1);
	StartDMACH1();

	uDMA_Addr += 0x80;
    if(uDMA_Addr >= 0x80000) //512K个字
    {
    	uDMA_Addr = 0;
    }
	//==================================================
	while(AdcRegs.ADCST.bit.INT_SEQ1!=1)//查转换状态位
    {}
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;//清除中断标志
                                    //
	AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;//清除中断标志


//===读取DSP AD的模拟采样值

	for(CounterTemp = 0;CounterTemp < 8;CounterTemp++)
	{
	  p->iSysADResult[CounterTemp] = (*(pADResult + CounterTemp)>>4);
	}

//	 p->fADResult[0] = ((p->iSysADResult[0] ) * 0.001221) * 96.154 - 239.02; // 商飞电子负载
	 p->fADResult[0] = ((p->iSysADResult[0] ) * 0.001221) * 24.0 - 60; // 轩宇10kW 电流A
	 p->fADResult[2] = ((p->iSysADResult[1] ) * 0.001221) * 24.0 - 60; // 轩宇10kW 电流C
	 p->fADResult[1] = -(p->fADResult[0] + p->fADResult[2]); // 轩宇10kW 电流B
//	 p->fADResult[2] = ((p->iSysADResult[2] ) * 0.0009768 - 2.0) * 304.60; // 商飞电子负载
//	 p->fADResult[3] = ((p->iSysADResult[3] ) * 0.0009768 - 2.0) * 304.60; // 商飞电子负载
//	 p->fADResult[4] = ((p->iSysADResult[4] ) * 0.0009768 - 2.0) * 304.60; // 商飞电子负载
	 p->fADResult[3] = ((p->iSysADResult[2] ) * 0.0009768 - 2.0) * 500.125 *1.1; // 轩宇10kW 电压A
	 p->fADResult[4] = ((p->iSysADResult[3] ) * 0.0009768 - 2.0) * 500.125 *1.1; // 轩宇10kW 电压B
	 p->fADResult[5] = ((p->iSysADResult[4] ) * 0.0009768 - 2.0) * 500.125 *1.1; // 轩宇10kW 电压C

	 //line[0] = p->fADResult[2] - p->fADResult[3];


//	 p->fADResult[5] = (p->iSysADResult[5] * 0.0004884) * 503.02 - 1.307; // 商飞电子负载

	 p->fADResult[6] = (p->iSysADResult[5] * 0.0004884) * 500.125 + 10; // 轩宇10kW 直流

	 p->fADResult[7] = (p->iSysADResult[6] * 0.001221);  //轩宇10kW NTC1
	 p->fADResult[8] = (p->iSysADResult[7] * 0.001221);  //轩宇10kW NTC2
/*
 for(CounterTemp = 0;CounterTemp < 8;CounterTemp++)
  {
//	if(CounterTemp == 0 || CounterTemp == 1)
//	{
//	  p->iSysADResult[CounterTemp] = (*(pADResult + CounterTemp)>>4) - 1365;//100A中频变频器输出电流0A对应进DSP为1V,进DSP范围为0~2V。
//	  p->fADResult_Offset[CounterTemp] = -0.0007326 * ((float32)p->iSysADResult[CounterTemp]) * SysSamScaParameter.fSysSamValue[CounterTemp];
//	}
//	else if(CounterTemp == 2 || CounterTemp == 3 || CounterTemp == 4)
//	{
//	  p->iSysADResult[CounterTemp] = (*(pADResult + CounterTemp)>>4) - 2048;
//	  p->fADResult_Offset[CounterTemp] = KAnalog * ((float32)p->iSysADResult[CounterTemp]) * SysSamScaParameter.fSysSamValue[CounterTemp];
//	}
//	else if(CounterTemp == 5)
//	{
//	  p->iSysADResult[CounterTemp] = (*(pADResult + CounterTemp)>>4);
//	  p->fADResult_Offset[CounterTemp] = KAnalog * ((float32)p->iSysADResult[CounterTemp]) * SysSamScaParameter.fSysSamValue[CounterTemp];//
//	}
//
//	p->uADResultAnaIn[CounterTemp] = (*(pADResult + CounterTemp)>>4);
//
//	//======== 零漂后的实际值 ====
//	p->fADResult_Offseted[CounterTemp] = p->fADResult_Offset[CounterTemp];
	p->iSysADResult[CounterTemp] = (*(pADResult + CounterTemp)>>4);
  }
 AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;//复位SEQ


	//============ 采样通道 =============
	//IU-->ADCINA0;    	IW-->ADCINB0;
	//VU-->ADCINA1;    	VV-->ADCINB1;
	//VW-->ADCINA2;    	VDC-->ADCINB2;
	//NTC1-->ADCINA3;   NTC2-->ADCINB3;
    p->fLVoltAB = p->fADResult_Offseted[2]-p->fADResult_Offseted[3];
    p->fLVoltBC = p->fADResult_Offseted[3]-p->fADResult_Offseted[4];

   //交流电流
 	p->fADResult[0] = p->fADResult_Offseted[0];  //Iu
 	p->fADResult[1] = -(p->fADResult_Offseted[0] + p->fADResult_Offseted[1]); //Iv
 	p->fADResult[2] = p->fADResult_Offseted[1];  //Iw
 	//交流电压

 	p->fADResult[3] = p->fADResult_Offseted[2]; //Uu
 	p->fADResult[4] = p->fADResult_Offseted[3]; //Uv
 	p->fADResult[5] = p->fADResult_Offseted[4]; //Uw

// 	p->fADResult[3] = D2By3 * (p->fLVoltAB + 0.5 * p->fLVoltBC ); //Uu
// 	p->fADResult[4] = D2By3 * (-0.5 * p->fLVoltAB + 0.5 * p->fLVoltBC); //Uv
// 	p->fADResult[5] = -(p->fADResult[3] + p->fADResult[4]); //Uw
// 	//直流电压
 	p->fADResult[6] = p->fADResult_Offseted[5]; //Vdc  实际值
#if LowVoltTest
 	p->fADResult[6] = fUdcTest;
#endif
*/

 	if(*pARMParamRdFlag == 0xce)
 	{
 	 SysSamDSPtoARM.fSamDSPtoARMIu = p->fADResult[0];
 	 SysSamDSPtoARM.fSamDSPtoARMIv = p->fADResult[1];
 	 SysSamDSPtoARM.fSamDSPtoARMIw = p->fADResult[2];

// 	 if(SysMoore.SysStateNew==SystemRun)
// 	 {
 	 	SysSamDSPtoARM.fSamDSPtoARMUu = p->fADResult[3];
 	 	SysSamDSPtoARM.fSamDSPtoARMUv = p->fADResult[4];
 	 	SysSamDSPtoARM.fSamDSPtoARMUw = p->fADResult[5];
// 	 }
// 	 else
// 	 {
//   	    SysSamDSPtoARM.fSamDSPtoARMUu = 0.0;
// 	    SysSamDSPtoARM.fSamDSPtoARMUv = 0.0;
// 	    SysSamDSPtoARM.fSamDSPtoARMUw = 0.0;
// 	 }

 	 SysSamDSPtoARM.fSamDSPtoARMUdc = p->fADResult[6];
 	}

  	if((SysMoore.SysStateNew == SystemReady) && (SysSampOffset.uSampleOffsetEn == TRUE))
  	{
       SysSampOffset.pfnSysOffsetParameterCal(&SysSampOffset);//计算系统零漂                                                                //
  	}
}
/***********************************************************
//函数名称：fnParaUpdateSysSamScaParameter
//函数功能：采样通道整定参数设定
//函数参数：无
************************************************************/

void fnParaUpdateSysSamScaParameter(void)
{

 Uint16 uLoopNum;

 SysSamScaParameter.fSysSamOutCurrent = *pCsvParamSamOutCurrent;//交流电流DSP 3V对应电流多少A

 SysSamScaParameter.fSysSamNTC1 = *pCsvParamSamNTC1;//NTC1 DSP 3V对应热敏电阻阻止多少欧姆
 SysSamScaParameter.fSysSamNTC2 = *pCsvParamSamNTC2;//NTC2 DSP 3V对应热敏电阻阻止多少欧姆

 SysSamScaParameter.fSysSamOutVoltage = *pCsvParamSamOutVoltage;//交流电压DSP 3V对应电压多少V
  
 SysSamScaParameter.fSysSamDCVoltage = *pCsvParamSamDCVoltage;//直流电压采样DSP 3V对应最大母线电压多少V


 if(SysBaseValue.fCurrBaseValue == 0.0)//为避免分母为0
  SysSamScaParameter.fSysSamValue[0] = 0.0;
 else
  SysSamScaParameter.fSysSamValue[0] = SysSamScaParameter.fSysSamOutCurrent /SysBaseValue.fCurrBaseValue;

 SysSamScaParameter.fSysSamValue[1] = SysSamScaParameter.fSysSamValue[0];

 if((SysBaseValue.fVoltBaseValue) == 0.0)//为避免分母为0
  SysSamScaParameter.fSysSamValue[2] = 0.0;
 else
  SysSamScaParameter.fSysSamValue[2] =  SysSamScaParameter.fSysSamOutVoltage / SysBaseValue.fVoltBaseValue;   //

 SysSamScaParameter.fSysSamValue[4] = SysSamScaParameter.fSysSamValue[3] = SysSamScaParameter.fSysSamValue[2];


 SysSamScaParameter.fSysSamValue[5] = 0.5 * SysSamScaParameter.fSysSamDCVoltage;//DSP 0~3V对应母线电压0~最大值

 for(uLoopNum = 0;uLoopNum < 8;uLoopNum ++)
 {
  //fnVarCopyToRam(sInComm.DSP_RAM,&SysSamScaParameter.fSysSamValue[uLoopNum],(BaseAddr_SysSamVal + (uLoopNum << 1)));// 
 }

}

void fnSysBaseValueCal(TypeSysBaseValue *p)
{
 float32 Temp1,Temp2;//
                     //
 p->fVoltBaseValueGrid = SQRT2By3 * SysRatedParameter.fVFDInputVolatge;	                 	                 
 //====电压基值====
 p->fVoltBaseValue = SQRT2By3 * SysRatedParameter.fMotorRatedVoltage;
 	 	 
 //====转速基值，弧度====
 p->fSpeedBaseValue = PI2 * SysRatedParameter.fMotorRatedFre;
 	 	 
 //====电流基值====                                                       
 p->fCurrBaseValue = SQRT2By3 * SysRatedParameter.fMotorRatedPower * 1000.0 / SysRatedParameter.fMotorRatedVoltage;		
  	 
 //====系统角度基值====
 p->fThetaBaseValue = PI2;	 
 	 
 //====功率基值(3/2) * Vbase * Ibase====
 p->fPowerBaseValue = 1.5 * p->fVoltBaseValue * p->fCurrBaseValue;
  	 
 //====系统阻抗基值Ubase/Ibase====
 p->fZBaseValue = p->fVoltBaseValue/p->fCurrBaseValue;
// 系统导纳基值  added by yp 20180131
 p->fYBaseValue = 1/p->fZBaseValue;
	 	 
 //====系统电感基值====
 p->fLBaseValue = p->fVoltBaseValue/(p->fSpeedBaseValue * p->fCurrBaseValue);
	 	 
 //====系统磁链基值====
 p->fPhirBaseValue = p->fVoltBaseValue/p->fSpeedBaseValue;
	 	 
 //====机械角度基值====
 p->fOmegBaseValue = SysRatedParameter.fMotorRateSpeed * KOmegBase;
	 
 //====系统转矩基值====
 p->fTeBaseValue = p->fPowerBaseValue/p->fOmegBaseValue;
	 
 //====系统转动惯量基值====
 Temp1 = POW2(SysRatedParameter.fMotorPoleNum);//
                                               //	 
 Temp2 = POW3(p->fSpeedBaseValue);//
                                  //
 p->fJBaseValue = (Temp1 * p->fPowerBaseValue)/Temp2;
	 
 //====系统摩擦系数基值====
 p->fFBaseValue = p->fTeBaseValue/p->fOmegBaseValue;
}

/***********************************************************
//函数名称：fnSysOffsetInit
//函数功能：零漂初始化
//函数参数：结构体指针TypeSysOffsetParameter *p
************************************************************/
void fnSysOffsetInit(TypeSysOffsetParameter *p)
{
	Uint16 i;

	p->uOffsetCounter = 0;//

	for(i=0;i<9;i++)
	{
		p->fOffsetValue[i] = *(pOffsetRam+i);
		p->fOffsetAdd[i] = 0;
	}
}

/***********************************************************
//函数名称：fnSysOffsetParameterCal
//函数功能：零漂计算
//函数参数：结构体指针TypeSysOffsetParameter *p
************************************************************/
void fnSysOffsetParameterCal(TypeSysOffsetParameter *p)
{
	Uint32 CounterTemp;

	if(p->uOffsetCounter >= 25000)
	{
		for(CounterTemp = 0;CounterTemp < 9;CounterTemp++)
		{
			p->fOffsetValue[CounterTemp] = p->fOffsetAdd[CounterTemp] / 20000.0;
																			  //
			p->fOffsetAdd[CounterTemp] = 0.0;

			if(CounterTemp>1)
			{
				p->fOffsetUpValue[CounterTemp] = p->fOffsetValue[CounterTemp-1];
			}
			else
				p->fOffsetUpValue[CounterTemp] = p->fOffsetValue[CounterTemp];

			p->fOffsetUpValue[6] = 0.0;
			p->fOffsetUpValue[7] = 0.0;
			p->fOffsetUpValue[8] = 0.0;
			fnVarCopyToRam(sInComm.DSP_RAM,&p->fOffsetUpValue[CounterTemp],(BaseAddr_OffsetCal + (CounterTemp<<1)));//
																  //零漂计算值     
		}
		
		p->uOffsetCounter = 0;
												 
	     p->uSampleOffsetEn = FALSE;
		 *(sInComm.DSP_RAM+926) = 0;
		 *(sInComm.DSP_RAM+927) = 0;
									  
	}
	else if(p->uOffsetCounter < 5000 )
	{
		p->uOffsetCounter++;
	}
	else
	{
		for(CounterTemp = 0;CounterTemp < 8;CounterTemp++)
		{
			p->fOffsetAdd[CounterTemp] += AnalogInput.fADResult_Offset[CounterTemp];
			p->fOffsetAdd[6] = 0.0;//母线电压不能做零漂，母线电压在待机时有值
			p->fOffsetAdd[7] = 0.0;//NTC1热敏电阻不能做零漂，热敏电阻不为0
			p->fOffsetAdd[8] = 0.0;//NTC2热敏电阻不能做零漂，热敏电阻不为0
		}
		p->uOffsetCounter++;
	}  
}

//===========================================================================
// No more.
//===========================================================================

