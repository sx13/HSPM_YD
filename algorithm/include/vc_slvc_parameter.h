/* =================================================================================
File name:       vc_slvc_parameter.H                     
                    

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the VC , SLVC and parameter test.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
2013.05.17  kegy  
2014.7.25   Zh.J                                                
------------------------------------------------------------------------------*/

#ifndef vc_slvc_parameter_H 
#define vc_slvc_parameter_H 

typedef struct { /*======输入变量========*/
				  float32  fIu;          //输入：变频器输出三相电流及电压
				  float32  fIv; 
				  float32  fIw;  

				  float32  fUu; 
				  float32  fUv; 
				  float32  fUw; 

				  float32  fFrRef;       //输入：频率给定
				  float32  fFrFbd;       //输入：编码器实际速度反馈

                 /*======输入参数========*/
                  Uint16   uParaTest;    //输入：是否选择参数辨识，1参数辨识，0非参数辨识            
				  Uint16   uCtrMethod;   //输入：控制方法选择，1 SLVC控制，0 VC控制
				  Uint32   uSoftStart;   //输入：预励磁计数值设置

				  float32  fRs;          //输入：定子电阻
				  float32  fRr;          //输入：转子电阻
				  float32  fLls;         //输入：定子漏感
				  float32  fLlr;         //输入：转子漏感
				  float32  fLm;          //输入：互感
				  float32  fNP;          //输入：磁极对数
				  float32  fCos;         //输入：功率因数

				  float32  fUb;          //输入：电压基值
				  float32  fIb;          //输入：电流基值
				  float32  fUrate;       //输入：电压额定值
				  float32  fIrate;       //输入：电流额定值
				  float32  fSliprate;    //输入：转差额定值（标幺值）
				  float32  fPrate;       //输入：额定功率

				  float32  fUdc;         //输入：直流侧电压
				  float32  fTs;          //输入：PWM中断周期

				  float32  fIqExc;       //输入：转速估算时的转矩激励电流
				  float32  fTimeExc;     //输入：激励时间
				  float32  fIdRef;       //输入：初始励磁给定
				  

                  float32  fCurKp;       //输入：电流环KP
                  float32  fCurKi;       //输入：电流环KI
				  float32  fCurUp;       //输入：电流环输出上限
				  float32  fCurLw;       //输入：电流环输出下限
				        
				  float32  fSpdKpmax_VC;  //输入：VC转速环KP最大值
				  float32  fSpdKpmax_SLVC;//输入：SLVC转速环KP最大值
				  float32  fSpdKpmin_VC;  //输入：VC转速环KP最小值
				  float32  fSpdKpmin_SLVC;//输入：SLVC转速环KP最小值
                  float32  fSpdKi;        //输入：转速环KI
				  float32  fSpdUp;        //输入：转速环输出上限
				  float32  fSpdLw;        //输入：转速环输出下限

				  float32  fPhrRef;      //输入：转子磁链给定
				  float32  fPhrFrLow;    //输入：转子磁链闭环频率阀值，当给定频率大于此值时转子磁链闭环工作
				  float32  fPhrKp;       //输入：转子磁链环KP
                  float32  fPhrKi;       //输入：转子磁链环KI
				  float32  fPhrUp;       //输入：转子磁链环输出上限
				  float32  fPhrLw;       //输入：转子磁链环输出下限
		  
				  float32  fSptestKp;       //输入：转速估算环KP
                  float32  fSptestKimin;    //输入：转速估算环KI最小值
				  float32  fSptestKimid;    //输入：转速估算环KI中间值
				  float32  fSptestKimax;    //输入：转速估算环KI最大值
				  float32  fSptestFrmin;    //输入：转速估计环中间频率设定值
				  float32  fSptestUp;       //输入：转速估算环输出上限
				  float32  fSptestLw;       //输入：转速估算环输出下限
				      
				  
				  float32  fTestKp;        //输入：参数辨识电流环KP
                  float32  fTestKi;        //输入：参数辨识电流环KI
				  float32  fTestUp;        //输入：参数辨识电流环输出上限
				  float32  fTestLw;        //输入：参数辨识流环输出下限

				  float32  fCutFre_dc;     //参数：滤除直流分量的低通滤波截止频率
                  float32  fCutFre_sw;     //参数：电流模型和电压模型的切换频率

				  /*======中间变量========*/
				  Uint16   Evaluate_period;   //参数赋值执行周期
				  Uint16   uReverse;          //SLVC电机反转判断标识

				  /*======输出变量========*/
				  float32  fParaRs;          //输出变量：定子电阻（标幺值）
				  float32  fParaRr;          //输出变量：转子电阻（标幺值）
				  float32  fParaLls;         //输出变量：定子漏感（标幺值）
				  float32  fParaLlr;         //输出变量：转子漏感（标幺值)
				  float32  fParaLm;          //输出变量：互感（标幺值）
				  Uint16   uTestOver;        //输出变量：电机参数辨识结束标志
				  Uint16   uTestFault;       //输出变量：电机参数辨识故障阶段
				  Uint16   uTestStep;        //输出变量：电机参数辨识处于第几阶段

				  float32  fSpeedTest;       //输出变量：SLVC估计电机转速
				  float32  fIsqSet;          //输出变量：矢量控制转矩电流给定值
				  float32  fIsdSet;          //输出变量：矢量控制励磁电流给定值
				  float32  fIsqAct;          //输出变量：矢量控制转矩电流实际值
				  float32  fIsdAct;          //输出变量：矢量控制励磁电流实际值
                  float32  fPhrAct;          //输出变量：实际转子磁链
				  float32  fUd;              //输出变量：d轴电压
				  float32  fUq;              //输出变量：q轴电压
				  float32  fTheta;           //输出变量：矢量控制同步角度

				  Uint16   uFlyStart;
				  float32  fFrRefFly;

				  float32  fSptestKpFly;       //输入：转速估算环KP(飞起时)
                  float32  fSptestKiminFly;    //输入：转速估算环KI最小值(飞起时)
				  float32  fSptestKimidFly;    //输入：转速估算环KI中间值(飞起时)
				  float32  fSptestKimaxFly;    //输入：转速估算环KI最大值(飞起时)

				  Uint32   uFaultTest;

		 	 	  void  (*pfnVccontrolcalc)();
		 	 	  void  (*pfnVccontrolinit)();
		 	 	  void  (*pfnVccontrolclear)();	 
				 } VCANDSLVCORPARA;	            

/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define VCANDSLVCORPARA_DEFAULTS {0,0,0,\
                                  0,0,0,\
                                  0.02,0,\
								  0,0,4000,\
								  0.03907,0.03102,0.067303,0.067303,1.51177,0,0,\
								  0,0,380,0,0.0533,2200,\
								  0,0.000230,\
								  0.2,1.0,0.6,\
								  0.2,0.04,1.0,-1.0,\
								  3.0,2.0,2.0,2.0,0.1,1.0,-1.0,\
								  0.95,0.06,0.1,0.0001,0.3,-0.3,\
								  1.0,0.01,0.1,0.1,0.2,1000.0,-1000.0,\
								  0.01,0.0004,1.0,-1.0,\
								  0.03,15.0,\
								  0,0,\
								  0,0,0,0,0,0,0,0,\
								  0,0,0,0,0,0,0,0,0,\
								  0,1.0,\
								  36.0,0.0004,5.0,5.0,\
								  0,\
              			         (void (*)(Uint32))pfnVccontrolcalc,\
              			         (void (*)(Uint32))pfnVccontrolinit,\
              			         (void (*)(Uint32))pfnVccontrolclear }
/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void pfnVccontrolcalc(VCANDSLVCORPARA *v);
void pfnVccontrolinit(VCANDSLVCORPARA *v);
void pfnVccontrolclear(VCANDSLVCORPARA *v);

extern VCANDSLVCORPARA VC_SLVC_PARAMETER;

extern void fnInitVCinput_off(void);
extern void fnInitVCinput_inter(void);
extern void fnVectorCtrlInterface(void);
extern void fnInitInterg_Encode(void);

#endif






              			  


