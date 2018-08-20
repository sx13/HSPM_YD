#include "SysCtl_AllHeaders.h"
/***********************************************************
//函数名称：fnVVVFCtrlInterface
//函数功能：VVVF控制算法计算函数，VF三段曲线计算
//函数参数：无
************************************************************/
void fnVVVFCtrlInterface(TypeSysVVVFCal *p)
{
	float Freq_Abs,VfSlope1,VfSlope2,VfSlope3,fDetaTheta;

	FreqEn_DSPtoARM = 0xc3;

	p->fFreqRefGive = FreqRef_ARMtoDSP;  //从ARM侧读给定频率
   //角度计算
	 fDetaTheta = p->fFreqRefGive * SysRatedParameter.fMotorRatedFre * SysVVVFCtrl.fVFPhseCoffic;//周期角度变化
	                                                                     //
	 p->fTheta_base += fDetaTheta;//相位积分
	                              //
	 if(p->fTheta_base > PI2)//正转大于2pi
	                         //
	    p->fTheta_base -= PI2;//
		                      //
	 else if(p->fTheta_base < N_PI2)//反转小于-2pi
	                                //
	    p->fTheta_base += PI2;//

  //幅值计算
    Freq_Abs = fabs(p->fFreqRefGive);

	if (Freq_Abs <= p->fFreqRefMin)
        p->fVoltageAmp = p->fVoltRefMin;
	else if ((Freq_Abs > p->fFreqRefMin)&&(Freq_Abs <= p->fFreqRefPoint1))
       {

        VfSlope1 = (p->fVoltRefPoint1 - p->fVoltRefMin)/(p->fFreqRefPoint1 - p->fFreqRefMin);

        p->fVoltageAmp= p->fVoltRefMin + VfSlope1*(Freq_Abs - p->fFreqRefMin);
       }
	else if ((Freq_Abs > p->fFreqRefPoint1)&&(Freq_Abs <= p->fFreqRefPoint2))
       {
        VfSlope2 = (p->fVoltRefPoint2 - p->fVoltRefPoint1)/(p->fFreqRefPoint2 - p->fFreqRefPoint1);
        p->fVoltageAmp = p->fVoltRefPoint1 + VfSlope2*(Freq_Abs - p->fFreqRefPoint1);
       }
	else if ((Freq_Abs > p->fFreqRefPoint2)&&(Freq_Abs <= p->fFreqRefBase))
       {

        VfSlope3 = (p->fVoltRefMax - p->fVoltRefPoint2)/(p->fFreqRefBase-p->fFreqRefPoint2);

        p->fVoltageAmp = p->fVoltRefPoint2 + VfSlope3*(Freq_Abs - p->fFreqRefPoint2);
       }
    else if (Freq_Abs >= p->fFreqRefBase)
        p->fVoltageAmp = p->fVoltRefMax;
    else
      {;}
	//调制波输出
	   SysVoltBase.fUu_base =  p->fVoltageAmp * sin(p->fTheta_base);//U相电压
		                                            //
	   SysVoltBase.fUv_base =  p->fVoltageAmp * sin(p->fTheta_base + f4_D_3PI);//V相电压
		                                                       //
	   SysVoltBase.fUw_base =  p->fVoltageAmp * sin(p->fTheta_base + f2_D_3PI);//W相电压
}

/***********************************************************
//函数名称：fnUnitTestingInterface
//函数功能：电抗器测试算法计算函数
//函数参数：无
************************************************************/
void fnUnitTestingInterface(TypeSysConTestParam *p)
{
 float32 fDetaTheta = 0.0;

 SysRatedParameter.fMotorRatedFre = *pCsvParamMotorRatedFre;         //频率固定为50Hz
   fDetaTheta = SysRatedParameter.fMotorRatedFre * SysVVVFCtrl.fVFPhseCoffic;// PI2 * PeriodTimeus * 0.000001;
                                                                     //
  p->fTheta_base += fDetaTheta;//相位积分
                              //
 if(p->fTheta_base > PI2)//正转大于2pi
                         //
	 p->fTheta_base -= PI2;//
	                      //
 else if(p->fTheta_base < N_PI2)//反转小于-2pi
                                //
	 p->fTheta_base += PI2;//
	                      //



   //if(SysMoore.SysStateNew == SystemRun)
   {
	   if(p->fVoltageAmp_temp == p->fVoltageAmpSet)
	   {
		   p->fVoltageAmpSet =  *pCsvParamVol_ManualSet;        ///逆变侧电压上限;
	   }

	   if(fabs(p->fVoltageAmpSet - p->fVoltageAmpSetLast) > 0.1001)
	   {
		   p->fVoltageAmpSet = p->fVoltageAmpSetLast;
	   }

	   p->fVoltageAmpSetLast = p->fVoltageAmpSet;
   }


   if(p->fVoltageAmp_temp < p->fVoltageAmpSet)
	   p->fVoltageAmp_temp = p->fVoltageAmp_temp + 0.000002;
   else if(p->fVoltageAmp_temp > p->fVoltageAmpSet + 0.000003)
	   p->fVoltageAmp_temp = p->fVoltageAmp_temp - 0.000002;
   else
	   p->fVoltageAmp_temp = p->fVoltageAmpSet;


   SysVoltBase.fUu_base =  p->fVoltageAmp_temp * sin(p->fTheta_base);//U相电压
	                                            //
   SysVoltBase.fUv_base =  p->fVoltageAmp_temp * sin(p->fTheta_base + f4_D_3PI);//V相电压
	                                                       //
   SysVoltBase.fUw_base =  p->fVoltageAmp_temp * sin(p->fTheta_base + f2_D_3PI);//W相电压

}
/***********************************************************
//函数名称：fnVVVFVarReset
//函数功能：VVVF控制算法复位函数
//函数参数：无
************************************************************/
void fnVVVFVarReset(TypeSysVVVFCal *p)
{

}
/***********************************************************
//函数名称：fnVVVFVarInit
//函数功能：VVVF控制算法初始化函数
//函数参数：无
************************************************************/
void fnVVVFVarInit(TypeSysVVVFCal *p)
{
	float32 fdata;
	fdata = vDSP_GPWM_CARRIER[0]->Reg.CARRIER * 0.001; //周期us
	p->fVFPhseCoffic =  PI2 * 0.000001 * 20 * fdata;

	//SysVoltBase.uCarrCount = vDSP_GPWM_CARRIER[0]->Reg.CARRIER;
}


