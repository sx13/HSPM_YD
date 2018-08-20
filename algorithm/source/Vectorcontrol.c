/*=====================================================================================
 File name:        Vectorcontrol.C                   
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  VC SLVC               

=====================================================================================
 History:
-------------------------------------------------------------------------------------
2013.05.20  kegy  1.0
-------------------------------------------------------------------------------------*/
#include "SysCtl_AllHeaders.h"

float32 fnSpeedTest_Ki = 0;
float32 fnSpeedTest_Ki_temp1 = 0;
Uint32 CNT_FR_VALUE = 20;
extern VECTOR_ST SpeedTest;
extern INTERG Interg_Vector;
extern PIREG SpeedControl;
extern PIREG CurrentControl_M;
extern PIREG CurrentControl_T;
extern EXCITCURRENT ExcitingCurrent;
extern SLIP Slipspeed;
extern PI_REG SpeedTestPI;
extern SPDESTCURVOL SpeedTest_CurVol;
extern IPARK Vol_ipark;
extern ICLARKE Vol_iclarke;
//extern PARK_DQ Uabc_To_Udq_Asyn;
//extern Scurve FreRefCurveOut_S;
//extern ScurveTime FreRefTime_S;
extern PIREG PhrPI;
extern INTERG Interg_phsAlpha;
extern INTERG Interg_phsBeta; 

void fnVectorCtrlInterface(void);

#pragma CODE_SECTION(fnVector_calc, "ramfuncs")
#pragma CODE_SECTION(fnVector_st_Calc, "ramfuncs")

void fnVector_calc(VECTORCONTROL *v)
{     	 
	float32 fnSpeedTest_Ki_temp = 0;
     v->uStartCount++;     //软启动计数                                                                              
     if (v->uStartCount > 3 * v->uSoftstart)  
     { 
       v->uStartCount = 3 * v->uSoftstart;           
     }

/*===================电机软启动期间，速度环输出为0========================*/      
     if (v->uStartCount < 3 * v->uSoftstart)
	 {
	     v->fIqSet = 0.0; 
         SpeedControl.f2Intg = 0.0;
		 v->fFrRef = 0.0;
		 v->uPhrCount = 0;
	 }                          

/*=======================励磁电流计算=====================================*/ 
     if(v->uParatest == 1) ExcitingCurrent.fExccurSet = 1.0 / SpeedTest.fLm;//0.33;
	 else 
	 {
//	 	if((GridCtlParameter.uGridEn == 1)&&(SysCtlInstrReg.bit.IOGridInstr == 1))//并网允许且接收到并网请求指令
//	 	{
//	 		ExcitingCurrent.fExccurSet = v->fIdRef + SynGridconnect.fIdRef;
//	 	}
//		else
		{	
			ExcitingCurrent.fExccurSet = v->fIdRef;
		}
	 }

	 ExcitingCurrent.fFref = v->fFrRef;
	 v->uPhrCount ++;
	 v->fPhrActFilter = v->fPhrActFilter + SpeedTest.fPhr;
	 if((v->uPhrCount >= (Uint32)(1.5* CNT_FR_VALUE )) && (v->uStartCount >= 3 * v->uSoftstart))//30
	 {		 
		 ExcitingCurrent.fPhrAct = v->fPhrActFilter/(1.0*CNT_FR_VALUE);//* 0.05,SpeedTest_CurVol.fPhr
		 ExcitingCurrent.pfnExcurcalc(&ExcitingCurrent); 
		 v->uPhrCount = (Uint32)(0.5* CNT_FR_VALUE);
		 v->fPhrActFilter = 0.0;
	 }

/************给定频率小于磁链闭环阈值，励磁电流给定恢复到初始值*****/
//15.8.18 Zh.J 根据005V01修改,原程序中没有针对反向运行时磁链闭环修改，15.8.28 Zh.J添加
   if(v->fFrRef >= 0)
   {
	 if(v->fFrRef < ExcitingCurrent.fFrLow)
	 {
		 if(ExcitingCurrent.fExccurOut < v->fIdRef)
		 {
			 PhrPI.fOut = PhrPI.fOut + 0.0001;
			 if(PhrPI.fOut >= 0.0) 
			 {
				 PhrPI.pfnReset(&PhrPI);
			 }	
		 }	
		 else
		 {
			 PhrPI.fOut = PhrPI.fOut - 0.0001;
			 if(PhrPI.fOut <= 0.0) 
			 {
				 PhrPI.pfnReset(&PhrPI);
			 }	
		 } 
	 }
   }
   else //反向运行 15.8.28 Zh.J添加
   {
     if(v->fFrRef > -ExcitingCurrent.fFrLow)
	 {
		 if(ExcitingCurrent.fExccurOut < v->fIdRef)
		 {
			 PhrPI.fOut = PhrPI.fOut + 0.0001;
			 if(PhrPI.fOut >= 0.0) 
			 {
				 PhrPI.pfnReset(&PhrPI);
			 }	
		 }	
		 else
		 {
			 PhrPI.fOut = PhrPI.fOut - 0.0001;
			 if(PhrPI.fOut <= 0.0) 
			 {
				 PhrPI.pfnReset(&PhrPI);
			 }	
		 } 
	 }
   }

	 if(ExcitingCurrent.fExccurOut > 0.75) ExcitingCurrent.fExccurOut = 0.75;
	 else if(ExcitingCurrent.fExccurOut < 0.15) ExcitingCurrent.fExccurOut = 0.15;

/*=======================电机软启动时，励磁电流为斜坡给定=================*/ 
	 if (v->uStartCount < 2 * v->uSoftstart)               
	 {
         v->fIdSet = 0.5 * ExcitingCurrent.fExccurOut * v->uStartCount / v->uSoftstart;
	 }
	 else
	 {
	     v->fIdSet = ExcitingCurrent.fExccurOut;
	 }


/*=========================无速度编码器矢量控制===========================*/ 

/*===============================转速估计模块==============================*/
          if(v->uStartCount < 2 * v->uSoftstart) 
      	  {
          	  SpeedTest.fSetSpd = VC_SLVC_PARAMETER.fFrRefFly;//飞车启动
			  SpeedTest.fKp = v->fSptestKpFly;
			  SpeedTest.fKimin = v->fSptestKiminFly;
			  SpeedTest.fKimid = v->fSptestKimidFly;
			  SpeedTest.fKimax = v->fSptestKimaxFly;
			  fnSpeedTest_Ki = SpeedTest.fKiTemp;
			  fnSpeedTest_Ki_temp1 = fnSpeedTest_Ki;
		  }
		  else if(v->uStartCount >= 2 * v->uSoftstart && v->uStartCount < 3 * v->uSoftstart)
		  {
				  if(SysCtlParameter.uStartMode == FLYMOD)
				  {
					  if((SpeedTest.fSpd <= SpeedTest.fFrmin) && (SpeedTest.fSpd >= 0.0))
					  {
						  fnSpeedTest_Ki_temp = v->fSptestKimin + v->fSptestKimid * SpeedTest.fSpd / SpeedTest.fFrmin;
						  if(fnSpeedTest_Ki_temp <= v->fSptestKimin) fnSpeedTest_Ki_temp = v->fSptestKimin;
						  if(fnSpeedTest_Ki_temp >= v->fSptestKimid) fnSpeedTest_Ki_temp = v->fSptestKimid;
					  } 
					  else if(SpeedTest.fSpd > SpeedTest.fFrmin)
					  {
						  fnSpeedTest_Ki_temp = v->fSptestKimid + v->fSptestKimax * (SpeedTest.fSpd - SpeedTest.fFrmin);
						  if(fnSpeedTest_Ki_temp <= v->fSptestKimid) fnSpeedTest_Ki_temp = v->fSptestKimid;
						  if(fnSpeedTest_Ki_temp >= v->fSptestKimax) fnSpeedTest_Ki_temp = v->fSptestKimax;
					  }
					  if((SpeedTest.fSpd >= -SpeedTest.fFrmin) && (SpeedTest.fSpd < 0.0))
					  {
						  fnSpeedTest_Ki_temp = v->fSptestKimin - v->fSptestKimid * SpeedTest.fSpd / SpeedTest.fFrmin;
						  if(fnSpeedTest_Ki_temp <= v->fSptestKimin) fnSpeedTest_Ki_temp = v->fSptestKimin;
						  if(fnSpeedTest_Ki_temp >= v->fSptestKimid) fnSpeedTest_Ki_temp = v->fSptestKimid;
					  } 
					  else if(SpeedTest.fSpd < -SpeedTest.fFrmin)
					  {
						  fnSpeedTest_Ki_temp = v->fSptestKimid + v->fSptestKimax * (SpeedTest.fFrmin - SpeedTest.fSpd);
						  if(fnSpeedTest_Ki_temp <= v->fSptestKimid) fnSpeedTest_Ki_temp = v->fSptestKimid;
						  if(fnSpeedTest_Ki_temp >= v->fSptestKimax) fnSpeedTest_Ki_temp = v->fSptestKimax;
					  }

				  	  fnSpeedTest_Ki = fnSpeedTest_Ki - (fnSpeedTest_Ki_temp1 - fnSpeedTest_Ki_temp)/v->uSoftstart;
					  if(v->uStartCount == 3 * v->uSoftstart - 1)
					  {
							fnSpeedTest_Ki = fnSpeedTest_Ki_temp;
					  }
				  }
				else//非飞车起动方式时，fnSpeedTest_Ki置0
				{
						fnSpeedTest_Ki = 0;
				}

				  SpeedTest.fSetSpd = VC_SLVC_PARAMETER.fFrRefFly;//飞车启动
				  SpeedTest.fKp = v->fSptestKpFly;
				  SpeedTest.fKimin = fnSpeedTest_Ki;
				  SpeedTest.fKimid = fnSpeedTest_Ki;
				  SpeedTest.fKimax = fnSpeedTest_Ki;
		  }
		  else
		  {		
              SpeedTest.fSetSpd = SpeedTest.fSpd;//采用估计的转速对转速识别KP、Ki进行调节
		      SpeedTest.fKp = v->fSptestKp;
			  SpeedTest.fKimin = v->fSptestKimin;
			  SpeedTest.fKimid = v->fSptestKimid;
			  SpeedTest.fKimax = v->fSptestKimax;

			  FreqEn_DSPtoARM = 0xc3;
		  }
	      SpeedTest.fVola = v->fUuIn;
	      SpeedTest.fVolb = v->fUvIn;
		  SpeedTest.fCura = v->fIuIn;
		  SpeedTest.fCurb = v->fIvIn;
		  SpeedTest.fwr = v->fFsSet;

		 // SpeedTest.fFrRefstop = v->fFrRefFly;  //tianyf 6.26为了能够实现无感飞车，将此变量在接口函数内赋值

//		  if(VC_SLVC_PARAMETER.fFrRefFly != 0)//初始搜索频率非0Hz时，励磁阶段执行转速辨识函数
//		  {
//		    SpeedTest.pfnCalc(&SpeedTest);
//		  }

		  v->fFrTest = SpeedTest.fSpd;

/*============软启动时间过后，转速估计模块开始工作，开始加转矩激励===========*/
		  if(v->uStartCount >= 3 * v->uSoftstart) 
		  {   		         		  
			  Interg_phsAlpha.fKs = 1.0-2.0* PI* VC_SLVC_PARAMETER.fCutFre_sw * VC_SLVC_PARAMETER.fTs;            
          	  Interg_phsBeta.fKs = Interg_phsAlpha.fKs;
		//	  if(VC_SLVC_PARAMETER.fFrRefFly == 0)//搜索起始频率0Hz时励磁阶段不执行转速辨识函数，励磁结束后执行
	//		  {
			    SpeedTest.pfnCalc(&SpeedTest);
	//		  }
			  v->fThetaVector = SpeedTest.fAng;
              v->fFrTest = SpeedTest.fSpd;

//		      if(v->uFlagFlystart == 0)
//			  {
//				 	 v->fFrRef = v->fFrTest;
//				  	 FreRefCurveOut.fFreRefCurveOut = v->fFrTest * SysRatedParameter.fMotorRatedFre;
//				 	 FreRefLimit.fFreRefLimitOut = v->fFrTest;
//				  v->uFlagFlystart = 1;
//			  }//飞车启动

/*=============转矩激励时间内，速度环不工作，转矩电流给一常值================*/
			   v->uExciteCount ++;  //转矩激励计数
			   if(v->uExciteCount >= v->fExciteTime) 
			   {
			        v->uExciteCount = v->fExciteTime;
			   }

			   if(v->uExciteCount < v->fExciteTime)
			   {
			        if(v->uReverse == 0) v->fIqSet = v->fIqExc;
                    else if(v->uReverse == 1) v->fIqSet = -v->fIqExc;	   	      
			   } 	   
			   else
			   {	  
					v->uFrCount++;
					if (v->uFrCount >= CNT_FR_VALUE)//20)//
					{
					    v->uFrCount = 0;
				        SpeedControl.fRef1 = v->fFrRef;
				        SpeedControl.fFdb1 = v->fFrTest;			        
						SpeedControl.pfnCalc(&SpeedControl);
						v->fIqSet=SpeedControl.fOut;// * v->fTetoIq / v->fIdSet;
					//	v->fIqSet=0.15;		
					}
			   }			   
		   }

		   /*========================== 电机滑差=================================*/
		  Slipspeed.fIsmSet = v->fIdSet;
	      Slipspeed.fIstSet = v->fIqSet;
	      Slipspeed.pfnSetcalc(&Slipspeed);
	      v->fFsSet = Slipspeed.fSlipSet;


		  CurrentControl_M.fRef1 = v->fIdSet;
	      CurrentControl_M.fFdb1 = v->fIdAct;

		  CurrentControl_T.fRef1 = v->fIqSet;
	      CurrentControl_T.fFdb1 = v->fIqAct;
	 
	      CurrentControl_M.pfnCalc(&CurrentControl_M);
		  CurrentControl_T.pfnCalc(&CurrentControl_T);	

        
	 v->fUsd = CurrentControl_M.fOut;
     v->fUsq = CurrentControl_T.fOut;	          	  		      
}

void fnVector_init(VECTORCONTROL *v)
{  
     SpeedControl.pfnReset(&SpeedControl);
     v->fThetaVector = 0.0;

	 CurrentControl_M.pfnReset(&CurrentControl_M);

	 CurrentControl_T.pfnReset(&CurrentControl_T);
/*
	 Interg_Vector.fIn = 0.0;
	 Interg_Vector.fInformer = 0.0;
	 Interg_Vector.fOutformer = 0.0;
	 Interg_Vector.fOut = 0.0;
*/
	 Slipspeed.fSlipSet = 0.0;

	 SpeedTest.pfnInit(&SpeedTest);
	 v->uExciteCount = 0;
	 v->uStartCount = 0;
	 v->fTetoIq = v->fLr / (1.5 * v->fNP * v->fLm * v->fLm);
	 v->fFrTest = 0.0;
	 v->fUsd = 0.0;
	 v->fUsq = 0.0; 
	 v->uFlagFlystart = 0;   

     v->uPhrCount = (Uint32)(0.5* CNT_FR_VALUE);
	 v->fPhrActFilter = 0.0;
	 v->uUq_startflag = 0;	 	   
}



