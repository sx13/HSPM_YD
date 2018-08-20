/*=====================================================================================
 File name:        vc_slvc_parameter.C                   
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  VC,SLVC and parameter test               

=====================================================================================
 History:
-------------------------------------------------------------------------------------
2013.05.20  kegy  1.0
-------------------------------------------------------------------------------------*/
#include "SysCtl_AllHeaders.h"

extern VECTOR_ST SpeedTest;
extern CLARKE Vol_clarke;
extern CLARKE Cur_clarke ;
extern PARK Cur_park ;
extern LPF_PLL2  LPF_W ;
extern LPF_PLL3 Spd_LPF ;
extern RATELIMIT Ratelimit ;
extern RATELIMIT SpeedRatelimit ;
extern RATELIMIT CurrentRatelimit ;
extern INTERG Interg_phsAlpha ;
extern INTERG Interg_phsBeta ;
extern INTERG Interg_Deta ;
extern INTERG Interg_Vf ;
extern INTERG Interg_Vfact ;
extern INTERG Interg_Vector ;
extern INTERG interg_pf ;
extern PIREG SpeedTestPI ;
extern PIREG SpeedControl ;
extern PIREG CurrentControl_M ;
extern PIREG CurrentControl_T ;
extern PIREG PhrPI;
extern SLIP Slipspeed ;
extern EXCITCURRENT ExcitingCurrent ;
extern VECTORCONTROL Vector_Control ;
extern SFILTER1ORDER SpeedFilter;
extern SFILTER1OR CurrentFilter ;
extern SFILTER1OR CurrentFilter_D ;
extern SFILTER1OR CurrentFilter_Q ;
//extern PARAMETERTEST Parameter_Test ;
extern RMS_OUT Rms_Para_Vol ;
extern RMS_OUT Rms_Para_Cur ;
extern SPEEDKPKI SpeedKpKi;
extern SPDESTCURVOL SpeedTest_CurVol;
extern IPARK Vol_ipark;
extern ICLARKE Vol_iclarke;
extern Uint32 CNT_FR_VALUE;

#pragma CODE_SECTION(fnVectorCtrlInterface, "ramfuncs")
#pragma CODE_SECTION(pfnVccontrolcalc, "ramfuncs")
void fnVectorCtrlInterface(void);
extern float Max(float a,float b,float c);
extern float Min(float a,float b,float c);

void pfnVccontrolcalc(VCANDSLVCORPARA *v)
{             	   
//	   if(v->uParaTest == 0)//非参数辨识
//	   {
	        if(v->Evaluate_period == 0) //100个中断赋值语句执行一次
			{
	            SpeedKpKi.fSpdKpmax_VC = v->fSpdKpmax_VC;
				SpeedKpKi.fSpdKpmin_VC = v->fSpdKpmin_VC;
				SpeedKpKi.fSpdKpmax_SLVC = v->fSpdKpmax_SLVC;
				SpeedKpKi.fSpdKpmin_SLVC = v->fSpdKpmin_SLVC;
				SpeedKpKi.fSpdKi_VC_SLVC = v->fSpdKi * v->fTs * 4000.0;

				SpeedControl.fOutMax = v->fSpdUp;
				SpeedControl.fOutMin = v->fSpdLw;

				CurrentControl_M.fKp = v->fCurKp;
				CurrentControl_M.fKiTs = v->fCurKi * v->fTs * 4000.0;
				CurrentControl_M.fOutMax = v->fCurUp;
				CurrentControl_M.fOutMin = v->fCurLw;

				CurrentControl_T.fKp = v->fCurKp;
				CurrentControl_T.fKiTs = v->fCurKi * v->fTs * 4000.0;
				CurrentControl_T.fOutMax = v->fCurUp;
				CurrentControl_T.fOutMin = v->fCurLw;

				ExcitingCurrent.fPhrRef = v->fPhrRef;
				ExcitingCurrent.fPhrLwLmt = v->fPhrLw;
				ExcitingCurrent.fPhrUpLmt = v->fPhrUp;

				Vector_Control.fSptestKp = v->fSptestKp;
                Vector_Control.fSptestKimin = v->fSptestKimin * v->fTs * 4000.0;
				Vector_Control.fSptestKimid = v->fSptestKimid * v->fTs * 4000.0; 
				Vector_Control.fSptestKimax = v->fSptestKimax * v->fTs * 4000.0;
				Vector_Control.fSptestKpFly = v->fSptestKpFly;
                Vector_Control.fSptestKiminFly = v->fSptestKiminFly * v->fTs * 4000.0;
				Vector_Control.fSptestKimidFly = v->fSptestKimidFly * v->fTs * 4000.0; 
				Vector_Control.fSptestKimaxFly = v->fSptestKimaxFly * v->fTs * 4000.0;
				Vector_Control.fFrRefFly = v->fFrRefFly;
			}

            v->Evaluate_period++;
			if(v->Evaluate_period >= 100)  v->Evaluate_period = 0;

		    SpeedKpKi.fFrRef = v->fFrRef;
			SpeedKpKi.pfnCalc(&SpeedKpKi);
			SpeedControl.fKp = SpeedKpKi.fSpdKp;
			SpeedControl.fKiTs = SpeedKpKi.fSpdKi; 
			

		     if(v->uCtrMethod == 0) v->uReverse = 0;

		     if((v->fFrRef < 0) && (v->uCtrMethod == 1) && (Vector_Control.uStartCount >= 3 * Vector_Control.uSoftstart))
			 {
				  v->uReverse = 1;
			      if(v->fFrRef > -0.004) v->fFrRef = -0.004;  //由于SLVC在起动后存在激励过程，激励后，电机已经有了一定的转速，因此转速给定不应从零开始
			 }
			 if((v->fFrRef >= 0) && (v->uCtrMethod == 1) && (Vector_Control.uStartCount >= 3 * Vector_Control.uSoftstart))
			 {
				  v->uReverse = 0;
			      if(v->fFrRef < 0.004) v->fFrRef = 0.004;    //由于SLVC在起动后存在激励过程，激励后，电机已经有了一定的转速，因此转速给定不应从零开始
			 }

/*             Cur_clarke.fU = v->fIu;
			 Cur_clarke.fV = v->fIv;
		     Cur_clarke.pfnCalc(&Cur_clarke);

		===================电流两相静止坐标系到两相旋转坐标系转换========================

			 Cur_park.fAlpha = Cur_clarke.fAlpha;
		     Cur_park.fBeta = Cur_clarke.fBeta;
		     Cur_park.fCos = cos(Vector_Control.fThetaVector);
			 Cur_park.fSin = sin(Vector_Control.fThetaVector);
		     Cur_park.pfnCalc(&Cur_park);
			 
			 Vector_Control.fIdAct = Cur_park.fDOut;
			 Vector_Control.fIqAct = Cur_park.fQOut;			 */
            
		     Vector_Control.uReverse = v->uReverse;
		     Vector_Control.fUdcVector = v->fUdc;
			 Vector_Control.fFrAct = v->fFrFbd;
			 Vector_Control.fFrRef = v->fFrRef;
			 Vector_Control.fIuIn = v->fIu;
             Vector_Control.fIvIn = v->fIv;
			 Vector_Control.fUuIn = v->fUu;
		     Vector_Control.fUvIn = v->fUv;
			 Vector_Control.fIdRef = v->fIdRef;
			 Vector_Control.pfnVectorcalc(&Vector_Control);
			 v->fIsdSet = Vector_Control.fIdSet;      //励磁电流给定值输出
			 v->fIsqSet = Vector_Control.fIqSet;      //转矩电流给定值输出
			 v->fIsdAct = Vector_Control.fIdAct;      //励磁电流实际GridConnect.fConFreq = RotorSpeed.fRotorFreqPU;值输出
			 v->fIsqAct = Vector_Control.fIqAct;      //转矩电流实际值输出
			 v->fPhrAct = SpeedTest.fPhr;             //转子磁链实际值输出
			 v->fSpeedTest = Vector_Control.fFrTest;  //SLVC估计转速输出
			 v->fTheta = Vector_Control.fThetaVector; //VC、SLVC同步角度输出
			 v->fUd = Vector_Control.fUsd;            //VC、SLVC励磁电压输出
             v->fUq = Vector_Control.fUsq;            //VC、SLVC转矩电压输出

//	   }
//	   else if(v->uParaTest == 1 && v->uTestOver == 0 && v->uTestFault == 0)//参数辨识并且无参数辨识故障
//	   {
//	       if(v->Evaluate_period == 0) //100个中断赋值语句执行一次
//			{
//				Parameter_Test.fCurKi_SLVC = v->fCurKi * v->fTs * 4000.0;
//				Parameter_Test.fCurKp_SLVC = v->fCurKp;
//				Parameter_Test.fCurUp_SLVC = v->fCurUp;
//				Parameter_Test.fCurLw_SLVC = v->fCurLw;
//				Parameter_Test.fSpdKpmax_SLVC = v->fSpdKpmax_SLVC;
//				Parameter_Test.fSpdKpmin_SLVC = v->fSpdKpmin_SLVC;
//				Parameter_Test.fSpdKpmax_VC = v->fSpdKpmax_VC;
//				Parameter_Test.fSpdKpmin_VC = v->fSpdKpmin_VC;
//				Parameter_Test.fSpdKi = v->fSpdKi * v->fTs * 4000.0;
//				Parameter_Test.fSpdUp = v->fSpdUp;
//				Parameter_Test.fSpdLw = v->fSpdLw;
//				Parameter_Test.fPhrKp = v->fPhrKp;
//				Parameter_Test.fPhrKi = v->fPhrKi * v->fTs * 4000.0;
//				Parameter_Test.fPhrUp = v->fPhrUp;
//				Parameter_Test.fPhrLw = v->fPhrLw;
//				Parameter_Test.fPhrRef = v->fPhrRef;
//				Vector_Control.fSptestKp = v->fSptestKp;
//                Vector_Control.fSptestKimin = v->fSptestKimin * v->fTs * 4000.0;
//				Vector_Control.fSptestKimid = v->fSptestKimid * v->fTs * 4000.0;
//				Vector_Control.fSptestKimax = v->fSptestKimax * v->fTs * 4000.0;
//				Vector_Control.fSptestKpFly = v->fSptestKpFly;
//                Vector_Control.fSptestKiminFly = v->fSptestKiminFly * v->fTs * 4000.0;
//				Vector_Control.fSptestKimidFly = v->fSptestKimidFly * v->fTs * 4000.0;
//				Vector_Control.fSptestKimaxFly = v->fSptestKimaxFly * v->fTs * 4000.0;
//				Vector_Control.fFrRefFly = v->fFrRefFly;
//			}
//
//			v->Evaluate_period++;
//			if(v->Evaluate_period >= 100)  v->Evaluate_period = 0;
//
//			Parameter_Test.fIuPara = v->fIu;
//			Parameter_Test.fIvPara = v->fIv;
//			Parameter_Test.fIwPara = v->fIw;
//			Parameter_Test.fUuin = v->fUu;
//			Parameter_Test.fUvin = v->fUv;
//			Parameter_Test.fUwin = v->fUw;
//			Parameter_Test.pfnParatestcalc(&Parameter_Test);
//			v->fIsdSet = CurrentControl_M.fRef1;      //励磁电流给定值输出
//			v->fIsqSet = CurrentControl_T.fRef1;      //转矩电流给定值输出
//			v->fIsdAct = CurrentControl_M.fFdb1;      //励磁电流实际值输出
//			v->fIsqAct = CurrentControl_T.fFdb1;      //转矩电流实际值出
//			v->fSpeedTest = Vector_Control.fFrTest;
//			v->fUd = Parameter_Test.fUd;                    //参数辨识励磁电压输出
//			v->fUq = Parameter_Test.fUq;                    //参数辨识转矩电压输出
//			v->fTheta = Parameter_Test.fTheta;              //参数辨识同步角度输出
//			v->uTestStep = Parameter_Test.uTestStep;        //参数辨识执行阶段输出
//			v->uTestOver = Parameter_Test.uTestOver;        //参数辨识完成标志位输出
//			v->uTestFault = Parameter_Test.uTestFault;      //参数辨识故障阶段输出
//
//			if(v->uTestFault == 1)
//			{
//			   SysErrStateReg1.bit.Paratest_Step1Fault = 1;//参数辨识第一阶段故障
//			                                      //
//			   fnSysCtl_StopProcess();//封锁输出 0封锁；1恢复
//			                          //
//			   SysErrIndexReg.bit.SysHFaultFlag = 1;//
//			}
//			else if(v->uTestFault == 2)
//			{
//			   SysErrStateReg1.bit.Paratest_Step2Fault = 1;//参数辨识第二阶段故障
//			                                      //
//			   fnSysCtl_StopProcess();//封锁输出 0封锁；1恢复
//			                          //
//			   SysErrIndexReg.bit.SysHFaultFlag = 1;//
//			}
//			else if(v->uTestFault == 3)
//			{
//			   SysErrStateReg1.bit.Paratest_Step3Fault = 1;//参数辨识第三阶段故障
//			                                      //
//			   fnSysCtl_StopProcess();//封锁输出 0封锁；1恢复
//			                          //
//			   SysErrIndexReg.bit.SysHFaultFlag = 1;//
//			}
//
//			if(v->uTestOver == 1)
//			{
//			 v->fParaRs = Parameter_Test.fParaRs;           //参数辨识定子电阻输出(标幺值)
//			 v->fParaRr = Parameter_Test.fParaRr;           //参数辨识转子电阻输出(标幺值)
//			 v->fParaLls = Parameter_Test.fParaLls;         //参数辨识定子漏感输出(标幺值)
//			 v->fParaLlr = Parameter_Test.fParaLlr;         //参数辨识转子漏感输出(标幺值)
//			 v->fParaLm = Parameter_Test.fParaLm;           //参数辨识互感输出(标幺值)
//			}
//	   }
}

void pfnVccontrolinit(VCANDSLVCORPARA *v)
{
         v->fUb = 0.81649658 * v->fUrate;                   //电机相电压峰值
	     v->fIb = 0.81649658 * v->fPrate / v->fUrate;       //电机相电流峰值
         v->uSoftStart = 4000;
	 	 v->fCurLw = -1.0;
		 v->fCurUp = 1.0;
		 v->fSptestLw = -1000.0;
		 v->fSptestUp = 1000.0;
	     v->fTestLw = -1.0;
		 v->fTestUp = 1.0;
		 v->fTheta = 0.0;
		 v->fIsdSet = 0.0;	 
		 v->fIsqSet = 0.0;
//		 v->fFrRef = v->fFrFbd;
		 v->fSpeedTest = 0.0;
		 v->fUd = 0.0;
		 v->fUq = 0.0;
		 v->Evaluate_period = 0;
		 v->uTestOver = 0; //待机状态下使辨识结束标志置0，解决辨识结束后变频器不能再起动问题。
		 v->uTestFault = 0;//待机状态下使辨识阶段故障置0。


 //        if(v->uParaTest == 0)
//		 {
			 Vector_Control.fUbVector = v->fUb;
			 Vector_Control.fThetaVector = 0.0;
			 Vector_Control.fFsRate = v->fSliprate;
			 Vector_Control.fIqExc = v->fIqExc;
	         Vector_Control.fLm = v->fLm;
			 Vector_Control.fLr = v->fLlr + v->fLm;
			 Vector_Control.fFrRef = 0.0;
			 Vector_Control.fIdSet = 0.0;
			 Vector_Control.fIqSet = 0.0; 
			 Vector_Control.uParatest = 0;
			 Vector_Control.uCtrMethod = v->uCtrMethod; //有速度或无速度编码器矢量控制选择，1为无速度，0为有速度
		     Vector_Control.uSoftstart = v->uSoftStart;       //软启动时间设置，启动后在此时间内速度环不工作，励磁给定逐渐增大到给定值，电机建立磁场
		     Vector_Control.fExciteTime = (Uint16)(v->fTimeExc / v->fTs);         //激励时间设置，采用无速度编码器矢量控制时，磁场建立完毕后，即软启动之后，先给电机一个转矩激励，维持时间即だ奔?
			 Vector_Control.pfnVectorinit(&Vector_Control);

			 SpeedKpKi.uMethod = v->uCtrMethod;

			 ExcitingCurrent.fPhrKp = v->fPhrKp;
			 ExcitingCurrent.fPhrKi = v->fPhrKi * v->fTs * 4000.0;
			 ExcitingCurrent.fFrLow = v->fPhrFrLow;

			 Slipspeed.fSlipLm = v->fLm;
			 Slipspeed.fSlipLlr = v->fLlr;
			 Slipspeed.fSlipRr = v->fRr;
			 Slipspeed.fSlipRate = v->fSliprate;

			 SpeedTest.uMethod = v->uCtrMethod;
			 SpeedTest.uParatest = v->uParaTest;
			 SpeedTest.fmin = v->fSptestLw;
		     SpeedTest.fmax = v->fSptestUp;
		     SpeedTest.fPwmTime = v->fTs;
			 SpeedTest.fRs = v->fRs;
			 SpeedTest.fRr = v->fRr;
			 SpeedTest.fLls = v->fLls;
			 SpeedTest.fLlr = v->fLlr;
			 SpeedTest.fLm = v->fLm;
			 SpeedTest.fFrmin = v->fSptestFrmin;
			 SpeedTest.uFlyStart = 0;//v->uSoftStart * 3 + (Uint16)(v->fTimeExc / v->fTs);
			 //SpeedTest.fFrRefstop = v->fFrRefFly;
			 
			 SpeedTest_CurVol.uMethod = v->uCtrMethod;
			 SpeedTest_CurVol.uParatest = v->uParaTest;
			 SpeedTest_CurVol.fCutFre_dc = v->fCutFre_dc;
             SpeedTest_CurVol.fCutFre_sw = v->fCutFre_sw;
			 SpeedTest_CurVol.fmin = v->fSptestLw;
		     SpeedTest_CurVol.fmax = v->fSptestUp;
		     SpeedTest_CurVol.fTs = v->fTs;
			 SpeedTest_CurVol.fRs = v->fRs;
			 SpeedTest_CurVol.fRr = v->fRr;
			 SpeedTest_CurVol.fLs = v->fLls + v->fLm;
			 SpeedTest_CurVol.fLr = v->fLlr + v->fLm;
			 SpeedTest_CurVol.fLm = v->fLm;
			 SpeedTest_CurVol.fFrRefstop = v->fFrRefFly;
//			 SpeedTest_CurVol.fFrmin = v->fSptestFrmin;
		//	 SpeedTest_CurVol.pfnInit(&SpeedTest_CurVol);
 //        }
//         else if(v->uParaTest == 1)
//		 {
//			 Parameter_Test.fUbPara = v->fUb;
//		     Parameter_Test.fIbPara = v->fIb;
//			 Parameter_Test.fUrate = v->fUrate;
//			 Parameter_Test.fIrate = v->fIrate;
//			 Parameter_Test.uParaTest = v->uParaTest;
//			 Parameter_Test.uCtrMethod = SysCtlParameter.fPaIdentAlgor;
////			 Parameter_Test.uCtrMethod = 0;
//			 Parameter_Test.uSoftStart = v->uSoftStart;
//			 Parameter_Test.uTestStep = 1;
//	         Parameter_Test.uParaStart = 10000;
//			 Parameter_Test.fPwmTime = v->fTs;
//			 Parameter_Test.fIqExc = v->fIqExc;
//			 Parameter_Test.fFsRate = v->fSliprate;
//			 Parameter_Test.fNP = v->fNP;
//			 Parameter_Test.fPrate = v->fPrate;
//			 Parameter_Test.uTestOver = 0;
//			 Parameter_Test.fTimeExc = v->fTimeExc;
//			 Parameter_Test.fCurKp = v->fTestKp;
//		     Parameter_Test.fCurKi = v->fTestKi * v->fTs * 4000.0;
//		     Parameter_Test.fLwlimt = v->fTestLw;
//		     Parameter_Test.fUplimt = v->fTestUp;
//		     Parameter_Test.fTs = v->fTs;
//			 Parameter_Test.fPhrFrLow = v->fPhrFrLow;
//	         Parameter_Test.fSptestFrmin = v->fSptestFrmin;
//			 Parameter_Test.fSptestUp = v->fSptestUp;
//			 Parameter_Test.fSptestLw = v->fSptestLw;
//			 Parameter_Test.fCurRef11 = 0.2;       //0.2输入参数：第一阶段电流给定1
//			 Parameter_Test.fCurRef12 = 0.4;       //0.4输入参数：第一阶段电流给定2
//			 Parameter_Test.fCurRef21 = 0.2;       //输入参数：第二阶段电流给定1
//			 Parameter_Test.fCurRef22 = 0.4;       //输入参数：第二阶段电流给定2
//			 Parameter_Test.fFrRefStep3 = 0.6;     //0.6/1输入参数：第三阶段转速时给定
//			 Parameter_Test.pfnParatestinit(&Parameter_Test);
//		 }

		 SpeedKpKi.pfnReset(&SpeedKpKi);
		 
		 ExcitingCurrent.pfnExcurreset(&ExcitingCurrent);
		 
		 Slipspeed.pfnSetinti(&Slipspeed);
/*
		 Interg_Vector.fKs = 1.0;
		 Interg_Vector.fKp = 314.15926;
		 Interg_Vector.fTs = v->fTs;
		 Interg_Vector.fFlag = 1;
		 Interg_Vector.fUpLmt = 30000.0;
		 Interg_Vector.fLwLmt = -30000.0;
*/
		 CurrentFilter_D.fCutFre = 1.0;
		 CurrentFilter_D.fSampFre = 1.0 / v->fTs;
		 CurrentFilter_D.pfnResFilter1order(&CurrentFilter_D);
		 CurrentFilter_D.pfnIniFilter1order(&CurrentFilter_D);
		 CurrentFilter_Q.fCutFre = 1.0;
	 	 CurrentFilter_Q.fSampFre = 1.0 / v->fTs;
		 CurrentFilter_Q.pfnResFilter1order(&CurrentFilter_Q);
		 CurrentFilter_Q.pfnIniFilter1order(&CurrentFilter_Q);

//		 interg_pf.fKp = 1;
//		 interg_pf.fTs = v->fTs;
//		 interg_pf.fFlag = 0;
//		 Spd_LPF.iN = 10.0;

	   if(SysCtlParameter.uStartMode == FLYMOD)
		{
			VC_SLVC_PARAMETER.fSptestKpFly = * pCsvParamSpeedEstKpFly;//1.0;//1.0;            //矢量控制转速估计闭环Kp
			VC_SLVC_PARAMETER.fSptestKiminFly = * pCsvParamSpeedEstKiMINFly;   //0.001;        //矢量控制转速估计闭环Ki最小值
			VC_SLVC_PARAMETER.fSptestKimidFly = * pCsvParamSpeedEstKiMIDFly;   //0.08;         //矢量控制转速估计闭环Ki中间值 0.1;
			VC_SLVC_PARAMETER.fSptestKimaxFly = * pCsvParamSpeedEstKiMAXFly;//0.08;         //矢量控制转速估计闭环Ki最大值 0.1
			VC_SLVC_PARAMETER.fFrRefFly = * pCsvParamSpeedEstFrRefFly;
			Vector_Control.fExciteTime = 0; //异步电机无速度编码器飞车起动时，不应有激励
			Vector_Control.fIqExc = 0.0;
	    }
		else
		{
			VC_SLVC_PARAMETER.fSptestKpFly = 0.0;//1.0;
			VC_SLVC_PARAMETER.fSptestKiminFly = 0.0; //
			VC_SLVC_PARAMETER.fSptestKimidFly = 0.0; //
			VC_SLVC_PARAMETER.fSptestKimaxFly = 0.0; //
			VC_SLVC_PARAMETER.fFrRefFly = 0.0;
	    }
	//电机反转时，注入的高频谐波相位取反，否则将发生先正转再反转的情况。
	   if(SysCtlReg.bit.MotorReverEn==1)
		VC_SLVC_PARAMETER.fFrRefFly=-1.0 * VC_SLVC_PARAMETER.fFrRefFly;
		 
/*		 Cur_clarke.sCw.all = 0x0002;
		 Vol_clarke.sCw.all = 0x0002;		*/
}

void pfnVccontrolclear(VCANDSLVCORPARA *v)
{
/*	     v->fTheta = 0.0;
	     Vector_Control.fThetaVector = 0.0;

		 SpeedKpKi.pfnReset(&SpeedKpKi);
	     SpeedControl.pfnReset(&SpeedControl);

	     ExcitingCurrent.pfnExcurreset(&ExcitingCurrent);	 
		 v->fIsdSet = 0.0;	 
		 v->fIsqSet = 0.0;
		 Vector_Control.fIdSet = 0.0;
		 Vector_Control.fIqSet = 0.0; 
	     SpeedTest.pfnInit(&SpeedTest);
		 Vector_Control.pfnVectorinit(&Vector_Control);
		 CurrentFilter_D.pfnResFilter1order(&CurrentFilter_D);
		 CurrentFilter_Q.pfnResFilter1order(&CurrentFilter_Q);
		 Parameter_Test.pfnParatestinit(&Parameter_Test);
		 v->fFrRef = v->fFrFbd;
*/
  v->fFrRef = v->fFrRef;
}

void fninterservice_vc(void)
{
	//float32 FreqPu_Ref=0.0;
	//float32 CutFreq=0.0;
	float32 FreqPu_RefTemp=0.0;
	if(uInterCount==0)
	{
		fnInitVCinput_inter();
	}
	uInterCount++;
	if(uInterCount>=100)  uInterCount=0;

	VC_SLVC_PARAMETER.fIu = AnalogInput.fADResult_Offseted[0];///((SysRatedParameter.fMotorRatedPower * 1000.0)/SysRatedParameter.fMotorRatedVoltage*SQRT2By3);            //变频器输出电流(U相标幺值)
	VC_SLVC_PARAMETER.fIv = AnalogInput.fADResult_Offseted[1];///((SysRatedParameter.fMotorRatedPower * 1000.0)/SysRatedParameter.fMotorRatedVoltage*SQRT2By3);            //变频器输出电流(V相标幺值)
	VC_SLVC_PARAMETER.fIw = AnalogInput.fADResult_Offseted[2];///((SysRatedParameter.fMotorRatedPower * 1000.0)/SysRatedParameter.fMotorRatedVoltage*SQRT2By3);           //变频器输出电流(W相标幺值)
/*	VC_SLVC_PARAMETER.fUu = VFDVoltLineToPhase.fVarA; //变频器输出电压(U相标幺值)
	VC_SLVC_PARAMETER.fUv = VFDVoltLineToPhase.fVarB; //变频器输出电压(V相标幺值)
	VC_SLVC_PARAMETER.fUw = VFDVoltLineToPhase.fVarC; //变频器输出电压(W相标幺值)
*/
	//采用直流侧电压与调制波计算A相电压（标幺值,输出电压实际值等于此相所有单元母线电压和乘以调制波）
//	VC_SLVC_PARAMETER.fUu = SysBusVoltCal.fSysBusVolt_A * VFVoltageBaseCal.fUu_AddMod/SysBaseValue.fVoltBaseValue;//变频器输出电压(U相标幺值)
	//采用直流侧电压与调制波计算B相电压（标幺值,输出电压实际值等于此相所有单元母线电压和乘以调制波）
//	VC_SLVC_PARAMETER.fUv = SysBusVoltCal.fSysBusVolt_B * VFVoltageBaseCal.fUv_AddMod/SysBaseValue.fVoltBaseValue;//变频器输出电压(V相标幺值)
    //采用直流侧电压与调制波计算C相电压（标幺值,输出电压实际值等于此相所有单元母线电压和乘以调制波）
//	VC_SLVC_PARAMETER.fUw = SysBusVoltCal.fSysBusVolt_C * VFVoltageBaseCal.fUw_AddMod/SysBaseValue.fVoltBaseValue;//变频器输出电压(W相标幺值)
	VC_SLVC_PARAMETER.fUu = 0.5*SysVoltBase.fUu_base*AnalogInput.fADResult[6]/SysBaseValue.fVoltBaseValue;//变频器输出电压(U相标幺值)
	VC_SLVC_PARAMETER.fUv = 0.5*SysVoltBase.fUv_base*AnalogInput.fADResult[6]/SysBaseValue.fVoltBaseValue;//变频器输出电压(V相标幺值)
	VC_SLVC_PARAMETER.fUw = 0.5*SysVoltBase.fUw_base*AnalogInput.fADResult[6]/SysBaseValue.fVoltBaseValue;//变频器输出电压(W相标幺值)

	if(uDirCount<4348)
	{
		uDirCount++;
	//	fnSysCtl_StopInv();//不能封锁整流
		VC_SLVC_PARAMETER.pfnVccontrolinit(&VC_SLVC_PARAMETER);
        uSoftStartCount=0;
	}
	uSoftStartCount++;
	if(uSoftStartCount>=VC_SLVC_PARAMETER.uSoftStart* 3)
	{

//		if(SysCtlParameter.uFref_SL == 0)
//		{
//			fnSysFreRefCal();
//		}
//		else
//		{
//			fnSysFreRefCal_S();
//		}
//		if((GridCtlParameter.uGridEn == 1)&&(SysCtlInstrReg.bit.IOGridInstr == 1))//并网允许且接收到并网请求指令
//		{
//			VC_SLVC_PARAMETER.fFrRef =  FreRefLimit.fFreRefLimitOut + SynGridconnect.fFrRef;
//		}
//		else
		    FreqPu_RefTemp =  FreqRef_ARMtoDSP;
			VC_SLVC_PARAMETER.fFrRef = FreqPu_RefTemp/SysRatedParameter.fMotorRatedFre;
//        FreqPu_Ref=fabs(VC_SLVC_PARAMETER.fFrRef);
//		if(FreqPu_Ref<=PhrCalCutFreqSet1)
//			CutFreq=PhrCalCutFreqVal1;
//		else if((FreqPu_Ref>PhrCalCutFreqSet1)&&(FreqPu_Ref<=PhrCalCutFreqSet2))
//			CutFreq=PhrCalCutFreqVal1+(PhrCalCutFreqVal2-PhrCalCutFreqVal1)/(PhrCalCutFreqSet2-PhrCalCutFreqSet1)* (FreqPu_Ref-PhrCalCutFreqSet1);
//		else if((FreqPu_Ref>PhrCalCutFreqSet2)&&(FreqPu_Ref<=PhrCalCutFreqSet3))
//			CutFreq=PhrCalCutFreqVal2+(PhrCalCutFreqVal3-PhrCalCutFreqVal2)/(PhrCalCutFreqSet3-PhrCalCutFreqSet2)* (FreqPu_Ref-PhrCalCutFreqSet2);
//        else
//			CutFreq=PhrCalCutFreqVal3;
//        VC_SLVC_PARAMETER.fCutFre_sw=CutFreq;
	}

	//VC_SLVC_PARAMETER.fFrFbd = RotorSpeed.fRotorFreqPU;    //实测转速反馈
	VC_SLVC_PARAMETER.pfnVccontrolcalc(&VC_SLVC_PARAMETER);

    if((SysCtlParameter.uStartMode == FLYMOD))
	{
	    if(SpeedTest.fFrRefstop==VC_SLVC_PARAMETER.fFrRefFly&&SpeedTest.fFrRefstop!=0)//+50Hz向下搜索时才进行方向判断
		{
			 if(uSoftStartCount < VC_SLVC_PARAMETER.uSoftStart* 4)//励磁完成后1s
			 {
		         // (当识别转速<3Hz,且持续时间大于1s时认为电机反转）
//		        if((uDirCountMax<4348)&&(
//		        	((SysCtlParameter.uMotorInverEn==FALSE)&&(SpeedTest.fSpd<0.06))
//					||((SysCtlParameter.uMotorInverEn==TRUE)&&(SpeedTest.fSpd>-0.06))))
//				{
//		        		uDirCountMax++;
//		        }
//		        else
//			 	{
//		         	if(uDirCountMax<4348)
//					 	uDirCountMax=0;
//			 	}
			 }
			 if(uDirCountMax>=4348)//判断转速反向时将计算值清零，将执行复位清零,1s后从-50Hz开始搜索
			 {
			 	uDirCount=0;
				SpeedTest.fFrRefstop=-1.0 * VC_SLVC_PARAMETER.fFrRefFly;
			 }
		}
	}
	else
	{
		uDirCount=4348;
		uDirCountMax=0.0;
	}

	if(uSoftStartCount > VC_SLVC_PARAMETER.uSoftStart* 4)
	    uSoftStartCount = VC_SLVC_PARAMETER.uSoftStart* 4;
}


void fnVectorCtrlInterface(void)
{
	fninterservice_vc();  //////矢量控制函数 
	                      //
	//======电压两相旋转坐标系到两相静止系转换=========// 
/*	Vol_ipark.fDs = VC_SLVC_PARAMETER.fUd;
	Vol_ipark.fQs = VC_SLVC_PARAMETER.fUq;
	Vol_ipark.fAngle = VC_SLVC_PARAMETER.fTheta;
	Vol_ipark.pfnIpcalc(&Vol_ipark);
	//======电压两相静止坐标系到三相静止坐标系转换==========// 
	Vol_iclarke.fAlpha = Vol_ipark.fAlpha;
	Vol_iclarke.fBeta = Vol_ipark.fBeta;
	Vol_iclarke.pfnIcalc(&Vol_iclarke);


	//三相调制波计算      

	SysVoltBase.fUu_base = Vol_iclarke.fAs;
	SysVoltBase.fUv_base = Vol_iclarke.fBs;
	SysVoltBase.fUw_base = Vol_iclarke.fCs;*/
}



