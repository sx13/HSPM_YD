/* =================================================================================
File name:       CUR_VOL_MODEL.H                     
                    
Originator:	

Description: 电流电压组合模型结构体
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 07-09-2013	Version 1.0                                                
------------------------------------------------------------------------------*/
#ifndef CUR_VOL_MODEL_H
#define CUR_VOL_MODEL_H  
typedef struct {/*输入变量*/
				//1
				float32	fIu;       //输入变量：相电流和相电压
				float32	fIv;
				float32	fUu;
				float32	fUv;
				float32 fIdSet;
				float32 fIqSet;
				float32 fSetSpd;  // 输入变量：给定转速
				float32 fSlip;
			
				/*输入参数*/
				//2
				float32	fTs;       //输入参数：PWM中断时间
				float32	fLm;       //输入参数：互感
				float32	fLs;       //输入参数：定子漏感
				float32	fLr;       //输入参数：转子漏感
				float32	fRr;       //输入参数：转子电阻
				float32	fRs;       //输入参数：定子电阻

				float32  fKp;      //参数：转速识别比例系数
				float32  fKimin;   //参数：转速识别积分系数最小值
				float32  fKimid;   //参数：转速识别积分系数中间值
                float32  fKimax;   //参数：转速识别积分系数最大值
				float32  fmin;     //参数：转速识别最小值
				float32  fmax;     //参数：转速识别最大值
				
				float32  fCutFre_dc;//参数：滤除直流分量的低通滤波截止频率
                float32  fCutFre_sw;//参数：电流模型和电压模型的切换频率

				float32  fFrmin;   //参数：转速估计Ki中间值频率
				float32  fFrmid;
				float32  fFrmax;
				
				Uint16   uMethod;  //参数：矢量控制方法标志位		
				Uint16   uParatest;  //参数：参数辨识标志位	
				Uint16   uFlyStart;	
				Uint16   uFlyCount;
				float32  fFrRefstop;

				/*中间变量*/
				//3
				float32	fLs_sigm;  //中间变量：漏感系数ls_sigm = ls - lm * lm/lr
				float32	fTr;       //中间变量：转子时间常数
				float32	fTr_invt;  //中间变量：转子时间常数倒数
				float32	fTsTr_invt;
				float32	fTs_invt;
				float32 fLrDivLm;
				float32 fIdSet_former;

				float32	fIAlpha_former;
				float32	fErAlpha;
				float32	fErBeta;
				float32	fIBeta_former;
				float32	fPhr_Cur_former;
				float32	fPhr_Cur;
				float32	fPhr_Cur_Alpha;
				float32	fPhr_Cur_Beta;

				float32	fErAlpha_Disdc;
				float32	fErBeta_Disdc;
				float32	fPhr_Vol_Alpha;
				float32	fPhr_Vol_Beta;
				float32	fPhr_Alpha;
				float32	fPhr_Beta;
				float32	fPhr_D;
				float32	fPhr_Q;

				float32  fKiTemp;    //中间变量：Ki计算中间值

				/*输出变量*/
				//4
				float32	fAng;
				float32	fPhr;        //输出变量：转子磁链
				float32 fSpeedTest;  //输出变量：估算转速

				/*函数*/
				void     (*pfnInit)();		// 初始化函数指针
				void     (*pfnCalc)();		// 计算函数指针
				 
} SPDESTCURVOL;
#define SPDESTCURVOL_DEFAULTS  {0,0,0,0,0,0,0,0,\
								0.00025,1.51177,1.5788,1.5788,0.03102,0.03907,\
								1.0,0.0001,0.1,0.1,-1000.0,1000.0,\
								0.03,15.0,\
								0.2,0.3,0.4,\
								0,0,0,0,0.0,\
								0,0,0,0,0,0,0,\
								0,0,0,0,0,0,0,0,\
								0,0,0,0,0,0,0,0,\
								0,\
								0,0,0,\
								(void (*)(Uint32))fnSpdest_init,\
								(void (*)(Uint32))fnSpdest_calc}


void fnSpdest_init(SPDESTCURVOL *p);
void fnSpdest_calc(SPDESTCURVOL *p);

#endif










