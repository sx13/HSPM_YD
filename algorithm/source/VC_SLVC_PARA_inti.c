#include "SysCtl_AllHeaders.h"
//#pragma CODE_SECTION(fnInitVCinput_off, "XPRORAM")
#pragma CODE_SECTION(fnInitVCinput_inter, "ramfuncs")


void fnInitVCinput_off(void);
void fnInitVCinput_inter(void);
void fnInitInterg_Encode(void);
extern VECTOR_ST SpeedTest;

extern INTERG Interg_Vector;
void fnInitVCinput_off(void)
{     
 	 VC_SLVC_PARAMETER.fUrate = SysRatedParameter.fMotorRatedVoltage;      //电机线电压额定值
	 VC_SLVC_PARAMETER.fIrate = SysRatedParameter.fMotorRatedCurrent;        //电机额定电流
	 VC_SLVC_PARAMETER.fPrate = SysRatedParameter.fMotorRatedPower * 1000.0;     //电机额定功率，单位(W)
	 VC_SLVC_PARAMETER.fSliprate = SysRatedParameter.fMotorRatedSlip;//0.018;  //电机额定滑差。额定滑差 = (同步转速-额定转速)/同步转速
	 VC_SLVC_PARAMETER.fRs = * pCsvParamAsynRs; //0.025;       //电机参数：定子电阻标幺值0.00835
	 VC_SLVC_PARAMETER.fRr = * pCsvParamAsynRr;//0.012;       //电机参数：转子电阻标幺值0.00606
	 VC_SLVC_PARAMETER.fLlr = * pCsvParamAsynLr;//0.114;     //电机参数：转子漏感标幺值0.12106
	 VC_SLVC_PARAMETER.fLls = * pCsvParamAsynLs;//0.091;     //电机参数：定子漏感标幺值0.08971
	 VC_SLVC_PARAMETER.fLm = * pCsvParamAsynLm;//3.3499;       //电机参数：互感标幺值3.42857
	 VC_SLVC_PARAMETER.fTs = PeriodTime;//0.000237;       //中断周期，单位(s)
	 VC_SLVC_PARAMETER.fIdRef = * pCsvParamExcitCurrentST;// 0.2;        //矢量控制电机励磁电流初始值给定
	 VC_SLVC_PARAMETER.fIqExc = * pCsvParamExcitationCurrent; //0.15;        //SLVC起动激励给定标幺值
	 VC_SLVC_PARAMETER.fTimeExc = * pCsvParamExcitationTime; //1.0;      //SLVC起动激励时间，单位(s)
     
     VC_SLVC_PARAMETER.fFrRef = 0.0;
     VC_SLVC_PARAMETER.fFrFbd = 0.0;//RotorSpeed.fRotorFreqPU;     //VC控制时，电机实际转速反馈

	 VC_SLVC_PARAMETER.uParaTest = 0;//*pCsvParamParamIdentificEN;// 0;       //参数辨识使能，1：参数辨识，0：非参数辨识
     VC_SLVC_PARAMETER.uCtrMethod = 1;//*pCsvParamVCORSLVC;  //0;      //有速度或无速度编码器矢量控制选择，0：有速度(VC)，1：无速度(SLVC)

	 VC_SLVC_PARAMETER.fPhrKp = * pCsvParamPhrKp;//0.0;        //矢量控制转子磁链闭环Kp
     VC_SLVC_PARAMETER.fPhrKi = * pCsvParamPhrKi;//0.0000;     //矢量控制转子磁幢栈稫i
	 VC_SLVC_PARAMETER.fPhrFrLow =*pCsvParamPhrLoopStartFreq; //0.06;        //矢量控制转子磁链闭环频率阀值，当给定频率大于此值时转子磁链闭环


	 VC_SLVC_PARAMETER.fTestKp = 0.01;      //参数辨识电流环Kp
	 VC_SLVC_PARAMETER.fTestKi = 0.0004;    //参数辨识电流环Ki

	 CNT_FR_VALUE = * pCsvParamCNT_FR_VALUE;//异步机转矩计算周期设置
	 if(CNT_FR_VALUE<1)
		CNT_FR_VALUE=1;

	 VC_SLVC_PARAMETER.fSptestFrmin = 0.2;  //矢量控制转速估计环中间频率设定值

	 VC_SLVC_PARAMETER.fCutFre_dc = 0.01;
	 VC_SLVC_PARAMETER.fCutFre_sw = 5.0;

	 VC_SLVC_PARAMETER.pfnVccontrolclear(&VC_SLVC_PARAMETER);  //矢量控制变量清零，目前没有用，暂时先留着。
	 VC_SLVC_PARAMETER.pfnVccontrolinit(&VC_SLVC_PARAMETER);   //矢量控制初始化

     uInterCount = 0;	
     uSoftStartCount = 0;

	 uDirCount=4348;
	 uDirCountMax=0.0; 
	 SpeedTest.fFrRefstop = VC_SLVC_PARAMETER.fFrRefFly;   //待机对飞车搜索频率进行赋值，解决反转与起动方式选择冲突的问题
}

void fnInitVCinput_inter(void)
{
  /*=============================矢量控制速度闭环参数设置============================*/
	VC_SLVC_PARAMETER.fSpdKpmax_VC = 25.0;//* pCsvParamVCSpeedKpMAX;  //3.0;         //有速度编码器矢量控制速度闭环Kp最大值
    VC_SLVC_PARAMETER.fSpdKpmax_SLVC = 10.0;//* pCsvParamSLVCSpeedKpMAX; //2.0;       //无速度编码器矢量控制速度闭环Kp最大值
    VC_SLVC_PARAMETER.fSpdKpmin_VC = 25;//* pCsvParamVCSpeedKpMIN;  //2.0;         //有速度编码器矢量控制速度闭环Kp最小值
    VC_SLVC_PARAMETER.fSpdKpmin_SLVC = 10.0;//* pCsvParamSLVCSpeedKpMIN; //2.0;       //无速度编码器矢量控制速度闭环Kp最小值
    VC_SLVC_PARAMETER.fSpdKi = * pCsvParamSpeedLoopKi; //0.1;               //矢量控制速度闭环Ki
	VC_SLVC_PARAMETER.fSpdLw = * pCsvParamSpeedLOutMin; // -0.1;              //矢量控制速度闭环输出最小值限制
    VC_SLVC_PARAMETER.fSpdUp = * pCsvParamSpeedLOutMax; // 0.1;               //矢量控制速度闭环输出最大值限制

/*=============================矢量控制电流闭环参数设置============================*/
	VC_SLVC_PARAMETER.fCurKp = * pCsvParamCurrentKp;//0.2;               //矢量控制电流闭环Kp
	VC_SLVC_PARAMETER.fCurKi = * pCsvParamCurrentKi;//0.04;              //矢量控制电流闭环Ki

/*===========================矢量控制转子磁链闭环参数设置============================*/
	VC_SLVC_PARAMETER.fPhrLw = * pCsvParamRotorFluxOutMin; //-0.3;              //矢量控制转子磁链闭环输出最小值限制
    VC_SLVC_PARAMETER.fPhrUp = * pCsvParamRotorFluxOutMax; //0.3;               //矢量控制转子磁链闭环输出最大值限制
	VC_SLVC_PARAMETER.fPhrRef = * pCsvParamRotorFluxGiven; //0.92;             //矢量控制转子磁链给定值

/*========================== 矢量控制转速估计闭环参数设置============================*/
	VC_SLVC_PARAMETER.fSptestKp = * pCsvParamSpeedEstKp;//1.0;//1.0;            //矢量控制转速估计闭环Kp
	VC_SLVC_PARAMETER.fSptestKimin = * pCsvParamSpeedEstKiMIN;   //0.001;        //矢量控制转速估计闭环Ki最小值
	VC_SLVC_PARAMETER.fSptestKimid = * pCsvParamSpeedEstKiMID;   //0.08;         //矢量控制转速估计闭环Ki中间值 0.1;
	VC_SLVC_PARAMETER.fSptestKimax = * pCsvParamSpeedEstKiMAX;//0.08;         //矢量控制转速估计闭环Ki最大值 0.1
}

void fnInitInterg_Encode(void)
{
	 Interg_Vector.fKs = 1.0;
	 Interg_Vector.fKp = 314.15926;
	 Interg_Vector.fTs = PeriodTime;
	 Interg_Vector.fFlag = 1;
	 Interg_Vector.fUpLmt = 30000.0;
	 Interg_Vector.fLwLmt = -30000.0;

	 Interg_Vector.fIn = 0.0;
     Interg_Vector.fInformer = 0.0;
     Interg_Vector.fOutformer = 0.0;
     Interg_Vector.fOut = 0.0;
}



