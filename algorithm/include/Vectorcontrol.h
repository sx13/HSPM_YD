/* =================================================================================
File name:       VECTORCONTROL.H                     
                    
Description: 
Header file containing constants, data type definitions, and 
function prototypes for the vector control.

=====================================================================================
 History:
-------------------------------------------------------------------------------------
2013.05.20   kegy  1.0                                                
------------------------------------------------------------------------------*/
#include "DSP2833x_Device.h"     // Headerfile Include File

#pragma CODE_SECTION(fnVector_calc, "ramfuncs")
//#pragma CODE_SECTION(fnVector_init, "ramfuncs") 

typedef struct {  Uint16   uCtrMethod;    //输入：有速度编码器和无速度编码器控制方法选择，0表示有速度编码器，1表示无速度编码器                  
                  Uint32   uSoftstart;    //输入：软启动时间设定
				  Uint16   uParatest;
                  Uint16   uReverse;
                  float32  fUdcVector;
				  float32  fFrRef;
				  float32  fFrAct;
				  float32  fFrTest;
				  float32  fIdAct;
				  float32  fIqAct;
				  float32  fFsRate;
				  float32  fIqExc;       //输入：转速估算时的转矩激励电流
				  float32  fIdRef;
				  
				  float32  fLr;          //输入：电机参数，电压，电流
				  float32  fLm;
				  float32  fNP;
				  float32  fUbVector;
				  float32  fUuIn;
				  float32  fUvIn;
				  float32  fIuIn;
				  float32  fIvIn;

				  Uint32   uStartCount;   //中间变量：软启动计算
				  Uint32   uExciteCount;
				  float32  fExciteTime;   //输入变量：转速估算激励时间
				  float32  fIdSet;
				  float32  fIqSet;
				  float32  fFsyn;
				  float32  fTetoIq;
				  Uint16   uFrCount;
				  float32  fFsSet;
 
                  float32  fUsd;          //输出：dq轴电压      
				  float32  fUsq;
				  float32  fThetaVector;  //输出：磁场定向角度

				  float32  fSptestKp;       //输入：转速估算环KP
                  float32  fSptestKimin;    //输入：转速估算环KI最小值
				  float32  fSptestKimid;    //输入：转速估算环KI中间值
				  float32  fSptestKimax;    //输入：转速估算环KI最大值

				  Uint32   uFlagFlystart;
				  float32  fFrRefFly;

				  float32  fSptestKpFly;       //输入：转速估算环KP(飞起时)
                  float32  fSptestKiminFly;    //输入：转速估算环KI最小值(飞起时)
				  float32  fSptestKimidFly;    //输入：转速估算环KI中间值(飞起时)
				  float32  fSptestKimaxFly;    //输入：转速估算环KI最大值(飞起时)

				  Uint16   uPhrCount;
				  float32  fPhrActFilter;
				  Uint16   uUq_startflag;

		 	 	  void  (*pfnVectorcalc)();
		 	 	  void  (*pfnVectorinit)();	 
				 } VECTORCONTROL;
				 	            
/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define VECTORCONTROL_DEFAULTS {  0,0,0,0,0,0,0,0,0,0,0,0,0,\
                                  0,0,0,0,0,0,0,0,\
                                  0,0,0,0,0,0,0,0,0,\
								  0,0,0,\
								  3.6,0.0002,0.2,0.2,\
								  0,1.0,\
								  36.0,0.0004,5.0,5.0,0,0.0,0,\
              			         (void (*)(Uint32))fnVector_calc,\
              			         (void (*)(Uint32))fnVector_init }  
/*------------------------------------------------------------------------------
Prototypes for the functions in PARK.C
------------------------------------------------------------------------------*/
void fnVector_calc(VECTORCONTROL *v);
void fnVector_init(VECTORCONTROL *v);

//extern VCANDSLVCORPARA VC_SLVC_PARAMETER;
extern float32 fFrAct;
extern Uint16 uInterCount;	
extern Uint32 uSoftStartCount;
extern VECTORCONTROL Vector_Control;


